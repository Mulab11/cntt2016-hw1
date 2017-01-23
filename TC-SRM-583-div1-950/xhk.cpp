// BEGIN CUT HERE

// END CUT HERE
#line 5 "RandomPaintingOnABoard.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m;
int cnt[10010],a[30][30],f[30][1510][2];
double ans;

class RandomPaintingOnABoard
{	public:
	double expectedSteps(vector <string> prob)
	{	int i,j,k,s,sta,sum;
		
		n=prob.size();
		m=prob[0].length();
		if(n<m)
		{	for(i=1;i<=n;i++)
				for(j=1;j<=m;j++)
					a[i][j]=prob[i-1][j-1]-48;
		}
		else
		{	for(i=1;i<=n;i++)
				for(j=1;j<=m;j++)
					a[j][i]=prob[i-1][j-1]-48;
			swap(n,m);
		}
		for(i=1;i<(1<<n);i++) cnt[i]=cnt[i-(i&(-i))]+1;
		sum=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				sum+=a[i][j];
		ans=0;
		for(i=0;i<(1<<n);i++) //枚举行有i这个状态为空 
		{	memset(f,0,sizeof(f));
			s=0;
			for(j=1;j<=n;j++)
				if(i&(1<<(j-1)))
				{	for(k=1;k<=m;k++)
						s+=a[j][k];
				}
			if(cnt[i]&1)
				f[0][s][1]=1;
			else
				f[0][s][0]=1;
			for(j=0;j<m;j++) //状压求出共有i行j列不给填sta=(i+j)&1不给填的值之和是k 
			{	s=0;
				for(k=1;k<=n;k++)
					if(!(i&(1<<(k-1))))
						s+=a[k][j+1];
				for(k=0;k<=sum;k++)
					for(sta=0;sta<2;sta++)
					{	if(f[j][k][sta]==0) continue;
						f[j+1][k][sta]+=f[j][k][sta];
						f[j+1][k+s][sta^1]+=f[j][k][sta];
					}
			}
			for(k=1;k<=sum;k++)
			{	ans-=f[m][k][0]/(1-(double)(sum-k)/sum);
				ans+=f[m][k][1]/(1-(double)(sum-k)/sum);
			}
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"10",
 "01"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.0; verify_case(0, Arg1, expectedSteps(Arg0)); }
	void test_case_1() { string Arr0[] = {"11",
 "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.6666666666666665; verify_case(1, Arg1, expectedSteps(Arg0)); }
	void test_case_2() { string Arr0[] = {"11",
 "12"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.9166666666666665; verify_case(2, Arg1, expectedSteps(Arg0)); }
	void test_case_3() { string Arr0[] = {"0976",
 "1701",
 "7119"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 11.214334077031307; verify_case(3, Arg1, expectedSteps(Arg0)); }
	void test_case_4() { string Arr0[] = {"000000000000001000000",
 "888999988889890999988",
 "988889988899980889999",
 "889898998889980999898",
 "988889999989880899999",
 "998888998988990989998",
 "998988999898990889899"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1028.7662876159634; verify_case(4, Arg1, expectedSteps(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	RandomPaintingOnABoard ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
