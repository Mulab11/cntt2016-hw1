// BEGIN CUT HERE

// END CUT HERE
#line 5 "StringGame.cpp"
#include<bits/stdc++.h>
using namespace std;

int n;
int a[110][30];

int dfs(int i,long long sta)
{int j,k,flag,ret=0;
 long long p;
 
 //cout<<i<<" "<<sta<<endl;
 if(sta==(1LL<<(i-1))) return 1;
 for(j=1;j<=26;j++)
 {	flag=1;
 	p=0;
 	for(k=1;k<=n;k++)
 	{	if(sta&(1LL<<(k-1)))
 		{	if(a[k][j]>a[i][j])
 				flag=0;
 			else if(a[k][j]==a[i][j])
 				p|=(1LL<<(k-1));
 		}
 		if(!flag) break;
 	}
 	if(flag && p!=sta) return dfs(i,p);
 }
 return 0;
}		

class StringGame
{	public:
	vector <int> getWinningStrings(vector <string> S)
	{	int i,j;
		vector<int> ans;
		
		n=S.size();
		memset(a,0,sizeof(a));
		
		//cout<<S[0]<<" "<<S[1]<<" "<<n<<endl;
		
		for(i=1;i<=n;i++)
			for(j=0;j<S[i-1].length();j++)
			{	//cout<<S[i-1][j]-96<<endl;
				a[i][S[i-1][j]-96]++;	
			}
		//cout<<"HH"<<endl;	
		ans.clear();		
		for(i=1;i<=n;i++)
			if(dfs(i,(1LL<<n)-1))
				ans.push_back(i-1);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"bcdefghijklmnopqrstuvwxyz", "acdefghijklmnopqrstuvwxyz", "abdefghijklmnopqrstuvwxyz", "abcefghijklmnopqrstuvwxyz", "abcdfghijklmnopqrstuvwxyz", "abcdeghijklmnopqrstuvwxyz", "abcdefhijklmnopqrstuvwxyz", "abcdefgijklmnopqrstuvwxyz", "abcdefghjklmnopqrstuvwxyz", "abcdefghiklmnopqrstuvwxyz", "abcdefghijlmnopqrstuvwxyz", "abcdefghijkmnopqrstuvwxyz", "abcdefghijklnopqrstuvwxyz", "abcdefghijklmopqrstuvwxyz", "abcdefghijklmnpqrstuvwxyz", "abcdefghijklmnoqrstuvwxyz", "abcdefghijklmnoprstuvwxyz", "abcdefghijklmnopqstuvwxyz", "abcdefghijklmnopqrtuvwxyz", "abcdefghijklmnopqrsuvwxyz", "abcdefghijklmnopqrstvwxyz", "abcdefghijklmnopqrstuwxyz", "abcdefghijklmnopqrstuvxyz", "abcdefghijklmnopqrstuvwyz", "abcdefghijklmnopqrstuvwxz", "abcdefghijklmnopqrstuvwxy", "defghijklmnopqrstuvwxyzbc", "defghijklmnopqrstuvwxyzac", "defghijklmnopqrstuvwxyzab", "efghijklmnopqrstuvwxyzabc", "dfghijklmnopqrstuvwxyzabc", "deghijklmnopqrstuvwxyzabc", "defhijklmnopqrstuvwxyzabc", "defgijklmnopqrstuvwxyzabc", "defghjklmnopqrstuvwxyzabc", "defghiklmnopqrstuvwxyzabc", "defghijlmnopqrstuvwxyzabc", "defghijkmnopqrstuvwxyzabc", "defghijklnopqrstuvwxyzabc", "defghijklmopqrstuvwxyzabc"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {14, 15, 16, 17,18,19,20,21,22,23,24,25 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getWinningStrings(Arg0)); }
	void test_case_1() { string Arr0[] = {"aabbcc", "aaabbb", "aaaccc"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getWinningStrings(Arg0)); }
	void test_case_2() { string Arr0[] = {"ab", "ba"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getWinningStrings(Arg0)); }
	void test_case_3() { string Arr0[] = {"xaocxsss", "oooxsoas", "xaooosss", "xaocssss", "coxaosxx"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getWinningStrings(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	StringGame ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
