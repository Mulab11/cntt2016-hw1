// BEGIN CUT HERE

// END CUT HERE
#line 5 "Ear.cpp"
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
vector <int> r,bx,by;
int times(int x1,int y1,int x2,int y2){return x1*y2-x2*y1;}
int findl(int a)
{
	for (int i=0;i<r.size();i++) if (r[i]>=bx[a]) return i-1;
	return r.size()-1;
}
int findr(int a)
{
	for (int i=r.size()-1;i>=0;i--) if (r[i]<=bx[a]) return i+1;
	return 0;
}
int getmax(int a,int b)
{
	for (int i=0;i<r.size();i++) if ((r[i]>=bx[a])||(times(bx[a]-r[i],by[a],bx[b]-r[i],by[b])<=0)) return i-1;
	return -1;
}
class Ear
{
        public:
        long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY)
        {
			string red,bluex,bluey;
			for (int i=0;i<redX.size();i++) red+=redX[i];
			for (int i=0;i<blueX.size();i++) bluex+=blueX[i];
			for (int i=0;i<blueY.size();i++) bluey+=blueY[i];
			red+=" ";bluex+=" ";bluey+=" ";
			
			int now=0;
			for (int i=0;i<red.size();i++)
			{
				if (red[i]==' ') {r.push_back(now);now=0;}
				else now=now*10+red[i]-'0';
			}
			for (int i=0;i<bluex.size();i++)
			{
				if (bluex[i]==' ') {bx.push_back(now);now=0;}
				else now=now*10+bluex[i]-'0';
			}
			for (int i=0;i<bluey.size();i++)
			{
				if (bluey[i]==' ') {by.push_back(now);now=0;}
				else now=now*10+bluey[i]-'0';
			}
			sort(r.begin(),r.end());
			long long ans=0;
			for (int p=0;p<bx.size();p++)
			for (int q=0;q<bx.size();q++) if (by[p]>by[q])
			{
				int ra=min(getmax(q,p),findl(p)),rb=findl(q),lc=findr(q);
				for (int i=0;i<r.size();i++)
				{
					if ((bx[q]>=r[i])||(bx[p]>=r[i])) continue;
					if (times(bx[q]-r[i],by[q],bx[p]-r[i],by[p])>=0) continue;
					ans+=(2ll*(rb-ra)+ra)*(ra+1)*(i-lc)/2;
				}
			}
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"3 2 8 7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"5 4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2 4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 1LL; verify_case(0, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"3 2 8 7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"2 8"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"3 4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(1, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"1 2 6 9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"3 6 8 5"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 5 4 3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 4LL; verify_case(2, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"10000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"10000 9999"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"10000 9999"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(3, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"100 2", "00", " 39", "9", " 800 900 9", "99"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"15", "0 250 ", "349"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2 3 1"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 12LL; verify_case(4, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"1", " ", "2", " ", "3", " ", "4 5 6", " 7 8 9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"4", " ", "5", " ", "6", " 7 ", "8"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1", " 2 ", "3 4", " 5"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 204LL; verify_case(5, Arg3, getCount(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        Ear ___test;
        ___test.run_test(5);
        return 0;
}
// END CUT HERE
