// BEGIN CUT HERE

// END CUT HERE
#line 5 "EllysBulls.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,lim,ans;
int a[110][20],b[110],c[20];
string str;
map<vector<int>,int> h;

void dfs(int i,int sta)
{int j,k,cnt;
 vector<int> w;
 
 if(i==lim+1)
 {	w.clear();
 	for(j=1;j<=m;j++)
 	{	cnt=0;
 		for(k=1;k<=lim;k++)
 			if(a[j][k]==c[k])
 				cnt++;
 		w.push_back(cnt);
 	}
 	if(h.find(w)!=h.end())
 		h[w]=-1;
 	else
 		h[w]=sta;
 	return;
 }
 for(j=0;j<=9;j++)
 {	c[i]=j;
 	dfs(i+1,sta*10+j);
 }
}

void dfs1(int i)
{int j,k,cnt,t,flag;
 vector<int> w;
 
 if(ans>1) return;
 if(i==n+1)
 {	w.clear();
 	flag=1;
 	for(j=1;j<=m;j++)
 	{	cnt=0;
 		for(k=lim+1;k<=n;k++)
 			if(a[j][k]==c[k])
 				cnt++;
 		if(cnt<=b[j])
 			w.push_back(b[j]-cnt);
 		else
 		{	flag=0;
 			break;
 		}
 	}
	if(flag && h.find(w)!=h.end())
	{	k=h[w];
		if(k==-1)
			ans=2;
		else
		{	//cout<<k<<" ## "<<" "<<w[0]<<" "<<c[1]<<" "<<c[2]<<" "<<c[3]<<endl;	
			ans++;
			t=k;
			for(j=lim;j>=1;j--)
			{	c[j]=t%10;
				t/=10;
			}
			str="";
			for(j=1;j<=n;j++)
				str+=c[j]+48;
		}
	}
	return;
 }
 for(j=0;j<=9;j++)
 {	c[i]=j;
 	dfs1(i+1);
 }
}

class EllysBulls
{	public:
	string getNumber(vector <string> guesses, vector <int> bulls)
	{	int i,j;
		
		n=guesses[0].length();
		m=guesses.size();
		for(i=1;i<=m;i++)
			for(j=1;j<=n;j++)
				a[i][j]=guesses[i-1][j-1]-48;
		for(i=1;i<=m;i++)
			b[i]=bulls[i-1];
		lim=n/2;
		h.clear();
		memset(c,0,sizeof(c));
		dfs(1,0);
		ans=0;
		str="";
		dfs1(lim+1);
		if(ans==1)
			return str;
		else if(ans>1)
			return "Ambiguity";
		else
			return "Liar";
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1234", "4321", "1111", "2222", "3333", "4444", "5555", "6666", "7777", "8888", "9999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 1, 1, 0, 2, 0, 0, 0, 1, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "1337"; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"0000", "1111", "2222"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Liar"; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"666666", "666677", "777777", "999999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 3, 1, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Ambiguity"; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"000", "987", "654", "321", "100", "010"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 1, 0, 0, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "007"; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"28", "92", "70", "30", "67", "63", "06", "65",
 "11", "06", "88", "48", "09", "65", "48", "08"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "54"; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"0294884", "1711527", "2362216", "7666148", "7295642",
 "4166623", "1166638", "2767693", "8650248", "2486509",
 "6138934", "4018642", "6236742", "2961643", "8407361",
 "2097376", "6575410", "6071777", "3569948", "2606380"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 0, 1, 3, 4, 4, 3, 2, 1, 1, 0, 4, 4, 3, 0, 0, 0, 0, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "4266642"; verify_case(5, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	EllysBulls ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
