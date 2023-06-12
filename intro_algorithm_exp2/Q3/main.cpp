#include <stdio.h>
#include "brt.h"
/*main.cpp--------------------------------------------------------*/
inline long int read_long_int()
{
  long int x = 0;
  char ch = getchar();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + ch - '0', ch = getchar();
  return x;
}

inline long int read_signed_long_int()
{
  long int x = 0;
  int f=1;
  char ch = getchar();
  if(ch=='-'){
    f=-1;
    ch=getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = x * 10 + ch - '0', ch = getchar();
  return x*f;
}

void write_long_int(long int x)
{
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write_long_int(x / 10);
  putchar(x % 10 + '0');
}

/*input instruction handler*/
inline void instruction_handler(BlackRedTree &brt)
{
  static char new_op = '\0';
  static t_id new_id = 0;
  static t_score new_score = 0;
  static long int k = 0;
  static long int l, r;

  new_op = getchar();
  switch (new_op)
  {
  case 'I': // insert new t_node with id and score
    new_id = read_long_int();
    new_score = read_long_int();
    brt.insert(new_id, new_score);
    break;
  case 'D': // delete the t_node with target id and score
    new_id = read_long_int();
    new_score = read_long_int();
    brt.delete_node(new_id, new_score);
    break;
  case 'L': // lookup if new_id is in the tree and return its score
    new_id = read_long_int();
    write_long_int(brt.lookup(new_id));
    putchar('\n');
    break;
  case 'S': // select the t_node with k-th largest score and return its id
    k = read_long_int();
    write_long_int(brt.select(k));
    putchar('\n');
    break;
  case 'M': // return the t_node id with its score in range of [k,+inf)
    k = read_long_int();
    write_long_int(brt.minimum_id(k));
    putchar('\n');
    break;
  case 'C': // count the t_nodes with score in range of [l,r]
    l = read_signed_long_int();
    r = read_signed_long_int();
    write_long_int(brt.count(l, r));
    putchar('\n');
    break;
  case 'P': // print out the whole tree for debug process
    brt.print_tree();
    break;
  default:
    break;
  }
}

int main()
{
  long int n = 0; // size
  scanf("%ld\n", &n);
  BlackRedTree brt;
  for (int i = 0; i < n; i++)
  {
    instruction_handler(brt);
  }
  return 0;
}

