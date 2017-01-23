// BEGIN CUT HERE

// END CUT HERE
#line 5 "GameInDarknessDiv1.cpp"
#include<bits/stdc++.h>
using namespace std;

struct edge
{int u,v,next;
};
struct edge e[100010];

int n,m,pa,pb,ans,num;
int head[10010],dep[10010],f[10010];
char a[60][60];

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

void dfs(int i,int fa) //dfs求出每个子树的深度 
{int j;
 
 f[i]=dep[i];
 j=head[i];
 while(j!=-1)
 {	if(e[j].v!=fa)
 	{	dep[e[j].v]=dep[i]+1;
 		dfs(e[j].v,i);
 		f[i]=max(f[i],f[e[j].v]);
 	}
 	j=e[j].next;
 }
}

class GameInDarknessDiv1
{	public:
	string check(vector <string> field)
	{	int i,j,s,k;
		
		n=field.size();
		m=field[0].length();
		num=0;
		memset(head,-1,sizeof(head));
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				a[i][j]=field[i-1][j-1];
		for(i=1;i<=n;i++) //建图 
			for(j=1;j<=m;j++)
			{	if(a[i][j]=='#') continue;
				if(j<m && a[i][j+1]!='#') add((i-1)*m+j,(i-1)*m+j+1);
				if(i<n && a[i+1][j]!='#') add((i-1)*m+j,i*m+j);
				if(a[i][j]=='A')
					pa=(i-1)*m+j;
				else if(a[i][j]=='B')
					pb=(i-1)*m+j;
			}
		ans=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++) //枚举每个点判断是否能作为分支点，有一个可以就是Bob wins 
			{	if(a[i][j]=='#') continue;
				dep[(i-1)*m+j]=f[(i-1)*m+j]=0;
				dfs((i-1)*m+j,0);
				s=0;
				k=head[(i-1)*m+j];
				while(k!=-1)
				{	if(f[e[k].v]>=3) s++;
					k=e[k].next;
				}
				if(dep[pa]>=dep[pb]+2 && s>=3)
				{	ans=1;
					break;
				}
			}
	 	return ans?"Bob wins":"Alice wins";	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"A.B..",
 "##.##",
 "##.##"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Alice wins"; verify_case(0, Arg1, check(Arg0)); }
	void test_case_1() { string Arr0[] = {"A.B..",
 ".#.#.",
 "#..##"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Bob wins"; verify_case(1, Arg1, check(Arg0)); }
	void test_case_2() { string Arr0[] = {"#...#",
 ".#A#.",
 "..B..",
 ".#.#.",
 "#...#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Alice wins"; verify_case(2, Arg1, check(Arg0)); }
	void test_case_3() { string Arr0[] = {"##..#",
 "A.#..",
 "#B..#",
 "#.##.",
 "....."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Alice wins"; verify_case(3, Arg1, check(Arg0)); }
	void test_case_4() { string Arr0[] = {"##################################################",
 "###..................#................#........###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###.################.########.#######.########.###",
 "###..........#######........#.#######........#.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "############.#######.########.#######.########.###",
 "###B.........#######..........#######..A.......###",
 "##################################################"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Bob wins"; verify_case(4, Arg1, check(Arg0)); }
	void test_case_5() { string Arr0[] = {"###.#",
 "###..",
 "A..B#",
 "###..",
 "###.#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Alice wins"; verify_case(5, Arg1, check(Arg0)); }
	void test_case_6() { string Arr0[] = {".....#.##.##.#.#",
 ".###.#.##.##....",
 "#......B#...#.#.",
 "#.#A#.#.#.#..##.",
 "...#..#....#...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Alice wins"; verify_case(6, Arg1, check(Arg0)); }
	void test_case_7() { string Arr0[] = {"...#.....###....#.....#...#.#.",
 ".#..#.##..#..#.#..###...#.....",
 "..#..#..#...#.#..#....##.#.###",
 ".#.#...###.#..#.#..###....#...",
 "...##.###..#.#..#.#...#.##..#.",
 ".#..#..#..#...#.#.#.#.#..#.#..",
 "..#..#.#.#..#..##.#.#..#.##..#",
 ".#.###.#.##..#.....A##......#.",
 "#.........#.#..#.###..###.#...",
 "..###.#.#.#..#.#....#.....#.#.",
 ".#..#.#.####.#..#.#..#.#.###..",
 "..#...#...#..#.#...#.#..#.#..#",
 "#..#.#..#.#.#..###.#.#.#....#.",
 "..#..##.##...#....#..#.#.####.",
 "#..#...#...#..#.#..###.#......",
 "#.#.##...#..#..#.#....#..#.#.#",
 "....#..##.#..#....#.#.#.#...#.",
 ".#.#..#....#.#.##..#..##..#.#.",
 "..##.#..##.#..#..#..#...#.#...",
 "#.#..##..#..#..#..#..##.#.#.#.",
 "..#.#.#.#.#..#...##.#...#..#..",
 ".##.....#..#.#.#.#..#.##.#..#.",
 "...#.#.#..#..#.###.#..#...#.#.",
 ".#..#....#..#.#...###.#.#..#..",
 ".#.#.#####.#....#..#..#.##.#.#",
 ".#...#......#.#..###B#....#...",
 "..###..####.#..#.#...#.#.#..#.",
 "#.#..#.#..#.#.#..#.#..#....#..",
 "..#.##..#.#.#.####..#.#####..#",
 "#.....#...#.#......#.......#.."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Bob wins"; verify_case(7, Arg1, check(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	GameInDarknessDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
