#include<bits/stdc++.h>
using namespace std;
#define P 1000000009
int N,i,j,k,a[305],f[305][305],g[305][305],h[305][305];
class TheExperiment
{
    public:
        int countPlacements(vector <string> intensity, int M, int L, int A, int B)
        {
            for(i=0;i<intensity.size();i++)for(j=0;j<intensity[i].size();j++,N++)a[N+1]=a[N]+intensity[i][j]-'0';
            for(i=h[0][0]=1;i<=N;i++)for(j=0;j<=M;j++)//动态规划 
            {
                h[i][j]=h[i-1][j]+g[i-1][j];//最后一个没接到 
                if(h[i][j]>=P)h[i][j]-=P;
                for(k=1;k<L&&k<=i;k++)if(a[i-k]+A<=a[i]&&a[i-k]+B>=a[i])//最后一个接到了，最后一段大小<L 
                {
                    f[i][j]+=f[i-k][j-1];
                    if(f[i][j]>=P)f[i][j]-=P;
                    f[i][j]+=h[i-k][j-1];
                    if(f[i][j]>=P)f[i][j]-=P;
                    g[i][j]+=g[i-k][j-1];
                    if(g[i][j]>=P)g[i][j]-=P;
                }
                if(i>=L&&a[i-k]+A<=a[i]&&a[i-k]+B>=a[i])//最后一个接到了，最后一段大小=L 
                {
                    g[i][j]+=f[i-k][j-1];
                    if(g[i][j]>=P)g[i][j]-=P;
                    g[i][j]+=g[i-k][j-1];
                    if(g[i][j]>=P)g[i][j]-=P;
                    g[i][j]+=h[i-k][j-1];
                    if(g[i][j]>=P)g[i][j]-=P;
                }
            }
            g[N][M]+=h[N][M];//计算答案 
            if(g[N][M]>=P)g[N][M]-=P;
            return g[N][M];
        }
};