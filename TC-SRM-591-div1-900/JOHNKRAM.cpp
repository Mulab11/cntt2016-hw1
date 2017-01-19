#include<bits/stdc++.h>
using namespace std;
#define P 1000000009
int f[8][8][256][256],ans,i,j,k,l;
class StringPath
{
    public:
        int countBoards(int n, int m, string A, string B)
        {
            if(A[0]!=B[0]||A[n+m-2]!=B[n+m-2])return 0;
            f[0][0][1][1]=1;
            for(i=0;i<n;i++)for(j=0;j<m;j++)for(k=0;k<1<<m;k++)for(l=0;l<1<<m;l++)if(f[i][j][k][l])if(j+1==m)if(i+1==n)goto xxx;
            else if(A[i+1]==B[i+1])
            {
                f[i+1][0][k][l]+=f[i][j][k][l];
                if(f[i+1][0][k][l]>=P)f[i+1][0][k][l]-=P;
                f[i+1][0][k&~1][l&~1]=(f[i+1][0][k&~1][l&~1]+25LL*f[i][j][k][l])%P;
            }
            else
            {
                f[i+1][0][k&~1][l]+=f[i][j][k][l];
                if(f[i+1][0][k&~1][l]>=P)f[i+1][0][k&~1][l]-=P;
                f[i+1][0][k][l&~1]+=f[i][j][k][l];
                if(f[i+1][0][k][l&~1]>=P)f[i+1][0][k][l&~1]-=P;
                f[i+1][0][k&~1][l&~1]=(f[i+1][0][k&~1][l&~1]+24LL*f[i][j][k][l])%P;
            }
            else if(A[i+j+1]==B[i+j+1])
            {
                f[i][j+1][k|((k>>j&1)||(k>>j+1&1))<<j+1][l|((l>>j&1)||(l>>j+1&1))<<j+1]+=f[i][j][k][l];
                if(f[i][j+1][k|((k>>j&1)||(k>>j+1&1))<<j+1][l|((l>>j&1)||(l>>j+1&1))<<j+1]>=P)f[i][j+1][k|((k>>j&1)||(k>>j+1&1))<<j+1][l|((l>>j&1)||(l>>j+1&1))<<j+1]-=P;
                f[i][j+1][k&~(1<<j+1)][l&~(1<<j+1)]=(f[i][j+1][k&~(1<<j+1)][l&~(1<<j+1)]+25LL*f[i][j][k][l])%P;
            }
            else
            {
                f[i][j+1][k&~(1<<j+1)][l|((l>>j&1)||(l>>j+1&1))<<j+1]+=f[i][j][k][l];
                if(f[i][j+1][k&~(1<<j+1)][l|((l>>j&1)||(l>>j+1&1))<<j+1]>=P)f[i][j+1][k&~(1<<j+1)][l|((l>>j&1)||(l>>j+1&1))<<j+1]-=P;
                f[i][j+1][k|((k>>j&1)||(k>>j+1&1))<<j+1][l&~(1<<j+1)]+=f[i][j][k][l];
                if(f[i][j+1][k|((k>>j&1)||(k>>j+1&1))<<j+1][l&~(1<<j+1)]>=P)f[i][j+1][k|((k>>j&1)||(k>>j+1&1))<<j+1][l&~(1<<j+1)]-=P;
                f[i][j+1][k&~(1<<j+1)][l&~(1<<j+1)]=(f[i][j+1][k&~(1<<j+1)][l&~(1<<j+1)]+24LL*f[i][j][k][l])%P;
            }
            xxx:for(i=1<<m-1;i<1<<m;i++)for(j=1<<m-1;j<1<<m;j++)
            {
                ans+=f[n-1][m-1][i][j];
                if(ans>=P)ans-=P;
            }
            return ans;
        }
};
