// BEGIN CUT HERE

// END CUT HERE
#line 5 "GearsDiv1.cpp"
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

void change(int T)
{int j;
 j=pre[T];
 while(j!=-1)
 {	e[j].f-=mf[T];
 	e[j^1].f+=mf[T];
 	j=pre[e[j].u];
 }
}

void sap(int S,int T,int N) //sap求二分图最大匹配 
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

int solve(int l,int r) //计算l颜色和r颜色同一个方向的情况 
{int i,j;
 
 num=0;
 memset(head,-1,sizeof(head));
 for(i=1;i<=n;i++)
 	if(a[i]==l)
 		add(1,1+i,1);
 	else if(a[i]==r)
 		add(1+i,1+n+1,1);
 for(i=1;i<=n;i++)
 	for(j=1;j<=n;j++)
 		if(a[i]==l && a[j]==r && ga[i][j])
 			add(1+i,1+j,inf);
 maxflow=0;
 sap(1,1+n+1,1+n+1); //网络流求出最少删除几个 
 return maxflow;
}

class GearsDiv1
{	public:
	int getmin(string color, vector <string> graph)
	{	int i,j;
		
		n=color.size();
		for(i=1;i<=n;i++)
			if(color[i-1]=='R')
				a[i]=1;
			else if(color[i-1]=='G')
				a[i]=2;
			else
				a[i]=3;
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				ga[i][j]=(graph[i-1][j-1]=='Y');
		ans=solve(1,2); //枚举那两个颜色同一个方向 
		ans=min(ans,solve(2,3));
		ans=min(ans,solve(1,3));
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "RGB"; string Arr1[] = {"NYY","YNY","YYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, getmin(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "RGBR"; string Arr1[] = {"NNNN","NNNN","NNNN","NNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, getmin(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "RGBR"; string Arr1[] = {"NYNN","YNYN","NYNY","NNYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, getmin(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "RRRRRGRRBGRRGBBGGGBRRRGBRGRRGG"; string Arr1[] = {"NNNNNYNNNYNNYNNNYNNNNNNNNYNNYY",
 "NNNNNNNNYNNNYNYNNYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNNNNYNNNNNNYNNNY",
 "NNNNNNNNNYNNYNNYYYNNNNYNNYNNNN",
 "NNNNNNNNNYNNYNNYYYNNNNYNNNNNNN",
 "YNYNNNYYYNNYNYYNNNNNYYNYNNYYNN",
 "NNNNNYNNNNNNNNNYYYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNYNNNNNNNNNNNNYN",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "YNNYYNNNYNNNNYYNNNYNYYNYNNNNNN",
 "NNNNNNNNNNNNYNNYNYNNNNYNNNNNNY",
 "NNNNNYNNNNNNYNNYYYNNNNNNNNNNYN",
 "YYNYYNNNYNYYNYYNNNYNYNNYNNNNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNYNYYY",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "NNNYYNYYYNYYNYYNNNYNYNNYYNYYNN",
 "YNNYYNYNYNNYNYYNNNYNNNNYYNNYNN",
 "NYNYYNYNYNYYNYYNNNNYYNNYYNYNNN",
 "NNYNNNNNNYNNYNNYYNNNNNYNNYNNNY",
 "NNNNNNNNNNNNNNNNNYNNNNYNNYNNNY",
 "NNNNNYNNNYNNYNNYNYNNNNYNNNNNYY",
 "NNNNNYNNNYNNNNNNNNNNNNYNNNNNNN",
 "NYNYYNYNYNYNNYYNNNYYYYNYYNYNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNNNNNY",
 "NNNNNNNNNNNNNNNYYYNNNNYNNYNNYY",
 "YYYYNNYNYNNNNYYNNNYYNNNNYNYYNN",
 "NNNNNYNNNNNNNNNYNYNNNNYNNYNNYN",
 "NNNNNYNNNNNNNYNYYNNNNNNNNYNNYY",
 "YYNNNNYYYNNYNYYNNNNNYNNNYNYYNN",
 "YYYNNNYNYNYNNYYNNNYYYNNYYNNYNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(3, Arg2, getmin(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	GearsDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
