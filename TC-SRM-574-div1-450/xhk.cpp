// BEGIN CUT HERE

// END CUT HERE
#line 5 "PolygonTraversal.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,col;
int used[20];
long long ans;
long long f[20][300010];

class PolygonTraversal
{	public:
	long long count(int N, vector <int> points)
	{	int i,j,k,p,last,sta;
		
		n=N;
		m=points.size();
		sta=0;
		for(i=1;i<=m;i++)
			sta|=(1<<(points[i-1]-1));
		memset(f,0,sizeof(f));	
		f[points[m-1]][sta]=1;
		for(i=sta;i<(1<<n)-1;i++)
		{	j=1;
			while(i&(1<<(j-1))) j++;
			while(!(i&(1<<((j+n-2)%n)))) j=(j+n-2)%n+1;
			//cout<<i<<" "<<j<<endl;
			k=j;
			last=0;
			col++;
			while(1)
			{	if(i&(1<<(k-1)))
					col++;
				else if(last && (i&(1<<(last-1))))
					col++;
				used[k]=col;
				last=k;
				k++;
				if(k>n) k=1;
				if(k==j) break;
			}
			for(k=1;k<=n;k++)
			{	if(f[k][i]==0 || (i&(1<<(k-1)))==0) continue;
				for(p=1;p<=n;p++)
				{	if((i&(1<<(p-1))) || (abs(used[k]-used[p])<=1 || (k==(j+n-2)%n+1 && used[p]==used[j]))) continue;
					f[p][i|(1<<(p-1))]+=f[k][i];
					//cout<<p<<" "<<(i|(1<<(p-1)))<<" "<<k<<" "<<i<<" "<<f[k][i]<<endl;
				}
			}
		}
		ans=0;
		for(i=1;i<=n;i++)
		{	if((i-points[0]+n+1)%n<=2) continue;
			ans+=f[i][(1<<n)-1];
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 9; int Arr1[] = {4, 7, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 38LL; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 6; int Arr1[] = {1, 4, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 7; int Arr1[] = {2, 4, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 7; int Arr1[] = {1, 2, 3, 4, 6, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 18; int Arr1[] = {1, 7, 18}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 4374612736LL; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	PolygonTraversal ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
