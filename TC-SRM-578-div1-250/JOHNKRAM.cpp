#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
int Pow(int x,int y)
{
    int s=1;
    for(;y;y>>=1,x=(ll)x*x%P)if(y&1)s=(ll)s*x%P;
    return s;
}
int A(int x)
{
    if(x<0)return -x;
    return x;
}
char c[55][55];
int n,m,d,s,i,j,a[2];
bool b[55][55];
void dfs(int x,int y)//搜索所有距离不超过d的点 
{
    b[x][y]=1;
    s++;
    int i,j;
    for(i=1;i<=n;i++)for(j=1;j<=m;j++)if(!b[i][j]&&c[i][j]=='v'&&A(i-x)+A(j-y)<=d)dfs(i,j);
}
class GooseInZooDivOne
{
    public:
        int count(vector <string> field, int dist)
        {
            n=field.size();
            m=field[0].size();
            d=dist;
            for(i=0;i<n;i++)for(j=0;j<m;j++)c[i+1][j+1]=field[i][j];
            for(i=1;i<=n;i++)for(j=1;j<=m;j++)if(c[i][j]=='v'&&!b[i][j])//枚举初始点 
            {
                s=0;
                dfs(i,j);
                a[s&1]++;
            }
            return Pow(2,a[0]+max(a[1]-1,0))-1;//计算答案 
        }
};