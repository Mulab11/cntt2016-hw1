#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

const int maxn=40;
const int d=37;

int en;

long long f[maxn][maxn<<1][2];

bool solve[maxn][2];

long long g[maxn][maxn<<1];

struct edge
{
    int e;
    edge *next;
}*v[maxn],ed[maxn<<1];

void add_edge(int s,int e)
{
    en++;
    ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;
}

void dfs(int now,int pre,int precol)
{
    if (solve[now][precol]) return;
    solve[now][precol]=true;
    for (int a=0;a<2;a++)
    {
        for (edge *e=v[now];e;e=e->next)
            if (e->e!=pre) dfs(e->e,now,a);
        memset(g,0,sizeof(g));
        if (a) g[0][d]=1;
        else
        {
            if (a==precol) g[0][-1+d]=1;
            else g[0][1+d]=1;
        }
        int cnt=0;
        for (edge *e=v[now];e;e=e->next)
            if (e->e!=pre)
            {
                for (int b=0;b<=d+d;b++)
                    if (f[e->e][b][a])
                        for (int c=0;c<=d+d;c++)
                            if (g[cnt][c]) g[cnt+1][c+b-d]+=g[cnt][c]*f[e->e][b][a];
                cnt++;
            }
        for (int b=0;b<=d+d;b++)
            f[now][b][precol]+=g[cnt][b];
    }
}

class CentaurCompany {
public:
    double getvalue(vector <int> a, vector <int> b) {
        en=0;
        memset(v,0,sizeof(v));
        int n=a.size();
        for (int c=0;c<n;c++)
            add_edge(a[c],b[c]),add_edge(b[c],a[c]);
        memset(solve,false,sizeof(solve));
        memset(f,0,sizeof(f));
        dfs(1,0,1);
        double ans=0;
        for (int a=0;a<=d+d;a++)
            ans+=(double)max(a-d-2,0)*f[1][a][1];
        ans*=2.0;
        n++;
        ans/=(1ll<<n);
        return ans;
    }
};


