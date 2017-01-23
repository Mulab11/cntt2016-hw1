// BEGIN CUT HERE

// END CUT HERE
#line 5 "History.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,tot;
int dis[310][310];
vector<int> a[110];
string ans;
char b[10010];

void update(int &i,int x)
{i=min(i,x);
}

class History
{	public:
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries)
	{	int i,j,k,l,r,l1,r1,x,y,p1,p2,s;
		
		n=dynasties.size();
		for(i=1;i<=n;i++)
		{	s=0;
			a[i].clear();
			for(j=0;j<dynasties[i-1].length();j++)
			{	if(dynasties[i-1][j]==' ')
				{	a[i].push_back(s);
					s=0;
				}
				else
					s=s*10+dynasties[i-1][j]-48;
			}
			a[i].push_back(s);
		}
		tot=0;
		for(i=1;i<=battles.size();i++)
			for(j=0;j<battles[i-1].length();j++)
				b[++tot]=battles[i-1][j];
		memset(dis,0x3f,sizeof(dis));	
		for(i=1;i<tot;i+=6)
		{	p1=b[i]-64;
			x=b[i+1]-48;
			p2=b[i+3]-64;
			y=b[i+4]-48;
			update(dis[p2][p1],a[p2][y+1]-1-a[p1][x]); //按照限制连边 
			update(dis[p1][p2],a[p1][x+1]-1-a[p2][y]);
		}
		for(i=1;i<=n;i++)
			for(j=0;j<a[i].size();j++)
				dis[(i-1)*10+j][(i-1)*10+j]=0;
		for(k=1;k<=n;k++)
			for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					if(i!=j && i!=k && j!=k)
						dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]); //floyd求出两个朝代之间的年差 
				
		ans="";
		for(i=0;i<queries.size();i++)
		{	p1=queries[i][0]-64;
			x=queries[i][1]-48;
			p2=queries[i][3]-64;
			y=queries[i][4]-48;
			l=a[p2][y];
			r=a[p2][y+1]-1;
			r+=dis[p1][p2];
			l-=dis[p2][p1];
			l1=a[p1][x];
			r1=a[p1][x+1]-1; //求出可行时间范围 

			if(l1<=r && r1>=l) //判断可行范围是否相交 
				ans.push_back('Y');
			else
				ans.push_back('N');
		}
		return ans;		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1 2 4",
 "1 2 3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A1-B0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"A0-B0",
 "A0-B1",
 "A1-B0",
 "A1-B1"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "NNYY"; verify_case(0, Arg3, verifyClaims(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"1000 2000 3000 10000",
 "600 650 2000",
 "1 1001 20001"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"B1-C0 A0-B0 A2-C1 B1-C1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"A0-B1",
 "A1-B1",
 "A2-B1",
 "C0-A0",
 "B0-A2",
 "C1-B0"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "YYYYNN"; verify_case(1, Arg3, verifyClaims(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"1 4 5",
 "10 13 17"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A0-B0 A0-B0 B0-A0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"A1-B0",
 "A0-B1",
 "A1-B1"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "YYY"; verify_case(2, Arg3, verifyClaims(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"1 5 6",
 "1 2 5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A0",
 "-B0 A",
 "1-B1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"A0-B0",
 "A1-B0",
 "A0-B1",
 "A1-B1"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "YNYY"; verify_case(3, Arg3, verifyClaims(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"2294 7344","366 384 449 965 1307 1415","307 473 648 688 1097","1145 1411 1569 2606","87 188 551 598 947 998 1917 1942"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A0-B4 B4-E2 B3-E2 D2-E4 A0-E4 B1-C3 A0-E3 A0-E6 D0","-E2 B2-E1 B4-E3 B4-D0 D0-E3 A0-D1 B2-C3 B1-C3 B4-E","3 D0-E1 B3-D0 B3-E2"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"A0-C2","E6-C2","A0-E4","B3-C1","C0-D2","B0-C1","D1-C3","C3-D0","C1-E3","D1-A0"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "YNYNNYNNNY"; verify_case(4, Arg3, verifyClaims(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	History ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
