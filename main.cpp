#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

//character to number
inline char n(char c){return c-'A';}

//number to character
inline char ch(char n){return n+'A';}

//positive modulo
inline int modulo(int i, int n) {return (i % n + n) % n;}

//encodes the message m with the key k
string code(string m, string k)
{
    string c;
    for(unsigned i=0; i < m.length(); i++)
    {
        c += ch( modulo(n(m[i]) + n( k[i%k.length()] ), 26));
    }
    return c;
}

//decodes the message c with the key k
string decode(string c, string k)
{
    string d;
    for(unsigned i=0; i < c.length(); i++)
    {
        d += ch( modulo(n(c[i]) - n( k[i%k.length()] ),26));
    }
    return d;
}

//calculates the index of coincidence of the message y
float IC(string y)
{
    float sum;
    for(unsigned i=0; i< 26; i++)
    {
        int n = (int) std::count(y.begin(), y.end(), i+'A');
        sum += n*(n-1);
    }
    return sum/(y.size()*(y.size()-1));
}

//calculates the g-index of mutual coincidence beetween the messages y and z
float IMC(string y, string z, char g)
{
    float sum;
    for(unsigned i=0; i < 26; i++)
    {
        int n = (int) std::count(y.begin(), y.end(), i+'A');
        int m = (int) std::count(z.begin(), z.end(), modulo(i-g,26)+'A');
        sum += n*m;
    }
    return sum/(y.size()*z.size());
}

//calculates the g-index of mutual coincidence beetween the message y and the probabilities
float IMC(string y, float probas[], char g)
{
    float sum;
    for(unsigned i=0; i < 26; i++)
    {
        int m = (int) std::count(y.begin(), y.end(), modulo(i-g,26)+'A');
        sum += probas[i]*m;
    }
    return sum/(y.size()*100);
}

//cuts the string c starting from start with a step step
string modulo(string c, unsigned start, unsigned step)
{
    string s;
    for(unsigned i=start; i < c.size(); i += step)
    {
        s += c[i];
    }
    return s;
}

//probabilities of apparition of french letters
float french_probas[26] ={7.11,1.14,3.18,3.67,12.10,1.11,1.23,1.11,6.59,.34,.59,4.96,2.62,6.39,5.02,2.49,.65, 6.07,6.51,5.92,4.49,1.11,.17,.38,.46,.15};


int main(int argc, char* argv[])
{
    //opens the 
    ifstream file("clair.txt");
    
    
    
    if(file&&(argc==2))
    {
        //the argument of the program is the key
        string m, k(argv[1]), c, d;
        unsigned k_size = k.size();
        
        getline(file,m);
        
        c = code(m,k);
        d = decode(c,k);
        
        char decalages[k_size-1];
        
        string sub_c[k_size];
        
        for(unsigned i=0; i< k_size; i++)
            sub_c[i] = modulo(c, i, k_size);
        
        
        //calculates the g-max of mutual coincidence beetween the first sub-message with the i-sub-message
        for(unsigned i=1; i<k_size; i++)
        {
            char max_g=0;
            float max=0;
            for(unsigned g=0; g<26; g++)
            {
                if(IMC(sub_c[0],sub_c[i],g)>max)
                {
                    max_g = g;
                    max = IMC(sub_c[0],sub_c[i],g);
                }
            }
            decalages[i-1] = max_g;
        }
        unsigned max_g=0;
        float max=0;
        
        //calculates the max of mutual coincidence
        for(unsigned g=0; g<26; g++)
        {
            if(IMC(sub_c[0],french_probas,g)>max)
            {
                max_g = g;
                max = IMC(sub_c[0],french_probas,g);
            }
        }
        
        //prints the key according to the program
        string k2;
        k2 += 'A'+modulo(-max_g,26);
        
        for(unsigned i=1; i<k_size; i++)
            k2 += 'A'+ modulo(-max_g-decalages[i-1],26);
        
        cout << k2 << endl;
    }
    else if (argc!=2)
        cout << "Not enough arguments" << endl;
    else
        cout << "Error file opening" << endl;
    
    return 0;
}
