#include<algorithm>
#include<string>
#include<map>
#include<vector>
#include<iostream>
#include<sstream>

using namespace std;

typedef map<int,long long> Map;

vector<int> a,b;
Map h;
	
bool check(long long n)
{int i=0;
 long long ec,c;
 vector<long long> t(a.size());
 map<int,long long>::iterator iter;

 for(iter=h.begin();iter!=h.end();iter++)
 {	ec=iter->second;
 	while(ec>0)
 	{	c=min(ec,n-t[i]);
 		if(a[i]<iter->first || c<=0)
 		{	i++;
 			if(i>=a.size()) return false;
 			continue;
 		}
		ec-=c;
		t[i]+=c;
	}
 }
 return true;
}

class SpaceWarDiv1
{
	public:
	long long minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount)
	{
		a=magicalGirlStrength;
		sort(a.begin(),a.end());
		b=enemyStrength;
		sort(b.begin(),b.end());

		int girlLen=a.size();
		int enemyLen=b.size();
		long long low,high,mid;

		if(a[girlLen-1]<b[enemyLen-1]) return -1;
		h.clear();
		for(int i=0;i<enemyStrength.size();i++)
			h[enemyStrength[i]]+=enemyCount[i];
		low=-1;
		high=1LL<<62;
		while(low<high)
		{	mid=(low+high)/2;
			if(check(mid))
				high=mid;
			else
				low=mid+1;
		}
		return low<(1LL<<62)?low:-1;
	}
// BEGIN CUT HERE
		
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 3, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long Arr2[] = {2, 9, 4}; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 7LL; verify_case(0, Arg3, minimalFatigue(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {2, 3, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long Arr2[] = {2, 9, 4}; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 5LL; verify_case(1, Arg3, minimalFatigue(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {14, 6, 22}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8, 33}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long Arr2[] = {9, 1}; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = -1LL; verify_case(2, Arg3, minimalFatigue(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {869, 249, 599, 144, 929, 748, 665, 37, 313, 99, 33, 437, 308, 137, 665, 834, 955, 958, 613, 417}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {789, 57, 684, 741, 128, 794, 542, 367, 937, 739, 568, 872, 127, 261, 103, 763, 864, 360, 618, 307}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long Arr2[] = {20626770196420, 45538527263992, 52807114957507, 17931716090785, 65032910980630, 88711853198687, 26353250637092,61272534748707, 89294362230771, 52058590967576, 60568594469453, 23772707032338, 43019142889727, 39566072849912,78870845257173, 68135668032761, 36844201017584, 10133804676521, 6275847412927, 37492167783296}; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 75030497287405LL; verify_case(3, Arg3, minimalFatigue(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	SpaceWarDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
