#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll f[262144][18],ans;
int n,m,i,j,k,l,r,a[19];
class PolygonTraversal
{
    public:
        long long count(int N, vector <int> points)
        {
            n=N;
            m=points.size();
            for(;j<m;j++)i|=1<<points[j]-1;
            for(f[i][points[m-1]-1]=1;i<1<<n;i++)//枚举状态 
            {
                for(j=0;j<n;j++)a[j+1]=a[j]+(i>>j&1);
                for(j=0;j<n;j++)if(i>>j&1)for(k=0;k<n;k++)if(!(i>>k&1))//状态转移 
                {
                    l=min(j,k)+1;
                    r=max(j,k);
                    if(a[l]<a[r]&&a[l]+a[n]>a[r]+1)f[i|1<<k][k]+=f[i][j];//判断是否相交 
                }
            }
            for(i=0;i<n;i++)//计算答案 
            {
                for(j=0;j<3;j++)if(i==(points[0]+n-j)%n)break;
                if(j==3)ans+=f[(1<<n)-1][i];
            }
            return ans;
        }
};