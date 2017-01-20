// BEGIN CUT HERE

// END CUT HERE
#line 5 "YamanoteLine.cpp"
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
#include <cassert>
using namespace std;
int n;
vector <int> s1,s2,t1,t2,l1,l2,des[55],js[55];
vector <long long> len[55];
long long dis[55];
int dd[55],cnt[55],cop[10001000];
bool ins[55],err;
void clear()
{
	for (int i=0;i<=n;i++)
	{
		des[i].clear();
		len[i].clear();
		js[i].clear();
		cnt[i]=dis[i]=dd[i]=0;
	}
}
void getin(int c,int d,long long s,int l=0)
{
	//cout<<c<<' '<<d<<' '<<s<<' '<<l<<endl;
	des[c].push_back(d);
	len[c].push_back(s);
	js[c].push_back(l);
}
string spfa()
{
	int head=0,tail=0;
	for (int i=0;i<=n;i++) {cop[++head]=i;ins[i]=true;cnt[i]++;}
	while (head!=tail)
	{
		tail++;if (tail==10000000) tail=0;
		int s=cop[tail];ins[s]=false;
		for (int k=0;k<des[s].size();k++)
		if (dis[des[s][k]]>dis[s]+len[s][k])
		{
			dis[des[s][k]]=dis[s]+len[s][k];
			dd[des[s][k]]=dd[s]+js[s][k];
		
			if (!ins[des[s][k]])
			{
				ins[des[s][k]]=true;
				cnt[des[s][k]]++;
				head++;if (head==10000000) head=0;
				cop[head]=des[s][k];
				if (cnt[des[s][k]]>=2*n+10)
				{
					if (dd[des[s][k]]>0) return "toosmall";
					else if (dd[des[s][k]]<0) return "toobig";
					else {err=true;return "noway";}
				}
			}
		}
	}
	return "ok";
}
string check(long long X)
{
	clear();
	for (int i=0;i<n;i++) getin(i+1,i,-1);
	getin(0,n,X,1);
	for (int k=0;k<s1.size();k++)
	{
		if (s1[k]<=t1[k]) getin(t1[k],s1[k],-l1[k]);
		else getin(t1[k],s1[k],X-l1[k],1);
	}
	for (int k=0;k<s2.size();k++)
	{
		if (s2[k]<=t2[k]) getin(s2[k],t2[k],l2[k]);
		else getin(s2[k],t2[k],-X+l2[k],-1);
	}
	return spfa();
}
class YamanoteLine
{
        public:
        long long howMany(int n_, vector <int> s1_, vector <int> t1_, vector <int> l1_, vector <int> s2_, vector <int> t2_, vector <int> l2_)
        {
        	n=n_;s1=s1_;s2=s2_;t1=t1_;t2=t2_;l1=l1_;l2=l2_;
			long long l=n-1,r=n-1;
			while (check(r)=="toosmall") {r<<=1;if (r>1e12) return 0ll;}
			while (l+1!=r)
			{
				long long mid=(l+r)>>1;
				if (check(mid)=="toosmall") l=mid;else r=mid;
				if (err) return 0;
			}
			long long llim=r;
			
			
			while (check(r)=="ok") {r<<=1;if (r>1e12) return -1ll;}
			while (l+1!=r)
			{
				long long mid=(l+r)>>1;
				if (check(mid)=="ok") l=mid;else r=mid;
				if (err) return 0;
			}
			long long rlim=l;
			
			return rlim-llim+1;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 7; int Arr1[] = {1, 3, 6, 4, 2, 4, 5, 1, 5, 2, 5, 5, 0, 0, 5, 1, 6, 1, 2, 4, 5, 6, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] ={4, 2, 1, 2, 0, 5, 4, 5, 6, 5, 2, 1, 2, 3, 6, 2, 3, 0, 6, 5, 4, 3, 5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {536477, 947899, 178928, 724586, 963817, 239114, 939275, 789295, 211532, 713004, 471517, 393454, 223264, 455674, 217586, 81481, 476463, 1045502, 926258, 244861, 941222, 491485, 475836}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {5, 1, 4, 3, 2, 0, 2, 1, 3, 4, 6, 1, 4, 6, 2, 0, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {4, 2, 6, 0, 4, 4, 3, 0, 1, 3, 1, 0, 3, 2, 0, 6, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] ={937903, 78534, 455914, 732223, 466737, 678325, 223494, 1045758, 875109, 948016, 171545, 1048632, 941740, 256309, 956402, 1146000, 1046372}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 0LL; verify_case(0, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { int Arg0 = 3; int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0,1,2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {1,2,0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {2,2,2}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 4LL; verify_case(1, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { int Arg0 = 3; int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0,1,2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {2,0,1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {3,3,3}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 2LL; verify_case(2, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { int Arg0 = 4; int Arr1[] = {0,1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,3,0,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3,4,4,3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1,3}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {3,1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {5,5}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 4LL; verify_case(3, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_4() { int Arg0 = 4; int Arr1[] = {0,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {5,5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1,3}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {3,1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {4,4}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 0LL; verify_case(4, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_5() { int Arg0 = 5; int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0,2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {2,4}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {2,2}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = -1LL; verify_case(5, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_6() { int Arg0 = 10; int Arr1[] = {5,7,2,3,9,4,6,0,4,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,8,3,9,8,0,8,7,1,7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {61,54,20,64,25,73,83,79,86,56}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {4,5,4,0,8,3,8,5,5,9}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {5,2,0,1,1,4,7,6,8,3}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {1951,6102,3625,5737,1590,1228,9234,1342,9060,1008}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 5726LL; verify_case(6, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        YamanoteLine ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE
