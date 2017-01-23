// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndGo3.cpp"
#include<bits/stdc++.h>
using namespace std;


const int maxn=10000,maxe=100000,inf=1e9;

struct edge
{int u,v,f,next;
};
struct edge e[2*maxe+10];

int num,maxflow;
int head[maxn+10],dis[maxn+10],gap[maxn+10],pre[maxn+10],mf[maxn+10],p1[maxn+10];
int n,m,ans;
int v[4][2]={0,1,0,-1,1,0,-1,0};
char a[110][110];

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

void change(int T) //建反向边 
{int j;
 j=pre[T];
 while(j!=-1)
 {	e[j].f-=mf[T];
 	e[j^1].f+=mf[T];
 	j=pre[e[j].u];
 }
}

void sap(int S,int T,int N) //sap求最大流 
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

class FoxAndGo3
{	public:
	int maxEmptyCells(vector <string> board)
	{	int i,j,k,x,y;
		
		n=board.size();
		m=board[0].length();
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				a[i][j]=board[i-1][j-1];
		num=0;
		memset(head,-1,sizeof(head));
		ans=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{	if(a[i][j]=='o') //连边，如果选这个白的作为空格，周围的空格都要被填掉 
				{	add(1,1+(i-1)*m+j,1);
					for(k=0;k<4;k++)
					{	x=i+v[k][0];
						y=j+v[k][1];
						if(x>0 && x<=n && y>0 && y<=m && a[x][y]=='.')
							add(1+(i-1)*m+j,1+(x-1)*m+y,inf);
					}
					ans++;
				}
				else if(a[i][j]=='.')
				{	add(1+(i-1)*m+j,1+n*m+1,1);
					ans++;
				}
			}
		//cout<<ans<<endl;
		maxflow=0;
		sap(1,1+n*m+1,1+n*m+1); //最大流 
		ans-=maxflow;
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"o.o",
 ".o.",
 "o.o"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, maxEmptyCells(Arg0)); }
	void test_case_1() { string Arr0[] = {"...",
 ".o.",
 "..."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(1, Arg1, maxEmptyCells(Arg0)); }
	void test_case_2() { string Arr0[] = {"xxxxx",
 "xxoxx",
 "xo.ox",
 "xxoxx",
 "xxxxx"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, maxEmptyCells(Arg0)); }
	void test_case_3() { string Arr0[] = {".xox.",
 ".o.ox",
 "x.o.o",
 "ox.ox",
 ".ox.."}
 ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(3, Arg1, maxEmptyCells(Arg0)); }
	void test_case_4() { string Arr0[] = {"o.o.o",
 ".ox..",
 "oxxxo",
 "..x..",
 "o.o.o"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(4, Arg1, maxEmptyCells(Arg0)); }
	void test_case_5() { string Arr0[] = {"...",
 "...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(5, Arg1, maxEmptyCells(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	FoxAndGo3 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
