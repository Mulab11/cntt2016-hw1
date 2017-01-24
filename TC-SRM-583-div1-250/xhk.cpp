// BEGIN CUT HERE

// END CUT HERE
#line 5 "TravelOnMars.cpp"
#include<bits/stdc++.h>
using namespace std;

const int maxn=50,maxd=100;
int n,ans;
int dis[maxn];

class TravelOnMars
{	public:
	int minTimes(vector <int> range, int startCity, int endCity)
	{	int i,j,k,s=1,city,next,prev;
		vector<int> a;
		
		n=range.size();
		
		for(i=0;i<n;i++)
			dis[i]=maxd;
		dis[startCity]=0;
		a.push_back(startCity);
		while(dis[endCity]==maxd)
		{	vector<int> b=a;
			a.clear();
			for(i=0;i<b.size();i++)
			{	city=b[i];
				for(j=1;j<=range[city];j++)
				{	next=(city+j)%n;
					if(dis[next]>s)
					{	dis[next]=s;
						a.push_back(next);
					}
					prev=(city-j+n)%n;
					if(dis[prev]>s)
					{	dis[prev]=s;
						a.push_back(prev);
					}
				}
			}
			++s;
		}
		ans=dis[endCity];
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 4; int Arg3 = 2; verify_case(0, Arg3, minTimes(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {2,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 1; int Arg3 = 3; verify_case(1, Arg3, minTimes(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {2,1,1,2,1,2,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 6; int Arg3 = 3; verify_case(2, Arg3, minTimes(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {3,2,1,1,3,1,2,2,1,1,2,2,2,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 13; int Arg3 = 4; verify_case(3, Arg3, minTimes(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TravelOnMars ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
