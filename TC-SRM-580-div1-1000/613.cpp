// BEGIN CUT HERE

// END CUT HERE
#line 5 "WallGameDiv1.cpp"
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
using namespace std;
int cost[55][55],sum[55][55],f[55][55][55],g[55][55][55];
class WallGameDiv1
{
        public:
        int play(vector <string> v)
        {
			int n=v.size(),m=v[0].size();
			for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				cost[i][j]=v[i-1][j-1]-'0';
				sum[i][j]=sum[i][j-1]+cost[i][j];
			}
			
			for (int i=n-1;i>=1;i--)
			for (int d=m;d>=0;d--)
			for (int l=1;l<=m-d;l++)
			{
				int r=l+d;
				
				f[i][l][r]=f[i+1][l][l]+cost[i+1][l];
				int ths=2100000000;
				if (l!=1) ths=min(ths,f[i][l-1][r]+cost[i][l-1]);
				if (r!=m) ths=min(ths,g[i][l][r+1]+sum[i][r+1]-sum[i][l]);
				if (ths!=2100000000) f[i][l][r]=max(f[i][l][r],ths);
				
				g[i][l][r]=g[i+1][r][r]+cost[i+1][r];
				ths=2100000000;
				if (l!=1) ths=min(ths,f[i][l-1][r]+sum[i][r-1]-sum[i][l-2]);
				if (r!=m) ths=min(ths,g[i][l][r+1]+cost[i][r+1]);
				if (ths!=2100000000) g[i][l][r]=max(g[i][l][r],ths);
			}
			
			int ans=2100000000;
			for (int i=1;i<=m;i++) ans=min(ans,f[1][i][i]+cost[1][i]);
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"12"
,"34"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(0, Arg1, play(Arg0)); }
	void test_case_1() { string Arr0[] = {"99999"
,"99999"
,"99999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 99; verify_case(1, Arg1, play(Arg0)); }
	void test_case_2() { string Arr0[] = {"11111"
,"90005"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(2, Arg1, play(Arg0)); }
	void test_case_3() { string Arr0[] = {"4417231387449337370319219832088987579792"
,"3117295688208899006196193430472892512797"
,"0835796222361526836944954410684516919758"
,"1988200069973565052900745230547016216225"
,"8080511471118865780390486996601082102418"
,"4229084185957675819725844582167613108400"
,"9068653877952162764545674979144308771754"
,"8551565425951612499712254182109991511690"
,"7090525592007482152807163656647658543093"
,"9198968742256995592729889137556032960142"
,"2071864379877766468141740053503050313101"
,"1055375249261868472993219156394129253481"
,"2461178270502857106406495509025426298874"
,"8216781259733537757203421037984512664825"
,"4693452554407216935375049784445568498482"
,"2709693439640250842244170297203200674391"
,"5122217695676372684217182241705137947908"
,"6668814191410691246849638388008228444294"
,"4952122070212780440963814752538149378639"
,"9827737761436134120332969866554332504400"
,"3412406588339828249986707470540386748886"
,"7521506848088506994554600408372456405830"
,"1916926179183007872881163173153907665999"
,"6636166791472761992310264951474925339024"
,"6679667717747231380196787943691121008076"
,"3218993234115685151069259138068533004433"
,"4920152552986426962081492913852060211795"
,"0365186235986445521382132973036266396894"
,"3205351414936828189305188614651974318855"
,"3144278971529524658788277656125598825426"
,"5525287537572356662391582052968411726245"
,"2130137226726919525622574701068062252930"
,"2369996694245544770519574837226971226841"
,"6806769058165410189286521891570936341547"
,"0448109211631660241710734664066810078242"
,"4622919135804954122810530631429501069659"
,"0235247446548732490429856705369583140671"
,"2193399741215975228987754171460722199304"
,"1203037020703833716225328076959743850915"
,"5419885193880826109484912489603262199432"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7366; verify_case(3, Arg1, play(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        WallGameDiv1 ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE