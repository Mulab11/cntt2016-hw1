#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
const int x[]={0,0,2,3,2,5,3,7,2,3,5},y[]={0,0,1,1,2,1,1,1,3,2,1};
ll P=1000000009,t[20][20];
int i,j,p,n;
struct node
{
    int r,c;
    ll a[20][20];
    void operator*=(const node& b)//矩阵乘法 
    {
        memset(t,0,sizeof(t));
        int i,j,k;
        for(i=0;i<r;i++)for(k=0;k<c;k++)for(j=0;j<b.c;j++)t[i][j]=(t[i][j]+a[i][k]*b.a[k][j])%P;
        c=b.c;
        for(i=0;i<r;i++)for(j=0;j<c;j++)a[i][j]=t[i][j];
    }
}A,S,O,T;
node Pow(node a,int x)//矩阵快速幂 
{
    node s=O;
    for(;x;x>>=1,a*=a)if(x&1)s*=a;
    return s;
}
class MegaFactorial
{
    public:
        int countTrailingZeros(int N, int K, int B)
        {
            P*=y[B];
            p=x[B];
            S.r=S.c=A.r=A.c=O.r=O.c=n=K+1;
            A.a[0][0]=1;
            for(i=0;i<n;i++)O.a[i][i]=1;
            for(i=1;i<n;i++)for(j=i;j<n;j++)A.a[i][j]=1;//矩阵预处理 
            for(S=O;N;N/=p)
            {
                T=S;
                S=Pow(A,N%p);
                S*=T;//求Pow(A,N%P)*S 
                A=Pow(A,p);
                for(i=1;i<n;i++)A.a[0][i]++;//更新矩阵 
            }
            return S.a[0][K]/y[B];
        }
};