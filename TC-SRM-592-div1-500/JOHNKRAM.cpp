#include<bits/stdc++.h>
using namespace std;
#define P 1000000007
#define ll long long
int f[55][55][2505],i,j,k;
class LittleElephantAndPermutationDiv1
{
    public:
        int getNumber(int N, int K)
        {
            for(i=f[0][0][0]=1;i<=N;i++)for(j=0;j<=i;j++)for(k=0;k<=K;k++)
            {
                f[i][j][min(k+i,K)]=(f[i][j][min(k+i,K)]+(ll)f[i-1][j][k]*((j<<1)+1))%P;
                f[i][j+1][k]+=f[i-1][j][k];
                if(f[i][j+1][k]>=P)f[i][j+1][k]-=P;
                if(j)f[i][j-1][min(k+(i<<1),K)]=(f[i][j-1][min(k+(i<<1),K)]+(ll)f[i-1][j][k]*j*j)%P;
            }
            for(i=1,j=f[N][0][K];i<=N;i++)j=(ll)j*i%P;
            return j;
        }
};
