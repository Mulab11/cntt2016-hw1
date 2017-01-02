#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,k,h[55],ne[2505],p[2505],a[10];
bool b[55];
void dfs(int x)//求哪些点与0连通 
{
    b[x]=1;
    for(int i=h[x];i;i=ne[i])if(!b[p[i]])dfs(p[i]);
}
class XorTravelingSalesman
{
    public:
        int maxProfit(vector <int> cityValues, vector <string> roads)
        {
            n=cityValues.size();
            for(i=0;i<n;i++)for(j=0;j<n;j++)if(roads[i][j]=='Y')//转成邻接表 
            {
                p[++m]=j;
                ne[m]=h[i];
                h[i]=m;
            }
            dfs(0);
            for(i=0;i<n;i++)if(b[i])for(j=9;~j;j--)if(cityValues[i]>>j&1)if(a[j])cityValues[i]^=a[j];//求线性基 
            else
            {
                a[j]=cityValues[i];
                for(k=j-1;~k;k--)if(a[j]>>k&1)a[j]^=a[k];
                for(k=j+1;k<10;k++)if(a[k]>>j&1)a[k]^=a[j];
                break;
            }
            for(i=j=0;i<10;i++)j^=a[i];//计算答案 
            return j;
        }
};