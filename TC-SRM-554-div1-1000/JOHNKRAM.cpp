#include<bits/stdc++.h>
using namespace std;
#define P 1234567891
#define ll long long
ll t[121][121];
const int x[15][4]={{0,0,0,0},{0,0,0,1},{0,0,1,0},{0,1,0,0},{0,0,1,1},{0,1,0,1},{0,1,1,0},{0,1,1,1},{0,0,1,2},{0,1,0,2},{0,1,2,0},{0,1,1,2},{0,1,2,1},{0,1,2,2},{0,1,2,3}},y[15]={1,2,2,2,2,2,2,2,3,3,3,3,3,3,4},z[15]={4,2,2,2,2,2,0,2,1,1,0,0,1,1,0};
struct node
{
    int r,c,a[121][121];
    void operator*=(const node& y)//矩阵乘法 
    {
        memset(t,0,sizeof(t));
        int i,j,k;
        for(i=0;i<r;i++)for(k=0;k<c;k++)for(j=0;j<y.c;j++)
        {
            t[i][j]+=(ll)a[i][k]*y.a[k][j];
            if((k&3)==3)t[i][j]%=P;
        }
        c=y.c;
        for(i=0;i<r;i++)for(j=0;j<c;j++)a[i][j]=t[i][j]%P;
    }
}a,s;
int A(int n,int m)//计算排列数 
{
    if(n<m)return 0;
    int i,j;
    for(i=0,j=1;i<m;i++)j=(ll)j*(n-i)%P;
    return j;
}
int i,j,k,l,m,d[4];
class TheBrickTowerHardDivOne
{
    public:
        int find(int C, int K, long long H)
        {
            a.r=a.c=s.c=15*(K+1)+1;//总状态数 
            s.r=1;
            for(i=0;i<15;i++)if(y[i]<=C)for(j=0;j<15;j++)if(y[j]<=C&&z[j]<=K)for(memset(d,0,sizeof(d)),d[0]=0;d[0]<=y[i];d[0]++)for(d[1]=0;d[1]<=y[i];d[1]++)if(y[j]<2||d[1]==y[i]||d[1]!=d[0])//判断是否是合法情况 
            {
                for(d[2]=0;d[2]<=y[i];d[2]++)if(y[j]<3||d[2]==y[i]||d[2]!=d[0]&&d[2]!=d[1])//判断是否是合法情况 
                {
                    for(d[3]=0;d[3]<=y[i];d[3]++)if(y[j]<4||d[3]==y[i]||d[3]!=d[0]&&d[3]!=d[1]&&d[3]!=d[2])//判断是否是合法情况 
                    {
                        for(k=l=0,m=z[j];k<4;k++)//统计其他颜色块数与同色相邻对数 
                        {
                            l+=d[k]==y[i];
                            m+=x[i][k]==d[x[j][k]];
                        }
                        l=A(C-y[i],l);//计算这种转移的系数 
                        for(k=0;k+m<=K;k++)a.a[k*15+i][(k+m)*15+j]=((ll)a.a[k*15+i][(k+m)*15+j]+l)%P;//更新矩阵 
                        if(y[j]<4)break;//不能继续，返回 
                    }
                    if(y[j]<3)break;//不能继续，返回 
                }
                if(y[j]<2)break;//不能继续，返回 
            }
            for(i=0;i<=15*(K+1);i++)a.a[i][15*(K+1)]=1;
            for(i=0;i<15;i++)if(z[i]<=K)s.a[0][z[i]*15+i]=A(C,y[i]);//初始状态 
            for(;H;H>>=1,a*=a)if(H&1)s*=a;//矩阵快速幂 
            return s.a[0][15*(K+1)];
        }
};