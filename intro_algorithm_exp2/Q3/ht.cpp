#include "brt.h"
/*ht.cpp--------------------------------------------------------*/

hash_table::hash_table(const int new_size) : size(new_size)
{
  table = new ht_node *[size];
  for (int i = 0; i < size; i++)
  {
    table[i] = nullptr;
  }
}

hash_table::~hash_table()
{
  for (int i = 0; i < size; i++)
  {
    delete table[i];
  }
}

inline int hash_table::hash(t_id id) const
{
  static const int prime = 1331;
  return (id % (size - prime) + prime) % size;
}

bool hash_table::insert(t_node *brt_node)
{
  int index = hash(brt_node->id);
  ht_node *p = table[index];
  if (p == nullptr)
  {
    table[index] = new ht_node;
    table[index]->brt_node = brt_node;
    table[index]->next = nullptr;
    return true;
  }
  while (p->next != nullptr)
  {
    p = p->next;
  }
  p->next = new ht_node;
  p = p->next;
  p->brt_node = brt_node;
  p->next = nullptr;
  return true;
}

t_score hash_table::search(t_id id) const
{
  int index = hash(id);
  ht_node *p = table[index];
  while (p != nullptr)
  {
    if (p->brt_node->id == id)
    {
      return p->brt_node->score;
    }
    else
    {
      p = p->next;
    }
  }
  return NOT_FOUND;
}

bool hash_table::delete_node(t_node *brt_node)
{
  int index = hash(brt_node->id);
  ht_node *p = table[index];
  ht_node *pre = p;
  if (p == nullptr)
    return false;
  if (p->brt_node == brt_node)
  {
    table[index] = p->next;
    delete p;
    return true;
  }
  p = p->next;
  while (p != nullptr)
  {
    if (p->brt_node == brt_node)
    {
      pre->next = p->next;
      delete p;
      return true;
    }
    else
    {
      pre = p;
      p = p->next;
    }
  }
  return false;
}
