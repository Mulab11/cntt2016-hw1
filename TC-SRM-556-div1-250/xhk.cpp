// BEGIN CUT HERE

// END CUT HERE
#line 6 "LeftRightDigitsGame2.cpp"
#include<bits/stdc++.h>
using namespace std;

int n;
int a[60],b[60],c[60],f[60][60];
string ans;

int calc(int i,int l,int r)
{int j,k,k1;
 
 //cout<<a[1]<<" "<<a[2]<<" "<<a[3]<<" "<<c[1]<<" "<<c[2]<<" "<<c[3]<<endl;
 
 memset(f,0,sizeof(f));
 if(a[i]==c[l]) f[i][1]=1;
 if(a[i]==c[r]) f[i][0]=1;
 for(j=i;j<=n;j++)
 	for(k=0;k<=j-i+1;k++)
 	{	if(!f[j][k]) continue;
	 	k1=j-i+1-k;
 		if(a[j+1]==c[l+k]) f[j+1][k+1]=1;
 		if(a[j+1]==c[r-k1]) f[j+1][k]=1;
 	}
 for(k=0;k<=n-i+1;k++)
 	if(f[n][k]) return 1;
 return 0;
}

int check(int m)
{int i,j,k;
 
 j=0;
 for(i=1;i<=n;i++)
 {	//cout<<m<<" "<<i<<" "<<j<<endl;
 	if(n-i+1>=m-j && calc(i,m-(n-i+1)+1,m)) return 1;
 	//cout<<"LL"<<endl;
	if(j<m && a[i]==c[j+1]) j++;
 }
 if(j==m) return 1;
 return 0;
}

class LeftRightDigitsGame2
{
	public:
	string minNumber(string digits, string lowerBound)
	{	int i,j,flag;
		
		n=digits.size();
		for(i=1;i<=n;i++) a[i]=digits[n-i]-48;
		for(i=1;i<=n;i++) b[i]=lowerBound[i-1]-48;
		ans="";
		
		for(i=1;i<=n;i++) c[i]=b[i];
		if(check(n))
		{	//cout<<"HH"<<endl;
			for(i=1;i<=n;i++) ans+=b[i]+48;
			return ans;
	 	}
	 	for(i=n;i>=1;i--)
	 	{	flag=0;
		 	for(j=b[i]+1;j<=9;j++)
			{	c[i]=j;
				if(check(i))
				{	flag=1;
					break;
				}
			}
			if(flag) break;
		}
		if(i==0) return "";
		//cout<<i<<" "<<"FF"<<endl;
		//cout<<i<<endl;
		for(i++;i<=n;i++)
		{	for(j=0;j<=9;j++)
			{	c[i]=j;
				if(check(i)) break;
			}
			if(j==10) return "";
		}
			
		for(i=1;i<=n;i++) ans+=c[i]+48;
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "565"; string Arg1 = "556"; string Arg2 = "556"; verify_case(0, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "565"; string Arg1 = "566"; string Arg2 = "655"; verify_case(1, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "565"; string Arg1 = "656"; string Arg2 = ""; verify_case(2, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "9876543210"; string Arg1 = "5565565565"; string Arg2 = "5678943210"; verify_case(3, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "8016352"; string Arg1 = "1000000"; string Arg2 = "1086352"; verify_case(4, Arg2, minNumber(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{LeftRightDigitsGame2 ___test;
 ___test.run_test(-1);
 return 0;
}
// END CUT HERE
