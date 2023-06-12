#include <stdio.h>
#include <complex>
#include <valarray>

const double PI = 3.1415926535;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

void fft(CArray &x)
{
  const size_t N = x.size();
  if (N <= 1)
    return;
  // divide
  CArray even = x[std::slice(0, N / 2, 2)];
  CArray odd = x[std::slice(1, N / 2, 2)];
  // conquer
  fft(even);
  fft(odd);
  // combine
  for (size_t k = 0; k < N / 2; ++k)
  {
    Complex t = std::polar(1.0, 2 * PI * k / N) * odd[k];
    x[k] = even[k] + t;
    x[k + N / 2] = even[k] - t;
  }
}

int ord(Complex c)
{
  double real = c.real();
  if (real > 0)
  {
    return int(real + 0.5);
  }
  else
  {
    return int(real - 0.5);
  }
}

int main()
{
  int n = 0; // input length
  int new_var;
  scanf("%d", &n);
  int m = 1; // extended length
  while (m < n)
  {
    m <<= 1;
  }
  m <<= 1;
  CArray a(m);
  CArray b(m);
  CArray c(m);
  int output[n];

  for (int i = 0; i < n; i++)
  {
    scanf("%d", &new_var);
    a[i] = Complex(double(new_var), 0);
  }
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &new_var);
    b[i] = Complex(double(new_var), 0);
  }
  for (int i = n; i < m; i++)
  {
    a[i] = b[i] = Complex(0.0, 0.0);
  }

  fft(a);
  fft(b);

  for (int i = 0; i < m; i++)
  {
    c[i] = a[i] * b[i];
    c[i] /= m;
    c[i] = std::conj(c[i]);
  }
  fft(c);

  for (int i = 0; i < n; i++)
  {
    output[i] = ord(c[i]) + ord(c[i + n]);
  }
  for (int i = 0; i < n; i++)
  {
    printf("%d\n", output[i]);
  }
  return 0;
}
