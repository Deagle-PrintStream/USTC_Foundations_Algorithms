#include <stdio.h>

typedef long long int ll;

const ll power(ll a, ll n, const ll mod)
{
  if (n == 0)
    return 1;
  else if (n % 2 == 1)
    return power(a, n - 1, mod) * a % mod;
  else
  {
    const ll temp = power(a, n / 2, mod) % mod;
    return temp * temp % mod;
  }
}

inline const ll gcd(ll a, ll b)
{
  ll temp;
  if (b > a)
  {
    temp = a;
    a = b;
    b = temp;
  }
  while (b != 0)
  {
    temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

inline const ll get_phi(const ll p)
{
  ll phi = 1;
  for (ll i = 2; i < p; i++)
  {
    if (p % i == 0)
    {
      continue;
    }
    if (gcd(i, p) == 1)
    {
      phi++;
    }
  }
  return phi;
}

inline const ll read_uint(void)
{
  ll x = 0;
  char ch = getchar();
  while (ch == '\n' || ch == ' ')
    ch = getchar();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + ch - '0', ch = getchar();
  return x;
}

inline const ll get_mod_advanced(ll a, ll b, ll c, ll p)
{
  a = a % p;
  b = b % (p - 1);
  const ll phi = get_phi(p - 1);
  const ll q_1 = c % phi;
  const ll q_2 = power(b, q_1, p - 1);
  const ll ans = power(a, q_2, p);
  return ans;
}

inline const ll get_mod(ll a, ll b, ll c, ll p)
{
  a = a % p;
  b = b % (p - 1);
  const ll q = power(b, c, p - 1);
  const ll ans = power(a, q, p);
  return ans;
}

int main()
{
  ll a, b, c, p;
  a = read_uint();
  b = read_uint();
  c = read_uint();
  p = read_uint();

  if (a == 1)
  {
    printf("1");
  }

  ll ans = get_mod_advanced(a, b, c, p);
  printf("%ld", ans);

  return 0;
}
