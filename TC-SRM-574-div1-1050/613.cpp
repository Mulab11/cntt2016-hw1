// BEGIN CUT HERE

// END CUT HERE
//#line 5 "Tunnels.cpp"
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
vector <string> mp;
int ans;
int edx,edy,tl[233],tr[233],f[55][55][55];
bool dfs(int x,int y)
{
	if ((x<0)||(x>=mp.size())||(y<0)||(y>=mp[0].size())||(mp[x][y]!='X')) return false;
	mp[x][y]='S';
	if ((dfs(x-1,y)||dfs(x+1,y)||dfs(x,y-1)||dfs(x,y+1))==false) {edx=x;edy=y;}
	return true;
}
bool pend(int i,int j)
{
	if (i>j) swap(i,j);
	return ((i==0)&&(j==mp[0].size()-1));
}
void update(int &x,int w){x=min(x,w);}
bool check(int x,int y)
{	
	if (mp[x][y]!='X') return false;
	int d=0;
	if ((x!=0)&&(mp[x-1][y]=='X')) d++;
	if ((x!=mp.size()-1)&&(mp[x+1][y]=='X')) d++;
	if ((y!=0)&&(mp[x][y-1]=='X')) d++;
	if ((y!=mp[0].size()-1)&&(mp[x][y+1]=='X')) d++;
	if (d>=2) {cout<<"HAHA";return false;}
	return true;
}
class Tunnels
{
        public:
        int minimumTunnels(vector <string> mmap)
        {
        	mp=mmap;
        	if (mp[0].size()==1)
        	{
        		bool bo=false;
        		for (int i=0;i<mp.size();i++) if (mp[i][0]=='X') bo=true;
        		return (int)bo;
        	}
        	
        	for (int j=0;j<mp[0].size();j++) if (check(0,j))
        	{
        		dfs(0,j);
        		int bgx=0,bgy=j;
        		if ((pend(bgy,edy))&&(bgx==edx)) tl[0]=tr[0]=4;
        		else if (edy==0) tl[edx]=2;
        		else if (edy==mp[0].size()-1) tr[edx]=2;
        		else if ((bgy==0)&&(bgx==edx)) tl[bgx]=2;
        		else if ((bgy==mp[0].size()-1)&&(bgx==edx)) tr[bgx]=2;
        		else ans++;
        	}
        	
        	for (int j=0;j<mp[0].size();j++) if (check(mp.size()-1,j))
        	{
        		dfs(mp.size()-1,j);
        		int bgx=mp.size()-1,bgy=j;
        		if ((pend(bgy,edy))&&(bgx==edx)) tl[mp.size()-1]=tr[mp.size()-1]=4;
        		else if (edy==0) tl[edx]=1;
        		else if (edy==mp[0].size()-1) tr[edx]=1;
        		else if ((bgy==0)&&(bgx==edx)) tl[bgx]=1;
        		else if ((bgy==mp[0].size()-1)&&(bgx==edx)) tr[bgx]=1;
        		else ans++;
        	}cout<<ans<<endl;
        	
			for (int i=1;i<mp.size()-1;i++)
			for (int j=0;j<mp[0].size();j+=mp[0].size()-1) if (check(i,j))
			{
				dfs(i,j);
				int bgx=i,bgy=j;
				/*if ((edx==0)||(bgx==0))
				{
					if (bgy==0) tl[bgx]=2;
					else if (bgy=mp[0].size()-1) tr[bgx]=2;
				}
				else if ((bgx==mp.size()-1)||(edx==mp.size()-1))
				{
					if (bgy==0) tl[bgx]=1;
					else if (bgy==mp[0].size()-1) tr[bgx]=1;
				}*/
				if ((edx==bgx)&&(pend(bgy,edy))) tl[i]=tr[i]=4;
				else if (pend(bgy,edy))
				{
					if (bgy==0) {tl[bgx]=3;tr[edx]=2;}
					else if (bgy=mp[0].size()-1) {tr[bgx]=3;tl[edx]=2;}
				}
				else if ((edy==bgy)&&(edx-bgx>=2))
				{
					if (bgy==0) {tl[bgx]=3;tl[edx]=2;}
					else if (bgy==mp[0].size()-1) {tr[bgx]=3;tr[edx]=2;}
				}
				else
				{
					if (bgy==0) tl[bgx]=1;
					else if (bgy==mp[0].size()-1) tr[bgx]=1;
				}
			}
			//for (int j=0;j<mp[0].size();j++) if (mp[0][j]=='X') {dfs(0,j);ans++;}
			
			memset(f,127,sizeof(f));
			f[mp.size()][0][0]=0;
			for (int i=mp.size();i>=1;i--)
			for (int j=0;j<=mp.size();j++)
			for (int k=0;k<=mp.size();k++)
			if (f[i][j][k]<5e8)
			{
				if (tl[i-1]==4)
				{
					update(f[i-1][j+1][k],f[i][j][k]+1);
					update(f[i-1][j][k+1],f[i][j][k]+1);
					if (j) update(f[i-1][j-1][k+1],f[i][j][k]);
					if (k) update(f[i-1][j+1][k-1],f[i][j][k]);
				}
				else
				{
					int c=f[i][j][k],pl=0,pr=0;
					if (tl[i-1]==1) {c++;pl++;}
					else if (tl[i-1]==2) {if (j) pl--;else c++;}
					else if (tl[i-1]==3) pl++;
					
					if (tr[i-1]==1) {c++;pr++;}
					else if (tr[i-1]==2) {if (k) pr--;else c++;}
					else if (tr[i-1]==3) pr++;
					
					update(f[i-1][j+pl][k+pr],c);
				}
			}
			int minn=2100000000;
			for (int j=0;j<=mp.size();j++)
			for (int k=0;k<=mp.size();k++)
				minn=min(minn,f[0][j][k]);
			for (int i=0;i<mp.size();i++) cout<<tl[i]<<' '<<tr[i]<<endl;
			return ans+minn;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); if ((Case == -1) || (Case == 8)) test_case_8(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"......XXX...X...X...X.......X.X.X.X.XX........X.XX", "........X...................X........X............", "........X...................XX.......X..XXXXXXXXXX", "XXXXXXXXX............................X............", ".....................................XXXXXX......X", "XXXXXXXXXXXXXXXX..........................X......X", "...............X..........................X.......", "XXXXXXX........X..........................XXXXXXXX", "......X........XXXXXXXXX.........................X", "XXXXX.X................X.........................X", "....X.X............XXXXX..........................", "XX..X.X............X..............................", "....X.X............XXX.........................XXX", "XXXXX.X...........................................", "......X........................................XXX", "XXXXXXX...........................................", "..................................................", "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "..................................................", "XXX...............................................", "..X..............................................X", "XXX..............................................X", "..................................................", "XXXXX.............................................", "....X....XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "X...X....X........................................"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, minimumTunnels(Arg0)); }
	void test_case_1() { string Arr0[] = {"X...................XXX.....XXX.XXXXX...........X.", "X.....................XXXX....XX....XXXXXX......XX", "X........................X.....X.........XXX.....X", "XX.....................XXX.....XX..........X.....X", ".X...................XXX........X..........XX.....", ".XXXXXXX.............X..........XX..........X.....", ".......X...........XXX...........X..........XXX..X", "XXXXXX.XX.........XX...........XXX............XXX.", ".....X..X.......XXX..........XXX................X.", "XX.XXX.XX.....XXX............X..................XX", ".X.X..XX.....XX..............XX...................", "XX.X.XX.....XX................XX..................", "...XX.......X..................XX.................", "....XX...XXXX...................XXXXX...........XX", ".....XX.XX..........................XX.........XX.", "......X.X............................X.........X..", "......XX............................XX.........XXX", "X......X...........................XX............X", "XX....XX...........................X............XX", ".XXXX.X............................XX.........XXX.", "....XX..............................XX........X...", ".....X...............................X........XXX.", ".....XX..............................X..........XX", "......XXX...........................XX...........X", "........XX.......................XXXX............X", ".........X.....................XXX...............X", ".........XX....................X..................", "..........X...................XX...............XXX", "..........X...................X................X..", "...XXXXXXXX...................X................XX.", "XXXX.......................XXXX.................XX", "X..........................X......................", "...........................XXXX...................", "..............................XXXX...............X", ".................................X...............X", ".................................XX..............X", "XXX...............................XX..............", "..XX...............................XXXXX.........X", "...X...................................X........XX", "...X...................................X.......XX.", ".XXX...................................X.......X..", "XX.....................................XX......XX.", "........................................X.......X.", "........................................XX......XX", ".........................................XXXX.....", "............................................X.....", "............................................XXXXX.", "................................................X.", "..................................................", "................................................XX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, minimumTunnels(Arg0)); }
	void test_case_2() { string Arr0[] = {".............",
 "XXXXXXXXXXXXX",
 ".............",
 "XXX.......XXX",
 "..........X..",
 "..........XXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, minimumTunnels(Arg0)); }
	void test_case_3() { string Arr0[] = {
 "XXXX...X..",
 "....XXXX.X",
 "XX.......X",
 "..........",
 "....XXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(3, Arg1, minimumTunnels(Arg0)); }
	void test_case_4() { string Arr0[] = {"X........X..",
 ".........XXX",
 "............",
 "XXXXXXXXXXXX",
 "............",
 "XXXXXXXXXXXX",
 "............",
 ".........XXX",
 "..XXXXXXXX.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(4, Arg1, minimumTunnels(Arg0)); }
	void test_case_5() { string Arr0[] = {"...............X.X....X",
 "XXXXX..........X.......",
 "....X..................",
 "XXX.X.........XXXXXXXXX",
 "..X.X.........X........",
 "XXX.X.........XXXXXXXXX",
 "....X..................",
 "XXXXX......XXXXXXXXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(5, Arg1, minimumTunnels(Arg0)); }
	void test_case_6() { string Arr0[] = {".",
 "X",
 "X",
 ".",
 "X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(6, Arg1, minimumTunnels(Arg0)); }
	void test_case_7() { string Arr0[] = {"X.XX",
 "X...",
 "...X",
 "X...",
 "X..X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(7, Arg1, minimumTunnels(Arg0)); }
	void test_case_8() { string Arr0[] = {"...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(8, Arg1, minimumTunnels(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        Tunnels ___test;
        ___test.run_test(1);
        return 0;
}
// END CUT HERE
