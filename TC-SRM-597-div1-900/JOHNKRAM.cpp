#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
#define N 1<<21
int f[N],I[N],n,i,j,k,x,s,ans;
class LittleElephantAndBoard
{
    public:
        int getNumber(int M, int R, int G, int B)
        {
            R=M-R;
            G=M-G;
            B=M-B;
            if(min(min(R,G),B)<0)return 0;
            for(i=f[0]=1;i<N;i++)f[i]=(ll)f[i-1]*i%P;
            for(I[1]=1,i=2;i<N;i++)I[i]=(ll)(P-P/i)*I[P%i]%P;
            for(i=I[0]=1;i<N;i++)I[i]=(ll)I[i-1]*I[i]%P;
            for(n=max(B-1,0);n<B+2;n++)for(x=1<<(i=(n^R^G)&1);i<=n;i+=2,x=((ll)x<<2)%P)
            {
                j=n-i+R-G>>1;
                k=n-i+G-R>>1;
                if(min(j,k)<0)continue;
                s=(ll)f[n]*I[i]%P*I[j]%P*I[k]%P;
                j=R-i-j;
                if(j<0)continue;
                s=(ll)s*f[n+j-1]%P*I[n-1]%P*I[j]%P;
                if(n==B)
                {
                    s<<=1;
                    if(s>=P)s-=P;
                }
                ans=(ans+(ll)s*x)%P;
            }
            ans<<=1;
            if(ans>=P)ans-=P;
            return ans;
        }
};
