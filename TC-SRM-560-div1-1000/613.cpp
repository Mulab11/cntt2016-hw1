// BEGIN CUT HERE

// END CUT HERE
#line 5 "BoundedOptimization.cpp"
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
string st;
int n,mx,mp[20][20],ch[20],sum[20];
vector <int> l,r;
double num[20],ans;
void search(int now)
{
	if (now==n)
	{
		for (int i=0;i<n;i++) if (ch[i]==0)
		for (int j=i+1;j<n;j++) if (ch[j]==0)
		{if (!mp[i][j]) return;}
		
		int s=0;
		for (int i=0;i<n;i++)
		{
			if (ch[i]==1) {num[i]=l[i];s+=l[i];}
			else if (ch[i]==2) {num[i]=r[i];s+=r[i];}
		}
		if (s>mx) return;
		
		int all=0,js=0;
		for (int i=0;i<n;i++) if (ch[i]==0)
		{
			sum[i]=0;
			for (int j=0;j<n;j++) if (mp[i][j]) sum[i]+=(ch[j]==1)?l[j]:((ch[j]==2)?r[j]:0);
			all+=sum[i];
			js++;
		}
		
		for (int i=0;i<n;i++) if (ch[i]==0)
		{
			num[i]=(double)sum[i]+(double)(mx-s)/js-(double)all/js;
			if ((num[i]<l[i])||(num[i]>r[i])) return;
		}
		double tmp=0;
		for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++) if (mp[i][j]) tmp+=num[i]*num[j];
		ans=max(ans,tmp);
		return;
	}
	ch[now]=0;search(now+1);
	ch[now]=1;search(now+1);
	ch[now]=2;search(now+1);
}
class BoundedOptimization
{
        public:
        double maxValue(vector <string> expr, vector <int> l_, vector <int> r_, int mx_)
        {
			st="";ans=0;mx=mx_;
			l=l_;r=r_;
			for (int i=0;i<expr.size();i++) st+=expr[i];
			for (int i=0;i<st.size();i+=3)
			{
				int p1=st[i]-'a',p2=st[i+1]-'a';
				mp[p1][p2]=mp[p2][p1]=1;
			}
			n=l.size();
			search(0);
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"ba+cb"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; double Arg4 = 2.25; verify_case(0, Arg4, maxValue(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arr0[] = {"ab"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {20, 20, 20}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 12; double Arg4 = 1.0; verify_case(1, Arg4, maxValue(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arr0[] = {"ca+fc+fa+d","b+da+","dc+c","b","+ed+eb+ea"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10,11,12,13,14,15}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {15,16,17,18,19,20}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 85; double Arg4 = 2029.25; verify_case(2, Arg4, maxValue(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arr0[] = {"db+ea+ik+kh+je+","fj+lk+i","d+jb+h","a+gk+mb+ml+lc+mh+cf+fd+","gc+ka+gf+bh+mj+eg+bf+hf+l","b+al+ja+da+i",
"f+g","h+ia+le+ce+gi+d","h+mc+fe+dm+im+kb+bc+","ib+ma+eb+mf+jk+kc+mg+mk+","gb+dl+ek+hj+dg+hi","+ch+ga+ca+fl+ij+fa+jl+dc+dj+fk","+li+jg"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {57,29,50,21,49,29,88,33,84,76,95,55,11}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {58,80,68,73,52,84,100,79,93,98,95,69,97}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 845; double Arg4 = 294978.3333333333; verify_case(3, Arg4, maxValue(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        BoundedOptimization ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE
