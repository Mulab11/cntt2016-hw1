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

int color[2510],head[2510],n,ecnt;

struct edge
{
    int to,next;
}e[100010];

int f(int x,int y) {return x*n+y;}

void push(int k,int x,int y)
{
    e[k].to=y;e[k].next=head[x];head[x]=k;
}

void addedge(int x,int y)
{
    push(ecnt++,x,y);push(ecnt++,y,x);
}

bool dfs(int k)
{
    int p=head[k];
    while (p!=-1)
    {
        if (!color[e[p].to])
        {
            color[e[p].to]=3-color[k];
            if (!dfs(e[p].to)) return 0;
        }
        else
            if (color[k]==color[e[p].to]) return 0;
        p=e[p].next;
    }
    return 1;
}

struct HexagonalBoard 
{
    int minColors(vector <string> board)
    {
        n=board.size();
        bool ok=1;
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                if (board[i][j]=='X') ok=0;
        if (ok) return 0;
        ok=1;ecnt=0;
        for (int i=0;i<n*n;i++) head[i]=-1;
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                if (board[i][j]=='X')
                {
                    if (i<n-1&&board[i+1][j]=='X')
                    {
                        ok=0;addedge(f(i,j),f(i+1,j));
                    }
                    if (i<n-1&&j&&board[i+1][j-1]=='X')
                    {
                        ok=0;addedge(f(i,j),f(i+1,j-1));
                    }
                    if (j<n-1&&board[i][j+1]=='X')
                    {
                        ok=0;addedge(f(i,j),f(i,j+1));
                    }
                }
        if (ok) return 1;
        for (int i=0;i<n*n;i++)
            if (!color[i])
            {
                color[i]=1;
                if (!dfs(i)) return 3;
            }
        return 2;
    }
};
