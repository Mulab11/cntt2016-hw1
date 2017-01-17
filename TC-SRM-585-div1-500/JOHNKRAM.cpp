#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
int n,m,i,j,f[3000],F[3000],I[3000];
int C(int x,int y)
{
    if(x<y)return 0;
    return (ll)F[x]*I[y]%P*I[x-y]%P;
}
class LISNumber
{
    public:
        int count(vector <int> cardsnum, int K)
        {
            n=cardsnum.size();
            for(i=0;i<n;i++)m+=cardsnum[i];
            for(i=F[0]=1;i<3000;i++)F[i]=(ll)F[i-1]*i%P;
            for(I[1]=1,i=2;i<3000;i++)I[i]=(ll)(P-P/i)*I[P%i]%P;
            for(I[0]=i=1;i<3000;i++)I[i]=(ll)I[i-1]*I[i]%P;
            for(i=1;i<=K;i++)
            {
                f[i]=1;
                for(j=0;j<n;j++)f[i]=(ll)f[i]*C(i,cardsnum[j])%P;
                for(j=1;j<i;j++)f[i]=(f[i]-(ll)f[j]*C(m+i-j,i-j))%P;
                if(f[i]<0)f[i]+=P;
            }
            return f[K];
        }
};
