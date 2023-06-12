#include <stdio.h>
#include <vector>

using std::vector;

/*preset maximum size of A and B*/
static const int ArowMax = 1300, AcolMax = 1300;
static const int BrowMax = 3000, BcolMax = 20000;

/*parameters for hash function*/
static const int k = 29, prime = 38734667;

/*actual size of A and B*/
int A_row = 0, A_col = 0;
int B_row = 0, B_col = 0;

/*pattern, sub string for matching*/
int A[ArowMax][AcolMax];
/*text, base string for matching*/
int B[BrowMax][BcolMax];

/**
 * @brief hashing 2D matrix into 1D string, each column of char into one int
 * 
 * @return vector<int> compressed pattern string
 */
inline vector<int> hash_pattern(void)
{
  vector<int> pattern(A_col);
  for (int j = 0; j < A_col; j++)
  {
    pattern[j] = 0;
    for (int i = 0; i < A_row; i++)
    {
      pattern[j] = (pattern[j] * k + A[i][j]) % prime;
    }
  }
  return pattern;
}

/**
 * @brief hashing 2D matrix into 1D string, each column of char into one int
 * 
 * @return vector<int> compressed main string for matching
 */
inline vector<int> hash_text(void)
{
  vector<int> text(B_col);
  for (int j = 0; j < B_col; j++)
  {
    text[j] = 0;
    for (int i = 0; i < A_row; i++)
    {
      text[j] = (text[j] * k + B[i][j]) % prime;
    }
  }
  return text;
}

/**
 * @brief iteriate the hashed main-string 
 * 
 * @param text hashed main-string
 * @param row iteriation start
 * @param index parameter for hashing
 */
inline void change(vector<int> &text,const int row,  const int index)
{
  for (int j = 0; j < B_col; j++)
  {
    text[j] = (((text[j] + k * prime - B[row - A_row + 1][j] * index) % prime * k) + B[row + 1][j]) % prime;
  }
}

/**
 * @brief compare pattern(compressed) with main-string in (row,col)
 * 
 * @param row row to match
 * @param col col to match
 * @retval if found matching
 */
inline const bool compare(const int row, const int col)
{
  int i = 0, j = 0;
  for (int i = 0; i < A_row; i++)
  {
    for (int j = 0; j < A_col; j++)
    {
      if (A[i][j] != B[row + i][col + j])
      {
        return false;
      }
    }
  }
  return true;
}

/**
 * @brief Get the prefix of 2D substring for KMP alg later on
 * 
 * @param pattern substring(compressed)
 * @return vector<int> prefix array of pattern
 */
vector<int> get_prefix(vector<int> pattern)
{
  int _size = int(pattern.size());
  vector<int> prefix(_size + 1);
  int i = 0, j = -1;
  prefix[0] = -1;
  while (i < _size)
  {
    while (j >= 0 && pattern[i] != pattern[j])
      j = prefix[j];
    i++;
    j++;
    prefix[i] = j;
  }
  return prefix;
}

/**
 * @brief KMP Alg for sub string matching in traditional way
 * 
 * @param pattern sub-string(compressed)
 * @param text main-string(compressed)
 * @param row (row index in main-string to match)
 */
inline void KMP(vector<int> pattern, vector<int> text, const int row)
{
  static vector<int> prefix = get_prefix(pattern);
  int i = 0, j = 0;
  while (i < B_col)
  {
    while (j >= 0 && text[i] != pattern[j])
    {
      j = prefix[j];
    }
    i++;
    j++;
    if (j == A_col)
    {
      int column = i - A_col;
      int row_diff = row - A_row + 1;
      if (compare(row_diff, column) == true)
      {
        /*answer output in stdio*/
        printf("%d %d\n", row_diff, column);
      }
      j = prefix[j];
    }
  }
}

int main()
{
  /*read in A and B*/
  scanf("%d %d\n", &A_row, &A_col);
  for (int i = 0; i < A_row; i++)
  {
    for (int *p = A[i], j = 0; j < A_col; j++)
    {
      *p++ = getchar() - 'a';
    }
    getchar(); // skip \n
  }

  scanf("%d %d\n", &B_row, &B_col);
  for (int i = 0; i < B_row; i++)
  {
    for (int *p = B[i], j = 0; j < B_col; j++)
    {
      *p++ = getchar() - 'a';
    }
    getchar(); // skip \n
  }

  /*hyper parameter for 2D string hashing iteriation*/
  int index = 1;
  for (int i = 0; i < A_row - 1; i++)
  {
    index = (index * k) % prime;
  }
  /*hashed pattern and main-string*/
  vector<int> text = hash_text();
  vector<int> pattern = hash_pattern();

  int row = A_row - 1;
  while (row < B_row)
  {
    KMP(pattern, text, row);
    if (row < B_row - 1)
    {
      change(text,row,  index);
    }
    row++;
  }

  return 0;
}
