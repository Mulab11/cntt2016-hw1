// BEGIN CUT HERE

// END CUT HERE
#line 5 "InducedSubgraphs.cpp"
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
#define mo 1000000009ll
using namespace std;
long long fac[55],nifac[55],a[55][55],b[55][55],ls[55][55],f[42][42][42][42];
vector <int> des[55];
int dis[55][55],size[55][55],n;
long long getmi(long long a,long long x)
{
	if (!x) return 1;
	long long ans=getmi(a,x>>1);
	ans=ans*ans%mo;
	if (x&1) ans=ans*a%mo;
	return ans;
}
void dfs(int s,int pre)
{
	if (a[pre][s]) return;
	a[pre][s]=size[pre][s]=1;
	for (int k=0;k<des[s].size();k++) if (des[s][k]!=pre)
	{
		dfs(des[s][k],s);
		size[pre][s]+=size[s][des[s][k]];
		a[pre][s]=a[pre][s]*a[s][des[s][k]]%mo*nifac[size[s][des[s][k]]]%mo;
	}
	a[pre][s]=a[pre][s]*fac[size[pre][s]-1]%mo;
}
void work(int s,int pre)
{
	if (b[pre][s]) return;
	b[pre][s]=1;
	f[pre][s][0][0]=1;
	int sz=0;
	for (int k=0;k<des[s].size();k++) if (des[s][k]!=pre)
	{
		work(des[s][k],s);
		memset(ls,0,sizeof(ls));
		for (int a=0;a<=size[s][des[s][k]];a++)
		for (int b=0;b<=size[s][des[s][k]];b++)
		for (int c=0;c<=sz;c++)
		for (int d=0;d<=sz;d++)
			ls[a+c][b+d]=(ls[a+c][b+d]+f[s][des[s][k]][a][b]*f[pre][s][c][d]%mo*nifac[a]%mo*nifac[b])%mo;
		sz+=size[s][des[s][k]];
		for (int a=0;a<=sz;a++)
		for (int b=0;b<=sz;b++)
			f[pre][s][a][b]=ls[a][b];
	}
	for (int i=0;i<=size[pre][s];i++)
	for (int j=0;j<=size[pre][s];j++)
		f[pre][s][i][j]=f[pre][s][i][j]*fac[i]%mo*fac[j]%mo;
	f[pre][s][0][size[pre][s]]=f[pre][s][size[pre][s]][0]=a[pre][s];
}
		
class InducedSubgraphs
{
        public:
        int getCount(vector <int> edge1, vector <int> edge2, int d)
        {
			fac[0]=nifac[0]=1;
			for (int i=1;i<=50;i++)
			{
				fac[i]=fac[i-1]*i%mo;
				nifac[i]=getmi(fac[i],mo-2);
				//cout<<i<<' '<<nifac[i]<<endl;
			}
			n=edge1.size()+1;
			if (d==1) {cout<<"HAHAHA";return fac[n];}
			memset(dis,127/3,sizeof(dis));
			for (int i=0;i<n;i++) dis[i][i]=0;
			for (int i=0;i<n-1;i++)
			{
				dis[edge1[i]][edge2[i]]=dis[edge2[i]][edge1[i]]=1;
				des[edge1[i]].push_back(edge2[i]);
				des[edge2[i]].push_back(edge1[i]);
			}
			for (int i=0;i<n;i++) dfs(i,n);
			for (int k=0;k<n;k++)
			for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			//for (int i=0;i<n;i++) for (int j=0;j<n;j++) cout<<dis[i][j];
			long long ans=0;
			if (d*2<=n)
			{
				for (int i=0;i<n;i++)
				for (int j=0;j<n;j++)
				if (dis[i][j]==n-2*d+1)
				{
					
					int k,x,y;
					for (k=0;k<des[i].size();k++) if (dis[des[i][k]][j]<dis[i][j]) break;
					x=des[i][k];
					//if (k==des[i].size()) assert(0);
					for (k=0;k<des[j].size();k++) if (dis[des[j][k]][i]<dis[i][j]) break;
					y=des[j][k];
					//cout<<i<<' '<<j<<x<<' '<<y<<endl;
					if ((size[x][i]==d)&&(size[y][j]==d)) ans=(ans+a[x][i]*a[y][j])%mo;
				}
			}
			else
			{
				for (int i=0;i<n;i++) work(i,n);
				for (int i=0;i<n;i++)
				{
					ans=(ans+f[n][i][n-d][n-d])%mo;
					//cout<<f[n][i][n-d][n-d]<<endl;
				}
				ans=ans*fac[2*d-n-1]%mo;
			}
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 2; verify_case(0, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0, 1, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 12; verify_case(1, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {5, 0, 1, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2, 4, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 4; verify_case(2, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 11; int Arg3 = 481904640; verify_case(3, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {5, 9, 4, 10, 10, 0, 7, 6, 2, 1, 11, 8}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 10, 3, 0, 6, 1, 1, 12, 12, 7, 11}
; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; int Arg3 = 800; verify_case(4, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {0, 5, 1, 0, 2, 3, 5}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 7, 0, 6, 7, 5, 0}
; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 0; verify_case(5, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_6() { int Arr0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 890964601; verify_case(6, Arg3, getCount(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        InducedSubgraphs ___test;
        ___test.run_test(3);
        return 0;
}
// END CUT HERE
