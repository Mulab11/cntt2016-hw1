#include<bits/stdc++.h>
using namespace std;
#define pb push_back
vector<int> x,y;
class HyperKnight
{
    public:
        long long countCells(int a, int b, int numRows, int numColumns, int k)
        {
            int dx[8]={a,a,-a,-a,b,b,-b,-b},dy[8]={b,-b,b,-b,a,-a,a,-a},i,j,o,l,n,m;
            long long ans=0;
            x.pb(0);
            x.pb(a);
            x.pb(b);
            x.pb(numRows-a);
            x.pb(numRows-b);
            x.pb(numRows);
            y.pb(0);
            y.pb(a);
            y.pb(b);
            y.pb(numColumns-a);
            y.pb(numColumns-b);
            y.pb(numColumns);
            sort(x.begin(),x.end());
            x.resize(n=unique(x.begin(),x.end())-x.begin());//求出每一段答案相同的横坐标区间的端点 
            sort(y.begin(),y.end());
            y.resize(m=unique(y.begin(),y.end())-y.begin());//求出每一段答案相同的纵坐标区间的端点 
            for(i=0;i+1<n;i++)for(j=0;j+1<m;j++)//枚举横纵坐标分别在哪一段区间内 
            {
                for(o=l=0;o<8;o++)if(x[i]+dx[o]>=0&&x[i]+dx[o]<numRows&&y[j]+dy[o]>=0&&y[j]+dy[o]<numColumns)l++;//统计走法 
                if(k==l)ans+=(long long)(x[i+1]-x[i])*(y[j+1]-y[j]);//计算答案 
            }
            return ans;
        }
};