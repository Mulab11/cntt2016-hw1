// BEGIN CUT HERE

// END CUT HERE
#line 5 "StringWeight.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
int n,ans;
int a[60],f[60][30][30];

void update(int &i,int x)
{if(i==-1 || x<i) i=x;
}

class StringWeight
{	public:
	int getMinimum(vector <int> L)
	{	int i,j,k,kc,ko,kco,p1,p2,last,s,s1;
		
		n=L.size();
		for(i=1;i<=n;i++) a[i]=L[i-1];
		memset(f,0x3f,sizeof(f));
		f[0][0][0]=0; //动态规划f[i][j][k]表示前i个串里面有j个字母还没结束，有k个字母已经结束了 
		last=0;
		for(i=0;i<n;i++)
		{	for(j=0;j<=26;j++)
				for(k=0;k<=26;k++)
				{	if(f[i][j][k]==inf) continue;
					if(a[i+1]<=26) //由贪心可以发现出现一次的字母为p1个，出现次数大于一的字母个数为p2 
					{	p1=a[i+1]; 
						p2=0;
					}
					else
					{	p1=25;
						p2=1;
					}
					for(kc=0;kc<=j;kc++) //枚举下一个串里面新开几个 
						for(ko=0;ko<=26-j-k;ko++) //枚举下一个串里面关闭几个字母 
						{	
							for(kco=0;kco+ko<=26-j-k;kco++) //即开又关 
							{	if(kc+ko+kco>p1+p2 || p1+p2-ko-kco>j) continue;
								if(kco>p1+p2-kc-ko) continue;
								
								s=(1+kc)*kc/2+kc*last-(last+a[i+1]+last+a[i+1]-ko+1)*ko/2;
								if(kc+ko==p1+p2)
								{	if(p2>0)
										s+=a[i+1]-p1-1;
								}
								else if(kc+ko+kco>p1)
									s+=a[i+1]-p1-1;
																
								update(f[i+1][j-kc+ko][k+kc+kco],f[i][j][k]+s);
							}
						}
				}
			//cout<<i+1<<" "<<f[i+1][0][i+1]<<endl;
			last+=a[i+1];					
		}
		ans=inf;
		for(i=0;i<=26;i++)
			if(f[n][0][i]!=-1)
			{	ans=min(ans,f[n][0][i]);
				//cout<<i<<" "<<f[n][0][i]<<endl;
				//break;
			}
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, getMinimum(Arg0)); }
	void test_case_1() { int Arr0[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, getMinimum(Arg0)); }
	void test_case_2() { int Arr0[] = {26, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(2, Arg1, getMinimum(Arg0)); }
	void test_case_3() { int Arr0[] = {25, 25, 25, 25}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1826; verify_case(3, Arg1, getMinimum(Arg0)); }
	void test_case_4() { int Arr0[] = {14, 6, 30, 2, 5, 61}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1229; verify_case(4, Arg1, getMinimum(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	StringWeight ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
