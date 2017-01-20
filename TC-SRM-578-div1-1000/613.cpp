// BEGIN CUT HERE

// END CUT HERE
#line 5 "DeerInZooDivOne.cpp"
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
#define N 5555
#define M 255555
using namespace std;
struct costflow
{
	int first[N],last[N],dis[N],cop[2000010],next[M],des[M],opp[M],vol[M],len[M],tt,n;
	bool inst[N];
	int from[N];
	void clear(int pn)
	{//cout<<pn<<endl;
		for (int i=1;i<=pn;i++) first[i]=last[i]=dis[i]=from[i]=inst[i]=0;
		for (int i=1;i<=tt;i++) next[i]=des[i]=opp[i]=vol[i]=len[i]=0;
		tt=0;n=pn;
	}
	void getin(int c,int d,int v,int l)
	{
		//cout<<c<<' '<<d<<' '<<v<<' '<<l<<endl;
	    des[++tt]=d;vol[tt]=v;len[tt]=l;
	    if (!first[c]) first[c]=last[c]=tt;else last[c]=next[last[c]]=tt;
	    opp[tt]=tt+1;
	    des[++tt]=c;vol[tt]=0;len[tt]=-l;
	    if (!first[d]) first[d]=last[d]=tt;else last[d]=next[last[d]]=tt;
	    opp[tt]=tt-1;
	}
	int spfa(int s,int t)
	{
	    for (int i=1;i<=n;i++) {dis[i]=2100000000;from[i]=0;inst[i]=false;}
	    dis[s]=0;int head=1,tail=0;cop[1]=s;inst[s]=true;
	    while (head!=tail)
	    {
	        int p=cop[++tail];inst[p]=false;
	        for (int k=first[p];k;k=next[k])
	        {
	            if (!vol[k]) continue;
	            if (dis[p]+len[k]<dis[des[k]])
	            {
	                dis[des[k]]=dis[p]+len[k];
	                from[des[k]]=k;
	                if (!inst[des[k]]) {inst[des[k]]=true;cop[++head]=des[k];}
	            }
	        }
	    }
	    if (dis[t]==2100000000) return -2100000000;
	    int now=t,mx=2100000000;
	    while (now!=s)
	    {
	        mx=min(mx,vol[from[now]]);
	        now=des[opp[from[now]]];
	    }
	    int ans=dis[t]*mx;
	    now=t;
	    while (now!=s)
	    {
	        vol[from[now]]-=mx;
	        vol[opp[from[now]]]+=mx;
	        now=des[opp[from[now]]];
	    }
	    return ans;
	}
	int work(int s,int t)
	{
	    int ans=0;
	    while (1)
	    {
	        int ths=spfa(s,t);
	        if (ths==-2100000000) break;
	        ans+=ths;
	    }
	    //if (abs(ans)>1) cout<<ans<<endl<<endl;
	    return ans;
	}
}costflow;
int n,fa[55],refa[55],ban1,ban2;
vector <int> des[55];
bool son[55][55];
int f[55][55];
void dfs(int s)
{
	for (int k=0;k<des[s].size();k++) if (des[s][k]!=fa[s])
	{
		fa[des[s][k]]=s;son[s][des[s][k]]=true;
		dfs(des[s][k]);
		for (int d=1;d<=n;d++) son[s][d]|=son[des[s][k]][d];
	}
}
void redfs(int s,int ban)
{
	for (int k=0;k<des[s].size();k++) if ((des[s][k]!=refa[s])&&(des[s][k]!=ban))
	{
		refa[des[s][k]]=s;
		redfs(des[s][k],ban);
	}
}
int getf(int s1,int s2)
{
	if (f[s1][s2]) return f[s1][s2];
	for (int k1=0;k1<des[s1].size();k1++) if ((des[s1][k1]!=fa[s1])&&(des[s1][k1]!=ban1))
	for (int k2=0;k2<des[s2].size();k2++) if ((des[s2][k2]!=refa[s2])&&(des[s2][k2]!=ban2))
		getf(des[s1][k1],des[s2][k2]);
	
	costflow.clear(des[s1].size()+des[s2].size()+2);
	for (int k1=0;k1<des[s1].size();k1++)
		if ((des[s1][k1]!=fa[s1])&&(des[s1][k1]!=ban1)) costflow.getin(des[s1].size()+des[s2].size()+1,k1+1,1,0);
	for (int k2=0;k2<des[s2].size();k2++)
		if ((des[s2][k2]!=refa[s2])&&(des[s2][k2]!=ban2)) costflow.getin(des[s1].size()+k2+1,des[s1].size()+des[s2].size()+2,1,0);
	
	for (int k1=0;k1<des[s1].size();k1++) if ((des[s1][k1]!=fa[s1])&&(des[s1][k1]!=ban1))
	for (int k2=0;k2<des[s2].size();k2++) if ((des[s2][k2]!=refa[s2])&&(des[s2][k2]!=ban2))
		costflow.getin(k1+1,des[s1].size()+k2+1,1,-getf(des[s1][k1],des[s2][k2]));

	return f[s1][s2]=-costflow.work(des[s1].size()+des[s2].size()+1,des[s1].size()+des[s2].size()+2)+1;
}
class DeerInZooDivOne
{
        public:
        int getmax(vector <int> a, vector <int> b)
        {
			n=a.size()+1;
			for (int i=0;i<n-1;i++)
			{
				des[a[i]+1].push_back(b[i]+1);
				des[b[i]+1].push_back(a[i]+1);
			}
			dfs(1);
			int ans=0;
			for (int i=2;i<=n;i++)
			for (int j=1;j<=n;j++) if ((i!=j)&&(!son[i][j]))
			{
				memset(refa,0,sizeof(refa));
				redfs(j,i);
				ban1=fa[i];ban2=i;
				memset(f,0,sizeof(f));
				ans=max(ans,getf(i,j));
			}
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, getmax(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 8, 1, 7, 4, 2, 5, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5, 3, 6, 8, 2, 6, 8, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, getmax(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, getmax(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0, 11, 10, 10, 19, 17, 6, 17, 19, 10, 10, 11, 9, 9, 14, 2, 13, 11, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7, 5, 2, 12, 8, 9, 16, 8, 4, 18, 8, 13, 15, 13, 17, 16, 3, 1, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; verify_case(3, Arg2, getmax(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {14, 13, 28, 15, 20, 4, 9, 6, 1, 23, 19, 25, 25, 8, 14, 16, 2, 8, 15, 25, 22, 22, 28, 10, 10, 14, 24, 27, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {21, 5, 12, 13, 27, 1, 24, 17, 27, 17, 23, 14, 18, 26, 7, 26, 11, 0, 25, 23, 3, 29, 22, 11, 22, 29, 15, 28, 29}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 11; verify_case(4, Arg2, getmax(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        DeerInZooDivOne ___test;
        ___test.run_test(3);
        return 0;
}
// END CUT HERE