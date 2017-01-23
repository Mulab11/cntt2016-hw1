// BEGIN CUT HERE

// END CUT HERE
#line 6 "FoxAndMp3.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,tot;
int a[110];
vector<string> ans;

class FoxAndMp3
{
	public:
	vector <string> playList(int N)
	{	int i,j,k;
		string s;
		
		n=N;
		tot=1;
		a[1]=1;
		ans.clear();
		k=1;
		for(i=1;i<=n && i<=50;i++)
		{	s="";
			for(j=1;j<=tot;j++) s+=a[j]+48;
			//cout<<i<<" "<<tot<<" "<<a[1]<<endl;
			ans.push_back(s+".mp3");
			if(k*10<=n)
			{	a[++tot]=0;
				k*=10;
			}
			else if(a[tot]!=9 && k+1<=n)
			{	a[tot]++;
				k++;
			}
			else
			{	k-=a[tot];
				a[tot--]=0;
				k/=10;
				a[tot]++;
				k++;
			}
		}
		return ans;		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"1.mp3", "2.mp3", "3.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, playList(Arg0)); }
	void test_case_1() { int Arg0 = 10; string Arr1[] = {"1.mp3", "10.mp3", "2.mp3", "3.mp3", "4.mp3", "5.mp3", "6.mp3", "7.mp3", "8.mp3", "9.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, playList(Arg0)); }
	void test_case_2() { int Arg0 = 16; string Arr1[] = {"1.mp3", "10.mp3", "11.mp3", "12.mp3", "13.mp3", "14.mp3", "15.mp3", "16.mp3", "2.mp3", "3.mp3", "4.mp3", "5.mp3", "6.mp3", "7.mp3", "8.mp3", "9.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, playList(Arg0)); }
	void test_case_3() { int Arg0 = 32; string Arr1[] = {"1.mp3", "10.mp3", "11.mp3", "12.mp3", "13.mp3", "14.mp3", "15.mp3", "16.mp3", "17.mp3", "18.mp3", "19.mp3", "2.mp3", "20.mp3", "21.mp3", "22.mp3", "23.mp3", "24.mp3", "25.mp3", "26.mp3", "27.mp3", "28.mp3", "29.mp3", "3.mp3", "30.mp3", "31.mp3", "32.mp3", "4.mp3", "5.mp3", "6.mp3", "7.mp3", "8.mp3", "9.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, playList(Arg0)); }
	void test_case_4() { int Arg0 = 100000009; string Arr1[] = {"1.mp3", "10.mp3", "100.mp3", "1000.mp3", "10000.mp3", "100000.mp3", "1000000.mp3", "10000000.mp3", "100000000.mp3", "100000001.mp3", "100000002.mp3", "100000003.mp3", "100000004.mp3", "100000005.mp3", "100000006.mp3", "100000007.mp3", "100000008.mp3", "100000009.mp3", "10000001.mp3", "10000002.mp3", "10000003.mp3", "10000004.mp3", "10000005.mp3", "10000006.mp3", "10000007.mp3", "10000008.mp3", "10000009.mp3", "1000001.mp3", "10000010.mp3", "10000011.mp3", "10000012.mp3", "10000013.mp3", "10000014.mp3", "10000015.mp3", "10000016.mp3", "10000017.mp3", "10000018.mp3", "10000019.mp3", "1000002.mp3", "10000020.mp3", "10000021.mp3", "10000022.mp3", "10000023.mp3", "10000024.mp3", "10000025.mp3", "10000026.mp3", "10000027.mp3", "10000028.mp3", "10000029.mp3", "1000003.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, playList(Arg0)); }
	void test_case_5() { int Arg0 = 1; string Arr1[] = {"1.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, playList(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{FoxAndMp3 ___test;
 ___test.run_test(-1);
 return 0;
}
// END CUT HERE
