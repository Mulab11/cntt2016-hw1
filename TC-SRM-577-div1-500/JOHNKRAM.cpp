#include<bits/stdc++.h>
using namespace std;
int f[16][16][16][16],i,j;
bool b[16][16];
int A(int x)
{
    if(x<0)return -x;
    return x;
}
int ask(int l1,int l2,int r1,int r2,int xi,int yi,int xa,int ya)//求在[xi,xa][yi,ya]的矩形内最后取在[l1,r1][l2,r2]矩形内的点的代价 
{
    int i,j,k;
    for(i=l1,k=0;i<=r1;i++)for(j=l2;j<=r2;j++)if(b[i][j])k+=max(max(A(i-xi),A(i-xa)),max(A(j-yi),A(j-ya)));
    return k;
}
int work(int xi,int yi,int xa,int ya)//记忆化搜索 
{
    if(~f[xi][yi][xa][ya])return f[xi][yi][xa][ya];
    if(xi==xa&&yi==ya)return f[xi][yi][xa][ya]=0;//一个格子 
    f[xi][yi][xa][ya]=1000000000;
    if(xi<xa)f[xi][yi][xa][ya]=min(f[xi][yi][xa][ya],min(work(xi+1,yi,xa,ya)+ask(xi,yi,xi,ya,xi,yi,xa,ya),work(xi,yi,xa-1,ya)+ask(xa,yi,xa,ya,xi,yi,xa,ya)));//上下最后取 
    if(yi<ya)f[xi][yi][xa][ya]=min(f[xi][yi][xa][ya],min(work(xi,yi+1,xa,ya)+ask(xi,yi,xa,yi,xi,yi,xa,ya),work(xi,yi,xa,ya-1)+ask(xi,ya,xa,ya,xi,yi,xa,ya)));//左右最后取 
    return f[xi][yi][xa][ya];
}
class EllysChessboard
{
    public:
        int minCost(vector <string> board)
        {
            memset(f,-1,sizeof(f));
            for(i=0;i<8;i++)for(j=0;j<8;j++)b[i+j][i-j+8]=board[i][j]=='#';//坐标变换 
            return work(0,0,15,15);
        }
};