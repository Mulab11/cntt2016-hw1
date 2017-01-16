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

int d[55][55];
bool v[55][55];

struct ArcadeManao
{
    int shortestLadder(vector <string> level, int coinRow, int coinColumn)
    {
        int n=level.size(),m=level[0].size();
        for (int i=1;i<n;i++)
            for (int j=1;j<=m;j++)
                d[i][j]=n;
        for (int j=1;j<=m;j++) d[n][j]=0;
        memset(v,0,sizeof(v));
        while (1)
        {
            int x=-1,y;
            for (int i=1;i<=n;i++)
                for (int j=1;j<=m;j++)
                    if ((!v[i][j])&&(x==-1||d[i][j]<d[x][y])) {x=i;y=j;}
            v[x][y]=1;
            if (x==coinRow&&y==coinColumn) return d[x][y];
            for (int k=1;k<=n;k++)
                if (level[k-1][y-1]=='X') d[k][y]=min(d[k][y],max(d[x][y],abs(x-k)));
            int k=y-1;
            while (k&&level[x-1][k-1]=='X') {d[x][k]=min(d[x][k],d[x][y]);k--;}
            k=y+1;
            while (k<=m&&level[x-1][k-1]=='X') {d[x][k]=min(d[x][k],d[x][y]);k--;}
        }
    }
};
