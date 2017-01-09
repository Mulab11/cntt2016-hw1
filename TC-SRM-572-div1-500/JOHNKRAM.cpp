#include<bits/stdc++.h>
using namespace std;
int n,m,i,N,M=1,X,a[50],b[50],t[500005][10],w[500005],d[500005],A;
string c[50],s,S[10005],ans;
void dfs(int x)//搜索前半段 
{
    if(x==N)
    {
        int i,j;
        for(i=0,j=1;i<n;j=t[j][a[i++]])if(!t[j][a[i]])t[j][a[i]]=++M;//插入Trie树 
        d[j]++;
        S[w[j]=++X]=s;
        return;
    }
    int j;
    for(char i='0';i<='9';i++)
    {
        s+=i;
        for(j=0;j<n;j++)a[j]+=c[j][x]==s[x];
        for(j=0;j<n;j++)if(a[j]>b[j])break;//剪枝 
        if(j==n)dfs(x+1);
        for(j=0;j<n;j++)a[j]-=c[j][x]==s[x];
        s.pop_back();
    }
}
void work(int x)//搜索后半段 
{
    if(x+N==m)
    {
        int i,j;
        for(i=0;i<n;i++)a[i]=b[i]-a[i];
        for(i=0,j=1;i<n;j=t[j][a[i++]]);//在Trie树上查找 
        for(i=0;i<n;i++)a[i]=b[i]-a[i];
        if(j)
        {
            A+=d[j];//统计个数 
            ans=S[w[j]]+s;//计算答案 
        }
        return;
    }
    int j;
    for(char i='0';i<='9';i++)
    {
        s+=i;
        for(j=0;j<n;j++)a[j]+=c[j][x+N]==s[x];
        for(j=0;j<n;j++)if(a[j]>b[j])break;//剪枝 
        if(j==n)work(x+1);
        for(j=0;j<n;j++)a[j]-=c[j][x+N]==s[x];
        s.pop_back();
    }
}
class EllysBulls
{
    public:
        string getNumber(vector <string> guesses, vector <int> bulls)
        {
            n=guesses.size();
            m=guesses[0].size();
            N=m>>1;
            for(i=0;i<n;i++)
            {
                c[i]=guesses[i];
                b[i]=bulls[i];
            }
            dfs(0);
            work(0);
            if(ans.empty())return "Liar";//无解 
            if(A>1)return "Ambiguity";//多解 
            return ans;
        }
};