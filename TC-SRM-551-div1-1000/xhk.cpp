// BEGIN CUT HERE

// END CUT HERE
#line 5 "SweetFruits.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007;
int n,m,n1,ans,S;
int d[50],a[50],b[50][50],f[50],g[50],comb[50][50],cnt[1100010];
vector<int> w[30];

bool cmp(int x,int y)
{return x>y;
}

int fpow(int i,int j)
{int ret=1;
 for(;j;i=(ll)i*i%mod,j/=2)
 	if(j&1) ret=(ll)ret*i%mod;
 return ret;
}

int gauss(int N)
{int i,j,k,t,ret,flag=1;
 
 for(i=1;i<=N;i++)
 {	j=i;
 	while(j<=N && b[j][i]==0) j++;
 	if(j<=N)
 	{	if(i!=j)
	 	{	swap(b[i],b[j]);
 			flag*=-1;
 		}
 	}
 	else
 		return 0;
 	for(j=i+1;j<=N;j++)
 	{	t=(ll)b[j][i]*fpow(b[i][i],mod-2)%mod;
 		for(k=i;k<=N;k++)
 			b[j][k]=(b[j][k]-(ll)b[i][k]*t%mod)%mod;
 	}
 }
 ret=flag;
 for(i=1;i<=N;i++)
 	ret=(ll)ret*b[i][i]%mod;
 return ret;
}

void dfs(int i,int j,int s)
{if(i==n1+1)
 {	w[j].push_back(s);
 	return;
 }
 dfs(i+1,j,s);
 dfs(i+1,j+1,s+a[i]);
}

void dfs2(int i,int j,int s)
{int k;

 if(i==m+1)
 {	for(k=0;k<=n1;k++)
		ans=(ans+(ll)g[j+k]*(lower_bound(w[k].begin(),w[k].end(),S-s+1)-w[k].begin())%mod)%mod;
	return;
 }
 dfs2(i+1,j,s);
 dfs2(i+1,j+1,s+a[i]);
}

class SweetFruits
{	public:
    int countTrees(vector <int> A, int s1)
    {	int i,j,k,s;
	
		S=s1;
		n=A.size();
      	for(i=0;i<=n;i++)
       	{	comb[i][0]=1;
       		for(j=1;j<=i;j++)
       			comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
      	}
       	cnt[0]=0;
       	for(i=1;i<(1<<((n+1)/2));i++) cnt[i]=cnt[i-(i&(-i))]+1;
       	for(i=1;i<=n;i++) a[i]=A[i-1];
       	sort(a+1,a+n+1,cmp);
       	for(i=1;i<=n;i++)
			if(a[i]<0) break;
       	m=i-1;
       	for(i=0;i<=m;i++)
       	{	memset(d,0,sizeof(d));
       		memset(b,0,sizeof(b));
			for(j=1;j<=i;j++)
       			for(k=j+1;k<=n;k++)
       				if(k<=i || k>m)
       				{	d[j]++;
       					d[k]++;
       					b[j][k]--;
       					b[k][j]--;
       				}
       		for(j=i+1;j<=m;j++)
				for(k=m+1;k<=n;k++)
				{	d[j]++;
					d[k]++;
					b[j][k]--;
					b[k][j]--;
				}
			for(j=m+1;j<=n;j++)
				for(k=j+1;k<=n;k++)
				{	d[j]++;
					d[k]++;
					b[j][k]--;
					b[k][j]--;
				}
			for(j=1;j<=n;j++)
				b[j][j]=d[j];	
			f[i]=gauss(n-1);	
		}
		for(i=0;i<=m;i++)
       	{	g[i]=f[i];
			for(j=0;j<i;j++)
       			g[i]=(g[i]-(ll)comb[i][j]*g[j]%mod)%mod;	   	
       	}
       	n1=m/2;
       	for(i=0;i<=n1;i++) w[i].clear();
       	dfs(1,0,0);
       	for(i=0;i<=n1;i++) sort(w[i].begin(),w[i].end());
		ans=0;
		dfs2(n1+1,0,0);
		return (ans+mod)%mod;
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
{      SweetFruits ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
