#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef int32_t i32;

typedef struct ArrayHeader ArrayHeader;
struct ArrayHeader
{
  size_t count;
  size_t capacity;
  size_t elem_size;
};

#define Array(T) T *
#define array_header(arr) (((ArrayHeader *)(arr)) - 1)
#define array_init(arr, capacity) arr = _array_init(capacity, sizeof(*arr))
#define array_deinit(arr) free(array_header(arr));
#define array_count(arr) array_header(arr)->count
#define array_push(arr, elem) arr = _array_push(arr, &elem)

void *
_array_init(size_t capacity, size_t elem_size)
{
  ArrayHeader *h = malloc(sizeof(ArrayHeader) + capacity * elem_size);
  h->count = 0;
  h->capacity = capacity;
  h->elem_size = elem_size;

  return h + 1;
}

void *
_array_push(void *array, const void *elem)
{
  ArrayHeader *h = array_header(array);

  if (h->count >= h->capacity)
    {
      h->capacity = 2 * h->capacity + 1;
      h = realloc(h, sizeof(ArrayHeader) + h->capacity * h->elem_size);
      array = h + 1;
    }

  memcpy((char *)array + h->count * h->elem_size, elem, h->elem_size);
  ++h->count;

  return array;
}

typedef struct HashNode HashNode;
struct HashNode
{
  const char *data;
  size_t count;
  size_t id;
  HashNode *next;
};

typedef struct HashTable HashTable;
struct HashTable
{
  HashNode **data;
  size_t count;
  size_t capacity;
};

void
hash_table_init(HashTable *t)
{
  t->count = 0;
  t->capacity = 32;
  t->data = malloc(t->capacity * sizeof(*t->data));

  for (size_t i = t->capacity; i-- > 0; )
    t->data[i] = NULL;
}

size_t
compute_hash(const char *data, size_t count)
{
  size_t hash = 5381;

  while (count-- > 0)
    hash = 33 * hash + data[count];

  return hash;
}

bool
are_strings_equal(const char *str0, size_t count0,
                  const char *str1, size_t count1)
{
  if (count0 != count1)
    return false;

  while (count0-- > 0)
    if (str0[count0] != str1[count0])
      return false;

  return true;
}

typedef struct HashResult HashResult;
struct HashResult
{
  size_t id;
  bool was_inserted;
};

HashResult
hash_insert(HashTable *t, size_t id, const char *data, size_t count)
{
  if (t->capacity == 0
      || (double)t->count / t->capacity > 0.75)
    {
      size_t new_capacity = 2 * t->capacity + 1;
      HashNode **new_table = malloc(new_capacity * sizeof(*new_table));

      for (size_t i = new_capacity; i-- > 0; )
        new_table[i] = NULL;

      for (size_t i = t->capacity; i-- > 0; )
        {
          HashNode *node = t->data[i];

          while (node != NULL)
            {
              size_t ind = compute_hash(node->data, node->count) % new_capacity;

              HashNode *const next = node->next;
              node->next = new_table[ind];
              new_table[ind] = node;
              node = next;
            }
        }

      free(t->data);
      t->capacity = new_capacity;
      t->data = new_table;
    }

  size_t ind = compute_hash(data, count) % t->capacity;
  HashNode *node = t->data[ind];

  while (node != NULL)
    {
      if (are_strings_equal(node->data, node->count, data, count))
        return (HashResult){ node->id, false };

      node = node->next;
    }

  node = malloc(sizeof(*node));
  node->data = data;
  node->count = count;
  node->id = id;
  node->next = t->data[ind];
  t->data[ind] = node;

  ++t->count;

  return (HashResult){ id, true };
}

enum AsmInstrType
  {
    Asm_Instr_Mov,
    Asm_Instr_Inc,
    Asm_Instr_Dec,
    Asm_Instr_Add,
    Asm_Instr_Sub,
    Asm_Instr_Mul,
    Asm_Instr_Div,
    Asm_Instr_Jmp,
    Asm_Instr_Cmp,
    Asm_Instr_Jne,
    Asm_Instr_Je,
    Asm_Instr_Jge,
    Asm_Instr_Jg,
    Asm_Instr_Jle,
    Asm_Instr_Jl,
    Asm_Instr_Call,
    Asm_Instr_Ret,
    Asm_Instr_Msg,
    Asm_Instr_End,
  };
typedef enum AsmInstrType AsmInstrType;

enum AsmInstrArgType
  {
    Asm_Instr_Arg_Integer = 0x1,
    Asm_Instr_Arg_Register = 0x2,
    Asm_Instr_Arg_Label = 0x4,
    Asm_Instr_Arg_String = 0x8,
  };
typedef enum AsmInstrArgType AsmInstrArgType;

typedef struct AsmInstrInfo AsmInstrInfo;
struct AsmInstrInfo
{
  AsmInstrType type;
  size_t offset;
};

typedef struct AsmInstrArg AsmInstrArg;
struct AsmInstrArg
{
  AsmInstrArgType type;
  i64 value;
};

typedef struct Asm Asm;
struct Asm
{
  Array(AsmInstrInfo) instrs;
  Array(AsmInstrArg) args;

  size_t last_unused_reg_id;
  size_t last_unused_label_id;

  HashTable regs;
  HashTable labels;
};

void
push_asm_instr(Asm *ass, AsmInstrType type)
{
  AsmInstrInfo info;
  info.type = type;
  info.offset = array_count(ass->args);

  array_push(ass->instrs, info);
}

void
push_asm_arg(Asm *ass, AsmInstrArg arg)
{
  array_push(ass->args, arg);
}

void
skip_spaces_and_comments(const char **prog)
{
  const char *at = *prog;

  while (*at != '\0')
    {
      while (isspace(*at))
        ++at;

      if (*at == ';')
        while (*at != '\n' && *at != '\0')
          ++at;
      else
        break;
    }

  *prog = at;
}

void
parse_asm_instr_arg(Asm *ass, u32 arg_types, const char **prog)
{
  skip_spaces_and_comments(prog);

  const char *at = *prog;
  AsmInstrArg arg;

  if (isdigit(*at))
    {
      assert((arg_types & Asm_Instr_Arg_Integer) && "integer is not expected for this command");

      arg.value = 0;
      do
        arg.value = 10 * arg.value + (*at++ - '0');
      while (isdigit(*at));

      arg.type = Asm_Instr_Arg_Integer;
      push_asm_arg(ass, arg);
    }
  else if (isalpha(*at))
    {
      size_t count = 0;
      while (isalnum(at[count]))
        ++count;

      if (arg_types & Asm_Instr_Arg_Register)
        {
          HashResult result = hash_insert(&ass->regs, ass->last_unused_reg_id, at, count);
          ass->last_unused_reg_id += result.was_inserted;

          arg.type = Asm_Instr_Arg_Register;
          arg.value = result.id;
        }
      else if (arg_types & Asm_Instr_Arg_Label)
        {
          HashResult result = hash_insert(&ass->labels, ass->last_unused_label_id, at, count);
          ass->last_unused_label_id += result.was_inserted;

          arg.type = Asm_Instr_Arg_Label;
          arg.value = result.id;
        }
      else
        assert(false && "identifier is not expected for this instruction");

      push_asm_arg(ass, arg);

      at += count;
    }
  else if (*at == '\'')
    {
      assert((arg_types & Asm_Instr_Arg_String) && "instruction doesn't accept string as argument");

      size_t count = 0;

      ++at;
      while (at[count] != '\'' && at[count] != '\0')
        ++count;

      assert(at[count] != '\0' && "no matching quote for a string");

      // TODO.

      push_asm_arg(ass, (AsmInstrArg){ Asm_Instr_Arg_String, -1 });
    }
  else
    assert(false && "invalid register");

  *prog = at;
}

Asm
parse_asm(const char *prog)
{
  Asm ass;
  array_init(ass.instrs, 32);
  array_init(ass.args, 32);

  ass.last_unused_reg_id = 0;
  ass.last_unused_label_id = 0;

  hash_table_init(&ass.regs);
  hash_table_init(&ass.labels);

  while (*prog != '\0')
    {
      skip_spaces_and_comments(&prog);

      if (*prog == '\0')
        break;

      static const struct
      {
        AsmInstrType type;
        const char *text;
        size_t count;
      } instrs[]
        = { { Asm_Instr_Mov, "mov", 3 },
            { Asm_Instr_Inc, "inc", 3 },
            { Asm_Instr_Dec, "dec", 3 },
            { Asm_Instr_Add, "add", 3 },
            { Asm_Instr_Sub, "sub", 3 },
            { Asm_Instr_Mul, "mul", 3 },
            { Asm_Instr_Div, "div", 3 },
            { Asm_Instr_Jmp, "jmp", 3 },
            { Asm_Instr_Cmp, "cmp", 3 },
            { Asm_Instr_Jne, "jne", 3 },
            { Asm_Instr_Je, "je", 2 },
            { Asm_Instr_Jge, "jge", 3 },
            { Asm_Instr_Jg, "jg", 2 },
            { Asm_Instr_Jle, "jle", 3 },
            { Asm_Instr_Jl, "jl", 2 },
            { Asm_Instr_Call, "call", 4 },
            { Asm_Instr_Ret, "ret", 3 },
            { Asm_Instr_Msg, "msg", 3 },
            { Asm_Instr_End, "end", 3 } };

      AsmInstrType type = -1;
      for (size_t i = 0; i < sizeof(instrs) / sizeof(*instrs); i++)
        {
          if (!strncmp(prog, instrs[i].text, instrs[i].count))
            {
              prog += instrs[i].count;
              type = instrs[i].type;
              break;
            }
        }

      // If it isn't a label, fail later on switch.
      if (type == -1 && isalpha(*prog))
        {
          parse_asm_instr_arg(&ass,
                              Asm_Instr_Arg_Label,
                              &prog);
          assert(*prog == ':');
          ++prog;

          continue;
        }

      push_asm_instr(&ass, type);

      switch (type)
        {
        case Asm_Instr_Mov:
        case Asm_Instr_Add:
        case Asm_Instr_Sub:
        case Asm_Instr_Mul:
        case Asm_Instr_Div:
        case Asm_Instr_Cmp:
          parse_asm_instr_arg(&ass,
                              Asm_Instr_Arg_Integer | Asm_Instr_Arg_Register,
                              &prog);
          skip_spaces_and_comments(&prog);
          assert(*prog == ',');
          ++prog;
          parse_asm_instr_arg(&ass,
                              Asm_Instr_Arg_Integer | Asm_Instr_Arg_Register,
                              &prog);
          break;
        case Asm_Instr_Inc:
          parse_asm_instr_arg(&ass,
                              Asm_Instr_Arg_Register,
                              &prog);
          break;
        case Asm_Instr_Jmp:
        case Asm_Instr_Jne:
        case Asm_Instr_Je:
        case Asm_Instr_Jge:
        case Asm_Instr_Jg:
        case Asm_Instr_Jle:
        case Asm_Instr_Jl:
        case Asm_Instr_Call:
          parse_asm_instr_arg(&ass,
                              Asm_Instr_Arg_Label,
                              &prog);
          break;
        case Asm_Instr_Ret:
          break;
        case Asm_Instr_Msg:
          {
            // TODO.
            assert(false);
          }

          break;
        case Asm_Instr_End:
          break;
        default:
          assert(false && "invalid instruction");
        }
    }

  return ass;
}

int
main(void)
{
  Asm ass = parse_asm("mov a, 2\n"
                      "mov a, 4\n"
                      "mov b, 5\n"
                      "label:\n"
                      "label:\n"
                      "inc c\n");
}
