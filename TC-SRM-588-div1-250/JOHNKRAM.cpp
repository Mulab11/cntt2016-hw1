#include<bits/stdc++.h>
using namespace std;
struct node
{
    int a,b;
    bool operator<(const node& y)const
    {
        return a<y.a;
    }
}a[105];
int n,i,j,k,f[105][105],ans;
class GUMIAndSongsDiv1
{
    public:
        int maxSongs(vector <int> duration, vector <int> tone, int T)
        {
            n=duration.size();
            for(i=0;i<n;i++)
            {
                a[i+1].a=tone[i];
                a[i+1].b=duration[i];
            }
            sort(a+1,a+n+1);
            memset(f,63,sizeof(f));
            for(i=1;i<=n;i++)if((f[i][1]=a[i].b)<=T)for(ans=max(ans,1),j=2;j<=i;j++)
            {
                for(k=j-1;k<i;k++)f[i][j]=min(f[i][j],f[k][j-1]+a[i].a+a[i].b-a[k].a);
                if(f[i][j]<=T)ans=max(ans,j);
                else break;
            }
            return ans;
        }
};
