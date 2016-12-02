#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,k,l,o,p,x[35][35],y[35][35],a[35][1805],b[35][1805],c[35][1805],d[35][1805],ans=-1;
class FoxAndFlowerShopDivOne
{
    public:
        int theMaxFlowers(vector <string> flowers, int maxDiff)
        {
            n=flowers.size();
            m=flowers[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)
            {
                if(flowers[i][j]!='.')
                {
                    y[i+1][j+1]=1;
                    if(flowers[i][j]=='L')x[i+1][j+1]=1;
                    else x[i+1][j+1]=-1;
                }
                x[i+1][j+1]+=x[i+1][j]+x[i][j+1]-x[i][j];//预处理二维前缀百合花数减牵牛花数 
                y[i+1][j+1]+=y[i+1][j]+y[i][j+1]-y[i][j];//预处理二维前缀花数 
            }
            memset(a,-1,sizeof(a));
            memset(b,-1,sizeof(b));
            memset(c,-1,sizeof(c));
            memset(d,-1,sizeof(d));
            for(i=1;i<=n;i++)for(j=1;j<=m;j++)for(k=i;k<=n;k++)for(l=j;l<=m;l++)
            {
                p=x[k][l]-x[i-1][l]-x[k][j-1]+x[i-1][j-1];
                o=y[k][l]-y[i-1][l]-y[k][j-1]+y[i-1][j-1];
                a[k][p+n*m]=max(a[k][p+n*m],o);//更新以第k行为下界，百合花数减牵牛花数为p的矩形最大花数 
                b[l][p+n*m]=max(b[l][p+n*m],o);//更新以第l列为右界，百合花数减牵牛花数为p的矩形最大花数 
                c[i][p+n*m]=max(c[i][p+n*m],o);//更新以第i行为上界，百合花数减牵牛花数为p的矩形最大花数 
                d[j][p+n*m]=max(d[j][p+n*m],o);//更新以第j列为左界，百合花数减牵牛花数为p的矩形最大花数 
            }
            for(i=1;i<=n;i++)for(j=0;j<=n*m<<1;j++)a[i][j]=max(a[i][j],a[i-1][j]);//计算下界不超过第i行，百合花数减牵牛花数为p的矩形最大花数 
            for(i=1;i<=m;i++)for(j=0;j<=n*m<<1;j++)b[i][j]=max(b[i][j],b[i-1][j]);//计算右界不超过第i列，百合花数减牵牛花数为p的矩形最大花数 
            for(i=n;i;i--)for(j=0;j<=n*m<<1;j++)c[i][j]=max(c[i][j],c[i+1][j]);//计算上界不超过第i行，百合花数减牵牛花数为p的矩形最大花数 
            for(i=m;i;i--)for(j=0;j<=n*m<<1;j++)d[i][j]=max(d[i][j],d[i+1][j]);//计算左界不超过第i列，百合花数减牵牛花数为p的矩形最大花数 
            for(i=0;i<=n;i++)for(j=0;j<=n*m<<1;j++)for(k=0;k<=n*m<<1;k++)if(j+k-(n*m<<1)>=-maxDiff&&j+k-(n*m<<1)<=maxDiff&&~a[i][j]&&~c[i+1][k])ans=max(ans,a[i][j]+c[i+1][k]);//计算纵坐标不相交矩形的答案 
            for(i=0;i<=m;i++)for(j=0;j<=n*m<<1;j++)for(k=0;k<=n*m<<1;k++)if(j+k-(n*m<<1)>=-maxDiff&&j+k-(n*m<<1)<=maxDiff&&~b[i][j]&&~d[i+1][k])ans=max(ans,b[i][j]+d[i+1][k]);//计算横坐标不相交矩形的答案 
            return ans;
        }
};