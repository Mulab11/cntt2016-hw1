#include <bits/stdc++.h>
using namespace std;
int n,m,mp[55][55],_mp[55][55],col[55];
vector<string> ans;
bool dfs(int u,int d)
{
    col[u]=d;
    for(int i=0;i<n;i++)
    if(mp[u][i]!=-1)
    {
        if(col[i]!=-1) 
        {
            if(col[i]==col[u]&&mp[u][i]==1) return 0;
            if(col[i]!=col[u]&&mp[u][i]==0) return 0;
        }
        else if(!dfs(i,d^mp[u][i])) return 0;
    }
    return 1;
}
bool check()
{
    memset(col,-1,sizeof(col));
    for(int i=0;i<n;i++) 
    if(col[i]==-1&&!dfs(i,0)) return 0;
    return 1;
}
class ThreeColorability
{
public:
    vector<string> lexSmallest(vector<string> s)
    {
        n=s.size(),m=s[0].length();
        memset(mp,-1,sizeof(mp));
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            for(int k=j+1;k<n;k++)
            if(s[j][i]!='?'&&s[k][i]!='?')
            {
                if(s[j][i]==s[k][i]) 
                {
                    if(mp[j][k]==1) return ans;
                    mp[j][k]=mp[k][j]=0;
                }
                else 
                {
                    if(mp[j][k]==0) return ans;
                    mp[j][k]=mp[k][j]=1;
                }
            }
        }
        //将确定关系的行连边，相同连0，不同连1.
        if(!check()) return ans;
        //判断是否有解
        for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        if(s[i][j]=='?')
        {
            bool flag=0;
            memcpy(_mp,mp,sizeof(mp));
            for(int k=0;k<n;k++)
            if(k!=i&&s[k][j]!='?')
            {
                if(s[k][j]=='N')
                {
                    if(mp[i][k]==1) {flag=1;break;}
                    mp[i][k]=mp[k][i]=0;
                }
                else 
                {
                    if(mp[i][k]==0) {flag=1;break;}
                    mp[i][k]=mp[k][i]=1;
                }
            }
            //试着填一个N并连边
            if(!flag&&check()) s[i][j]='N';
            else
            {
                memcpy(mp,_mp,sizeof(mp));
                s[i][j]='Z';
                for(int k=0;k<n;k++)
                if(k!=i&&s[k][j]!='?')
                {
                    if(s[k][j]=='Z') mp[i][k]=mp[k][i]=0;
                    else mp[i][k]=mp[k][i]=1;
                }
            	//不行的话恢复，再填Z，重新连边
            } 
        }
        return s;
    }
}; 
