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
    Asm_Instr_Label,
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

typedef struct Asm Asm;
struct Asm
{
  i64 *instrs;
  size_t count;
  size_t capacity;

  size_t last_unused_reg_id;
  size_t last_unused_label_id;

  HashTable regs;
  HashTable labels;
};

void
push_asm_instr(Asm *ass, i64 value)
{
  if (ass->count >= ass->capacity)
    {
      ass->capacity = 2 * ass->capacity + 1;
      ass->instrs = realloc(ass->instrs, ass->capacity * sizeof(*ass->instrs));
    }

  ass->instrs[ass->count++] = value;
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

enum AsmInstrArgType
  {
    Asm_Instr_Arg_Integer = 0x1,
    Asm_Instr_Arg_Register = 0x2,
    Asm_Instr_Arg_Label = 0x4,
    Asm_Instr_Arg_String = 0x8,
  };
typedef enum AsmInstrArgType AsmInstrArgType;

void
parse_asm_instr_arg(Asm *ass, u32 arg_types, const char **prog)
{
  skip_spaces_and_comments(prog);

  const char *at = *prog;

  if (isdigit(*at))
    {
      assert((arg_types & Asm_Instr_Arg_Integer) && "integer is not expected for this command");

      i64 value = 0;
      do
        value = 10 * value + (*at++ - '0');
      while (isdigit(*at));

      push_asm_instr(ass, Asm_Instr_Arg_Integer);
      push_asm_instr(ass, value);
    }
  else if (isalpha(*at))
    {
      size_t count = 0;
      while (isalnum(at[count]))
        ++count;

      HashResult result;

      if (arg_types & Asm_Instr_Arg_Register)
        {
          result = hash_insert(&ass->regs, ass->last_unused_reg_id, at, count);
          ass->last_unused_reg_id += result.was_inserted;

          push_asm_instr(ass, Asm_Instr_Arg_Register);
        }
      else if (arg_types & Asm_Instr_Arg_Label)
        {
          result = hash_insert(&ass->labels, ass->last_unused_label_id, at, count);
          ass->last_unused_label_id += result.was_inserted;

          push_asm_instr(ass, Asm_Instr_Arg_Label);
        }
      else
        assert(false && "identifier is not expected for this instruction");

      push_asm_instr(ass, result.id);

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

      push_asm_instr(ass, Asm_Instr_Arg_String);
      push_asm_instr(ass, -1);
    }
  else
    assert(false && "invalid register");

  *prog = at;
}

Asm
parse_asm(const char *prog)
{
  Asm ass;
  ass.count = 0;
  ass.capacity = 32;
  ass.instrs = malloc(ass.capacity * sizeof(*ass.instrs));

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
            { Asm_Instr_Label, "label", 5 },
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
        case Asm_Instr_Label:
          parse_asm_instr_arg(&ass,
                              Asm_Instr_Arg_Label,
                              &prog);
          assert(*prog == ':');
          ++prog;
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
            // Get the location of the number of arguments of "msg"
            // instruction to modify it after the number of arguments
            // is known.
            size_t arg_count_loc = ass.count;
            size_t arg_count = 0;

            push_asm_instr(&ass, 0);

            for (bool first_iteration = true; ; first_iteration = false)
              {
                skip_spaces_and_comments(&prog);

                if (!first_iteration)
                  {
                    assert(*prog == ',');
                    ++prog;
                  }

                parse_asm_instr_arg(&ass,
                                    Asm_Instr_Arg_Register | Asm_Instr_Arg_String,
                                    &prog);
                ++arg_count;
              }

            ass.instrs[arg_count_loc] = arg_count;
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
  parse_asm("mov a, 2\n"
            "inc a\n");
}
