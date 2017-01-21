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

const int INF=0x3f3f3f3f;

int s,t,depth[110],q[110],en;

struct edge
{
    int e,f;
    edge *next,*op;
}*v[110],ed[21000];

void add_edge(int s,int e,int f1,int f2)
{
    en++;
    ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;v[s]->f=f1;
    en++;
    ed[en].next=v[e];v[e]=ed+en;v[e]->e=s;v[e]->f=f2;
    v[s]->op=v[e];v[e]->op=v[s];
}

bool bfs()
{
    memset(depth,0,sizeof(depth));
    depth[s]=1;
    q[1]=s;
    int front=1,tail=1;
    for (;front<=tail;)
    {
        int now=q[front++];
        for (edge *e=v[now];e;e=e->next)
            if (e->f && !depth[e->e])
            {
                depth[e->e]=depth[now]+1;
                if (e->e==t) return true;
                q[++tail]=e->e;
            }
    }
    return false;
}

int dfs(int now,int cur_flow)
{
    if (now==t) return cur_flow;
    int rest=cur_flow;
    for (edge *e=v[now];e && rest;e=e->next)
        if (e->f && depth[e->e]==depth[now]+1)
        {
            int new_flow=dfs(e->e,min(rest,e->f));
            e->f-=new_flow;
            e->op->f+=new_flow;
            rest-=new_flow;
        }
    if (rest==cur_flow) depth[now]=-1;
    return cur_flow-rest;
}

int dinic()
{
    int ans=0;
    while (bfs())
        ans+=dfs(s,INF);
    return ans;
}

class OldBridges {
public:
    string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn) {
        int n=bridges.size();
        //a1++;a2++;b1++;b2++;
        an<<=1;bn<<=1;
        s=n;t=n+1;
        en=0;
        memset(v,0,sizeof(v));
        for (int a=0;a<n;a++)
            for (int b=a+1;b<n;b++)
                if (bridges[a][b]=='O') add_edge(a,b,2,2);
                else
                {
                    if (bridges[a][b]=='N') add_edge(a,b,INF,INF);
                }
        add_edge(s,a1,an,0);
        add_edge(a2,t,an,0);
        add_edge(s,b1,bn,0);
        add_edge(b2,t,bn,0);
        if (dinic()!=an+bn) return "No";
        swap(b1,b2);
        en=0;
        memset(v,0,sizeof(v));
        for (int a=0;a<n;a++)
            for (int b=a+1;b<n;b++)
                if (bridges[a][b]=='O') add_edge(a,b,2,2);
                else
                {
                    if (bridges[a][b]=='N') add_edge(a,b,INF,INF);
                }
        add_edge(s,a1,an,0);
        add_edge(a2,t,an,0);
        add_edge(s,b1,bn,0);
        add_edge(b2,t,bn,0);
        if (dinic()!=an+bn) return "No";
        return "Yes";
    }
};

