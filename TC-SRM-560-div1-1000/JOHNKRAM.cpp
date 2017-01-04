#include<bits/stdc++.h>
using namespace std;
#define eps 1e-7
bitset<13> b[13],o;
bool z[13];
int x[13],y[13],n;
double a[13],A[13],ans;
void dfs(int N,double S,int s,bitset<13> B)//搜索情况 
{
    int i,j;
    if(N==n)
    {
        if(!s)return;
        for(i=0;i<n;i++)A[i]=a[i];
        for(i=0;i<n;i++)if(z[i])for(j=0;j<n;j++)if(!z[j]&&b[i][j])//计算差值 
        {
            A[i]+=A[j];
            S-=A[j];
        }
        for(i=0;i<n;i++)if(z[i])A[i]+=S/s;//计算准确值 
        for(i=0;i<n;i++)if(A[i]<x[i]-eps||A[i]>y[i]+eps)return;//判断是否在合法范围内 
        double k=0;
        for(i=0;i<n;i++)for(j=i+1;j<n;j++)if(b[i][j])k+=A[i]*A[j];//计算结果 
        ans=max(ans,k);//计算答案 
        return;
    }
    z[N]=1;
    if(B[N])dfs(N+1,S,s+1,B&b[N]);//其他值 
    z[N]=0;
    a[N]=x[N];
    dfs(N+1,S-a[N],s,B);//最小值 
    a[N]=y[N];
    dfs(N+1,S-a[N],s,B);//最大值 
    a[N]=0;
}
class BoundedOptimization
{
    public:
        double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum)
        {
            string s;
            n=lowerBound.size();
            int m=expr.size(),i,j;
            for(i=0;i<m;i++)s+=expr[i];
            m=s.size();
            for(i=0;i<m;i+=3)b[s[i]-'a'][s[i+1]-'a']=b[s[i+1]-'a'][s[i]-'a']=1;//转换成矩阵格式 
            for(i=j=0;i<n;i++)
            {
                x[i]=lowerBound[i];
                j+=y[i]=upperBound[i];
                o[i]=1;
            }
            maxSum=min(maxSum,j);
            dfs(0,maxSum,0,o);//计算答案 
            return ans;
        }
};