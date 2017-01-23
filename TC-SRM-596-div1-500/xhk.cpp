// BEGIN CUT HERE

// END CUT HERE
#line 5 "BitwiseAnd.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m;
int b[110];
long long a[110];
vector<long long> ans;

class BitwiseAnd
{	public:
	vector<long long> lexSmallest(vector<long long> subset, int N)
	{	int i,j,k,q,flag;
		long long s;
				
		n=subset.size();
		m=N;
		ans.clear();
		for(i=1;i<=n;i++) a[i]=subset[i-1],ans.push_back(a[i]);
		for(i=1;i<=n;i++) //判断初始是否合法 
			for(j=1;j<=n;j++)
				if(i!=j && (a[i]&a[j])==0)
				{	ans.clear();
					return ans;
				}
		for(i=1;i<=n;i++) //判断初始是否合法
			for(j=1;j<=n;j++)
				for(k=1;k<=n;k++)
					if(i!=j && j!=k && i!=k && ((a[i]&a[j]&a[k])!=0))
					{	ans.clear();
						return ans;
					}
		memset(b,0,sizeof(b));
		for(i=1;i<=n;i++) //统计初始每位数量 
			for(j=0;j<60;j++)
				if(a[i]&(1LL<<j))
				{	b[j]++;
					if(b[j]>2)
					{	ans.clear();
						return ans;
					}
				}
		for(q=n+1;q<=m;q++) //一个一个贪心加入 
		{	s=0;
			for(i=1;i<=n;i++)
			{	if(a[i]&s) continue;
				flag=0;
				for(j=0;j<60;j++)
				{	if(b[j]==2) continue;
					if((a[i]&(1LL<<j))==0) continue;
					b[j]++;
					s|=(1LL<<j);
					flag=1;
					break;
				}
				if(!flag)
				{	ans.clear();
					return ans;
				}
			}
			flag=1;
			k=0;
			for(j=0;j<60;j++) //预留与后面的公共位 
			{	if(b[j]!=0) continue;
				if(k<m-q)
					k++;
				else
					break;
				b[j]=1;
				s|=1LL<<j;
			}
			ans.push_back(s);
			a[++n]=s;
		}
		sort(ans.begin(),ans.end());
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector<long long> &Expected, const vector<long long> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long Arr0[] = {14, 20}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long Arr2[] = {14, 18, 20 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, lexSmallest(Arg0, Arg1)); }
	void test_case_1() { long Arr0[] = {11, 17, 20}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; long Arr2[] = { }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, lexSmallest(Arg0, Arg1)); }
	void test_case_2() { long Arr0[] = {99, 157}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; long Arr2[] = {99, 157, 262, 296 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, lexSmallest(Arg0, Arg1)); }
	void test_case_3() { long Arr0[] = {1152921504606846975}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long Arr2[] = { }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, lexSmallest(Arg0, Arg1)); }
	void test_case_4() { long Arr0[] = {}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; long Arr2[] = {15, 113, 402, 676, 840 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, lexSmallest(Arg0, Arg1)); }
	void test_case_5() { long Arr0[] = {1, 3, 5, 7, 9, 11}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; long Arr2[] = { }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, lexSmallest(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	BitwiseAnd ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
