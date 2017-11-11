#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

inline bool ok(const unsigned long int& n, const unsigned long int& s,const unsigned long int& t) {return n==t*t-s*s;}

int main()
{
    const unsigned long int n = 23360947609;
    unsigned long int s,t;
    
    for(s=0;!ok(n,s,t)&&!ok(n,s,t+1); s++)
    {
        t=floor(sqrt(n+s*s));
    }
    
    if (ok(n,s,t+1))
        t++;
    
    cout << t-s << " * " << t+s << " = " << t*t - s*s << endl;
    return 0;
}
