// BEGIN CUT HERE

// END CUT HERE
//#line 5 "CosmicBlocks.cpp"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
#define inf 700000000
using namespace std;
int st[10],top,ans,minn,mx;
int h[10],js[10],ls[10],inn[10],up[10][10],fac[10];
struct flows
{
	int first[2010],last[2010],des[2010],vol[2010],next[2010],opp[2010],cur[2010],tt,n;
	int dis[2010],cop[2010];
	void init(int pn)
	{
		for (int i=1;i<=n;i++) first[i]=last[i]=0;
		for (int i=1;i<=tt;i++) des[i]=vol[i]=next[i]=opp[i]=0;
		tt=0;n=pn;
	}
	void getin(int c,int d,int s)
	{
		des[++tt]=d;vol[tt]=s;opp[tt]=tt+1;
		if (!first[c]) first[c]=last[c]=tt;
		else last[c]=next[last[c]]=tt;
		
		des[++tt]=c;vol[tt]=0;opp[tt]=tt-1;
		if (!first[d]) first[d]=last[d]=tt;
		else last[d]=next[last[d]]=tt;
	}
	bool bfs(int s,int t)
	{
		for (int i=1;i<=n;i++) dis[i]=inf;dis[t]=0;
		int head=1,tail=0;cop[head]=t;
		while (head!=tail)
		{
			int p=cop[++tail];
			for (int k=first[p];k;k=next[k]) if ((vol[opp[k]])&&(dis[des[k]]==inf))
			{
				dis[des[k]]=dis[p]+1;
				cop[++head]=des[k];
			}
		}
		return dis[s]!=inf;
	}
	int dfs(int s,int t,int minvol=inf)
	{
		if (s==t) return minvol;
		int bg=0;
		for (int k=cur[s];k;k=next[k])
		{
			cur[s]=k;
			if ((vol[k])&&(dis[des[k]]==dis[s]-1))
			{
				int p=dfs(des[k],t,min(vol[k],minvol-bg));
				bg+=p;
				vol[k]-=p;vol[opp[k]]+=p;
				if (bg==minvol) break;
			}
		}
		return bg;
	}		
	int dinic(int s,int t)
	{
		int ans=0;
		while (bfs(s,t))
		{
			for (int i=1;i<=n;i++) cur[i]=first[i];
			ans+=dfs(s,t);
		}
		return ans;
	}
	bool check(int s)
	{
		for (int k=first[s];k;k=next[k]) if (vol[k]) return false;
		return true;
	}
}flow;
struct wks
{
	int n,in[10];
	void init(int pn)
	{
		n=pn;
		for (int i=1;i<=n;i++) in[i]=0;
		flow.init(n+2);
	}
	void add(int c,int d,int low,int high)
	{
		flow.getin(c,d,high-low);
		in[d]+=low;in[c]-=low;
		//flow.getin(n+1,d,low);
		//flow.getin(c,n+2,low);
	}
	bool check()
	{
		for (int i=1;i<=n;i++)
			if (in[i]>0) flow.getin(n+1,i,in[i]);
			else if (in[i]<0) flow.getin(i,n+2,-in[i]);
		flow.dinic(n+1,n+2);
		return flow.check(n+1);
	}
}wk;
bool pend()
{
	//printf("pend\n");
	for (int s1=1;s1<=top;s1++)
	for (int s2=1;s2<=top;s2++)
		if (up[s1][s2]) inn[s2]++;
	
	bool bo=true;
	for (int i=1;i<=top;i++)
	{
		int s=ls[i];
		if (inn[s]) bo=false;
		for (int s2=1;s2<=top;s2++) if (up[s][s2]) inn[s2]--;
	}
	//for (int i=1;i<=top;i++) cout<<ls[i]<<' ';cout<<endl;
	return bo;
}		
void dfs2(int i,int j)
{
	//printf("dfs2\n");
	if (i>top)
	{
		wk.init(2*top+2);
		wk.add(2*top+2,2*top+1,0,inf);
		for (int s=1;s<=top;s++) wk.add(s,s+top,st[s],st[s]);
		for (int s1=1;s1<=top;s1++)
		for (int s2=1;s2<=top;s2++)
			if (up[s1][s2]) wk.add(s2+top,s1,1,inf);
		for (int s=1;s<=top;s++)
		{
			if (h[s]==1) wk.add(2*top+1,s,st[s],st[s]);
			wk.add(s+top,2*top+2,0,inf);
		}
		if (wk.check())
		{
			for (int i=1;i<=top;i++) ls[i]=i;
			int ths=0;
			for (int i=1;i<=fac[top];i++)
			{
				ths+=pend();
				next_permutation(ls+1,ls+top+1);
			}
			if ((ths>=minn)&&(ths<=mx))
			{
				ans++;
			}
		}
		return;
	}
	up[i][j]=false;
	if (j!=top) dfs2(i,j+1);else dfs2(i+1,1);
	if (h[i]==h[j]+1)
	{
		up[i][j]=true;
		if (j!=top) dfs2(i,j+1);else dfs2(i+1,1);
	}
}
void dfs1(int s)
{
	//printf("dfs1\n");
	if (s>top)
	{
		//cout<<h[1]<<' '<<h[2]<<' '<<h[3]<<endl;
		memset(js,false,sizeof(js));
		for (int i=1;i<=top;i++) js[h[i]]++;
		for (int i=2;i<=top;i++) if ((js[i]!=0)&&(js[i-1]==0)) return;
		dfs2(1,1); 
		return;
	}
	for (int i=1;i<=top;i++)
	{
		h[s]=i;
		dfs1(s+1);
	}
}
		
class CosmicBlocks
{
        public:
        int getNumOrders(vector <int> v, int minnn, int mxx)
        {
        	fac[0]=1;for (int i=1;i<=9;i++) fac[i]=fac[i-1]*i;
			minn=minnn;mx=mxx;
			for (int i=0;i<v.size();i++) st[++top]=v[i];
			dfs1(1);
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 6; verify_case(0, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 720; int Arg2 = 720; int Arg3 = 1; verify_case(1, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 3; verify_case(2, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 2; verify_case(3, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; verify_case(4, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {1,2,4,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 30; int Arg3 = 27; verify_case(5, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_6() { int Arr0[] = {1,2,3,4,5,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 720; int Arg3 = 4445; verify_case(6, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_7() { int Arr0[] = {7500,1000,7500,1000,7500}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; int Arg2 = 88; int Arg3 = 448; verify_case(7, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        CosmicBlocks ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE
