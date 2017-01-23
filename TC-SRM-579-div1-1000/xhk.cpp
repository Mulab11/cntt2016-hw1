// BEGIN CUT HERE

// END CUT HERE
#line 5 "RockPaperScissors.cpp"
#include<bits/stdc++.h>
using namespace std;

int n;
double ans;
double a[60],b[60],c[60],f[51][51][51][51],comb[60][60];

class RockPaperScissors
{	public:
	double bestScore(vector <int> rockProb, vector <int> paperProb, vector <int> scissorsProb)
	{	int i,j,k,p,u;
		double s1,s2,s3,c1,c2,c3,pr;
		
		n=rockProb.size();
		for(i=1;i<=n;i++) a[i]=rockProb[i-1]/300.0;
		for(i=1;i<=n;i++) b[i]=paperProb[i-1]/300.0;
		for(i=1;i<=n;i++) c[i]=scissorsProb[i-1]/300.0;
		comb[0][0]=1;
		for(i=1;i<=n;i++) //组合数计算 
		{	comb[i][0]=1;
			for(j=1;j<=i;j++)
				comb[i][j]=comb[i-1][j-1]+comb[i-1][j];
		}
		memset(f,0,sizeof(f));
		for(u=1;u<=n;u++) //dp求出不用u这个骰子前j+k+p个有j个石头，k个布，p个剪刀的概率。 
		{	f[u][0][0][0]=1;
			for(i=0;i<n;i++)
			{	if(i+1==u) continue;	
				for(j=i;j>=0;j--)
					for(k=i-j;k>=0;k--)
						for(p=i-j-k;p>=0;p--)
						{	f[u][j+1][k][p]+=f[u][j][k][p]*a[i+1];
							f[u][j][k+1][p]+=f[u][j][k][p]*b[i+1];
							f[u][j][k][p+1]+=f[u][j][k][p]*c[i+1];
						}
				//if(u==1) 
				//	cout<<i<<" "<<f[u][1][0][0]<<" "<<f[u][2][0][0]<<endl;		
			}
			for(j=0;j<n;j++)
				for(k=0;j+k<n;k++)
					for(p=0;j+k+p<n;p++)
						f[u][j][k][p]/=comb[n][j+k+p];
		}
		//cout<<f[1][2][0][0]<<" "<<f[1][0][2][0]<<" "<<f[1][0][0][2]<<endl;
		//cout<<f[2][2][0][0]<<" "<<f[2][0][2][0]<<" "<<f[2][0][0][2]<<endl;
		//cout<<f[3][2][0][0]<<" "<<f[3][0][2][0]<<" "<<f[3][0][0][2]<<endl;
		//cout<<f[1][1][0][0]<<endl;
		//cout<<"####"<<endl;
		ans=0;
		for(j=0;j<=n;j++) //算出前j+k+p个有j个石头，k个布，p个剪刀时下一个手势的概率 
			for(k=0;j+k<=n;k++)
				for(p=0;j+k+p<=n;p++)
				{	if(j+k+p==n) continue;
					//cout<<j<<" "<<k<<" "<<p<<" "<<ans<<endl;
					s1=0;
					s2=0;
					s3=0;
					pr=0;
					for(u=1;u<=n;u++)
					{	s1+=f[u][j][k][p]*a[u]/(n-j-k-p);
						s2+=f[u][j][k][p]*b[u]/(n-j-k-p);
						s3+=f[u][j][k][p]*c[u]/(n-j-k-p);
						pr+=f[u][j][k][p];
					}
					pr/=(n-j-k-p);
					//cout<<pr<<endl;
					//cout<<s1<<" "<<s2<<" "<<s3<<" "<<pr<<endl;
					//cout<<"^^^"<<endl;
					c1=3*s1+s2;
					c2=3*s2+s3;
					c3=3*s3+s1;
					ans+=max(c1,max(c2,c3));
				}
		return ans;		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {100, 100, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {100, 100, 100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100, 100, 100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 3.999999999999999; verify_case(0, Arg3, bestScore(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {300}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 3.0; verify_case(1, Arg3, bestScore(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {300, 0,   0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,   300, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,   0,   300}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 6.333333333333332; verify_case(2, Arg3, bestScore(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {100,  0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {200, 100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,   200}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 3.7222222222222223; verify_case(3, Arg3, bestScore(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {150,300,300,300,300,300,300,300,300,300,300,300,300,300
,300,300,300,300,300,300,300,300,300,300,300,300,300,300
,300,300,300,300,300,300,300,300,300,300,300,300,300,300
,300,300,300,300,300,300,300,300}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 149.00000000000003; verify_case(4, Arg3, bestScore(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	RockPaperScissors ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
