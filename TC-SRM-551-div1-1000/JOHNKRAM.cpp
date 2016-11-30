#include<bits/stdc++.h>
using namespace std;
#define P 1000000007
#define ll long long
struct node
{
    int a,b;
    inline bool operator<(const node& y)const
    {
        return a<y.a;
    }
}x[1048576],y[1048576];
int n,m,N,M,i,j,k,l,o,p,ans,a[50],s[50],a1[50],a2[50],c[50][50],d[50][50];
void dfs(node *A,int &n,int N,int r,int x,int y,int z)//搜索每种可能的选取情况 
{
    if(y>N)return;
    if(x==r)
    {
        A[n].a=y;
        A[n++].b=z;
        return;
    }
    dfs(A,n,N,r,x+1,y,z);
    if(~a[x])dfs(A,n,N,r,x+1,y+a[x],z+1);
}
int Pow(int x,int y)//快速幂 
{
    int s=1;
    for(;y;y>>=1,x=(ll)x*x%P)if(y&1)s=(ll)s*x%P;
    return s;
}
class SweetFruits
{
    public:
        int countTrees(vector <int> sweetness, int maxSweetness)
        {
            n=sweetness.size();
            for(i=0;i<n;i++)a[i]=sweetness[i];
            dfs(x,N,maxSweetness,n>>1,0,0,0);//搜索前半部分 
            dfs(y,M,maxSweetness,n,n>>1,0,0);//搜索后半部分 
            sort(x,x+N);
            sort(y,y+M);
            for(i=0;i<M;i++)s[y[i].b]++;
            for(i=0,j=M-1;i<N&&~j;i++)//meet in the middle计算第一部分答案 
            {
                for(;~j&&x[i].a+y[j].a>maxSweetness;--s[y[j--].b]);
                for(k=0;k<=n+1>>1;k++)//枚举后半部分选取的甜水果个数 
                {
                    a1[x[i].b+k]+=s[k];
                    if(a1[x[i].b+k]>=P)a1[x[i].b+k]-=P;
                }
            }
            for(i=0;i<n;i++)if(~a[i])m++;
            for(i=c[0][0]=1;i<=m;i++)for(j=c[i][0]=1;j<=i;j++)//预处理组合数 
            {
                c[i][j]=c[i-1][j]+c[i-1][j-1];
                if(c[i][j]>=P)c[i][j]-=P;
            }
            for(i=0;i<=m;i++)//计算第二部分答案 
            {
                for(j=0;j<n;j++)for(k=0;k<n;k++)if(j==k)d[j][k]=n-1;
                else d[j][k]=P-1;
                for(j=0;j<m;j++)for(k=max(i,j+1);k<m;k++)//预处理矩阵 
                {
                    d[j][k]=d[k][j]=0;
                    d[j][j]--;
                    d[k][k]--;
                }
                for(a2[i]=1,j=0;j+2<n;j++)//高斯消元 
                {
                    for(k=j;k+1<n;k++)if(d[k][j])break;
                    if(k+1==n)break;
                    if(j!=k)for(a2[i]=P-a2[i],l=j;l+1<n;l++)swap(d[j][l],d[k][l]);
                    for(o=Pow(d[j][j],P-2),k=j+1;k+1<n;k++)for(p=(ll)d[k][j]*o%P,l=j;l+1<n;l++)d[k][l]=(d[k][l]-(ll)d[j][l]*p%P+P)%P;
                }
                for(j=0;j+1<n;j++)a2[i]=(ll)a2[i]*d[j][j]%P;//计算行列式 
                for(j=0;j<i;j++)a2[i]=(a2[i]-(ll)c[i][j]*a2[j]%P+P)%P;//消去不合法部分 
            }
            for(i=0;i<=m;i++)ans=(ans+(ll)a1[i]*a2[i])%P;//计算答案 
            return ans;
        }
};