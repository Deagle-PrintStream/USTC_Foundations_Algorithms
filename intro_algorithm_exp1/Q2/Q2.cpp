#include <stdio.h>
#include <iostream>
#include <string.h>

#define NAME_MAX (11)

struct employee
{
  int order;
  char name[NAME_MAX];
  int score;
};

inline int compare(employee *A,employee *B){
  int is_prior=0;
  is_prior=(strcmp(A->name,B->name));
  if(is_prior==0){
    is_prior=(A->order - B->order);
  }
  return is_prior;
}

int getMax(employee *arr[], int n)
{
    int max = arr[0]->score;
    for (int i = 1; i < n; i++)
        if (arr[i]->score > max)
            max = arr[i]->score;
    return max;
}

void radix_sort(employee *arr[], int n, int exp)
{
    employee *output[n]; 
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(arr[i]->score / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i]->score / exp) % 10] - 1] = arr[i];
        count[(arr[i]->score / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void sort_by_score(employee *arr[], int n)
{
    const int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        radix_sort(arr, n, exp);
}

void sort_by_name(employee *arr[],int n){
  int begin=0;
  int end=0;
  while(end<n){
    while(end<n && arr[begin]->score==arr[end]->score){
      end++;
    }
    for (int i=begin;i<end;i++){
      for(int j=i+1;j<end;j++){
        if(compare(arr[i],arr[j])<0){
          std::swap(arr[i],arr[j]);
        }
      }
    }
    begin=end;
  }
}

int main(){
  int list_len=0;
  scanf("%d",&list_len);
  employee *employee_list=new employee[list_len];
  employee *employee_list_ptr[list_len];
  int new_score_all=0;
  int new_score_one=0;

  for(int i=0;i<list_len;i++){
    employee new_employee;
    scanf("%d %s %d %d",&new_employee.order,new_employee.name,\
    &new_score_one,&new_score_all);
    new_score_all+=new_score_one;
    new_employee.score=new_score_all*100+new_score_one;

    employee_list[i]=new_employee;
    employee_list_ptr[i]=&employee_list[i];
  }
  sort_by_score(employee_list_ptr,list_len);
  sort_by_name(employee_list_ptr,list_len);

  for (int i=list_len-1;i>=0;i--){
    printf("%06d\n",employee_list_ptr[i]->order);
  }

  return 0;
}
