// BEGIN CUT HERE

// END CUT HERE
#line 5 "SurroundingGame.cpp"
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
/*
先把图黑白染色，就构成了一个二分图。
然后把每个点都拆成两个，左边的点拆成$$X_1和X_2$$，
$$S$$到$$X_1$$连一条容量为$$cost$$的边，$$X_1$$到$$X_2$$连一条容量为$$benefit$$的边。
右边的点如法炮制，拆成$$Y_1$$,$$Y_2$$ , 之间连一条$$benefit$$的边，$$Y_1$$到$T$连$$cost$$的边。
既然已经把两边的边都连好了，那么就可以来连中间的边了，
对于每一对相邻的点，我们在$$(X_1, Y_2)$$和$$(X_2, Y_1)$$之间都连上一条$$\infty$$的边。
这样来跑个最小割，用总收益减去最小割就是答案了。
*/
struct flows
{
	int first[200010],last[200010],des[200010],vol[200010],next[200010],opp[200010],tt,n;
	int dis[200010],cop[200010];
	void init(int pn){n=pn;}
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
		//cout<<s<<" "<<t<<endl;
		int ans=0;
		while (bfs(s,t))
		{
			//int d=dfs(s,t);cout<<d<<endl;
			ans+=dfs(s,t);
		}
		return ans;
	}
}flow;
int d[55][55][2];
int go(char ch)
{
	if (ch<='9') return ch-'0';
	else if (ch<='Z') return ch-'A'+36;
	else return ch-'a'+10;
}
class SurroundingGame
{
        public:
        int maxScore(vector <string> cost, vector <string> value)
        {
			int n=cost.size(),m=cost[0].size(),tp=0,ans=0;
			for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
			{
				d[i][j][0]=++tp;
				d[i][j][1]=++tp;
			}
			flow.init(tp+2);
			for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
			{
				ans+=go(value[i][j]);//cout<<value[i][j]<<endl;
				int d0=d[i][j][0],d1=d[i][j][1];
				flow.getin(d0,d1,go(value[i][j]));
				if ((i+j)&1)
				{
					flow.getin(tp+1,d0,go(cost[i][j]));
					if (i!=0) {flow.getin(d0,d[i-1][j][0],inf);flow.getin(d1,d[i-1][j][1],inf);}
					if (i!=n-1) {flow.getin(d0,d[i+1][j][0],inf);flow.getin(d1,d[i+1][j][1],inf);}
					if (j!=0) {flow.getin(d0,d[i][j-1][0],inf);flow.getin(d1,d[i][j-1][1],inf);}
					if (j!=m-1) {flow.getin(d0,d[i][j+1][0],inf);flow.getin(d1,d[i][j+1][1],inf);}
				}
				else flow.getin(d1,tp+2,go(cost[i][j]));
			}
			//cout<<ans<<endl;
			return ans-flow.dinic(tp+1,tp+2);
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
{
        SurroundingGame ___test;
        ___test.run_test(3);
        return 0;
}
// END CUT HERE
