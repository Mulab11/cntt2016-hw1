#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define PII pair<int,int>
#define PPP pair<PII,PII>
#define P 1000000009
const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};
int n,m,i,j,N,a[50][50],p[2000],d[2000],ans;
bool b[50][50],c=1;
PPP x;
map<PPP,int> s;
int move(int x,int y,int z)//计算向z方向移动到达的点的标号 
{
    return b[x+dx[z]][y+dy[z]]?a[x+dx[z]][y+dy[z]]:a[x][y];
}
class CoinsGame
{
    public:
        int ways(vector <string> board)
        {
            n=board.size();
            m=board[0].size();
            memset(b,1,sizeof(b));
            for(i=p[0]=1;i<2000;i++)//预处理2的幂次 
            {
                p[i]=p[i-1]<<1;
                if(p[i]>=P)p[i]-=P;
            }
            for(i=0;i<n;i++)for(j=0;j<m;j++)N+=b[i+1][j+1]=a[i+1][j+1]=board[i][j]=='.';//计算初始标号 
            ans=p[N]-1;
            while(c)
            {
                s.clear();//预处理 
                N=c=0;
                for(i=1;i<=n;i++)for(j=1;j<=m;j++)if(a[i][j])
                {
                    x=mp(mp(move(i,j,0),move(i,j,1)),mp(move(i,j,2),move(i,j,3)));//计算四元组 
                    if(!s[x])s[x]=++N;//计算新标号 
                    if(s[x]!=a[i][j])c=1;//判断是否有标号变化 
                    a[i][j]=s[x];//更新标号 
                }
            }
            for(i=1;i<=n;i++)for(j=1;j<=m;j++)d[a[i][j]]++;//统计每组个数 
            for(i=1;i<2000;i++)ans=(ans-p[d[i]]+1+P)%P;//计算答案 
            return ans;
        }
};