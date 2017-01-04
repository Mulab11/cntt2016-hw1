#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 3200
#define P 555555555
int c[N][N];
class XorBoard
{
    public:
        int count(int H, int W, int Rcount, int Ccount, int S)
        {
            int i,j,ans=0;
            for(i=c[0][0]=1;i<N;i++)for(j=c[i][0]=1;j<=i;j++)//计算组合数 
            {
                c[i][j]=c[i-1][j-1]+c[i-1][j];
                if(c[i][j]>=P)c[i][j]-=P;
            }
            for(i=Rcount&1;i<=H&&i<=Rcount;i+=2)for(j=Ccount&1;j<=W&&j<=Ccount;j+=2)if(i*W+j*H==S+2*i*j)ans=(ans+(ll)c[H][i]*c[W][j]%P*c[H-1+(Rcount-i>>1)][H-1]%P*c[W-1+(Ccount-j>>1)][W-1])%P;//计算答案 
            return ans;
        }
};