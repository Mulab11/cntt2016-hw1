#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
int n,m,i,j,h[105],ne[10005],p[10005],w[10005],d[105],l,r,a1=1,a2=1;
bool b[105];
bool dfs(int x)//计算每个点与某个点的差并返回是否存在合法情况 
{
    b[x]=1;
    if(x<n)l=max(l,d[x]);
    else r=min(r,d[x]);
    for(int i=h[x];i;i=ne[i])if(!b[p[i]])
    {
        d[p[i]]=d[x]+w[i];
        if(!dfs(p[i]))return 0;
    }
    else if(d[p[i]]!=d[x]+w[i])return 0;
    return 1;
}
class EqualSums
{
    public:
        int count(vector <string> board)
        {
            n=board.size();
            for(i=0;i<n;i++)for(j=0;j<n;j++)if(board[i][j]!='-')//建图 
            {
                p[++m]=j+n;
                ne[m]=h[i];
                w[m]=board[i][j]-'0';
                h[i]=m;
                p[++m]=i;
                ne[m]=h[j+n];
                w[m]='0'-board[i][j];
                h[j+n]=m;
            }
            for(i=0;i<n;i++)if(!b[i])
            {
                l=-1000000000;
                r=1000000000;
                if(!dfs(i)||l>r)return 0;
                a1=(ll)a1*(r-l+1)%P;//最小值>=0
                a2=(ll)a2*(r-l)%P;//最小值>0
            }
            return (a1-a2+P)%P;//容斥原理计算答案 
        }
};