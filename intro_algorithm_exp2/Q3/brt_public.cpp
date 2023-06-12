#include "brt.h"
#include <stdio.h>
/*brt_public.cpp--------------------------------------------------------*/

BlackRedTree::BlackRedTree()
{
	nil = new t_node{0, 0, 0, nullptr, nullptr, nullptr, black};
	nil->left = nil->right = nil->parent = nil;
	root = nil;
	hash_table ht(HASH_TABLE_SIZE);
}

BlackRedTree::~BlackRedTree()
{
	ht.~hash_table();
}

void BlackRedTree::insert(t_id id, t_score score)
{
	if (ht.search(id) == score)
		return;

	t_node *new_node = new t_node{id, score, 1, nil, nil, nil, red};
	t_node *y = nil;
	t_node *x = root;
	while (x != nil)
	{
		y = x;
		y->siz += 1;
		/*records with same score, the one with smaller id is prior*/
		if (compare(new_node, y) < 0)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	new_node->parent = y;
	if (y == nil)
	{
		root = new_node;
	}
	else if (compare(new_node, y) < 0)
	{
		y->left = new_node;
	}
	else
	{
		y->right = new_node;
	}
	insert_misc(new_node);

	ht.insert(new_node);
}

void BlackRedTree::delete_node(t_id id, t_score score)
{
	t_node *target = find(id, score);
	
	if (target==nil)
	{
		return;
	}
	t_node *y = target;
	t_node *x;
	t_node *f;
	Color yc = y->color;
	if (target->left == nil)
	{
		f = x = target->right;
		transplant(target, x);
	}
	else if (target->right == nil)
	{
		f = x = target->left;
		transplant(target, x);
	}
	else
	{
		y = minimum(target->right);
		yc = y->color;
		f = y->parent;
		x = y->right;
		if (y->parent == target)
		{
			x->parent = y;
		}
		else
		{
			transplant(y, x);
			y->right = target->right;
			y->right->parent = y;
		}
		transplant(target, y);
		y->left = target->left;
		y->left->parent = y;
		y->color = target->color;
	}
	nil->siz = 0;
	if (f == nil)
	{
		f = target->parent;
	}
	while (f != nil)
	{
		f->siz = f->left->siz + f->right->siz + 1;
		f = f->parent;
	}
	if (yc == black)
	{
		delete_misc(x);
	}

	ht.delete_node(target);
}

t_score BlackRedTree::lookup(t_id id) const
{
	return ht.search(id);
}

t_id BlackRedTree::select(long int k) const
{
	if (k > root->siz)
	{
		return SELECT_ERROR;
	}
	else
	{
		return find_kth(root, k);
	}
}

t_id BlackRedTree::minimum_id(t_score lowerBound) const
{
	t_node *p = find_next(lowerBound);
	if (p->score < lowerBound)
	{
		return MINIMUM_ERROR;
	}
	else
	{
		return p->id;
	}
}

long int BlackRedTree::count(t_score l, t_score r) const
{
	if (l > r)
		return 0;
	t_node *p_left=root;
	t_node *p_right=root;
	long int left_rank=get_rank(p_left,l-1);
	long int right_rank=get_rank(p_right,r);
	return right_rank-left_rank;

}

void BlackRedTree::print_tree(t_node *p) const
{
	if (p == nil)
	{
		printf("-\n");
		return;
	}
	printf("%ld : %ld\n", p->id, p->score);
	print_tree(p->left);
	print_tree(p->right);
}

void BlackRedTree::print_tree(void) const
{
	print_tree(root);
}
