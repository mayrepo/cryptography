#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm> 

using namespace std;

inline int mod(unsigned n, unsigned m){return (n%m+m)%m;}

template <typename T>
T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

int main(int argc, char* argv[])
{
    if(argc!=4)
        return 1;
    unsigned g = stoi(argv[1]), b = stoi(argv[2]), n = stoi(argv[3]);
    
    unsigned m = ceil(sqrt((float)n));
    
    vector< pair<unsigned,unsigned> > S,T;
    
    unsigned i;
    unsigned p,q;
    
    unsigned g_m = modpow<int>(g, n-1-m, n);
    
    for(i=0, p=1, q=b; i<m; i++)
    {
        S.push_back(make_pair(mod(p,n),i));
        p = mod(p*g,n);
        
        T.push_back(make_pair(mod(q,n),i));
        q = mod(q*g_m,n);
    }
    
    sort(S.begin(), S.end());
    sort(T.begin(), T.end());
    unsigned logg = 0;
    
    
    vector< pair<unsigned,unsigned> >::iterator Si = S.begin(), Ti = T.begin();
    
    while(Si!=S.end() && Ti!=T.end())
    {
        if((*Si).first > (*Ti).first)
            Si++;
        else if ((*Si).first < (*Ti).first)
            Ti++;
        else
        {
            logg = (*Ti).second*m + (*Si).second;
            break;
        }
    }
    if(logg!=0)
        cout << logg << endl;
    return 0;
}
