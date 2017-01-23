// BEGIN CUT HERE

// END CUT HERE
#line 5 "SurroundingGame.cpp"
#include<bits/stdc++.h>
using namespace std;

#define number(i,j) ((i-1)*m+j)
const int inf=0x3f3f3f3f;

struct edge
{int u,v,f,next;
};
struct edge e[1000010];

int n,m,num,ans,maxflow;
int b[1010][1010],c[1010][1010],pre[10010],dis[10010],mf[10010],gap[10010],head[10010],p1[10010],v[4][2]={0,1,1,0,-1,0,0,-1};

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

int calc(char x)
{if(x<=57) return x-48;
 if(x>=97) return 10+x-97;
 return 36+x-65;
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

void sap(int S,int T,int N) //sap求最大流 
{int i,j,flag,md,me;
 
 memset(dis,0,sizeof(dis));
 memset(pre,-1,sizeof(pre));
 memset(gap,0,sizeof(gap));
 for(i=1;i<=N;i++) p1[i]=head[i];
 gap[0]=N;
 i=S;
 dis[S]=0;
 mf[S]=inf;
 while(dis[i]<=N)
 {	j=p1[i];
 	flag=0;
 	while(j!=-1)
 	{	if(e[j].f && dis[e[j].v]==dis[i]-1)
 		{	p1[i]=j;
 			mf[e[j].v]=min(mf[i],e[j].f);
 			pre[e[j].v]=j;
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
 		me=-1;
 		j=head[i];
 		while(j!=-1)
 		{	if(e[j].f && dis[e[j].v]<md)
 			{	md=dis[e[j].v];
 				me=j;
 			}
 			j=e[j].next;
 		}
 		gap[dis[i]]--;
		if(!gap[dis[i]]) return;
		dis[i]=md+1;
		gap[dis[i]]++;
		p1[i]=me;
		if(i!=S) i=e[pre[i]].u;
	}
 }
}

class SurroundingGame
{	public:
	int maxScore(vector <string> cost, vector <string> benefit)
	{	int i,j,x,y,k;
	
		n=cost.size();
		m=cost[0].length();
		ans=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{	c[i][j]=calc(cost[i-1][j-1]);
				b[i][j]=calc(benefit[i-1][j-1]);
				ans+=b[i][j];
				//cout<<b[i][j]<<" "<<c[i][j]<<endl;
			}
		memset(head,-1,sizeof(head));
		num=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++) //连边 
				if((i+j)&1)
				{	add(1,1+number(i,j)*2-1,c[i][j]);
					add(1+number(i,j)*2-1,1+number(i,j)*2,b[i][j]);
					for(k=0;k<4;k++)
					{	x=i+v[k][0];
						y=j+v[k][1];
						if(x>0 && x<=n && y>0 && y<=m)
						{	add(1+number(i,j)*2-1,1+number(x,y)*2,inf);
							add(1+number(i,j)*2,1+number(x,y)*2-1,inf);
						}
					}
				}
				else
				{	add(1+number(i,j)*2-1,1+n*m*2+1,c[i][j]);
					add(1+number(i,j)*2,1+number(i,j)*2-1,b[i][j]);
				}
		//cout<<n<<" "<<m<<endl;		
		maxflow=0;
		sap(1,1+n*m*2+1,1+n*m*2+1); //网络流 
		ans-=maxflow;
		return ans;		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"21","12"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"21","12"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(0, Arg2, maxScore(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"ZZ","ZZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"11","11"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, maxScore(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"XXX","XXX","XXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"aaa","aZa","aaa"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(2, Arg2, maxScore(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"asam","atik"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"123A","45BC"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 71; verify_case(3, Arg2, maxScore(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"IIIIIIII",
 "IIWWWWII",
 "IIWIIIII",
 "IIWIIIII",
 "IIWWWWII",
 "IIIIIWII",
 "IIIIIWII",
 "IIWWWWII",
 "IIIIIIII"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"IIIIIIII",
 "II0000II",
 "II0II0II",
 "II0II0II",
 "II0000II",
 "II0II0II",
 "II0II0II",
 "II0000II",
 "IIIIIIII"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 606; verify_case(4, Arg2, maxScore(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	SurroundingGame ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
