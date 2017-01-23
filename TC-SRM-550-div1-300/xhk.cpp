// BEGIN CUT HERE

// END CUT HERE
#line 5 "RotatingBot.cpp"
#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> PI;
int n,bx,by,sx,sy,ans;
int b[60],a[210][210],v[4][2]={0,1,-1,0,0,-1,1,0};
vector<PI> c;

int solve(int d)
{int i,j,x,y,nx,ny;
 
 bx=by=sx=sy=100;
 x=100;
 y=100;
 memset(a,0,sizeof(a));
 a[x][y]=1;
 c.clear();
 for(i=1;i<=n;i++)
 {	for(j=0;j<b[i];j++)
 	{	nx=x+v[d][0];
 		ny=y+v[d][1];
		if(a[nx][ny]) return -1;
		x=nx;
		y=ny;
		bx=max(bx,x);
		by=max(by,y);
		sx=min(sx,x);
		sy=min(sy,y);
		a[x][y]=1;
	}
	nx=x+v[d][0];
	ny=y+v[d][1];
	if(!a[nx][ny] && i!=n) c.push_back(make_pair(nx,ny));
	d=(d+1)%4;
 }
 for(i=0;i<c.size();i++)
 	if(c[i].first>=sx && c[i].first<=bx && c[i].second>=sy && c[i].second<=by)
 		return -1;
 return (bx-sx+1)*(by-sy+1);
}

class RotatingBot
{	public:
	int minArea(vector <int> moves)
	{	int i,j,s;
		
		n=moves.size();
		for(i=1;i<=n;i++) b[i]=moves[i-1];
		if(n==1) return moves[0]+1;
		ans=solve(0);
		s=solve(1);
		if(by==100 && sx==100)
		{	if(s<ans || ans==-1)
				ans=s;
		}
		return ans;
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
{	RotatingBot ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
