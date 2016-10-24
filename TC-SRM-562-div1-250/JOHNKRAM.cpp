#include<bits/stdc++.h>
using namespace std;
#define ll long long
class PastingPaintingDivOne
{
    public:
        vector<long long> countColors(vector<string> clipboard, int T)
        {
            int n=clipboard.size(),m=clipboard[0].size(),i,j,k;
            vector<ll> ans(3,0);
            ll a1=0,a2=0,a3=0;
            vector<string> a(n,string(m,'.'));
            vector<string> b;
            for(i=0;i<T;i++)//依次放下每一个矩形
            {
                if(a==b)//判断状态是否发生变化
                {
                    j=T-i;
                    ans[0]+=a1*j;
                    ans[1]+=a2*j;
                    ans[2]+=a3*j;
                    break;
                }
                b=a;
                a1=a2=a3=0;
                for(j=0;j+1<n;j++)for(k=0;k+1<m;k++)a[j][k]=a[j+1][k+1];
                for(j=0;j<n;j++)a[j][m-1]='.';
                for(k=0;k<m;k++)a[n-1][k]='.';
                for(j=0;j<n;j++)for(k=0;k<m;k++)//放下一个矩形
                {
                    a1-=a[j][k]=='R';
                    a2-=a[j][k]=='G';
                    a3-=a[j][k]=='B';
                    if(clipboard[j][k]!='.')a[j][k]=clipboard[j][k];
                    a1+=a[j][k]=='R';
                    a2+=a[j][k]=='G';
                    a3+=a[j][k]=='B';
                }
                ans[0]+=a1;
                ans[1]+=a2;
                ans[2]+=a3;
            }
            return ans;
        }
};
