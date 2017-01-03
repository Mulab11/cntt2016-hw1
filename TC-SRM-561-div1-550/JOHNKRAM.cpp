#include<bits/stdc++.h>
using namespace std;
int n,N,i,j,k,f[55],h[55],ne[55],s[55],a[55],l[55],r[55],d[55],w[55],ans;
bool b[55];
void dfs(int x)//DFS求SG函数 
{
    w[l[x]=++N]=x;//DFS序 
    int i;
    for(i=h[x];i;i=ne[i])
    {
        dfs(i);
        s[x]^=a[i];
    }
    r[x]=N;//求出子树对应的区间 
    memset(b,0,sizeof(b));
    for(i=l[x];i<=r[x];i++)b[d[w[i]]^=s[x]]=1;//求出删掉每个点之后的SG值 
    for(i=0;;i++)if(!b[i])break;//SG=所有后续局面的SG的mex 
    a[x]=i;
    for(i=l[x];i<=r[x];i++)d[w[i]]^=a[x];//更新子树内结点的值 
}
class CirclesGame
{
    public:
        string whoCanWin(vector <int> x, vector <int> y, vector <int> r)
        {
            n=x.size();
            for(i=0;i<n;i++)//建树 
            {
                for(j=0,k=-1;j<n;j++)if(r[j]>r[i]&&(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<=r[j]*r[j]&&((!~k)||r[k]>r[j]))k=j;//求父亲结点 
                f[i+1]=k+1;
                ne[i+1]=h[k+1];
                h[k+1]=i+1;
            }
            for(i=1;i<=n;i++)if(!f[i])
            {
                dfs(i);
                ans^=a[i];//整体的SG等于所有树SG的异或 
            }
            if(ans)return "Alice";//判断是否先手必胜 
            return "Bob";
        }
};