// BEGIN CUT HERE

// END CUT HERE
#line 5 "Orienteering.cpp"
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
vector <string> vec;
int p1,p2,tp,all,dis[2010][2010],dt[2010][2010];
bool near[2010][2010],pd[2010];
double c[310][310];
void dfs(int i,int j,int pre,int bg,int d,bool pd)
{
	if (dt[i][j]!=bg)
	{
		dis[bg][dt[i][j]]=d;
		near[bg][dt[i][j]]=pd;//if (pd) cout<<bg<<' '<<dt[i][j]<<endl;
		pd=false;
	}
	if ((i!=0)&&(dt[i-1][j]!=pre)&&(vec[i-1][j]!='#')) dfs(i-1,j,dt[i][j],bg,d+1,pd);
	if ((i!=p1-1)&&(dt[i+1][j]!=pre)&&(vec[i+1][j]!='#')) dfs(i+1,j,dt[i][j],bg,d+1,pd);
	if ((j!=0)&&(dt[i][j-1]!=pre)&&(vec[i][j-1]!='#')) dfs(i,j-1,dt[i][j],bg,d+1,pd);
	if ((j!=p2-1)&&(dt[i][j+1]!=pre)&&(vec[i][j+1]!='#')) dfs(i,j+1,dt[i][j],bg,d+1,pd);
}
class Orienteering
{
        public:
        double expectedLength(vector <string> vec_, int d)
        {
        	vec=vec_;
			p1=vec.size();p2=vec[0].size();
			tp=0;all=0;
			for (int i=0;i<p1;i++)
			for (int j=0;j<p2;j++)
				if (vec[i][j]!='#') {dt[i][j]=++tp;if (vec[i][j]=='*') {pd[dt[i][j]]=true;all++;}}
			for (int i=0;i<p1;i++)
			for (int j=0;j<p2;j++)
				if (vec[i][j]!='#') dfs(i,j,-1,dt[i][j],0,true);
			c[0][0]=1;
			for (int i=1;i<=300;i++)
			{
				c[i][0]=1;
				for (int j=1;j<=i;j++) c[i][j]=c[i-1][j]+c[i-1][j-1];
			}
			
			double ths0=0;
			for (int i=1;i<=tp;i++)
			for (int j=i+1;j<=tp;j++)
			if (near[i][j])
			{
				int js=0;
				for (int k=1;k<=tp;k++) if ((pd[k])&&(dis[i][k]>=dis[j][k])) js++;
				ths0+=(c[all][d]-c[js][d]-c[all-js][d])*dis[i][j];
			}
			ths0/=c[all][d];
			
			double ths1=0;
			for (int i=1;i<=tp;i++) if (pd[i])
			for (int j=i+1;j<=tp;j++) if (pd[j])
			{
				int js=0;
				for (int k=1;k<=tp;k++) if ((i!=k)&&(j!=k)&&(pd[k]))
				{
					if (max(dis[i][k],dis[j][k])<dis[i][j]) js++;
					else if ((dis[i][k]==dis[i][j])&&(dis[j][k]<dis[i][j])&&(k>j)) js++;
					else if ((dis[j][k]==dis[i][j])&&(dis[i][k]<dis[i][j])&&(k>i)) js++;
					else if ((dis[i][k]==dis[i][j])&&(dis[j][k]==dis[i][j])&&(k>i)&&(k>j)) js++;
				}
				ths1+=c[js][d-2]*dis[i][j];
			}
			ths1/=c[all][d];
			
			cout<<ths0<<' '<<ths1<<endl;
			return 2*ths0-ths1;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"*#..#",
 ".#*#.",
 "*...*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; double Arg2 = 3.8333333333333353; verify_case(0, Arg2, expectedLength(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"*#..#",
 ".#*#.",
 "*...*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; double Arg2 = 8.0; verify_case(1, Arg2, expectedLength(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"#.#**",
 "....#",
 "#*#**",
 "**#*#",
 "#..##",
 "*#..#",
 ".#.#.",
 "....*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; double Arg2 = 10.825000000000024; verify_case(2, Arg2, expectedLength(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"###################",
 "#*###############*#",
 "#.....#######.....#",
 "#*###*.#.*.#.*###*#",
 "#*####*.*#*.*####*#",
 "#*#####*###*#####*#",
 "###################"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; double Arg2 = 30.272233648704244; verify_case(3, Arg2, expectedLength(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"**##*.**#..#.*...*#...*#..#.##..#..#.#*...#.##*##.",
 ".#..###..#..#.#.##..#.#.*#.*..#..#.#*..##.#*...*..",
 "..#.....###.#*.##..#.#.#*..#.#..#....#..#...#*####",
 ".#.##*#.*#..#*#*.#.#...*.#.*#.#.##.#*.##.#.#..*...",
 "..*.*#*.###.#..#.#..##.##.*#..#.....#.....#..#.#.#",
 ".#.##.#..##..*#..#.#...#*##*#*..#.#.#.#.##.##.#.#*",
 "..##....#..#.#*#...*.##...#.#.####...#.#*.....#...",
 ".#.*#.##.*#*.#*.#.#.#..#.#..#.#*#.###..##.##.#.##*",
 ".*.#*..*.#.#...#.*##.#.**.#.*...**..*#..#.#.#*.#..",
 ".#*.#*##....##.#.#*..*.###.#.##.##.#.#.#....#.#*.#",
 "*.#..#*#.#*#*....#.#.#..*#**...##.#.#.**#*##.*.#..",
 ".#*.##..##..##.#.#..#.#.###.###...#...#*#..##*#.#.",
 "#..#*.#..*.###..#.#...#.###.#.#*#.#.#**##.#...*.#*",
 "..#..#.#.##.#..#.**.##*#.#**.**..#.#..#...#.##*#..",
 ".#*#.#.*..#.*#...#.#...#...#.##.#..*#*.##*....###.",
 ".*.#.#.#.#*#..*##.**.##*##..#.*#.#*###..*.#.##.#..",
 ".#......#...#.#.*#.#.#..#..#.#*#....#*.#*#.*#..*.#",
 "#..####..#*#...#*.#..#.###...#.#.#.###*#..##*##.#.",
 ".#.*..#.#...#.#..#.##...#..#.#.#.#.###..##..*.*.*.",
 ".#.#.#.#..##.*..#.*.#.##.#..##*...#.#..#.#.##.#.##",
 ".#..#*.#.#..#.##..##..#.*..#.*#.#...##....#...###.",
 ".#.#.#.#*.#.#..#.#..#..#.#.*#...#.##...#.##.##.*..",
 ".#...#.#.##.#.#..*#.*#..###..#.#.#*###.##...#*.##.",
 ".#.##.*.......*.#.*#.#.#*###..*...*..#.*.##.#.#..#",
 "...###*####*#.#..##*...#..#..##.#.#.#..##*#*.*.*#.",
 "#.#.#....*#..#.#.#.#.##..#*.#...#..#.#*#...#.##.*.",
 "..*.#*##.#.#*#.###...#..##.#.#.#*###*#.*#.#.*###.#",
 "##*##..##...#.....##.#.#.**#..#*.....##.#..#*.#.*.",
 ".....#.*.##..##.##*.*#...#.#.#.##.#*#.**..#..#.#.#",
 "##.#.#*##.#.#.*.*.#.#*#.#.#....*...#*##*##.#....#.",
 "*.**#**....*..##.#*.*.**..##.###.##.....##...##.**",
 "#.####.##*#*##..#.*#*#.##*...#.##..#.##....#*..##.",
 "....#...##.#...#*.#..##.##.#*..*.#....##.#.*##...#",
 "#.#..*##*..#.#..#..#..#*....#.##..##.#*##.##.*##..",
 "..#.#*.*.##.#.#*#.#*##.###.##...#............#*.#.",
 "#.#.##.#....*....*..##..*#.#.#.###.#.#.#.###..#..#",
 ".#**..#*#.#*#*#.#.#...*##....##.#*..#..#*..*#..#..",
 "...#*#.....#..#.#..#*#.*##.#..#.#.##..#.*#*#.#...#",
 ".#*.###.#.#.#.#.*#*##.##..#.#*..#...#.#.#..#*.*#..",
 "#*.#.#.#..#..#..#....*#.*##..##.#.#..#...##.#.#..#",
 "*.#..#..#...#..##.#*#..#.#*#.#.#.###..#.#*...#.#..",
 "#...#.#...#.#.#..#.*.#*.....**.*..#*##.#*.##....##",
 "#*#....#*#..#.*.###*#..#*##.##.#.#...#.*.##.##.##.",
 "..##*##*..#*#.#..#*.*##*.##.#...#.#.#.#.#..*#.##..",
 "#...#*##.#*#**.##.*#.*.##..*.#*#**....#**##...*.*#",
 "*#.##......*#.##.#.#.##**.#.#.#.#.#.##..#...#*#*#*",
 "*....##.#.#..#.....#..##.#....*....#.#.##.#.#.##**",
 "#.##*#...#..#.#.##..#..##.##.##.##........##.#*#.#",
 "..#...#.#*#*..*#..*#.*#.#......##.#.#.#*#..#..****",
 ".###.#..#...#.#..#..#.#...#.#.#...**.#..*#*.*##*#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 150; double Arg2 = 1309.4951033725558; verify_case(4, Arg2, expectedLength(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        Orienteering ___test;
        ___test.run_test(2);
        return 0;
}
// END CUT HERE
