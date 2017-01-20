// BEGIN CUT HERE

// END CUT HERE
#line 5 "RotatingBot.cpp"
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
struct point
{
	int x,y;
	friend point operator +(point a,point b){return (point){a.x+b.x,a.y+b.y};}
	friend point operator *(int a,point b){return (point){a*b.x,a*b.y};}
};
const point ff[4]={(point){1,0},(point){0,1},(point){-1,0},(point){0,-1}};
bool vis[5010][5010];
class RotatingBot
{
        public:
        int minArea(vector <int> vec)
        {
        	memset(vis,0,sizeof(vis));
			point wei=(point){2505,2505};vis[2505][2505]=true;
			int minx=2505,maxx=2505,miny=2505,maxy=2505,now=0;
			for (int i=1;i<=vec.size();i++)
			{
				for (int j=1;j<=vec[i-1];j++)
				{
					wei=wei+ff[now];
					if (vis[wei.x][wei.y]) return -1;
					vis[wei.x][wei.y]=true;
				}
				now=(now+1)&3;
				minx=min(minx,wei.x);
				maxx=max(maxx,wei.x);
				miny=min(miny,wei.y);
				maxy=max(maxy,wei.y);
			}
			memset(vis,0,sizeof(vis));
			wei=(point){2505,2505};vis[2505][2505]=true;now=0;
			for (int i=1;i<=vec.size();i++)
			{
				for (int j=1;j<=vec[i-1];j++)
				{
					wei=wei+ff[now];
					//if (vis[wei.x][wei.y]) return -1;
					vis[wei.x][wei.y]=true;
				}
				if (!vis[wei.x+ff[now].x][wei.y+ff[now].y])
					if (!((now==0)&&(wei.x==maxx)))
						if (!((now==1)&&(wei.y==maxy)))
							if (!((now==2)&&(wei.x==minx)))
								if (!((now==3)&&(wei.y==miny)))
									if (!(i==vec.size()))
										return -1;
				now=(now+1)&3;
			}
			return (maxx-minx+1)*(maxy-miny+1);
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {15}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(0, Arg1, minArea(Arg0)); }
	void test_case_1() { int Arr0[] = {3,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 44; verify_case(1, Arg1, minArea(Arg0)); }
	void test_case_2() { int Arr0[] = {1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(2, Arg1, minArea(Arg0)); }
	void test_case_3() { int Arr0[] = {9,5,11,10,11,4,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 132; verify_case(3, Arg1, minArea(Arg0)); }
	void test_case_4() { int Arr0[] = {12,1,27,14,27,12,26,11,25,10,24,9,23,8,22,7,21,6,20,5,19,4,18,3,17,2,16,1,15}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 420; verify_case(4, Arg1, minArea(Arg0)); }
	void test_case_5() { int Arr0[] = {8,6,6,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(5, Arg1, minArea(Arg0)); }
	void test_case_6() { int Arr0[] = {8,6,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 63; verify_case(6, Arg1, minArea(Arg0)); }
	void test_case_7() { int Arr0[] = {5,4,5,3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 30; verify_case(7, Arg1, minArea(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        RotatingBot ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
