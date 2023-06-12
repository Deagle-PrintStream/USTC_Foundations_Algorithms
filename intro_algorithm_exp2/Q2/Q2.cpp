#include <stdio.h>

#define NONE (-1)
#define MAX_ATTEMPT (100)
#define CONSTANT (31)

typedef long int t_key;

class HashTable
{
private:
  const int size;
  const int max_attempt;
  int constant;
  t_key *table[2];

  const int hash(const t_key key,int order=0)const;
  bool insert(const t_key &new_key,const int attempt,const int order=0);
public:
  HashTable(const int _size);
  ~HashTable();
  bool insert(const t_key &new_key);
  bool delete_key(const t_key &new_key);
  const int lookup(const t_key &new_key)const;
  void print(void)const;

};

HashTable::HashTable(const int _size):\
size(int(_size*1.05)),max_attempt(size*2)
{
  table[0]=new t_key[size];
  table[1]=new t_key[size];
  for(int i=0;i<size;i++){
    table[0][i]=table[1][i]=NONE;
  }
  constant=CONSTANT;
}

HashTable::~HashTable()
{
  delete table[0];
  delete table[1];  
}

inline const int HashTable::hash\
(const t_key key, const int order)const{
  if(order==0){
    return key%size;
  }else{
    return (constant+key%(size-constant))%size;
  }
}

bool HashTable::insert\
(const t_key &new_key,const int attempt,const int order)
{
  if(lookup(new_key)==1){
    return true;
  }
  if(attempt>=max_attempt){
    return false;
  }
  int index0=hash(new_key,order);
  int index1=hash(new_key,!order);
  //if one of four slots is empty
  if(table[order][index0]==NONE){table[order][index0]=new_key;return true;}
  if(table[order][index1]==NONE){table[order][index1]=new_key;return true;}
  if(table[!order][index0]==NONE){table[!order][index0]=new_key;return true;}
  if(table[!order][index1]==NONE){table[!order][index1]=new_key;return true;}
  //all of four slots are full, then replace the 1st one
  t_key old_key=table[order][index0];
  table[order][index0]=new_key;
  return insert(old_key,attempt+1,!order);
}

bool HashTable::insert(const t_key &new_key)
{
  return insert(new_key, 0, 0);
}


bool HashTable::delete_key(const t_key &new_key)
{
  if(lookup(new_key)==false){
    return false;
  }
  int index0=hash(new_key,0);
  int index1=hash(new_key,1);
  if(table[0][index0]==new_key){table[0][index0]=NONE;return true;}
  if(table[0][index1]==new_key){table[0][index1]=NONE;return true;}
  if(table[1][index0]==new_key){table[1][index0]=NONE;return true;}
  if(table[1][index1]==new_key){table[1][index1]=NONE;return true;}
  return false;
}

const int HashTable::lookup(const t_key &new_key) const
{
  int index0=hash(new_key,0);
  int index1=hash(new_key,1);
  return int(table[0][index0]==new_key || \
    table[0][index1]==new_key ||\
    table[1][index0]==new_key ||\
    table[1][index1]==new_key);
}

void HashTable::print(void) const
{
  printf("index\tT1\tT2\n");
  for(int i=0;i<size;i++){
    printf("%ld:\t %ld\t%ld\n",i,table[0][i],table[1][i]);
  }
}

inline t_key read_long_int(void)
{
  t_key x=0;
  char ch=getchar();
  while(ch>='0' && ch<='9')
    x=x*10+ch-'0',ch=getchar();
  return x;
}

/*input instruction handler*/
inline void instruction_handler(HashTable &ht){
  static char new_op='\0';
  static t_key new_key=0;
  new_op=getchar();
  new_key=read_long_int();
  switch (new_op)
  {
  case 'I'://insert new t_node with id and score
    ht.insert(new_key);
    break;
  case 'D'://delete the t_node with target id
    ht.delete_key(new_key);
    break;
  case 'L'://lookup if new_id is in the tree and return its score
    putchar(ht.lookup(new_key)+'0');
    putchar('\n');
    break;
  case 'P':
    ht.print();
    break;
  default:
    break;
  }
}

int main(){
  int m=0;
  int n=0;
  scanf("%d %d\n",&m,&n);
  HashTable ht(m);
  for(int i=0;i<n;i++){
    instruction_handler(ht);
  }
  return 0;
}
