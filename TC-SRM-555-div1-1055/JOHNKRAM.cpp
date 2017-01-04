#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a[1200],x[600],y[600],z[600],b[40],X;
bitset<36> B[36],O;
ll ans;
class MapGuessing
{
    public:
        void dfs(int x,int s,bitset<36> a)//容斥去重 
        {
            if(x==X)
            {
                ans+=(ll)s<<a.count();
                return;
            }
            if(x&&a.none())return;//剪枝保证复杂度 
            dfs(x+1,s,a);
            dfs(x+1,-s,a&B[x]);
        }
        long long countPatterns(string goal, vector <string> code)
        {
            int n=goal.size(),m=code.size(),N=0,i,j,k,l,r;
            string s="";
            for(i=0;i<m;i++)s+=code[i];
            m=s.size();
            //求出磁头初始位置区间及每次修改的信息 
            for(i=j=l=r=0;i<m;i++,l=min(l,j),r=max(r,j))if(s[i]=='<')j--;
            else if(s[i]=='>')j++;
            else
            {
                x[++N]=j;
                y[N]=s[i];
                z[N]=a[j+m];
                a[j+m]=N;
            }
            if(r>=l+n)return 0;
            for(i=0;i<n;i++)O[i]=1;
            X=n+l-r;
            for(i=-l;i+r<n;i++)//对于每个磁头初始位置，求出哪些位置可以任意赋值 
            {
                memset(b,-1,sizeof(b));
                for(j=1;j<=N;j++)b[i+x[j]]=y[j];
                for(j=k=m=0;j<n;j++)
                {
                    if(~b[j])m++;
                    if(b[j]==goal[j])k++;
                }
                for(j=N;j&&k!=m;j--)if(z[j])
                {
                    if(b[i+x[j]]==goal[i+x[j]])k--;
                    b[i+x[j]]=y[z[j]];
                    if(b[i+x[j]]==goal[i+x[j]])k++;
                }
                else
                {
                    m--;
                    if(b[i+x[j]]==goal[i+x[j]])k--;
                    b[i+x[j]]=-1;
                }
                for(j=0;j<n;j++)if(~b[j])B[i+l][j]=1;
            }
            ans=1LL<<n;
            dfs(0,-1,O);
            return ans;
        }
};