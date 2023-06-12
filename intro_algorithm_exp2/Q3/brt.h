/*brt.h--------------------------------------------------------*/

#ifndef __BRT_H
#define __BRT_H

#define NOT_FOUND (0)
#define SELECT_ERROR (-1)
#define MINIMUM_ERROR (-1)
#define HASH_TABLE_SIZE (1e5)

/*public typedef*/
typedef long int t_id;
typedef long int t_score;
enum Color
{
  black,
  red
};

struct t_node
{
  t_id id;
  t_score score;
  int siz;
  t_node *left;
  t_node *right;
  t_node *parent;
  Color color;
};

struct ht_node
{
  t_node *brt_node;
  ht_node *next;
};

class hash_table
{
private:
  const int size;
  ht_node **table;
  int hash(t_id id) const;
public:
  hash_table(const int new_size = HASH_TABLE_SIZE);
  ~hash_table();

  bool insert(t_node *brt_node);
  t_score search(t_id id) const;
  bool delete_node(t_node *brt_node);
};

/*class defines*/
class BlackRedTree
{
private:
  t_node *nil;
  t_node *root;
  hash_table ht;

  int compare(t_node *a, t_node *b) const;
  void left_rotate(t_node *p);
  void right_rotate(t_node *p);
  void insert_misc(t_node *new_t_node);
  /*find the minimum child node of target node*/
  t_node *minimum(t_node *x) const;
  void transplant(t_node *u, t_node *v);
  void delete_misc(t_node *x);
  t_node *find(t_id id, t_score score) const;
  /*find the k-th largest node*/
  long int find_kth(t_node *x, long int k) const;
  /*find the previous t_node with smaller score to the target score*/
  t_node *find_pre(t_score score) const;
  /*find the next t_node with larger score to the target score*/
  t_node *find_next(t_score score) const;
  /*count how many elements is smaller that target score*/
  long int get_rank(t_node *x, t_score score) const;
  /*root is private member so need to packaged up*/
  void print_tree(t_node *p) const;

public:
  BlackRedTree();
  ~BlackRedTree();
  void insert(t_id id, t_score score);
  void delete_node(t_id id, t_score score);
  /*return the score of target ID, return 0 if not found*/
  t_score lookup(t_id id) const;
  /*return ID with k-th largest score, return -1 if k > size*/
  t_id select(long int k) const;
  /*return the ID with score in range [k,+inf),
  return the minimum ID if they have same least score,
  return -1 if not found*/
  t_id minimum_id(t_score lowerBound) const;
  /*count how many ID with score in range [l,r]*/
  long int count(t_score l, t_score r) const;
  /*for debug, print out the tree in pre-order, '-' for nil*/
  void print_tree(void) const;
};

#endif
