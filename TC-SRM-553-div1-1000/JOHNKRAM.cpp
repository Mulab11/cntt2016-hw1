#include<bits/stdc++.h>
using namespace std;
long long d[55][55][105],l,r,oo;
int i,j,k,x,y,m=51;
inline void add(int u,int v,int x,long long w)//更新最短路 
{
    d[u][v][x+m]=min(d[u][v][x+m],w);
}
class YamanoteLine
{
    public:
        long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2)
        {
            memset(d,63,sizeof(d));
            r=oo=d[0][0][0];
            for(i=0;i<=n;i++)add(i,i,0,0);
            for(i=0;i<n;i++)add(i+1,i,0,-1);//固有限制 
            add(0,n,1,0);
            add(n,0,-1,0);
            for(i=0;i<s1.size();i++)add(t1[i],s1[i],s1[i]>t1[i],-l1[i]);//第一类约束 
            for(i=0;i<s2.size();i++)add(s2[i],t2[i],-(s2[i]>t2[i]),l2[i]);//第二类约束 
            for(k=0;k<=n;k++)for(i=0;i<=n;i++)for(x=-m;x<=m;x++)if(d[i][k][x+m]!=oo)for(j=0;j<=n;j++)for(y=-m;y<=m;y++)if(d[k][j][y+m]!=oo&&x+y+m>=0&&x+y<=m)add(i,j,x+y,d[i][k][x+m]+d[k][j][y+m]);//Floyd解差分约束 
            l=n;
            for(i=0;i<=n;i++)for(x=-m;x<=m;x++)if(x)
            {
                if(d[i][i][x+m]!=oo)if(x>0)l=max(l,(-d[i][i][x+m]-1)/x+1);//x系数为正的环 
                else r=min(r,d[i][i][x+m]/(-x));//x系数为负的环 
            }
            else if(d[i][i][x+m]<0)return 0;//x系数为0的环 
            if(r<l)return 0;//判断是否无解 
            if(r==oo)return -1;//判断是否无上界 
            return r-l+1;
        }
};