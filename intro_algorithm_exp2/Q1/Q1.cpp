#include <stdio.h>
#include <math.h> //for std::sqrt
#include <iostream> //for std::min

#define INFTY (1e6)          /*the maximum distance in the problem set*/
#define ZERO (1e-10)         /*if two points' position are the same*/
#define MAX_POINT_PANEL (11) /*maximum count of points in the target panel*/

struct t_point
{
  double x;
  double y;
};

inline double distance(t_point a, t_point b)
{
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void quick_sort(t_point *points, int left, int right, int axis = 0)
{
  if (left >= right)
  {
    return;
  }
  int i = left, j = right;
  t_point pivot = points[left];
  while (i < j)
  {
    if (axis == 0)
    { // sort by x axis
      while (i < j && points[j].x >= pivot.x)
        j--;
      if (i < j)
        points[i++] = points[j];
      while (i < j && points[i].x <= pivot.x)
        i++;
      if (i < j)
        points[j--] = points[i];
    }
    else
    {//sort by y axis
      while (i < j && points[j].y >= pivot.y)
        j--;
      if (i < j)
        points[i++] = points[j];
      while (i < j && points[i].y <= pivot.y)
        i++;
      if (i < j)
        points[j--] = points[i];
    }
  }
  points[i] = pivot;

  quick_sort(points, left, i - 1, axis);
  quick_sort(points, i + 1, right, axis);
}

double get_min_distance(t_point *points_by_x, t_point *points_by_y, t_point *points_filtered,\
 int left, int right)
{
  using std::min;

  // atomic situation
  int len = right - left + 1;
  if (len < 2)
  {
    return INFTY;
  }
  else if (len == 2)
  {
    return distance(points_by_x[left], points_by_x[left + 1]);
  }
  else if (len == 3)
  {
    double d1 = distance(points_by_x[left], points_by_x[left + 1]);
    double d2 = distance(points_by_x[left], points_by_x[left + 2]);
    double d3 = distance(points_by_x[left + 1], points_by_x[left + 2]);
    return min(d1, min(d2, d3));
  }

  // when len > 4, divide into two phase then conquer
  // divide part
  int mid = (left + right) / 2;
  int base_x = points_by_x[mid].x;
  int count_left = 0, count_right = 0;
  for (int i = left; i < right; i++)
  {
    if (points_by_y[i].x <= base_x && left + count_left <= mid)
    {
      points_filtered[left + count_left] = points_by_y[i];
      count_left++;
    }
    else
    {
      points_filtered[mid + count_right] = points_by_y[i];
      count_right++;
    }
  }
  double d1 = get_min_distance(points_by_x, points_filtered, points_by_y, left, mid);
  double d2 = get_min_distance(points_by_x, points_filtered, points_by_y, mid + 1, right);
  double min_d = min(d1, d2);

  // conquer part
  int count = 0;
  for (int i = left; i <= right; i++)
  {
    double new_x = points_by_y[i].x;
    if (base_x - min_d <= new_x && new_x <= min_d + base_x)
    {
      points_filtered[count] = points_by_y[i];
      count++;
    }
  }
  // the panel holding 11 points for maximum
  for (int i = 0; i < count; i++)
  {
    for (int k = 1; k <= MAX_POINT_PANEL; k++)
    {
      if (i + k < count)
      {
        double new_d = distance(points_filtered[i], points_filtered[i + k]);
        if (new_d < min_d && new_d > ZERO) // to avoid two-same-point situation
          min_d = new_d;
      }
    }
  }
  return min_d;
}

int main()
{
  int n;
  scanf("%d", &n);
  t_point points_by_x[n], points_by_y[n], points_filtered[n];
  double new_x, new_y;
  for (int i = 0; i < n; i++)
  {
    scanf("%lf", &new_x);
    scanf("%lf", &new_y);
    points_by_x[i].x = new_x;
    points_by_x[i].y = new_y;
    points_by_y[i] = points_by_x[i];
  }
  // sort by x and y axis and store individually
  quick_sort(points_by_x, 0, n - 1, 0);
  quick_sort(points_by_y, 0, n - 1, 1);
  double min_distance = get_min_distance(points_by_x, points_by_y, points_filtered, 0, n - 1);
  printf("%.6lf", std::sqrt(min_distance));
  return 0;
}
