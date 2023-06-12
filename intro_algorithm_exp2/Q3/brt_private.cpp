#include "brt.h"
/*brt_private.cpp--------------------------------------------------------*/
int BlackRedTree::compare(t_node *a, t_node *b) const
{
  t_score score_diff = a->score - b->score;
  return (score_diff == 0) ? (a->id - b->id) : ((score_diff > 0) ? (1) : (-1));
}

void BlackRedTree::left_rotate(t_node *p)
{
  if (p == nil)
    return;
  t_node *r = p->right;
  p->right = r->left;
  if (r->left != nil)
  {
    r->left->parent = p;
  }
  r->parent = p->parent;
  if (p->parent == nil)
  {
    root = r;
  }
  else if (p == p->parent->left)
  {
    p->parent->left = r;
  }
  else
  {
    p->parent->right = r;
  }
  r->left = p;
  r->siz = p->siz;
  p->parent = r;
  p->siz = p->left->siz + p->right->siz + 1;
}

void BlackRedTree::right_rotate(t_node *p)
{
  if (p == nil)
    return;
  t_node *l = p->left;
  p->left = l->right;
  if (l->right != nil)
  {
    l->right->parent = p;
  }
  l->parent = p->parent;
  if (p->parent == nil)
  {
    root = l;
  }
  else if (p == p->parent->left)
  {
    p->parent->left = l;
  }
  else
  {
    p->parent->right = l;
  }
  l->right = p;
  l->siz = p->siz;
  p->parent = l;
  p->siz = p->left->siz + p->right->siz + 1;
}
void BlackRedTree::insert_misc(t_node *new_node)
{
  t_node *y;
  while (new_node->parent->color == red)
  {
    if (new_node->parent == new_node->parent->parent->left)
    {
      y = new_node->parent->parent->right;
      if (y->color == red)
      {
        new_node->parent->color = black;
        y->color = black;
        new_node->parent->parent->color = red;
        new_node = new_node->parent->parent;
      }
      else
      {
        if (new_node == new_node->parent->right)
        {
          new_node = new_node->parent;
          left_rotate(new_node);
        }
        new_node->parent->color = black;
        new_node->parent->parent->color = red;
        right_rotate(new_node->parent->parent);
      }
    }
    else
    {
      y = new_node->parent->parent->left;
      if (y->color == red)
      {
        new_node->parent->color = black;
        y->color = black;
        new_node->parent->parent->color = red;
        new_node = new_node->parent->parent;
      }
      else
      {
        if (new_node == new_node->parent->left)
        {
          new_node = new_node->parent;
          right_rotate(new_node);
        }
        new_node->parent->color = black;
        new_node->parent->parent->color = red;
        left_rotate(new_node->parent->parent);
      }
    }
  }
  root->color = black;
}

t_node *BlackRedTree::find(t_id id, t_score score) const
{
  t_node *x = root;
  while (x != nil)
  {
    if (score < x->score)
    {
      x = x->left;
    }
    else if (score > x->score)
    {
      x = x->right;
    }
    else
    {
      if (id < x->id)
      {
        x = x->left;
      }
      else if (id > x->id)
      {
        x = x->right;
      }
      else
      {
        return x;
      }
    }
  }
  return nil;
}

long int BlackRedTree::find_kth(t_node *z, long int k) const
{
  if (z == nil)
    return -1;
  if (k <= z->right->siz)
  {
    return find_kth(z->right, k);
  }
  else if (k == z->right->siz + 1)
  {
    return z->id;
  }
  else
  {
    return find_kth(z->left, k - z->right->siz - 1);
  }
}

t_node *BlackRedTree::minimum(t_node *x) const
{
  while (x->left != nil)
  {
    x = x->left;
  }
  return x;
}
void BlackRedTree::transplant(t_node *u, t_node *v)
{
  if (u->parent == nil)
  {
    root = v;
  }
  else if (u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  v->parent = u->parent;
}
void BlackRedTree::delete_misc(t_node *x)
{
  t_node *w;
  while (x != root && x->color == black)
  {
    if (x == x->parent->left)
    {
      w = x->parent->right;
      if (w->color == red)
      {
        w->color = black;
        x->parent->color = red;
        left_rotate(x->parent);
        w = x->parent->right;
      }
      if (w->left->color == black && w->right->color == black)
      {
        w->color = red;
        x = x->parent;
      }
      else
      {
        if (w->right->color == black)
        {
          w->left->color = black;
          w->color = red;
          right_rotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = black;
        w->right->color = black;
        left_rotate(x->parent);
        x = root;
      }
    }
    else
    {
      w = x->parent->left;
      if (w->color == red)
      {
        w->color = black;
        x->parent->color = red;
        right_rotate(x->parent);
        w = x->parent->left;
      }
      if (w->right->color == black && w->left->color == black)
      {
        w->color = red;
        x = x->parent;
      }
      else
      {
        if (w->left->color == black)
        {
          w->right->color = black;
          w->color = red;
          left_rotate(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = black;
        w->left->color = black;
        right_rotate(x->parent);
        x = root;
      }
    }
  }
  x->color = black;
}

t_node *BlackRedTree::find_pre(t_score score) const
{
  t_node *x = root;
  t_node *pre = nil;
  while (x != nil)
  {
    if (x->score <= score)
    {
      pre = x;
      x = x->right;
    }
    else
    {
      x = x->left;
    }
  }
  return pre;
}

t_node *BlackRedTree::find_next(t_score score) const
{
  t_node *x = root;
  t_node *nxt = nil;
  while (x != nil)
  {
    if (x->score >= score)
    {
      nxt = x;
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  return nxt;
}

long int BlackRedTree::get_rank(t_node *z, t_score score) const
{
  if (z == nil)
    return 0;
  if(score >= z->score){
    return z->left->siz + 1 + get_rank(z->right, score);
  }else{
    return get_rank(z->left, score);
  }

}
