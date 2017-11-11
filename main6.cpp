#include <iostream>
#include <map>
#include <cmath>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <cassert>  

#define n0 (256)
#define k0 (64)
#define k1 (64)

using namespace std;

inline int mod(unsigned n, unsigned m){return (n%m+m)%m;}

template <typename T>
T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0)
  {
    if (exp & 1)
        result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

bool RabinTest(unsigned long int n, unsigned t)
{
    unsigned long int r = n-1, s = 0, a, y;
    
    if(n==0 || n==1)
        return false;
    
    if(n==3)
        return true;
    
    while(!(r & 1))
    {
        r>>=1;
        s++;
    }
    if(s==0)
        return n==2;
    
    for(unsigned i = 0; i < t; i++)
    {
        a = rand()%(n-3) + 2;
        
        y = modpow<long int>(a,r,n);
        
        if(y != 1 && y != n-1)
        {
            for(unsigned j = 0; j < s-1 && y != n-1; j++)
            {
                y = (y*y) % n;
                if(y == 1)
                    return false;
            }
            if(y!= n-1)
                 return false;
        }
    }
    
    return true;
}



string Format(string m)
{
    assert(m.length()==n0-k0-k1);
    
    int r = rand() % (((long) 1) << k0);
    r;
}

int main()
{
    srand (time(NULL));
    
    for(int i=0; i < 1000; i++)
        if(RabinTest(i, 25))
            cout << i << " ";
    
    cout << endl;
    return 0;
}
