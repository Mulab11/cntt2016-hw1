// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndRGB.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,tot;
int a[2510];
long long ans;
long long f[2510],h[2510];

class LittleElephantAndRGB
{	public:
	long long getNumber(vector <string> list, int minGreen)
	{	int i,j,k,s,s1,flag,last;
		
		n=list.size();
		m=minGreen;
		tot=0;
		for(i=0;i<list.size();i++)
			for(j=0;j<list[i].length();j++)
				a[++tot]=(list[i][j]=='G'?1:0);
		memset(f,0,sizeof(f));
		ans=0;
		last=1;
		for(i=1;i<=tot;i++)
		{	
			s=0;
			flag=1;
			s1=0;
			for(j=i;j>=1;j--) //统计i左侧有多少右侧连续恰好f[]的方案 
			{	if(flag)
				{	s+=a[j];
					s=min(s,m);
					if(!a[j])
						flag=0;
					f[s]++;
				}
				else
				{	if(s1>=m || s>=m)
						f[m]++;
					else 
					{	s1+=a[j];
						if(!a[j] && s1<m) s1=0;
						s1=min(s1,m);
						if(s1>=m)
							f[m]++;
						else
							f[s]++;
					}
				}
			}	
			
			memset(h,0,sizeof(h));
			s=0;
			flag=1;
			s1=0;
			for(j=i+1;j<=tot;j++) //统计i右侧有多少右侧连续>=h[]的方案  
			{	if(flag)
				{	s+=a[j];
					s=min(s,m);
					if(!a[j])
						flag=0;
					h[s]++;
				}
				else
				{	if(s1>=m || s>=m)
						h[m]++;
					else 
					{	s1+=a[j];
						if(!a[j] && s1<m) s1=0;
						s1=min(s1,m);
						if(s1>=m)
							h[m]++;
						else
							h[s]++;
					}
				}
			}	
			for(j=m;j>=0;j--)
				h[j]+=h[j+1];
			for(j=0;j<=m;j++) ans+=f[j]*h[m-j]; //两边乘起来 
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"GRG"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 1LL; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"GG", "GG"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long long Arg2 = 9LL; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"GRBGRBBRG"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 11LL; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"RRBRBBRRR", "R", "B"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; long long Arg2 = 0LL; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"GRGGGRBRGG", "GGGGGGGG", "BRGRBRB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; long long Arg2 = 12430LL; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	LittleElephantAndRGB ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
