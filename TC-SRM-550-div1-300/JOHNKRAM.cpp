#include<bits/stdc++.h>
using namespace std;
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
#define N 2500
int a,b,c,d,x,y,z,n,i,j;
bool v[5005][5005];
class RotatingBot
{
    public:
        int minArea(vector <int> moves)
        {
            n=moves.size();
            for(v[N][N]=1;i<n;i++)//模拟每一次前进 
            {
                for(j=0;j<moves[i];j++)//模拟每一步 
                {
                    if(v[x+dx[z]+N][y+dy[z]+N])return -1;//判断是否重复经过格子 
                    x+=dx[z];
                    y+=dy[z];
                    v[x+N][y+N]=1;
                }
                if(!a&&x<0)a=x;//确定x下界 
                if(!b&&x>0)b=x;//确定x上界 
                if(!c&&y<0)c=y;//确定y下界 
                if(!d&&y>0)d=y;//确定y上界 
                if(x<a||x>b||y<c||y>d||i+1<n&&x+dx[z]>=a&&x+dx[z]<=b&&y+dy[z]>=c&&y+dy[z]<=d&&!v[x+dx[z]+N][y+dy[z]+N])return -1;//判断是否越界或非法转弯 
                z=z+1&3;//转弯 
            }
            return (b-a+1)*(d-c+1);//计算答案 
        }
};