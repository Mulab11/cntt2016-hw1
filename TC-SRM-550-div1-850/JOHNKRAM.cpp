#include<bits/stdc++.h>
using namespace std;
#define P 1000000007
#define ll long long
ll t[80][80];
struct node
{
    int r,c,a[80][80];
    inline void operator*=(const node& y)//矩阵乘法 
    {
        int i,j,k;
        for(i=0;i<r;i++)for(j=0;j<y.c;j++)t[i][j]=0;
        for(i=0;i<r;i++)for(k=0;k<c;k++)for(j=0;j<y.c;j++)
        {
            t[i][j]+=(ll)a[i][k]*y.a[k][j];
            if((k&7)==7)t[i][j]%=P;
        }
        c=y.c;
        for(i=0;i<r;i++)for(j=0;j<c;j++)a[i][j]=t[i][j]%P;
    }
}A,S;
int x[11],y[11],n,i,j,k,m,N,a,b,z[12][12];
class ConversionMachine
{
    public:
        int countAll(string word1, string word2, vector <int> costs, int maxCost)
        {
            n=word1.size();
            for(i=0;i<n;i++)
            {
                x[i]=word1[i]-'a';
                y[i]=word2[i]-'a';
                for(j=x[i],k=0;j!=y[i];j=(j+1)%3)
                {
                    maxCost-=costs[j];//扣除必要代价 
                    if(maxCost<0)return 0;
                    k++;
                    m++;
                }
                if(k==1)b++;//计算有多少个位置距离为1 
                if(k==2)a++;//计算有多少个位置距离为2 
            }
            if(maxCost<0)return 0;
            m+=maxCost/(costs[0]+costs[1]+costs[2])*3;//计算最多操作次数 
            for(i=0;i<=n;i++)for(j=0;i+j<=n;j++)z[i][j]=N++;
            for(i=0;i<=n;i++)for(j=0;i+j<=n;j++)//计算转移矩阵 
            {
                k=n-i-j;
                if(i)A.a[z[i][j]][z[i-1][j+1]]=i;//操作的位置距离为2 
                if(j)A.a[z[i][j]][z[i][j-1]]=j;//操作的位置距离为1 
                if(k)A.a[z[i][j]][z[i+1][j]]=k;//操作的位置距离为0 
            }
            A.a[z[0][0]][N]=A.a[N][N]=1;//统计和 
            N++;
            A.r=A.c=S.c=N;
            S.r=1;
            S.a[0][z[a][b]]=1;//初始状态 
            for(m++;m;m>>=1,A*=A)if(m&1)S*=A;
            return S.a[0][N-1];
        }
};