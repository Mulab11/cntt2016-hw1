// BEGIN CUT HERE

// END CUT HERE
#line 5 "DrawingPointsDivOne.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;

struct unit
{int x,y;
};
struct unit a[110];

int n,maxn;
int f[610][610],g[610][610],used[610][610],s[610][610];

int calc(int x,int y)
{if(x<=0 || y<=0) return 0;
 if(x>maxn || y>maxn) return inf;
 return s[x][y];
}

int check(int x)
{int i,j,cnt;
 
 for(i=1;i<=maxn;i++)
 	for(j=1;j<=maxn;j++) //二维(田字形)前缀和 
 		s[i][j]=g[i][j]+calc(i,j-2)+calc(i-2,j)-calc(i-2,j-2);
 for(i=1;i<=maxn;i++)
 	for(j=1;j<=maxn;j++)
	{	if(used[i][j]) continue; //如果这个点在最终结果没有二有因该出现，那么就不合法 
		cnt=calc(i+x,j+x)-calc(i+x,j-x-2)-calc(i-x-2,j+x)+calc(i-x-2,j-x-2);
		if(cnt==(x+1)*(x+1)) return 0;
	}
 return 1;
}

class DrawingPointsDivOne
{	public:
	int maxSteps(vector <int> x, vector <int> y)
	{	int i,j,q;
		
		maxn=600;
		n=x.size();
		for(i=1;i<=n;i++) //放大坐标系 
		{	a[i].x=x[i-1]*2+300;
			a[i].y=y[i-1]*2+300;
		}
		memset(used,0,sizeof(used));
		memset(f,0,sizeof(f));
		for(i=1;i<=n;i++)
		{	used[a[i].x][a[i].y]=1;
			f[a[i].x][a[i].y]=1;
		}
		for(q=1;q<=140;q++) //枚举答案 
		{	memset(g,0,sizeof(g));
			for(i=1;i<=maxn;i++)
				for(j=1;j<=maxn;j++) //构造出当前状态 
				{	if(!f[i][j]) continue;
					g[i-1][j-1]=1;
					g[i-1][j+1]=1;
					g[i+1][j-1]=1;
					g[i+1][j+1]=1;
				}
			if(!check(q)) return q-1; //判断是否合法，不合法的话返回q-1 
			for(i=1;i<=maxn;i++)
				for(j=1;j<=maxn;j++)
					f[i][j]=g[i][j];
		}
		return -1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, maxSteps(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, maxSteps(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-70}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, maxSteps(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {-41,-40,1,-11,-32,-7,24,-11,49,-15,-22,20,-8,54,54,69,16,-30,36,-6,-30,40,64,20,-66,
 -37,-33,-18,-35,36,9,61,-43,45,5,60,-8,-58,65,-66,41,12,34,-11,-57,-38,46,63,-55,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,-24,-2,-4,23,14,1,70,-26,45,15,48,32,-41,54,-47,-67,-46,-9,-53,54,28,-61,11,53,68,
 -33,62,37,-8,-17,-17,48,19,-49,56,-41,16,17,-50,28,59,10,50,23,-16,56,31,-70,-44}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(3, Arg2, maxSteps(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	DrawingPointsDivOne ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
