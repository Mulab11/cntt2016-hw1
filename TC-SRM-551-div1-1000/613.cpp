// BEGIN CUT HERE

// END CUT HERE
#line 5 "SweetFruits.cpp"
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
#define mo 1000000007ll
using namespace std;
int a[55],n,all;
vector <int> dt[2][55];
long long ans[55],c[55][55],mat[55][55],tree[55];
void search(int now,int ed,int tp,int num=0,int sum=0)
{
	if (now>ed)
	{
		dt[tp][num].push_back(sum);
		return;
	}
	search(now+1,ed,tp,num,sum);
	if (a[now]!=-1) search(now+1,ed,tp,num+1,sum+a[now]);
}
void addedge(int s,int t)
{
	mat[s][t]--;mat[t][s]--;
	mat[s][s]++;mat[t][t]++;
}
long long getmi(long long a,long long x)
{
	if (!x) return 1;
	long long ans=getmi(a,x>>1);
	ans=ans*ans%mo;
	if (x&1) ans=ans*a%mo;
	return ans;
}
long long guass()
{
	/*for (int i=1;i<n;i++)
	for (int j=1;j<n;j++)
	{
		cout<<mat[i][j]<<' ';
		if (j==n-1) cout<<endl;
	}*/
	long long ans=1;
	for (int i=1;i<n;i++)
	{
		int ths=-1;
		for (int j=i;j<n;j++) if (mat[j][i]!=0) {ths=j;break;}
		if (ths==-1) return 0;
		for (int j=1;j<n;j++) swap(mat[i][j],mat[ths][j]);
		if (i!=ths) ans=ans*(mo-1)%mo;
		
		long long d=getmi(mat[i][i],mo-2);ans=ans*mat[i][i]%mo;
		for (int j=1;j<n;j++) mat[i][j]=mat[i][j]*d%mo;
		for (int j=1;j<n;j++) if (i!=j)
		{
			long long d=mat[j][i];
			for (int k=1;k<=n;k++) mat[j][k]=(mat[j][k]-d*mat[i][k]%mo+mo)%mo;
		}
	}
	/*for (int i=1;i<n;i++)
	for (int j=1;j<n;j++)
	{
		cout<<mat[i][j]<<' ';
		if (j==n-1) cout<<endl;
	}*/
	//cout<<ans<<endl<<endl;
	return ans;
}
void calctree()
{
	for (int d=0;d<=all;d++)
	{
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) mat[i][j]=0;
		for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
		{
			//if ((i<=d)||(i>all)) addedge(i,j);
			//else if (j>all) addedge(i,j);
			if((j>all)||((i<=d)&&(j<=d))) addedge(i,j);
		}
		tree[d]=guass();
	}
}
class SweetFruits
{
        public:
        int countTrees(vector <int> sw, int mx)
        {
			n=sw.size();
			for (int i=1;i<=n;i++) a[i]=sw[i-1];
			search(1,n/2,0);
			search(n/2+1,n,1);
			for (int i=0;i<=n/2+1;i++)
			{
				sort(dt[0][i].begin(),dt[0][i].end());
				sort(dt[1][i].begin(),dt[1][i].end());
			}
			for (int i=0;i<=n/2+1;i++)
			for (int j=0;j<=n/2+1;j++)
			{
				for (int k=0;k<dt[0][i].size();k++)
					ans[i+j]+=upper_bound(dt[1][j].begin(),dt[1][j].end(),mx-dt[0][i][k])-dt[1][j].begin();
				ans[i+j]%=mo;
			}
			//for (int i=0;i<=n;i++) printf("%d %d\n",i,ans[i]);
			all=0;for (int i=1;i<=n;i++) all+=(a[i]!=-1);
			calctree();
			c[0][0]=1;
			for (int i=1;i<=50;i++)
			{
				c[i][0]=1;
				for (int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mo;
			}
			for (int i=1;i<=n;i++)
			for (int j=0;j<i;j++)
				tree[i]=(tree[i]-tree[j]*c[i][j]%mo+mo)%mo;
			//for (int i=0;i<=n;i++) cout<<tree[i]<<endl;
			long long allans=0;
			for (int i=0;i<=all;i++) allans=(allans+tree[i]*ans[i])%mo;
			return allans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, -1, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; verify_case(0, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 2, -1, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 7; verify_case(1, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-1, -1, 2, 5, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 20; verify_case(2, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {2, 6, 8, 4, 1, 10, -1, -1, -1, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; int Arg2 = 17024000; verify_case(3, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1078451, -1, 21580110, 8284711, -1, 4202301, 3427559, 8261270, -1, 16176713,
22915672, 24495540, 19236, 5477666, 12280316, 3305896, 17917887, 564911, 22190488, 21843923,
23389728, 14641920, 9590140, 12909561, 20405638, 100184, 23336457, 12780498, 18859535, 23180993,
10278898, 5753075, 21250919, 17563422, 10934412, 22557980, 24895749, 7593671, 10834579, 5606562}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 245243285; int Arg2 = 47225123; verify_case(4, Arg2, countTrees(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        SweetFruits ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE
