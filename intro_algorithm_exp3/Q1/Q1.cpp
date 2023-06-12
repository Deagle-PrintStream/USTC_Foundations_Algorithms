#include <stdio.h>
#define INFTY ((int)(2147483647))
inline int read_int(void)
{
  int x = 0;
  int f = 1;
  char ch = getchar();
  while (ch == '\n' || ch == ' ')
    ch = getchar();
  if (ch == '-')
  {
    f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = x * 10 + ch - '0', ch = getchar();
  return x * f;
}

/*@brief find the shortest interval with sum >=k
@param n length of array a[]
@param k threshold for sum*/
int get_min_length_interval(int a[], int n, int k)
{
  int sum = 0;
  int i = 0, j = 0;
  int min_length = INFTY;
  while (j < n)
  {
    sum += a[j];
    while (sum >= k)
    {
      if (j - i + 1 < min_length)
      {
        min_length = j - i + 1;
      }
      sum -= a[i];
      i++;
    }
    j++;
  }
  if (min_length == INFTY)
    return 0;
  else
    return min_length;
}

int main()
{
  int n = 0;
  long long int K = 0;
  scanf("%d  %lld\n", &n, &K);
  /*read in input numbers*/
  int *array = new int[n];
  int *ptr = array;
  for (int i = 0; i < n; i++)
    *ptr++ = read_int();

  /*get minimum length of interval*/
  int min_length = get_min_length_interval(array, n, K);
  printf("%d\n", min_length);
  return 0;
}
