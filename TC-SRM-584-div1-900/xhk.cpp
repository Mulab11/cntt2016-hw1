// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxTheLinguist.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;

struct edge
{int u,v,c,next;
};
struct edge e[10010];

int n,num,l,tot,ans;
int head[110],used[110],q[100010],f[110][1100];
string a;

void add(int u,int v,int c)
{e[num].u=u;
 e[num].v=v;
 e[num].c=c;
 e[num].next=head[u];
 head[u]=num;
 num++;
}

void spfa(int sta) //spfa转移f[][sta] 
{int i,j,t,w;
 
 t=1;
 w=0;
 for(i=1;i<=tot;i++)
 	if(f[i][sta]<inf)
 		q[++w]=i;
 memset(used,0,sizeof(used));		
 while(t<=w)
 {	i=q[t];
 	used[i]=0;
 	j=head[i];
 	while(j!=-1)
 	{	if(f[i][sta]+e[j].c<f[e[j].v][sta])
 		{	f[e[j].v][sta]=f[i][sta]+e[j].c;
 			if(!used[e[j].v])
 			{	used[e[j].v]=1;
 				q[++w]=e[j].v;
 			}
 		}
 		j=e[j].next;
 	}
 	t++;
 }
}

class FoxTheLinguist
{	public:
	int minimalHours(int N, vector <string> courseInfo)
	{	int i,j,k,x,y,z;
		
		n=N;
		a="";
		for(i=0;i<courseInfo.size();i++)
			a+=courseInfo[i];
		l=a.length();
		num=0;
		memset(head,-1,sizeof(head));
		for(i=0;i+10<l;i+=12) //按课程建边，为了方便将边反向 
		{	x=(a[i]-65)*10+a[i+1]-48+1;
			y=(a[i+4]-65)*10+a[i+5]-48+1;
			z=(a[i+7]-48)*1000+(a[i+8]-48)*100+(a[i+9]-48)*10+a[i+10]-48;
			add(y,x,z);
		}
		tot=n*10;
		for(i=1;i<=n;i++) //学了Ai默认会学会Ai-1 
		{	for(j=2;j<=10;j++)
			{	x=(i-1)*10+j;
				y=(i-1)*10+j-1;
				add(y,x,0);
			}
			x=tot+1;
			y=(i-1)*10+1;
			add(y,x,0);
		}
		tot++;
		
		//for(i=0;i<num;i++)
		//	cout<<e[i].u<<" "<<e[i].v<<" "<<e[i].c<<" "<<e[i].next<<endl;
		
		memset(f,0x3f,sizeof(f));
		for(i=1;i<=n;i++) f[i*10][1<<(i-1)]=0;
		for(i=1;i<(1<<n);i++) //跑斯坦纳树 
		{	for(j=1;j<=tot;j++)
				for(k=(i-1)&i;k>0;k=(k-1)&i)
					f[j][i]=min(f[j][i],f[j][k]+f[j][i^k]);
			spfa(i);
		}
		ans=f[tot][(1<<n)-1];
		return ans!=inf?ans:-1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; string Arr1[] = {"A0->A9:1000 A0->A6:0300 A3->A9:0600"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 900; verify_case(0, Arg2, minimalHours(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; string Arr1[] = {"A0->A9:1000 B0->B9:1000 A1->B9:0300 B1->A9:0200"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1200; verify_case(1, Arg2, minimalHours(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; string Arr1[] = {"C0->A6:00", "01 A3", "->B9:0001 A3->C6:000", "1",
" C3->A9:0001 A9->C9:0001 A0->A9:9999",
" B0->B9:9999 C0->C9:9999 A6->A9:9999"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(2, Arg2, minimalHours(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4; string Arr1[] = {"A0->A6:6666 A0->A9:9999",
" B0->B6:6666 B0->B9:9999",
" C0->C6:6666 C0->C9:9999",
" D0->D6:6666 D0->D9:9999",
" A6->B6:0666 B6->C6:0666",
" C6->D6:0666 D6->A6:0666",
" A9->B9:0099 B9->C9:0099",
" C9->D9:0099 D9->A9:0099"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10296; verify_case(3, Arg2, minimalHours(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1; string Arr1[] = {"A0->A9:9999 A0->A9:8888"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8888; verify_case(4, Arg2, minimalHours(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 1; string Arr1[] = {"A9->A9:0000",
" A9->A0:0000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(5, Arg2, minimalHours(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	FoxTheLinguist ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
