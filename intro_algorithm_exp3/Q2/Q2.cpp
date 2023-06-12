#include <stdio.h>

#define NONE (-1)
#define ROOT (0)

struct t_node
{
  bool covered=false;
  int child_count=0;
  int *child=nullptr;
  int parent=NONE;
};

inline int read_uint(void)
{
  int x=0;
  char ch=getchar();  
  if(ch=='\n' || ch==' ')
    ch=getchar();
  while(ch>='0' && ch<='9')
    x=x*10+ch-'0',ch=getchar();
  return x;
}

inline void BFS_tree(t_node *tree,int n,int *id_list){
  id_list[0]=ROOT;
  int id_list_len=1;
  for(int i=0;i<n;i++){
    int id=id_list[i];
    if(tree[id].child==nullptr)
      continue;
    int rank=tree[id].child_count;
    for (int j=0;j<rank;j++){
      id_list[id_list_len]=tree[id].child[j];
      id_list_len++;
    }
  }
}
inline int get_r_father_id(int id,int r,t_node *tree){
  int father_id=id;
  for(int i=0;i<r;i++){
    if(father_id!=ROOT){
      father_id=tree[father_id].parent;
    }else{
      return ROOT;
    }
  }
  return father_id;
}

void update_coverset(int id,t_node *tree,int r){
  if(r<0) return;
  tree[id].covered=true;
  if(id!=ROOT){
    update_coverset(tree[id].parent,tree,r-1); 
  }
  int rank=tree[id].child_count;
  for (int i=0;i<rank;i++){
    update_coverset(tree[id].child[i],tree,r-1);
  }
}

int main()
{
  int n=0;
  int r=0;
  int covset_size=0;
  scanf("%d  %d\n", &n,&r);

  if(n<=1 || r<=0){
    printf("%d",n);
    return 0;
  }

  t_node *tree=new t_node[n];

  int *id_list=new int[n];
  t_node *ptr=tree;
  ptr->parent=NONE;
  int node_counted=1;
  for (int i = 0; i < n; i++)
  {
    int new_child_count=read_uint();
    ptr->child_count=new_child_count;
    if(new_child_count!=0){
      ptr->child=new int[new_child_count];
      for(int j=0;j<new_child_count;j++){
        int new_child_id=read_uint()-1;
        ptr->child[j]=new_child_id;
        tree[new_child_id].parent=i;
      }
    }

    ptr++;
    node_counted+=new_child_count;
    if(node_counted>=n) break;
  }

  BFS_tree(tree,n,id_list);
  for(int i=n-1;i>=0;i--){
    int id=id_list[i];
    if(tree[id].covered==false){
      int r_father_id=get_r_father_id(id,r,tree);
      update_coverset(r_father_id,tree,r);
      covset_size++;
    }
  }

  printf("%d",covset_size);
  return 0;
}

