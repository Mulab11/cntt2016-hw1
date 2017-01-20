// BEGIN CUT HERE

// END CUT HERE
#line 5 "OldBridges.cpp"
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
#define ms(x) memset(x,0,sizeof(x))
#define inf 700000000
using namespace std;
struct flows
{
	int first[200010],last[200010],des[200010],vol[200010],next[200010],opp[200010],tt,n;
	int dis[200010],cop[200010];
	void init(int pn)
	{
		n=pn;tt=0;
		ms(first);ms(last);ms(des);ms(vol);ms(next);ms(opp);
	}
	void getin(int c,int d,int s)
	{
		//cout<<c<<" "<<d<<" "<<s<<endl;
		des[++tt]=d;vol[tt]=s;opp[tt]=tt+1;
		if (!first[c]) first[c]=last[c]=tt;
		else last[c]=next[last[c]]=tt;
		
		des[++tt]=c;vol[tt]=0;opp[tt]=tt-1;
		if (!first[d]) first[d]=last[d]=tt;
		else last[d]=next[last[d]]=tt;
	}
	bool bfs(int s,int t)
	{
		for (int i=1;i<=n;i++) dis[i]=2100000000;dis[t]=0;
		int head=1,tail=0;cop[head]=t;
		while (head!=tail)
		{
			int p=cop[++tail];
			for (int k=first[p];k;k=next[k]) if ((vol[opp[k]])&&(dis[des[k]]==2100000000))
			{
				dis[des[k]]=dis[p]+1;
				cop[++head]=des[k];
			}
		}
		return dis[s]!=2100000000;
	}
	int dfs(int s,int t,int minvol=2100000000)
	{
		if (s==t) return minvol;
		int bg=0;
		for (int k=first[s];k;k=next[k]) if ((vol[k])&&(dis[des[k]]==dis[s]-1))
		{
			int p=dfs(des[k],t,min(vol[k],minvol-bg));
			bg+=p;
			vol[k]-=p;vol[opp[k]]+=p;
			if (bg==minvol) break;
		}
		return bg;
	}		
	int dinic(int s,int t)
	{
		int ans=0;
		while (bfs(s,t))
		{
			ans+=dfs(s,t);
		}
		return ans;
	}
}flow;
class OldBridges
{
        public:
        string isPossible(vector <string> br, int a1, int a2, int an, int b1, int b2, int bn)
        {
			int n=br.size();
			a1++;a2++;b1++;b2++;
			//
			flow.init(n+2);
			for (int i=0;i<n;i++)
			for (int j=0;j<n;j++) if (i!=j)
			{
				if (br[i][j]=='N') flow.getin(i+1,j+1,inf);
				else if (br[i][j]=='O') flow.getin(i+1,j+1,2);
			}
			flow.getin(n+1,a1,2*an);
			flow.getin(n+1,b1,2*bn);
			flow.getin(a2,n+2,2*an);
			flow.getin(b2,n+2,2*bn);
			if (flow.dinic(n+1,n+2)!=2*(an+bn)) {cout<<"WAHA";return "No";}
			//
			
			//
			flow.init(n+2);
			for (int i=0;i<n;i++)
			for (int j=0;j<n;j++) if (i!=j)
			{
				if (br[i][j]=='N') flow.getin(i+1,j+1,inf);
				else if (br[i][j]=='O') flow.getin(i+1,j+1,2);
			}
			flow.getin(n+1,a1,2*an);
			flow.getin(n+1,b2,2*bn);
			flow.getin(a2,n+2,2*an);
			flow.getin(b1,n+2,2*bn);
			if (flow.dinic(n+1,n+2)!=2*(an+bn)) return "No";
			//
			
			return "Yes";
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
{
        OldBridges ___test;
        ___test.run_test(1);
        return 0;
}
// END CUT HERE
