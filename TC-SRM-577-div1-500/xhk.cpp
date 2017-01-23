// BEGIN CUT HERE

// END CUT HERE
#line 5 "EllysChessboard.cpp"
#include<bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
const int inf=1e9;

struct unit
{int x,y;
};
struct unit a[110];

int n,ans;
int ga[10][10];
map<VI,int> h;

int calc(VI A,int x,int y) //计算(x,y)这个点对于A矩形的代价 
{return max(max(abs(A[0]-x),abs(A[1]-x)),max(abs(A[2]-y),abs(A[3]-y)));
}

int check(VI A,int x,int y) //判断(x,y)在不在A代表的矩形内 
{return x>=A[0] && x<=A[1] && y>=A[2] && y<=A[3];
}

int work(VI A) //一个vector里面4个数表示旋转过坐标系的x,y轴最大最小值 
{int i,j,s,ret,flag;
 VI w;
 
 if(h.find(A)!=h.end()) return h[A];
 
 flag=1;
 for(i=1;i<=n;i++)
 	if(!check(A,a[i].x,a[i].y))
 	{	flag=0;
 		break;
 	}
 if(flag) return h[A]=0;
 ret=inf;
 for(i=1;i<=n;i++) //枚举接下来第一个选那个点 
 	if(!check(A,a[i].x,a[i].y))
 	{	s=calc(A,a[i].x,a[i].y);
	 	w=A;
	 	w[0]=min(A[0],a[i].x);
		w[1]=max(A[1],a[i].x);
		w[2]=min(A[2],a[i].y);
		w[3]=max(A[3],a[i].y);
		for(j=1;j<=n;j++) //被新点包含的点随后选取 
			if(j!=i && !check(A,a[j].x,a[j].y) && check(w,a[j].x,a[j].y))
				s+=calc(w,a[j].x,a[j].y);
		ret=min(ret,s+work(w)); //递归下去 
	}
 return h[A]=ret;
}

class EllysChessboard
{	public:
	int minCost(vector <string> board)
	{	int i,j;
		VI w;
		
		n=0;
		for(i=1;i<=8;i++)	
			for(j=1;j<=8;j++)
				if(board[i-1][j-1]=='#')
				{	ga[i][j]=1;
					a[++n].x=i+j; //旋转坐标系，这样可以把x,y轴分开来 
					a[n].y=i-j;
				}
		if(!n) return 0;		
		h.clear();
		ans=inf;
		for(i=1;i<=8;i++)
			for(j=1;j<=8;j++)
			{	if(!ga[i][j]) continue;
				w.clear();
				w.push_back(i+j);
				w.push_back(i+j);
				w.push_back(i-j);
				w.push_back(i-j);
				ans=min(ans,work(w)); //枚举起始点 
			}	
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"........",
 "........",
 "...#....",
 ".#......",
 ".......#",
 "........",
 "........",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(0, Arg1, minCost(Arg0)); }
	void test_case_1() { string Arr0[] = {"........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, minCost(Arg0)); }
	void test_case_2() { string Arr0[] = {".#......",
 "........",
 "..#..#.#",
 "...#..#.",
 "........",
 "...#...#",
 "...#...#",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; verify_case(2, Arg1, minCost(Arg0)); }
	void test_case_3() { string Arr0[] = {"##..####",
 "#####..#",
 "..#.#...",
 "#..##.##",
 ".#.###.#",
 "####.###",
 "#.#...#.",
 "##....#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 275; verify_case(3, Arg1, minCost(Arg0)); }
	void test_case_4() { string Arr0[] = {"########",
 "########",
 "########",
 "########",
 "########",
 "########",
 "########",
 "########"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 476; verify_case(4, Arg1, minCost(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	EllysChessboard ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
