// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndDice.cpp"
#include<bits/stdc++.h>
using namespace std;

struct unit
{int x,num;
};
struct unit a[110];

int n,m,lim,tot;
int f[60][2510],b[5010];
double ans;

bool operator <(unit A,unit B)
{return A.x<B.x;
}

class KingdomAndDice
{	public:
	double newFairness(vector <int> firstDie, vector <int> secondDie, int X)
	{	int i,j,k,p,mi,s,s1;
		
		n=firstDie.size();
		lim=X;
		for(i=1;i<=n;i++) a[i]=(unit){firstDie[i-1],1};
		for(i=1;i<=n;i++) a[n+i]=(unit){secondDie[i-1],2};
		sort(a+1,a+2*n+1);
		a[2*n+1].x=lim+1;
		s=0;
		s1=0;
		m=0;
		tot=0;
		for(i=1;i<=2*n;i++)
		{	if(a[i].num==2)
				s++;
			else
				s1+=s;
			if(a[i].x==0) m++;
			for(j=1;j<=min(n,a[i+1].x-a[i].x-1);j++)
				b[++tot]=s;
		}
		//for(i=1;i<=tot;i++) cout<<b[i]<<" ";
		//cout<<endl;
		memset(f,0,sizeof(f));
		f[0][s1]=1;
		for(i=1;i<=tot;i++)
			for(j=m;j>=1;j--)
				for(k=b[i];k<=n*n;k++)
					f[j][k]|=f[j-1][k-b[i]];
		mi=-1;
		for(k=0;k<=n*n;k++)
			for(j=0;j<=m;j++)
			{	if(!f[j][k]) continue;
				//cout<<j<<" "<<k<<" "<<abs(n*n-2*k)<<" "<<endl;
				if(mi==-1 || abs(n*n-2*k)<abs(n*n-2*mi)) mi=k;
			}
		//cout<<mi<<endl;	
		ans=(double)mi/(n*n);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 2, 7, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 3, 8, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 12; double Arg3 = 0.4375; verify_case(0, Arg3, newFairness(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0, 2, 7, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 3, 8, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; double Arg3 = 0.375; verify_case(1, Arg3, newFairness(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5, 8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 47; double Arg3 = 0.5; verify_case(2, Arg3, newFairness(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {19, 50, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {26, 100, 37}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1000; double Arg3 = 0.2222222222222222; verify_case(3, Arg3, newFairness(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {6371, 0, 6256, 1852, 0, 0, 6317, 3004, 5218, 9012}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1557, 6318, 1560, 4519, 2012, 6316, 6315, 1559, 8215, 1561}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10000; double Arg3 = 0.49; verify_case(4, Arg3, newFairness(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	KingdomAndDice ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
