int
Length(Node *head)
{
  int count = 0;

  for (; head != NULL; head = head->next)
    ++count;

  return count;
}

int
Count(Node *head, int data)
{
  int count = 0;

  for (; head != NULL; head = head->next)
    count += head->data == data;

  return count;
}
