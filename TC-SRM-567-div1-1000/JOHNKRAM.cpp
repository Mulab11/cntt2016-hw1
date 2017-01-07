#include<bits/stdc++.h>
using namespace std;
#define P 1000000009
#define vi vector<int>
map<int,int> s[10];
vi a,z;
vector<string> c;
int n,m;
int A(int x)
{
    if(x<0)return -x;
    return x;
}
int work(vi x,int t)//求第i行高度为x[i],当前山峰为t的方案数 
{
    if(!~t)return 1;
    int i=0,j,X=0;
    for(;i<m;i++)X=(X*666LL+x[i])%P;//Hash压缩状态 
    if(s[t].find(X)!=s[t].end())return s[t][X];//记忆化搜索 
    for(i=0;i<m;i++)//枚举在哪一列 
    {
        vi y=x;
        for(j=0;j<m;j++)
        {
            y[j]=max(y[j],a[t]-A(i-j));//求出新的高度 
            if((a[t]>x[j]+A(i-j))==(c[t][j]=='-'))break;//判断是否是合法方案 
        }
        if(j==m)s[t][X]=(s[t][X]+work(y,t-1))%P;//计算答案 
    }
    return s[t][X];
}
class Mountains
{
    public:
        int countPlacements(vector <int> heights, vector <string> visibility)
        {
            n=(a=heights).size();
            z.resize(m=(c=visibility)[0].size());
            return work(z,n-1);
        }
};