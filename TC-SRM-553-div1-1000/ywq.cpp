#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const ll inf=1000000000000000ll;
const ll inf2=1000000000000ll;

int n;
ll f[55][55][105];

void addedge(int x,int y,int z,ll l)
{
    f[x][y][z+n]=min(f[x][y][z+n],l);
}

struct YamanoteLine 
{
    long long howMany(int n0, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2)
    {
        n=n0;
        for (int i=0;i<=n;i++)
            for (int j=0;j<=n;j++)
                for (int k=0;k<=2*n;k++)
                    f[i][j][k]=inf;
        for (int i=0;i<=n;i++) f[i][i][n]=0;
        for (int i=0;i<n;i++) addedge(i+1,i,0,-1);
        addedge(0,n,1,0);addedge(n,0,-1,0);
        int m=s1.size();
        for (int i=0;i<m;i++)
            if (s1[i]<t1[i]) addedge(t1[i],s1[i],0,-l1[i]); else addedge(t1[i],s1[i],1,-l1[i]);
        m=s2.size();
        for (int i=0;i<m;i++)
            if (s2[i]<t2[i]) addedge(s2[i],t2[i],0,l2[i]); else addedge(s2[i],t2[i],-1,l2[i]);
        //floyd
        for (int k=0;k<=n;k++)
            for (int i=0;i<=n;i++)
                for (int j=0;j<=n;j++)
                    for (int p=0;p<=2*n;p++)
                        for (int q=max(0,n-p);q<=min(2*n,3*n-p);q++)
                        {
                            int x=p+q-n;
                            f[i][j][x]=min(f[i][j][x],f[i][k][p]+f[k][j][q]);
                        }
        ll l=n,r=inf;
        for (int i=0;i<=n;i++) //enumerate the node on the circle
            for (int j=0;j<=2*n;j++) //enumerate the length of the circle
            {
                if (j<n) r=min(r,f[i][i][j]/(n-j));
                if (j==n&&f[i][i][j]<0) return 0;
                if (j>n) l=max(l,(-f[i][i][j]-1)/(j-n)+1);
            }
        if (l>r) return 0;
        if (r>=inf2) return -1;
        return r-l+1;
    }
};
