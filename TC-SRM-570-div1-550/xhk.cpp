// BEGIN CUT HERE

// END CUT HERE
#line 5 "CentaurCompany.cpp"
#include<bits/stdc++.h>
using namespace std;

const int base=40,lim=80;

struct edge
{int u,v,next;
};
struct edge e[210];

int n,num;
int head[110];
double ans;
double f[40][90][2],g[90][2];

void add(int u,int v)
{e[num].u=u;
 e[num].v=v;
 e[num].next=head[u];
 head[u]=num;
 num++;
 e[num].u=v;
 e[num].v=u;
 e[num].next=head[v];
 head[v]=num;
 num++;
}

void dfs(int i,int fa)
{int j,j1,j2;
 
 f[i][base][0]=0.5;
 f[i][base+1][1]=0.5;
 j=head[i];
 while(j!=-1)
 {	if(e[j].v!=fa)
 	{	dfs(e[j].v,i);
 		memset(g,0,sizeof(g));
		for(j1=0;j1<=lim;j1++)
			for(j2=0;j2<=lim;j2++)
			{	if(j1+j2-base>=0 && j1+j2-base<=lim)
				{	g[j1+j2-base][0]+=f[i][j1][0]*f[e[j].v][j2][0];
					g[j1+j2-base][0]+=f[i][j1][0]*f[e[j].v][j2][1];
					g[j1+j2-base][1]+=f[i][j1][1]*f[e[j].v][j2][0];
				}
				if(j1+j2-2-base>=0 && j1+j2-2-base<=lim)
					g[j1+j2-2-base][1]+=f[i][j1][1]*f[e[j].v][j2][1];
			}
		for(j1=0;j1<=lim;j1++)
		{	f[i][j1][0]=g[j1][0];
			f[i][j1][1]=g[j1][1];
		}
	}
	j=e[j].next;
 }
}

class CentaurCompany
{	public:
	double getvalue(vector <int> a, vector <int> b)
	{	int i,j;
		
		n=a.size()+1;
		num=0;
		memset(head,-1,sizeof(head));
		for(i=1;i<n;i++)
			add(a[i-1],b[i-1]);
		//cout<<"hh"<<endl;
		memset(f,0,sizeof(f));
		dfs(1,0);
		ans=0;
		for(i=base+2;i<=lim;i++)
		{	//cout<<i<<" "<<f[1][i][0]<<" "<<f[1][i][1]<<endl;
			ans+=2*(f[1][i][0]+f[1][i][1])*(i-base-2);
		}
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.0; verify_case(0, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.125; verify_case(1, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.375; verify_case(2, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1,2,3,4,5,6,7,8,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.41796875; verify_case(3, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 15.500000001076842; verify_case(4, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {10, 7, 2, 5, 6, 2, 4, 9, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8, 10, 10, 4, 1, 6, 2, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.646484375; verify_case(5, Arg2, getvalue(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	CentaurCompany ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
