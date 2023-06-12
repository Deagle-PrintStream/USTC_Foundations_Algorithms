#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int mod=1000;
const int max_size=1e5;
const int max_k=100;

/*array for input numbers without order*/
int a[max_size];
int dp[max_size][max_k];
int tree[max_size][max_k];

/*array for ordered storage of input*/
vector<int> V;
int num[max_size];
/*array of index of ordered numbers in V from a[]*/
int vis[max_size];
int temp[max_size];

/*@brief used for DP alg
@return max { n s.t. x%n==0, n=2^k,k is int }
*/
inline const int lowbit(const int x){ return x & (-x);}

/*@brief update tree with given info
@param depth length of increasing array
@param pos start of updating
@param adder count of increasing array with length of (depth-1)
*/
inline void add \
(int pos,const int depth ,const int adder,const int array_size){
  while(pos<=array_size){
    tree[pos][depth]=(tree[pos][depth]+adder)%mod;
    pos+=lowbit(pos);
  }
}

/*@brief sum up count of increasing array with length of depth
@param pos start of calculating
@param depth length of increasing array
@retval sum of the count
*/
inline int query(int pos,int depth){
  int ans=0;
  while(pos>0){
    ans=(ans+tree[pos][depth])%mod;
    pos-=lowbit(pos);
  }
  return ans;
}

/*@brief faster read-in funcution, alternate for scanf("%d") 
*/
inline const int read_int(void)
{
  int x=0;  int f=1;
  char ch=getchar();
  while(ch=='\n' || ch==' ')
    ch=getchar();
  if (ch=='-') {f=-1;ch=getchar();}
  while(ch>='0' && ch<='9')
    x=x*10+ch-'0',ch=getchar();
  return x*f;
}

int main(){
  int n=0;  int k=0;
  scanf("%d  %d\n", &n,&k);
  /*input size exceptions handler*/
  if(n<=1 || k==1){
    printf("%d",n);
    return 0;
  }
  if(k>n){
    printf("0");
    return 0;
  }
  /*read in numbers*/
  for (int i = 0; i < n; i++)
  {
    int new_num=read_int();
    a[i]=new_num;
    V.push_back(new_num);
  }
  /*get the sorted array ,get the index from a[] to V, and exclude duplicate numbers*/
  sort(V.begin(),V.end());
  V.erase(unique(V.begin(),V.end()),V.end());
  for(int i = 0; i < n; i++){
    vis[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
  }
  int array_size=V.size();
  /*sum up all trees*/
  for(int i = 0; i < n; i++){
    int pos=vis[i];
    num[pos]++;
    dp[pos][1]=num[pos];
    add(pos,1,1,array_size);

    for(int j=2;j<=k;j++){
      temp[j]=query(pos-1,j-1);
      dp[pos][j]=(dp[pos][j]+temp[j])%mod;
    }
    for(int j=2;j<k;j++){
      add(pos,j,temp[j],array_size);
    }
  }
  /*get the sum*/
  int ans=0;
  for(int i=1;i<=n;i++){
    ans=(ans+dp[i][k])%mod;
  }
  printf("%d",ans);
  return 0;
}
