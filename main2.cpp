#include <iostream>
#include <deque>
#include <vector>
#include <cmath>

using namespace std;

//function f
bool f(bool i,bool j,bool k,bool l)
{
    bool f[] = {0,1,0,0,0,1,0,0,1,1,0,1,1,1,0,1};
    return f[i + 2*j + 4*l + 8*k];
}

//LFSR objet
class LFSR
{
  public:
    unsigned n;
    deque<bool> state;
    vector<bool> poly;
    
    //constructor
    LFSR(unsigned char m_n, vector<bool> m_poly, vector<bool> init)
    {
        n=m_n;
        for(unsigned i=0; i<n-1; i++)
        {
            state.push_back(init[i]);
            poly.push_back(m_poly[i]);
        }
        state.push_back(init[n-1]);
    }
    
    //compute the next output of the LFSR
    bool next()
    {
        
        //calculate the value of the polynomial
        unsigned sum=0;
        
        deque<bool>::iterator j=state.begin();
        for(vector<bool>::iterator i = poly.begin();
            i!=poly.end() && j!=state.end(); i++, j++)
            sum += (*i)*(*j);
        
        bool last = *j;
        
        sum+=last;
        
        //store the remainder 
        state.push_front(sum%2);
        
        //remove the output stored in last
        state.pop_back();
        
        //return the output
        return last;
    }
    
};

//returns the rank-th bit of n
inline bool r(unsigned n, char rank)
{
    return ((n >> rank)%2);
}

float* correlation(bool (*f)(bool,bool,bool,bool))
{
    unsigned corr[4]={0,0,0,0};
    
    bool ff;
    
    for(unsigned i=0; i < 2; i++)
        for(unsigned j =0; j <2; j++)
            for(unsigned k=0; k <2 ; k++)
                for(unsigned l=0; l <2 ; l++)
                {
                    ff = f(i,j,k,l);
                    for(unsigned m=0; m < 4; m++)
                        if( ff == (m==0 ? i : (m==1 ? j : (m==2 ? k : l) ) ) )
                            corr[m]++;
                }
    float* corr2 = new float[4];
    for(unsigned i=0; i<4; i++)
        corr2[i]=corr[i]/16.;
    return corr2;
}

//surmise the initial value of the register
unsigned Si(unsigned N, vector<bool> z, unsigned char L, vector<bool> P)
{
    //calculate and returns the register value that gives the highest correlation in absolute value
    
    unsigned i_max=0;
    
    int max=0;
    
    int corr=0;
    
    for(unsigned i=0; i < pow(2,L); i++)
    {
        vector<bool> S;
        
        for(unsigned j=0; j<L;j++)
            S.push_back(r(i,j));
        
        LFSR LFSRs(L,P,S);
        
        for(unsigned j=0; j<L;j++)
            LFSRs.next();
        
        corr=0;
        
        for(unsigned j=0; j<N;j++)
            corr += ( LFSRs.next() == z[j] )?1:-1;
        
        if(abs(corr)>abs(max))
        {
            i_max = i;
            max = corr;
        }
    }
    return i_max;
}


int main()
{
    //calculate the correlation between f and its variables
    float* corr = correlation(f);
    
    //print it
    for(unsigned i=0; i<4; i++)
        cout << corr[i] << endl;
    
    delete(corr);
    
    //initialisations
    unsigned char L1 = 7, L2 = 6, L3 = 9, L4 = 8;
    vector<bool> P1 = {1,0,0,0,0,0}, P2 = {1,0,1,1,0}, P3 = {0,0,0,1,0,0,0,1}, P4 = {0,1,1,1,0,0,0};
    vector<bool> S1 = {1,0,1,0,0,1,0}, S2 = {0,1,0,0,0,1}, S3 = {1,0,1,0,0,1,1,1,0}, S4 = {0,0,0,1,0,0,0,1};
    
    
    vector<unsigned char> L = {L1,L2,L3,L4};
    vector<vector<bool> > P = {P1,P2,P3,P4};
    vector<vector<bool> > S = {S1,S2,S3,S4};
    
    unsigned char Lmax =L3;
    unsigned N=pow((sqrt((Lmax-1)*log(2)) + 3*sqrt(2*pow(.5,Lmax)*(1-pow(.5,Lmax))))/(sqrt(2)*(.5-pow(.5,Lmax))),2);
    N=100;
    
    //create LFSR objects
    vector<LFSR> LFSRs;
    for(unsigned i = 0; i < 4 ; i++)
        LFSRs.push_back(LFSR(L[i], P[i], S[i]));
    
    for(unsigned j=0; j<4;j++)
        for(unsigned i=0; i<L[j];i++)
            LFSRs[j].next();
    
    vector<bool> z;
    
    //calculate z
    for(unsigned j=0; j<N;j++)
    {
        z.push_back( f(LFSRs[0].next(),LFSRs[1].next(), LFSRs[2].next(), LFSRs[3].next()) );
    }
    
    unsigned Sk;
    
    //for every variable
    for(unsigned i = 0; i < 4; i++)
    {
        //surmise the initial value of the register
        Sk = Si(N,z,L[i],P[i]);
        
        //print it
        cout << "S" << i+1 << " = ";
        for(unsigned j=0;j<L[i]; j++)
            cout << r(Sk,j);
        cout << endl;
    }
    return 0;
}
