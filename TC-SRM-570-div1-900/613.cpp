// BEGIN CUT HERE

// END CUT HERE
#line 5 "CurvyonRails.cpp"
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
using namespace std;
struct flow
{
	vector <int> des[200010],vol[200010],cost[200010],opp[200010];
	int n,dis[200010],back[200010],bkl[200010],cop[5001000];
	bool ins[200010];
	void getin(int c,int d,int v,int l)
	{
		//cout<<c<<' '<<d<<' '<<v<<' '<<l<<endl;
		des[c].push_back(d);
		vol[c].push_back(v);
		cost[c].push_back(l);
		opp[c].push_back(des[d].size());
		
		des[d].push_back(c);
		vol[d].push_back(0);
		cost[d].push_back(-l);
		opp[d].push_back(des[c].size()-1);
		
	}
	pair<int,int> spfa(int s,int t)
	{
		for (int i=1;i<=n;i++) {dis[i]=700000000;ins[i]=false;}
		dis[s]=0;
		int head=1,tail=0;cop[head]=s;ins[s]=true;
		while (head!=tail)
		{//cout<<head<<endl;
			int p=cop[++tail];ins[p]=false;
			for (int k=0;k<des[p].size();k++) if ((vol[p][k])&&(dis[des[p][k]]>dis[p]+cost[p][k]))
			{
				dis[des[p][k]]=dis[p]+cost[p][k];
				back[des[p][k]]=p;
				bkl[des[p][k]]=k;
				if (!ins[des[p][k]])
				{
					ins[des[p][k]]=true;
					cop[++head]=des[p][k];
				}
			}
		}
		if (dis[t]==700000000) return make_pair(0,0);
		int now=t,minvol=2100000000,cc=0;
		while (now!=s)
		{
			minvol=min(minvol,vol[back[now]][bkl[now]]);
			now=back[now];
		}
		now=t;//cout<<"HAHA\n";
		while (now!=s)
		{	
			vol[back[now]][bkl[now]]-=minvol;
			vol[now][opp[back[now]][bkl[now]]]+=minvol;
			cc+=cost[back[now]][bkl[now]];
			now=back[now];
		}
		//cout<<"WAHA\n";
		return make_pair(minvol,cc*minvol);
	}
	pair<int,int> mincostflow(int s,int t)
	{
		pair<int,int> ans=make_pair(0,0);
		while (1)
		{
			pair<int,int> p=spfa(s,t);
			if (p.first==0) return ans;
			ans.first+=p.first;ans.second+=p.second;
		}
	}
}flow;
int pp[55][55][3],top;
class CurvyonRails
{
        public:
        int getmin(vector <string> board)
        {
			int n=board.size(),m=board[0].size();
			for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
			{
				pp[i][j][0]=++top;
				pp[i][j][1]=++top;
				pp[i][j][2]=++top;
			}
			int S=++top,T=++top,js1=0,js2=0;
			for (int i=0;i<n;i++)
			for (int j=0;j<m;j++) if (board[i][j]!='w')
			{
				if ((i+j)&1)
				{
					flow.getin(S,pp[i][j][0],2,0);
					flow.getin(pp[i][j][0],pp[i][j][1],1,0);
					flow.getin(pp[i][j][0],pp[i][j][1],1,board[i][j]=='C');
					flow.getin(pp[i][j][0],pp[i][j][2],1,0);
					flow.getin(pp[i][j][0],pp[i][j][2],1,board[i][j]=='C');
					if (i) flow.getin(pp[i][j][1],pp[i-1][j][1],1,0);
					if (i!=n-1) flow.getin(pp[i][j][1],pp[i+1][j][1],1,0);
					if (j) flow.getin(pp[i][j][2],pp[i][j-1][2],1,0);
					if (j!=m-1) flow.getin(pp[i][j][2],pp[i][j+1][2],1,0);
					js1+=2;
				}
				else
				{
					flow.getin(pp[i][j][0],T,2,0);
					flow.getin(pp[i][j][1],pp[i][j][0],1,0);
					flow.getin(pp[i][j][1],pp[i][j][0],1,board[i][j]=='C');
					flow.getin(pp[i][j][2],pp[i][j][0],1,0);
					flow.getin(pp[i][j][2],pp[i][j][0],1,board[i][j]=='C');
					js2+=2;
				}
			}
			flow.n=top;//cout<<top<<' '<<js<<endl;
			pair<int,int> ans=flow.mincostflow(S,T);
			if (ans.first!=js1) return -1;
			if (ans.first!=js2) return -1;
			return ans.second;
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
{
        CurvyonRails ___test;
        ___test.run_test(5);
        return 0;
}
// END CUT HERE
