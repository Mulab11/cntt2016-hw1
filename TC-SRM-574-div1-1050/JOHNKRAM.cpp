#include<bits/stdc++.h>
using namespace std;
const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};
int n,m,N,i,j,k,x,y,s,lx,rx,ly,ry,b[55][55],f[55][55][55],ans;
bool lu[55],ru[55],ld[55],rd[55],lr[55],z;
char c[55][55];
void dfs(int x,int y)//Flood-fill
{
    if(b[x][y])return;
    lx=min(lx,x);
    rx=max(rx,x);
    ly=min(ly,y);
    ry=max(ry,y);
    b[x][y]=N;
    s++;
    for(int i=0;i<4;i++)if(c[x+dx[i]][y+dy[i]]=='X')dfs(x+dx[i],y+dy[i]);
}
class Tunnels
{
    public:
        int minimumTunnels(vector <string> frame)
        {
            n=frame.size();
            m=frame[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)c[i+1][j+1]=frame[i][j];
            if(m==1)//m=1特判 
            {
                for(i=1;i<=n;i++)if(c[i][1]=='X')return 1;
                return 0;
            }
            for(i=1;i<=n;i++)for(j=1;j<=m;j++)if(c[i][j]=='X'&&!b[i][j])
            {
                N++;
                s=0;
                lx=rx=i;
                ly=ry=j;
                dfs(i,j);
                if(s==2&&ly==ry&&(ly==1||ry==m))//特殊情况1 
                {
                    if(lx==1)if(ly==1)ld[rx]=1;
                    else rd[rx]=1;
                    else if(ly==1)lu[lx]=1;
                    else ru[lx]=1;
                    continue;
                }
                if(ly==1)//更新左边 
                {
                    if(b[lx][ly]==N&&lx!=1&&(c[lx+1][ly]!='X'||c[lx][ly+1]!='X'))lu[lx]=1;
                    if(b[rx][ly]==N&&!lu[rx]&&(c[rx-1][ly]!='X'||c[rx][ly+1]!='X'))ld[rx]=1;
                }
                if(ry==m)//更新右边 
                {
                    if(b[lx][ry]==N&&lx!=1&&(c[lx+1][ry]!='X'||c[lx][ry-1]!='X'))ru[lx]=1;
                    if(b[rx][ry]==N&&!ru[rx]&&(c[rx-1][ry]!='X'||c[rx][ry-1]!='X'))rd[rx]=1;
                }
            }
            for(i=1;i<=m;i++)c[0][i]='.';
            for(i=1;i<=n;i++)//特殊情况2 
            {
                for(j=1;j<=m;j++)if(c[i][j]=='.'||c[i-1][j]!='.'||c[i+1][j]!='.')break;
                if(j>m)
                {
                    lr[i]=1;
                    lu[i]=ld[i]=ru[i]=rd[i]=0;
                }
            }
            memset(f,128,sizeof(f));
            f[n+1][0][0]=0;
            for(i=n;i;i--)for(j=0;j<=n;j++)for(k=0;k<=n;k++)if(f[i+1][j][k]>=0)for(x=-1;x<2;x++)for(y=-1;y<2;y++)if(j+x>=0&&k+y>=0)//动态规划 
            {
                z=1;//能否转移 
                if(lr[i])if(i==1)z=(!x&&!y)||(!x&&!~y)||(!~x&&!y);
                else z=x!=y&&(x==1||y==1);
                else
                {
                    if(lu[i])z=x==1;
                    else if(ld[i])z=x!=1;
                    else z=!x;
                    if(ru[i])z&=y==1;
                    else if(rd[i])z&=y!=1;
                    else z&=!y;
                }
                if(z)f[i][j+x][k+y]=max(f[i][j+x][k+y],f[i+1][j][k]+(!~x)+(!~y));//状态转移 
            }
            for(i=0;i<=n;i++)for(j=0;j<=n;j++)ans=max(ans,f[1][i][j]);//计算答案 
            return N-ans;
        }
};