// BEGIN CUT HERE

// END CUT HERE
#line 5 "CurvyonRails.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;

struct edge
{int u,v,f,c,next;
};
struct edge e[200010];

int n,m,num,maxflow,cost;
int head[10010],used[10010],q[1000010],dis[10010],pre[10010],mf[10010],a[110][110],v[4][2]={0,1,1,0,0,-1,-1,0};

void add(int u,int v,int f,int c)
{e[num].u=u;
 e[num].v=v;
 e[num].f=f;
 e[num].c=c;
 e[num].next=head[u];
 head[u]=num;
 num++;
 e[num].u=v;
 e[num].v=u;
 e[num].f=0;
 e[num].c=-c;
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

int spfa(int S,int T)
{int i,j,t,w;
 
 memset(dis,0x3f,sizeof(dis));
 t=w=1;
 q[t]=S;
 dis[S]=0;
 memset(used,0,sizeof(used));
 mf[1]=inf;
 while(t<=w)
 {	i=q[t];
 	used[i]=0;
 	j=head[i];
 	while(j!=-1)
	{	if(e[j].f>0 && dis[i]+e[j].c<dis[e[j].v])
		{	dis[e[j].v]=dis[i]+e[j].c;
			mf[e[j].v]=min(mf[i],e[j].f);
			pre[e[j].v]=j;
			if(!used[e[j].v])
			{	used[e[j].v]=1;
				q[++w]=e[j].v;
			}
		}
		j=e[j].next;
 	}
	t++;
 }
 return dis[T]!=inf;
}

class CurvyonRails
{	public:
	int getmin(vector <string> field)
	{	int i,j,x,y,k,p,p1,s,S,T;
	
		n=field.size();
		m=field[0].length();
		memset(a,0,sizeof(a));
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(field[i-1][j-1]=='.')
					a[i][j]=1;
				else if(field[i-1][j-1]=='C')
					a[i][j]=2;
		num=0;
		memset(head,-1,sizeof(head));
		s=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{	if(!a[i][j]) continue;
				s+=2;
				p=(i-1)*m+j;
				if((i+j)&1)
				{	add(1,1+p,2,0);
					add(1+p,1+n*m+2*p-1,1,0);
					add(1+p,1+n*m+2*p-1,1,a[i][j]==2);
					add(1+p,1+n*m+2*p,1,0);
					add(1+p,1+n*m+2*p,1,a[i][j]==2);
				}
				else
				{	add(1+p,1+n*m+2*n*m+1,2,0);
					add(1+n*m+2*p-1,1+p,1,0);
					add(1+n*m+2*p-1,1+p,1,a[i][j]==2);
					add(1+n*m+2*p,1+p,1,0);
					add(1+n*m+2*p,1+p,1,a[i][j]==2);
				}
				if((i+j)&1)
				{	for(k=0;k<4;k++)
					{	x=i+v[k][0];
						y=j+v[k][1];
						if(x>=1 && x<=n && y>=1 && y<=m && a[x][y])
						{	p1=(x-1)*m+y;
							add(1+n*m+2*p-(k&1),1+n*m+2*p1-(k&1),1,0);
						}
					}
				}
			}
		//cout<<"hh"<<endl;	
		memset(pre,-1,sizeof(pre));
		maxflow=0;
		cost=0;
		S=1;
		T=1+n*m+2*n*m+1;
		while(spfa(S,T))
		{	maxflow+=mf[T];
			cost+=mf[T]*dis[T];
			change(T);
		}
		if(maxflow!=s/2)
			return -1;
		else
			return cost;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".."
,".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, getmin(Arg0)); }
	void test_case_1() { string Arr0[] = {"wCCww"
,"wCC.."
,"..w.."
,"....w"
,"ww..w"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, getmin(Arg0)); }
	void test_case_2() { string Arr0[] = {"C.w"
,"..."
,".C."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, getmin(Arg0)); }
	void test_case_3() { string Arr0[] = {"."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, getmin(Arg0)); }
	void test_case_4() { string Arr0[] = {"w"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(4, Arg1, getmin(Arg0)); }
	void test_case_5() { string Arr0[] = {"CC..CCCw.CwC..CC.w.C",
 "C.CCCwCCC.w.w..C.w..",
 "wwww...CC.wC.Cw.CC..",
 "CC..CC.w..w.C..CCCC.",
 "CC.CCC..CwwCCC.wCC..",
 "w.C..wwCC.CC.wwwCC..",
 ".CC.CC..CCC..CC.CC.C",
 "Cw....C.C.CCC...CC..",
 "CC.C..Cww.C.CwwwC..w",
 "wCCww..C...CCCCCCC.w",
 "C.CCw.CC.ww...C.CCww",
 "C.C.C.CCwCC..wCCw.Cw",
 "CCC.C...w..C.wC.wCCw",
 "CC.C..C..CCC.CC.C...",
 "C.ww...CCC..CC...CCC",
 "...CCC.CwwwC..www.C.",
 "wwCCCCC.w.C.C...wCwC",
 "CCwC.CwCCC.C.w.Cw...",
 "C.w.wC.CC.CCC.C.w.Cw",
 "CCw.CCC..C..CC.CwCCw",
 "C.wwwww.CwwCCwwwwwww"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(5, Arg1, getmin(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	CurvyonRails ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
