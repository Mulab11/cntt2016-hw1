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

#define get(a,b) (a*m+b)

const int maxn=26*26*3;
const int maxm=maxn*20;
const int INF=0x3f3f3f3f;

int s,t,en,cost,q[maxn],dist[maxn],f[maxn],bx[5],by[5];

bool use[maxn];

struct edge
{
		int e,f,d;
		edge *next,*op;
}*v[maxn],ed[maxm],*fe[maxn];

void add_edge(int s,int e,int f,int d)
{
		en++;
		ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;v[s]->f=f;v[s]->d=d;
		en++;
		ed[en].next=v[e];v[e]=ed+en;v[e]->e=s;v[e]->f=0;v[e]->d=-d;
		v[s]->op=v[e];v[e]->op=v[s];
}

bool spfa()
{
		int front=1,tail=2;
		q[1]=s;
		use[s]=true;
		memset(dist,0x3f,sizeof(dist));
		dist[s]=0;
		for (;front!=tail;)
		{
				int now=q[front++];
				if (front==maxn) front=0;
				use[now]=false;
				for (edge *e=v[now];e;e=e->next)
						if (e->f && dist[e->e]>dist[now]+e->d)
						{
								dist[e->e]=dist[now]+e->d;
								f[e->e]=now;
								fe[e->e]=e;
								if (!use[e->e])
								{
										q[tail++]=e->e;
										if (tail==maxn) tail=0;
										use[e->e]=true;
								}
						}
		}
		return dist[t]!=INF;
}

int agument()
{
		int delta=INF;
		for (int p=t;p!=s;p=f[p])
				delta=min(delta,fe[p]->f);
		for (int p=t;p!=s;p=f[p])
		{
				fe[p]->f-=delta;
				fe[p]->op->f+=delta;
		}
		cost+=delta*dist[t];
		return delta;
}

int flow()
{
		int ans=0;
		while (spfa())
				ans+=agument();
		return ans;
}

class CurvyonRails {
		public:
				int getmin(vector <string> field) {
						bx[1]=1;bx[2]=-1;by[3]=1;by[4]=-1;
						int n=field.size();
						int m=field[0].size();
						en=0;
						memset(v,0,sizeof(v));
						int sum=0,cnt=0;
						s=n*m*3;t=s+1;
						for (int a=0;a<n;a++)
								for (int b=0;b<m;b++)
										if (field[a][b]!='w')
										{
												if (!((a+b)&1))
												{
														cnt++;
														sum+=2;
														add_edge(s,get(a,b),2,0);
														add_edge(get(a,b),get(a,b)+n*m,1,0);add_edge(get(a,b),get(a,b)+2*n*m,1,0);
														add_edge(get(a,b),get(a,b)+n*m,1,field[a][b]=='C');add_edge(get(a,b),get(a,b)+2*n*m,1,field[a][b]=='C');
														for (int c=1;c<=4;c++)
														{
																int x=a+bx[c];
																int y=b+by[c];
																if (x>=0 && x<n && y>=0 && y<m && field[x][y]!='w')
																{
																		if (x==a) add_edge(get(a,b)+n*m,get(x,y)+n*m,1,0);
																		else add_edge(get(a,b)+2*n*m,get(x,y)+2*n*m,1,0);
																}
														}
												}
												else
												{
														cnt--;
														add_edge(get(a,b),t,2,0);
														add_edge(get(a,b)+n*m,get(a,b),1,0);add_edge(get(a,b)+n*m*2,get(a,b),1,0);
														add_edge(get(a,b)+n*m,get(a,b),1,field[a][b]=='C');add_edge(get(a,b)+n*m*2,get(a,b),1,field[a][b]=='C');
												}
										}
						if (cnt!=0) return -1;
						cost=0;
						if (flow()==sum) return cost;
						else return -1;
				}
};


