// BEGIN CUT HERE

// END CUT HERE
#line 5 "TravellingPurchasingMan.cpp"
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
int cost[55],gl[55],gr[55],top;
int dis[55][55];
int f[550000][22];
int getbit(int s)
{
	int ans=0;
	while (s)
	{
		ans++;
		s-=s&(-s);
	}
	return ans;
}
class TravellingPurchasingMan
{
        public:
        int maxStores(int n, vector <string> stores, vector <string> roads)
        {
			for (int i=0;i<stores.size();i++)
			{
				string st=stores[i]+" ";
				int l=0,r=0,d=0,lst=0;
				for (int i=0;i<st.size();i++) if (st[i]!=' ') l=l*10+st[i]-'0';else {lst=i+1;break;}
				for (int i=lst;i<st.size();i++) if (st[i]!=' ') r=r*10+st[i]-'0';else {lst=i+1;break;}
				for (int i=lst;i<st.size();i++) if (st[i]!=' ') d=d*10+st[i]-'0';else {lst=i+1;break;}
				top++;
				gl[top]=min(l,r);gr[top]=max(l,r);cost[top]=d;
			}
			memset(dis,127/3,sizeof(dis));
			for (int i=0;i<roads.size();i++)
			{
				string st=roads[i]+" ";
				int s=0,t=0,len=0,lst=0;
				for (int i=0;i<st.size();i++) if (st[i]!=' ') s=s*10+st[i]-'0';else {lst=i+1;break;}
				for (int i=lst;i<st.size();i++) if (st[i]!=' ') t=t*10+st[i]-'0';else {lst=i+1;break;}
				for (int i=lst;i<st.size();i++) if (st[i]!=' ') len=len*10+st[i]-'0';else {lst=i+1;break;}
				s++;t++;
				//cout<<s<<' '<<t<<' '<<len<<endl;
				dis[s][t]=min(dis[s][t],len);
				dis[t][s]=min(dis[t][s],len);
			}
			
			for (int i=1;i<=n;i++) dis[i][i]=0;
			for (int k=1;k<=n;k++)
			for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
				
			memset(f,127/3,sizeof(f));
			for (int i=1;i<=top;i++)
				if (dis[n][i]<=gr[i]) f[1<<(i-1)][i]=max(dis[n][i],gl[i])+cost[i];
			
			int ans=0;
			for (int s=1;s<(1<<top);s++)
			for (int i=1;i<=top;i++) if (f[s][i]<700000000)
			{
				for (int j=1;j<=top;j++) if (((s&(1<<(j-1)))==0)&&(f[s][i]+dis[i][j]<=gr[j]))
					f[s|(1<<(j-1))][j]=min(f[s|(1<<(j-1))][j],max(f[s][i]+dis[i][j],gl[j])+cost[j]);
				ans=max(ans,getbit(s));
			}
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"1 10 10" , "1 55 31", "10 50 100" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 2 10"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(0, Arg3, maxStores(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; string Arr1[] = {"1 10 10" , "1 55 30", "10 50 100" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 2 10"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(1, Arg3, maxStores(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 5; string Arr1[] = {"0 1000 17"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2 3 400", "4 1 500", "4 3 300", "1 0 700", "0 2 400"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(2, Arg3, maxStores(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        TravellingPurchasingMan ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE