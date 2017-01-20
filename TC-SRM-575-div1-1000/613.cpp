// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheTilesDivOne.cpp"
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
#define inf 2100000000
using namespace std;
struct flows
{
	int first[600010],last[600010],des[600010],vol[600010],next[600010],opp[600010],tt,n;
	int dis[600010],cop[600010];
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
class TheTilesDivOne
{
        public:
        int find(vector <string> board)
        {
			int n=board.size(),m=board[0].size();
			flow.init(n*m*2+2);
			for (int i=0;i<n;i++)
			for (int j=0;j<m;j++) if (board[i][j]=='.')
			{
				flow.getin(1+i*m+j,1+i*m+j+n*m,1);
				if ((i+j)&1)
				{
					if (i&1)
					{
						flow.getin(2*n*m+1,1+i*m+j,inf);
						if ((i!=0)&&(board[i-1][j]=='.')) flow.getin(1+i*m+j+n*m,1+(i-1)*m+j,1);
						if ((i!=n-1)&&(board[i+1][j]=='.')) flow.getin(1+i*m+j+n*m,1+(i+1)*m+j,1);
						if ((j!=0)&&(board[i][j-1]=='.')) flow.getin(1+i*m+j+n*m,1+i*m+(j-1),1);
						if ((j!=m-1)&&(board[i][j+1]=='.')) flow.getin(1+i*m+j+n*m,1+i*m+(j+1),1);
					}
					else
					{
						flow.getin(1+i*m+j+n*m,2*n*m+2,inf);
						if ((i!=0)&&(board[i-1][j]=='.')) flow.getin(1+(i-1)*m+j+n*m,1+i*m+j,1);
						if ((i!=n-1)&&(board[i+1][j]=='.')) flow.getin(1+(i+1)*m+j+n*m,1+i*m+j,1);
						if ((j!=0)&&(board[i][j-1]=='.')) flow.getin(1+i*m+(j-1)+n*m,1+i*m+j,1);
						if ((j!=m-1)&&(board[i][j+1]=='.')) flow.getin(1+i*m+(j+1)+n*m,1+i*m+j,1);
					}
				}
			}
			return flow.dinic(2*n*m+1,2*n*m+2);
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"X.X",
 "...",
 "X.X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, find(Arg0)); }
	void test_case_1() { string Arr0[] = {"...",
 "...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, find(Arg0)); }
	void test_case_2() { string Arr0[] = {"......X.X.XXX.X.XX."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, find(Arg0)); }
	void test_case_3() { string Arr0[] = {"X.....XXX.XX..XXXXXXXXX...X.XX.XX....X",
 ".XXXX..X..XXXXXXXX....XX.X.X.X.....XXX",
 "....XX....X.XX..X.X...XX.X..XXXXXXX..X",
 "XX.XXXXX.X.X..X..XX.XXX..XX...XXX.X..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(3, Arg1, find(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        TheTilesDivOne ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE
