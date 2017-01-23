// BEGIN CUT HERE

// END CUT HERE
#line 5 "ShoutterDiv1.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=1e9;

int n,ans;
int a[3010],b[3010],dis[3010],f[3010],h[3010],q[3010];
vector<int> g[2510];
string sa,sb,sc,sd,ta,tb,tc,td;

void bfs() //宽搜求出每个区间扩展到l/r的最少转发次数 
{int i,j,t,w;
 
 t=1;
 w=0;
 for(i=1;i<=n;i++) 
 	if(dis[i]!=-1) q[++w]=i;
 while(t<=w)
 {	i=q[t];
 	for(j=0;j<g[i].size();j++)
	 	if(dis[g[i][j]]==-1)
		{	dis[g[i][j]]=dis[i]+1;
			q[++w]=g[i][j];
		}
	t++;
 }
}

string connect(vector<string> A) //转换格式 
{string ret;
 int i;
 
 ret="";
 for(i=0;i<A.size();i++)
 	ret+=A[i];
 return ret;
}

class ShoutterDiv1
{	public:
	int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1)
	{	int i,j,l,r,k;	
	
		sa=connect(s1000);
		sb=connect(s100);
		sc=connect(s10);
		sd=connect(s1);
		ta=connect(t1000);
		tb=connect(t100);
		tc=connect(t10);
		td=connect(t1);
		
		n=sa.size();
		for(i=1;i<=n;i++)
		{	a[i]=(sa[i-1]-48)*1000+(sb[i-1]-48)*100+(sc[i-1]-48)*10+sd[i-1]-48;
			b[i]=(ta[i-1]-48)*1000+(tb[i-1]-48)*100+(tc[i-1]-48)*10+td[i-1]-48;
		}
		//for(i=1;i<=n;i++)
		//	cout<<i<<" "<<a[i]<<" "<<b[i]<<endl;
		l=inf;
		r=-inf;
		for(i=1;i<=n;i++)
		{	r=max(r,a[i]);
			l=min(l,b[i]);
		}
		memset(dis,-1,sizeof(dis));
		for(i=1;i<=n;i++)
		{	if(a[i]<=l && b[i]>=l) dis[i]=0;
			//if(a[i]<=r && b[i]>=r) add(1+n+1,1+i,0);
		}
		for(i=1;i<=n;i++) g[i].clear();
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(i!=j)
				{	if(a[i]<=b[j] && b[i]>=a[j])
						g[i].push_back(j);
				}
		bfs(); //计算扩展到l的答案 
		for(i=1;i<=n;i++)
		{	f[i]=dis[i];
			if(f[i]==-1) return -1; //有一个不合法就是-1 
	 	}
		
		memset(dis,-1,sizeof(dis));
		for(i=1;i<=n;i++)
			if(a[i]<=r && b[i]>=r) dis[i]=0;
		
		bfs(); //计算扩展到l的答案 
		for(i=1;i<=n;i++) h[i]=f[i]+dis[i];		
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(a[i]<=b[j] && b[i]>=a[j])
					h[i]=min(h[i],h[j]+1);
		ans=0;
		for(i=1;i<=n;i++) ans+=h[i];
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"22", "2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00", "0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"11", "1"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"21", "4"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = {"22", "2"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); string Arr5[] = {"00", "0"}; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); string Arr6[] = {"11", "1"}; vector <string> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); string Arr7[] = {"43", "6"}; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); int Arg8 = 2; verify_case(0, Arg8, count(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_1() { string Arr0[] = {"00"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"00"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"13"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = {"00"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); string Arr5[] = {"00"}; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); string Arr6[] = {"00"}; vector <string> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); string Arr7[] = {"24"}; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); int Arg8 = -1; verify_case(1, Arg8, count(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_2() { string Arr0[] = {"0000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"0000"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"1234"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = {"0000"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); string Arr5[] = {"0000"}; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); string Arr6[] = {"0000"}; vector <string> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); string Arr7[] = {"2345"}; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); int Arg8 = 6; verify_case(2, Arg8, count(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_3() { string Arr0[] = {"0000000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0000000000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"0000000000"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"7626463146"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = {"0000000000"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); string Arr5[] = {"0000000000"}; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); string Arr6[] = {"0000000000"}; vector <string> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); string Arr7[] = {"9927686479"}; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); int Arg8 = 18; verify_case(3, Arg8, count(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_4() { string Arr0[] = {"00000000000000000000000000000000000000000000000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00000000000000000000000000000000000000000000000000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"50353624751857130208544645495168271486083954769538"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"85748487990028258641117783760944852941545064635928"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = {"00000000000000000000000000000000000000000000000000"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); string Arr5[] = {"00000000000000000000000000000000000000000000000000"}; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); string Arr6[] = {"61465744851859252308555855596388482696094965779649"}; vector <string> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); string Arr7[] = {"37620749792666153778227385275518278477865684777411"}; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); int Arg8 = 333; verify_case(4, Arg8, count(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	ShoutterDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
