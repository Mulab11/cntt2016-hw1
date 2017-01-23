// BEGIN CUT HERE

// END CUT HERE
#line 5 "CheckerExpansion.cpp"
#include<bits/stdc++.h>
using namespace std;

vector<string> ans;

int calc(long long x,long long y,int i)
{if(x<0 || y<0) return 0;
 if(i==1)
 {	if(x==0 && y==0) return 1;
 	if((x==1 && y==1) || (x==2 && y==0)) return 2;
	return 0;
 }
 if(y>=(1LL<<(i-1)))
 	return calc(x-(1LL<<(i-1)),y-(1LL<<(i-1)),i-1);
 else if(x>=(1LL<<i))
 	return calc(x-(1LL<<i),y,i-1);
 else
 	return calc(x,y,i-1);
}	

class CheckerExpansion
{	public:
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h)
	{	int i,j,flag;
		long long x,y;
		string s;
		
		ans.clear();
		for(j=0;j<h;j++)
		{	s="";
			for(i=0;i<w;i++)
			{	x=x0+i;
				y=y0+h-1-j;
				//cout<<x<<" "<<y<<endl;
				flag=0;
				if(x+y<=2*(t-1)) flag=calc(x,y,60);				
				if(!flag)
					s+='.';
				else if(flag==1)
					s+='A';
				else
					s+='B';
			}
			ans.push_back(s);
		}
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long long Arg0 = 1LL; long long Arg1 = 0LL; long long Arg2 = 0LL; int Arg3 = 4; int Arg4 = 4; string Arr5[] = {"....", "....", "....", "A..." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(0, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { long long Arg0 = 5LL; long long Arg1 = 4LL; long long Arg2 = 1LL; int Arg3 = 3; int Arg4 = 4; string Arr5[] = {"A..", "...", "B..", ".B." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(1, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { long long Arg0 = 1024LL; long long Arg1 = 1525LL; long long Arg2 = 512LL; int Arg3 = 20; int Arg4 = 2; string Arr5[] = {"B...B...B...........", ".B.A.B.A.B.........." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(2, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { long long Arg0 = 53LL; long long Arg1 = 85LL; long long Arg2 = 6LL; int Arg3 = 5; int Arg4 = 14; string Arr5[] = {".....", ".....", "B....", ".B.A.", ".....", ".....", ".....", ".....", ".....", ".....", "B....", ".B...", "..B..", ".A.B." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(3, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	CheckerExpansion ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
