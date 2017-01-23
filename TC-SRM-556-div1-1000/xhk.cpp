// BEGIN CUT HERE

// END CUT HERE
#line 5 "OldBridges.cpp"
#include<bits/stdc++.h>
using namespace std;

const int maxn=10000,maxe=100000,inf=1e9;

struct edge
{int u,v,f,next;
};
struct edge e[2*maxe+10];

int num,maxflow;
int head[maxn+10],dis[maxn+10],gap[maxn+10],pre[maxn+10],mf[maxn+10],p1[maxn+10];
int n;
char ga[110][110];

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

class OldBridges
{	public:
	string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn)
	{	int i,j;
		
		n=bridges.size();
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				ga[i][j]=bridges[i-1][j-1];
		a1++;
		a2++;
		b1++;
		b2++;		
		num=0;
		memset(head,-1,sizeof(head));
		add(1,1+a1,an);
		add(1,1+b1,bn);
		add(1+a2,1+n+1,an);
		add(1+b2,1+n+1,bn);
		for(i=1;i<=n;i++) //a1->a2,b1->b2合起来连边判断 
			for(j=1;j<=n;j++)
				if(i!=j)
				{	if(ga[i][j]=='O')
						add(1+i,1+j,1);
					else if(ga[i][j]=='N')
						add(1+i,1+j,inf);
				}
		maxflow=0;
		sap(1,1+n+1,1+n+1);
		if(maxflow!=an+bn) return "No";
		
		num=0;
		memset(head,-1,sizeof(head));
		add(1,1+a1,an);
		add(1,1+b2,bn);
		add(1+a2,1+n+1,an);
		add(1+b1,1+n+1,bn);
		for(i=1;i<=n;i++) //将b反向,a1->a2,b2->b1合起来连边判断 
			for(j=1;j<=n;j++)
				if(i!=j)
				{	if(ga[i][j]=='O')
						add(1+i,1+j,1);
					else if(ga[i][j]=='N')
						add(1+i,1+j,inf);
				}
		maxflow=0;
		sap(1,1+n+1,1+n+1);
		if(maxflow!=an+bn) return "No";
		return "Yes"; //都合法就是可行的 
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"XOXX","OXOX","XOXO","XXOX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; int Arg3 = 1; int Arg4 = 2; int Arg5 = 3; int Arg6 = 1; string Arg7 = "Yes"; verify_case(0, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { string Arr0[] = {"XOXX","OXOX","XOXO","XXOX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 1; int Arg4 = 1; int Arg5 = 3; int Arg6 = 1; string Arg7 = "No"; verify_case(1, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { string Arr0[] = {"XOXO","OXOX","XOXO","OXOX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 1; int Arg4 = 1; int Arg5 = 3; int Arg6 = 1; string Arg7 = "Yes"; verify_case(2, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { string Arr0[] = {"XNXO","NXOX","XOXO","OXOX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 1; int Arg4 = 1; int Arg5 = 3; int Arg6 = 2; string Arg7 = "No"; verify_case(3, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_4() { string Arr0[] = {"XOXOO","OXOXO","XOXOO","OXOXO","OOOOX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 2; int Arg4 = 1; int Arg5 = 3; int Arg6 = 2; string Arg7 = "Yes"; verify_case(4, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_5() { string Arr0[] = {"XOOOX","OXOOX","OOXOX","OOOXN","XXXNX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 4; int Arg3 = 3; int Arg4 = 1; int Arg5 = 2; int Arg6 = 2; string Arg7 = "No"; verify_case(5, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	OldBridges ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
