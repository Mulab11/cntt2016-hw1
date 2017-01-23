// BEGIN CUT HERE

// END CUT HERE
#line 5 "SkiResorts.cpp"
#include<bits/stdc++.h>
using namespace std;

int n;
int ga[110][110],a[110],sa[110],used[110],q[1000010];
long long ans;
long long f[110][110];

class SkiResorts
{	public:
	long long minCost(vector <string> road, vector <int> altitude)
	{	int i,j,k,t,w,flag;
		long long s=-1;
		
		n=road.size();
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				ga[i][j]=(road[i-1][j-1]=='Y'?1:0);
		for(i=1;i<=n;i++)
		{	a[i]=altitude[i-1];
			sa[i]=a[i];
		}
		sort(sa+1,sa+n+1);
		memset(f,-1,sizeof(f));
		for(i=1;i<=n;i++) f[1][i]=abs(a[1]-sa[i]);
		memset(used,0,sizeof(used));
		t=w=1;
		q[t]=1;
		while(t<=w)
		{	i=q[t];
			used[i]=0;
			for(j=1;j<=n;j++)
				if(ga[i][j])
				{	s=-1;
					flag=0;
					for(k=n;k>=1;k--)
					{	if(f[i][k]!=-1 && (s==-1 || f[i][k]<s)) s=f[i][k];
						if(s==-1) continue;
						if(f[j][k]==-1 || s+abs(sa[k]-a[j])<f[j][k])
						{	//cout<<j<<" "<<k<<" "<<s<<" "<<i<<endl;	
							f[j][k]=s+abs(sa[k]-a[j]);
							flag=1;
						}
					}
					if(flag && !used[j])
					{	used[j]=1;
						q[++w]=j;
					}
				}
			t++;
		}
		ans=-1;
		for(i=1;i<=n;i++)
			if(f[n][i]!=-1 && (ans==-1 || f[n][i]<ans))
				ans=f[n][i];
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYN",
 "YNY",
 "NYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {30, 20, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(0, Arg2, minCost(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"NY",
 "YN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 10LL; verify_case(1, Arg2, minCost(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"NYN",
 "YNN",
 "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {573, 573, 573}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = -1LL; verify_case(2, Arg2, minCost(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"NNYNNYYYNN",
 "NNNNYNYNNN",
 "YNNNNYYNNN",
 "NNNNNNYNYY",
 "NYNNNNNNYY",
 "YNYNNNNYNN",
 "YYYYNNNYNN",
 "YNNNNYYNNN",
 "NNNYYNNNNN",
 "NNNYYNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7, 4, 13, 2, 8, 1, 8, 15, 5, 15}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 12LL; verify_case(3, Arg2, minCost(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	SkiResorts ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
