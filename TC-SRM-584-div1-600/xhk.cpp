// BEGIN CUT HERE

// END CUT HERE
#line 5 "Excavations.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m;
int used[110];
long long ans;
long long f[60][60],g[60],comb[60][60];
pair<int,int> a[110];

class Excavations
{	public:
	long long count(vector <int> kind, vector <int> depth, vector <int> found, int K)
	{	int i,j,k,p,s;
		
		n=kind.size();
		m=K;
		for(i=1;i<=n;i++)
			a[i]=make_pair(depth[i-1],kind[i-1]);	
		memset(used,0,sizeof(used));	
		for(i=0;i<found.size();i++) used[found[i]]=1;
		sort(a+1,a+n+1);
		for(i=0;i<=n;i++) //预处理组合数 
		{	comb[i][0]=1;
			for(j=1;j<=i;j++)
				comb[i][j]=comb[i-1][j-1]+comb[i-1][j];
		}
		a[n+1].first=100001;
		ans=0;
		for(i=1;i<=n+1;i++) //枚举第i个为第一个遇到的没被探测到的建筑 
		{	if(i!=n+1 && used[a[i].second]) continue;
			memset(f,0,sizeof(f));
			f[0][0]=1;
			for(j=0;j<50;j++) //按照种类dp计数 
			{	if(!used[j+1])
				{	for(k=0;k<=m;k++)
						f[j+1][k]=f[j][k];
				}
				else
				{	s=0;
					for(k=1;k<i;k++) //计算i之前深度比i浅的j+1种类的数量 
					{	if(a[k].first>=a[i].first) break;
						if(a[k].second==j+1) s++;
					}
					memset(g,0,sizeof(g));
					for(k=0;k<=m;k++)
						for(p=1;p+k<=m;p++)
							g[k+p]+=f[j][k]*comb[s][p];
					s=0;
					for(k=1;k<i;k++) //计算i之前深度和i一样的j+1种类的数量 
						if(a[k].first==a[i].first && a[k].second==j+1)
							s++;
					for(k=0;k<=m;k++)
						for(p=0;p+k<=m && p<=s;p++)
							f[j+1][k+p]+=g[k]*comb[s][p];
				}
			}
			if(i<=n)
			{	for(k=1;k<m;k++)
					ans+=f[50][k]*comb[n-i][m-k-1];
			}
			else
				ans+=f[50][m];
		}
		return ans;
	}	
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {18, 3, 47, 40, 47, 20, 3, 33, 43, 10, 43, 47, 3, 47, 33, 18, 3, 40, 33, 47, 33, 35, 10, 10, 43, 40, 47, 40, 47, 40, 18, 15, 15, 35, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {64194, 77986, 21359, 67619, 21359, 22878, 78267, 21359, 34650, 34650, 45007, 82232, 34650, 64194, 78267, 34650, 78267, 76559, 45007, 77986, 82232, 22878, 46150, 22878, 76559, 82232, 77986, 26782, 79777, 76559, 78267, 77986, 26782, 2645, 82232}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {18, 15, 33, 3, 47}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 7; long long Arg4 = 31969LL; verify_case(0, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {1, 1, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 15, 10, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; long long Arg4 = 4LL; verify_case(1, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {1, 2, 3, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 10, 10, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; long long Arg4 = 0LL; verify_case(2, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {1, 2, 2, 3, 1, 3, 2, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {12512, 12859, 125, 1000, 99, 114, 125, 125, 114}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 7; long long Arg4 = 35LL; verify_case(3, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {50}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 18; long long Arg4 = 9075135300LL; verify_case(4, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	Excavations ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
