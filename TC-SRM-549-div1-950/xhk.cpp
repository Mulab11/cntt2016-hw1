// BEGIN CUT HERE

// END CUT HERE
#line 5 "CosmicBlocks.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,dep,L,R,ans;
int a[20],d[20],c[20],c1[20],c2[20],used[20];
vector<int> b[20];

void calc(long long sta)
{int i,j,k,p,s=0,flag,s1,mask;
 
 //cout<<sta<<endl;	
 for(i=0;i<n;i++)
 {	c1[i]=d[i+1]!=1?a[i+1]:0;
 	c2[i]=d[i+1]!=dep?a[i+1]:0;
 }
 for(k=0;k<n;k++)
	for(p=0;p<n;p++)
		if(sta&(1LL<<(k*n+p)))
		{	c2[p]--;
		 	c1[k]--;
		}
 for(i=0;i<n;i++)
 	if(c1[i]<0 || c2[i]<0) return;		 	
 for(p=0;p<(1<<n);p++)
 {	mask=0;
 	s1=0;
	for(k=0;k<n;k++)
		if(p&(1<<k))
		{	s1+=c1[k];
			mask|=(sta>>(k*n))&((1<<n)-1);
		}
		//cout<<s1<<" "<<c1[0]<<" "<<c2[0]<<endl;	
	for(k=0;k<n;k++)
		if(mask&(1<<k)) s1-=c2[k];
	if(s1>0) return;
 }
 s=0;
 for(i=1;i<=n;i++) c[i]=i-1;
 for(;;)
 {	flag=1;	
 	for(i=1;i<=n;i++)
 	{	for(j=i+1;j<=n;j++)
 			if(sta&(1LL<<(c[j]*n+c[i]))) flag=0;
 		if(!flag) break;	
 	}
 	s+=flag;
 	if(!next_permutation(c+1,c+n+1)) break;
 }
 //cout<<sta<<" "<<s<<endl;
 if(s>=L && s<=R) ans++;
}

long long check()
{int i,j,k;
 long long ret=0;

 memset(used,0,sizeof(used));
 for(i=1;i<=n;i++) used[d[i]]=1;
 for(i=1;i<n;i++)
 	if(!used[i] && used[i+1]) return -1;
 for(i=n;i>=1;i--)
 	if(used[i])
	{	dep=i;
		break;
	}
 for(i=1;i<=dep;i++)
 	b[i].clear();
 for(i=1;i<=n;i++)
 	b[d[i]].push_back(i-1);
 ret=0;	
 for(i=1;i<dep;i++)
 	for(j=0;j<b[i+1].size();j++)
 		for(k=0;k<b[i].size();k++)
		 	ret+=(1LL<<(b[i+1][j]*n+b[i][k]));	 	
 return ret;	
}

void dfs(int i)
{int j;
 long long p,s;

 //cout<<i<<endl;
 if(i==n+1)
 {	s=check();
 	if(s!=-1)
 	{	for(p=s;p>0;p=(p-1)&s)
 			calc(p);
 		if(dep==1) calc(0);	
 	}
 	return;
 }
 for(j=1;j<=n;j++)
 {	d[i]=j;
	dfs(i+1);
 }
}

class CosmicBlocks
{	public:
	int getNumOrders(vector <int> blockTypes, int minWays, int maxWays)
	{	int i,j;
	
		n=blockTypes.size();
		L=minWays;
		R=maxWays;
		for(i=1;i<=n;i++) a[i]=blockTypes[i-1];
		ans=0;
		dfs(1);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 6; verify_case(0, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 720; int Arg2 = 720; int Arg3 = 1; verify_case(1, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 3; verify_case(2, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 2; verify_case(3, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; verify_case(4, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {1,2,4,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 30; int Arg3 = 27; verify_case(5, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_6() { int Arr0[] = {1,2,3,4,5,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 720; int Arg3 = 4445; verify_case(6, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }
	void test_case_7() { int Arr0[] = {7500,1000,7500,1000,7500}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; int Arg2 = 88; int Arg3 = 448; verify_case(7, Arg3, getNumOrders(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	CosmicBlocks ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
