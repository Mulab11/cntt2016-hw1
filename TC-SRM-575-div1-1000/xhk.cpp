// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheTilesDivOne.cpp"
#include<bits/stdc++.h>
using namespace std;

const int maxn=10000,maxe=100000,inf=1e9;

struct edge
{int u,v,f,next;
};
struct edge e[2*maxe+10];

int num,maxflow;
int head[maxn+10],dis[maxn+10],gap[maxn+10],pre[maxn+10],mf[maxn+10],p1[maxn+10];

int n,m;
int a[110][110],v[4][2]={0,1,0,-1,1,0,-1,0};

void add(int u,int v,int f)
{e[num].u=u;
 e[num].v=v;
 e[num].f=f;
 e[num].next=head[u];
 head[u]=num;
 num++;
 e[num].u=v;
 e[num].v=u;
 e[num].f=0;
 e[num].next=head[v];
 head[v]=num;
 num++;
}

void change(int T)
{int j;
 j=pre[T];
 while(j!=-1)
 {	e[j].f-=mf[T];
 	e[j^1].f+=mf[T];
 	j=pre[e[j].u];
 }
}

void sap(int S,int T,int N)
{int i,j,md,me,flag;
 
 memset(pre,-1,sizeof(pre));
 memset(dis,0,sizeof(dis));
 memset(gap,0,sizeof(gap));
 gap[0]=N;
 for(i=1;i<=N;i++) p1[i]=head[i];
 i=S;
 mf[S]=inf;
 while(dis[i]<=N)
 {	j=p1[i];
 	flag=0;
 	while(j!=-1)
 	{	if(e[j].f>0 && dis[e[j].v]==dis[i]-1)
 		{	p1[i]=j;
 			pre[e[j].v]=j;
 			mf[e[j].v]=min(mf[i],e[j].f);
			i=e[j].v;
 			flag=1;
			if(i==T)
 			{	change(T);
 				maxflow+=mf[T];
 				i=S;
 			}
 			break;
 		}
 		j=e[j].next;
 	}
 	if(!flag)
 	{	md=N+1;
 		me=0;
 		j=head[i];
 		while(j!=-1)
 		{	if(e[j].f>0 && dis[e[j].v]<md)
 			{	md=dis[e[j].v];
 				me=j;
 			}
 			j=e[j].next;
 		}
 		gap[dis[i]]--;
 		if(gap[dis[i]]==0) return;
 		dis[i]=md+1;
 		gap[dis[i]]++;
 		p1[i]=me;
 		if(i!=S) i=e[pre[i]].u;
 	}
 }
}

class TheTilesDivOne
{	public:
	int find(vector <string> board)
	{	int i,j,k,x,y;
		
		n=board.size();
		m=board[0].length();
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(board[i-1][j-1]=='X')
					a[i][j]=1;
				else
					a[i][j]=0;
		num=0;
		memset(head,-1,sizeof(head));			
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{	if(a[i][j]) continue;
				if(!((i+j)&1))
					add(1+(i-1)*m+j,1+n*m+(i-1)*m+j,1);
				else
				{	for(k=0;k<4;k++)
					{	x=i+v[k][0];
						y=j+v[k][1];
						if(x<=0 || x>n || y<=0 || y>m || a[x][y]) continue;
						if(i&1)
							add(1+(i-1)*m+j,1+(x-1)*m+y,1);
						else
							add(1+n*m+(x-1)*m+y,1+(i-1)*m+j,1);
					}
					if(i&1)
						add(1,1+(i-1)*m+j,1);
					else
						add(1+(i-1)*m+j,1+n*m+n*m+1,1);
				}
			}
		maxflow=0;
		sap(1,1+n*m+n*m+1,1+n*m+n*m+1);
		return maxflow;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"X.X",
 "...",
 "X.X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, find(Arg0)); }
	void test_case_1() { string Arr0[] = {"...",
 "...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, find(Arg0)); }
	void test_case_2() { string Arr0[] = {"......X.X.XXX.X.XX."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, find(Arg0)); }
	void test_case_3() { string Arr0[] = {"X.....XXX.XX..XXXXXXXXX...X.XX.XX....X",
 ".XXXX..X..XXXXXXXX....XX.X.X.X.....XXX",
 "....XX....X.XX..X.X...XX.X..XXXXXXX..X",
 "XX.XXXXX.X.X..X..XX.XXX..XX...XXX.X..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(3, Arg1, find(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TheTilesDivOne ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
