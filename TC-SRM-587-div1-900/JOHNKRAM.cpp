#include<bits/stdc++.h>
using namespace std;
int n,m,M,i,j,h[10005],ne[10005],p[10005],w[10005],c[10005];
vector<string> ans;
bool dfs(int x,int y)
{
    if(!~c[x])c[x]=y;
    else return c[x]==y;
    for(int i=h[x];i;i=ne[i])if(!dfs(p[i],y^w[i]))return 0;
    return 1;
}
class ThreeColorability
{
    public:
        vector <string> lexSmallest(vector <string> cells)
        {
            n=cells.size();
            m=cells[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)if(cells[i][j]!='?')
            {
                p[++M]=j;
                ne[M]=h[i+m];
                w[M]=cells[i][j]=='Z';
                h[i+m]=M;
                p[++M]=i+m;
                ne[M]=h[j];
                w[M]=cells[i][j]=='Z';
                h[j]=M;
            }
            memset(c,-1,sizeof(c));
            if(!dfs(m,0))return ans;
            for(i=0;i<n+m;i++)if(!~c[i]&&!dfs(i,i<m?0:c[0]))return ans;
            for(i=0;i<n;i++)for(ans.push_back(string()),j=0;j<m;j++)ans[i]+=c[i+m]^c[j]?'Z':'N';
            return ans;
        }
};
