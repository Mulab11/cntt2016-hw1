// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndCity.cpp"
#include<bits/stdc++.h>
using namespace std;

const int maxn=10000,maxe=100000,inf=1e9;

struct edge
{int u,v,f,next;
};
struct edge e[2*maxe+10];

int num,maxflow;
int head[maxn+10],dis[maxn+10],gap[maxn+10],pre[maxn+10],mf[maxn+10],p1[maxn+10];
int n,ans;
int a[110],ga[110][110];

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

class FoxAndCity
{	public:
	int minimalCost(vector <string> linked, vector <int> want)
	{	int i,j,k;
		
		n=want.size();
		for(i=1;i<=n;i++) a[i]=want[i-1];
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				ga[i][j]=(linked[i-1][j-1]=='Y');
		num=0;
		memset(head,-1,sizeof(head));
		add(1,1+1,inf); //对1号点连边 
		add(1+1,1+2,a[1]*a[1]);
		for(j=2;j<=n;j++)
			add(1+j,1+j+1,inf);
		add(1+n+1,1+n*(n+1)+1,inf);
		for(i=2;i<=n;i++) //对剩下的连边 
		{	add(1,1+(i-1)*(n+1)+1,inf);
			add(1+(i-1)*(n+1)+1,1+(i-1)*(n+1)+2,inf);
			for(j=2;j<=n;j++)
				add(1+(i-1)*(n+1)+j,1+(i-1)*(n+1)+j+1,(j-1-a[i])*(j-1-a[i]));
			add(1+(i-1)*(n+1)+n+1,1+n*(n+1)+1,inf);
		}
		for(i=1;i<=n;i++) //如果(i,j)有边连接，那么限制他们的dis差不超过1 
			for(j=1;j<=n;j++)
				if(i!=j && ga[i][j])
				{	for(k=2;k<=n+1;k++)
						add(1+(i-1)*(n+1)+k,1+(j-1)*(n+1)+k-1,inf);
				}
		maxflow=0;
		sap(1,1+n*(n+1)+1,1+n*(n+1)+1); //求最小割 
		ans=maxflow;
		return ans;		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYN",
 "YNY",
 "NYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(0, Arg2, minimalCost(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"NYNN",
 "YNYN",
 "NYNY",
 "NNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 3, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(1, Arg2, minimalCost(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"NYNNNY",
 "YNYNNN",
 "NYNYNN",
 "NNYNYN",
 "NNNYNY",
 "YNNNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 2, 2, 2, 2, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(2, Arg2, minimalCost(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"NYY","YNN","YNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(3, Arg2, minimalCost(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"NYNNNN",
 "YNYNNN",
 "NYNYYY",
 "NNYNYY",
 "NNYYNY",
 "NNYYYN"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2, 3, 0, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(4, Arg2, minimalCost(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"NYNNNN",
 "YNYNNN",
 "NYNYYY",
 "NNYNYY",
 "NNYYNY",
 "NNYYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2, 4, 0, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(5, Arg2, minimalCost(Arg0, Arg1)); }
	void test_case_6() { string Arr0[] = {"NYNYYYYYYYY","YNYNNYYNYYY","NYNNNYYNYYN","YNNNYYYYYYY","YNNYNYYYNYY","YYYYYNNYYNY","YYYYYNNNYYY","YNNYYYNNNYY","YYYYNYYNNNY","YYYYYNYYNNY","YYNYYYYYYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,2,0,0,5,1,3,0,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 28; verify_case(6, Arg2, minimalCost(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	FoxAndCity ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
