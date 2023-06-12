#include <iostream>
#include <string.h>
#include <stdio.h>

#define NAME_MAX (11)

struct employee
{
  int order;
  char name[NAME_MAX];
  int score_all;
  int score_one;
};

/*if A < B , then return a positve number*/
inline int compare(employee *A,employee *B){
  int is_prior=0;
  is_prior=(B->score_all - A->score_all);
  if (is_prior==0){
    is_prior=(B->score_one - A->score_one);
  }
  if (is_prior==0){    
    is_prior=(strcmp(A->name,B->name));
  }
  if(is_prior==0){
    is_prior=(A->order - B->order);
  }
  return is_prior;
}

void quick_sort(employee **list_ptr,int l,int r){
  if (l>=r){
    return;
  }
  int i,j;
  employee *pivot;
  i = l;
  j = r;
  pivot=list_ptr[(r+l)/2];  /*can be picked randomly*/
  while(i<j){
    while(compare(list_ptr[j],pivot)>0){
      j--;
    }
    while(compare(pivot,list_ptr[i])>0){
      i++;
    }
    if(i<=j){
      std::swap(list_ptr[i],list_ptr[j]);
      i++;
      j--;
    }
  }
  quick_sort(list_ptr,l,j);
  quick_sort(list_ptr,i,r);  
}

inline void sort(employee **list_ptr,int len){
  quick_sort(list_ptr,0,len-1);
}

int main(){
  int list_len=0;
  scanf("%d",&list_len);
  employee *employee_list=new employee[list_len];
  employee *employee_list_ptr[list_len];

  for(int i=0;i<list_len;i++){
    employee new_employee;
    scanf("%d %s %d %d",&new_employee.order,new_employee.name,\
    &new_employee.score_one,&new_employee.score_all);
    new_employee.score_all+=new_employee.score_one;

    employee_list[i]=new_employee;
    employee_list_ptr[i]=&employee_list[i];
  }
  sort(employee_list_ptr,list_len);

  for (int i=0;i<list_len;i++){
    printf("%06d\n",employee_list_ptr[i]->order);
  }

  return 0;
}
