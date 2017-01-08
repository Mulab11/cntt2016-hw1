#include<bits/stdc++.h>
using namespace std;
int a[50],n,m,i,j,ans=-1,u[2500],v[2500],S;
bool b[50];
void dfs(int x,int s,int S)//搜索求解 
{
    if(S<ans||s*3<n*2)return;//剪枝 
    if(x==m)
    {
        ans=S;//更新答案 
        return;
    }
    if(!b[u[x]]||!b[v[x]])//已经删掉了一个点 
    {
        dfs(x+1,s,S);
        return;
    }
    b[u[x]]=0;//删掉u[x] 
    dfs(x+1,s-1,S-a[u[x]]);
    b[u[x]]=1;
    b[v[x]]=0;//删掉v[x] 
    dfs(x+1,s-1,S-a[v[x]]);
    b[v[x]]=1;
}
class MagicMolecule
{
    public:
        int maxMagicPower(vector <int> magicPower, vector <string> magicBond)
        {
            n=magicPower.size();
            for(i=0;i<n;b[i++]=1)S+=a[i]=magicPower[i];//初始状态所有点都被选了 
            for(i=0;i<n;i++)for(j=0;j<i;j++)if(magicBond[i][j]=='N')//求出所有不在图中的边 
            {
                u[m]=i;
                v[m++]=j;
            }
            dfs(0,n,S);
            return ans;
        }
};