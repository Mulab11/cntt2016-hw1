// BEGIN CUT HERE

// END CUT HERE
//#line 5 "EllysBulls.cpp"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
#include <cassert>
using namespace std;
vector <pair<int,string> > vec;
vector <int> bit[10];
int chk[10][10],n,wei;
string outp;
int search(int now)
{
	if (now>=n)
	{
		for (int i=0;i<wei;i++)
		{
			int js=0;
			for (int j=0;j<=9;j++) if (chk[i][j]==0) js++;
			if (js==0) assert(0);
			if (js>1) return 1;
		}
		if (outp!="") return 1;
		for (int i=0;i<wei;i++)
		{
			for (int j=0;j<=9;j++) if (chk[i][j]==0) outp+=(char)(j+'0');
		}
		return 0;
	}
	string st=vec[now].second;int ls[10][10];
	for (int k=0;k<bit[vec[now].first].size();k++)
	{
		memcpy(ls,chk,sizeof(chk));
		bool can=true;
		for (int i=0;i<wei;i++)
		{
			if (bit[vec[now].first][k]&(1<<i))
			{
				if (chk[i][st[i]-'0']) {can=false;break;}
				for (int d=0;d<=9;d++) chk[i][d]=((d==st[i]-'0')?0:1);
			}
			else
			{
				chk[i][st[i]-'0']=1;
				int sum=0;for (int d=0;d<=9;d++) sum+=chk[i][d];
				if (sum==10) {can=false;break;}
			}
		}
		if (can)
		{
			int p=search(now+1);
			if (p==1) return 1;
		}
		memcpy(chk,ls,sizeof(chk));
	}
	return 0;
}
			
map<string,int> mp;	
class EllysBulls
{
        public:
        string getNumber(vector <string> guess, vector <int> po)
        {
			for (int i=0;i<guess.size();i++)
			{
				if (!mp.count(guess[i]))
				{
					vec.push_back(make_pair(po[i],guess[i]));
					mp[guess[i]]=po[i];
				}
				else if (mp[guess[i]]!=po[i]) return "Liar";
			}
			n=vec.size();wei=guess[0].size();
			for (int i=1;i<=2090;i++) swap(vec[rand()%n],vec[rand()%n]);
			//sort(vec.begin(),vec.end());
			//reverse(vec.begin(),vec.end());
			for (int i=0;i<(1<<wei);i++)
			{
				int p=0,ths=i;
				while (ths) {p++;ths-=(ths)&(-ths);}
				bit[p].push_back(i);
			}
			//cout<<bit[vec[1].first][8]<<endl;
			int p=search(0);
			if (p==1)
			{
				/*for (int i=0;i<wei;i++)
				{
					for (int j=0;j<=9;j++) cout<<chk[i][j]<<' ';
					cout<<endl;
				}*/
				return "Ambiguity";
			}
			else if (outp=="") return "Liar";
			else return outp;
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
{
        EllysBulls ___test;
        ___test.run_test(5);
        return 0;
}
// END CUT HERE
