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

const int inf=1000000000;

int a[55],e[2510][2];
bool v[55];
int s,ans,cnt,n;

void dfs(int k,int res)
{
    if (k>cnt) {ans=min(ans,s);return;}
    if (v[e[k][0]]||v[e[k][1]])
        dfs(k+1,res);
    else
        if (res)
            for (int i=0;i<2;i++)
            {
                s+=a[e[k][i]];v[e[k][i]]=1;
                dfs(k+1,res-1);
                s-=a[e[k][i]];v[e[k][i]]=0;
            }
}

struct MagicMolecule 
{
    int maxMagicPower(vector <int> magicPower, vector <string> magicBond)
    {
        n=magicPower.size();cnt=0;
        for (int i=0;i<n;i++) a[i]=magicPower[i];
        for (int i=0;i<n;i++)
            for (int j=i+1;j<n;j++)
                if (magicBond[i][j]=='N')
                {
                    e[++cnt][0]=i;e[cnt][1]=j;
                }
        int m=1;
        while (3*m<2*n) m++;
        ans=inf;s=0;
        memset(v,0,sizeof(v));
        dfs(1,n-m);
        if (ans==inf) return -1;
        ans=-ans;
        for (int i=0;i<n;i++) ans+=a[i];
        return ans;
    }
};
