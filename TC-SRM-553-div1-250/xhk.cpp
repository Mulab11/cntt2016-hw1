// BEGIN CUT HERE

// END CUT HERE
#line 5 "Suminator.cpp"
#include<bits/stdc++.h>
using namespace std;


struct data
{int x;
 long long y;
};

data operator +(data A,data B)
{return (data){A.x+B.x,A.y+B.y};
}

int n,top;
int a[110];
long long ans;
data b[110];

void work(data A)
{if(A.x==-1)
 {	if(top>1)
 	{	b[top-1]=b[top-1]+b[top];
 		top--;
 	}
 }
 else
 	b[++top]=A;
}

class Suminator
{	public:
	int findMissing(vector <int> program, int wantedResult)
	{	int i,j;
		
		n=program.size();
		for(i=1;i<=n;i++) a[i]=program[i-1];
		top=0;
		for(i=1;i<=n;i++)
			if(a[i]==-1 || a[i]==0)
				work((data){-1,0});
			else
				work((data){0,a[i]});
		if(b[top].y==wantedResult) return 0;
		top=0;
		for(i=1;i<=n;i++)
			if(a[i]==-1)
				work((data){1,0});
			else if(a[i]==0)
				work((data){-1,0});
			else
				work((data){0,a[i]});
		//cout<<top<<" "<<b[top].x<<" "<<b[top].y<<" "<<ans<<endl;		
		if(b[top].x==0)
		{	if(b[top].y==wantedResult)
				return 1;
			else
				return -1;
		}
		ans=(wantedResult-b[top].y)/b[top].x;
		if(ans>0)
			return ans;
		else
			return -1;		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {7,-1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 3; verify_case(0, Arg2, findMissing(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {100, 200, 300, 0, 100, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 600; int Arg2 = 0; verify_case(1, Arg2, findMissing(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-1, 7, 3, 0, 1, 2, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; int Arg2 = 0; verify_case(2, Arg2, findMissing(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {-1, 8, 4, 0, 1, 2, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; int Arg2 = -1; verify_case(3, Arg2, findMissing(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1000000000, 1000000000, 1000000000,  1000000000, -1, 0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; int Arg2 = -1; verify_case(4, Arg2, findMissing(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {7, -1, 3, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = -1; verify_case(5, Arg2, findMissing(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	Suminator ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
