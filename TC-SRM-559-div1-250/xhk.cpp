// BEGIN CUT HERE

// END CUT HERE
#line 5 "HyperKnight.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
int n,m,w,tot,cnt;
int v[8][2],sa[110];
long long ans;
pair<int,int> c[110];

int check(int x,int y) //判断(x,y)有几个方向可以跳出去 
{int i,nx,ny,ret=0;
 
 for(i=0;i<8;i++)
 {	nx=x+v[i][0];
 	ny=y+v[i][1];
 	if(nx>0 && nx<=n && ny>0 && ny<=m) ret++;
 }
 return ret;
}

class HyperKnight
{	public:
	long long countCells(int a, int b, int numRows, int numColumns, int K)
	{   int i,j;
		
		n=numRows;
		m=numColumns;
		w=K;
		v[0][0]=a;
		v[0][1]=b;
		v[1][0]=a;
		v[1][1]=-b;
		v[2][0]=-a;
		v[2][1]=b;
		v[3][0]=-a;
		v[3][1]=-b;
		v[4][0]=b;
		v[4][1]=a;
		v[5][0]=b;
		v[5][1]=-a;
		v[6][0]=-b;
		v[6][1]=a;
		v[7][0]=-b;
		v[7][1]=-a;
		tot=0;
		sa[++tot]=1;
		sa[++tot]=a;
		sa[++tot]=b;
		sa[++tot]=n;
		sa[++tot]=m;
		sa[++tot]=n-a;
		sa[++tot]=n-b;
		sa[++tot]=m-a;
		sa[++tot]=m-b;
		sort(sa+1,sa+tot+1); //离散化 
		ans=0;
		cnt=0;
		for(i=1;i<=tot;i++) //每个区间对应到一个区间 
			if(sa[i]!=sa[i-1])
				c[++cnt]=make_pair(sa[i],1);
		for(i=1;i<tot;i++)	
			if(sa[i]<sa[i+1]-1)
				c[++cnt]=make_pair(sa[i]+1,sa[i+1]-sa[i]-1);
		//for(i=1;i<=cnt;i++)
		//	cout<<c[i].first<<" "<<c[i].second<<endl;		
		for(i=1;i<=cnt;i++)
			for(j=1;j<=cnt;j++) //枚举每个离散后的点 
				if(c[i].first<=n && c[j].first<=m)
				{	if(check(c[i].first,c[j].first)==w)
						ans+=(ll)c[i].second*c[j].second;
				}
		return ans;		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 8; int Arg3 = 8; int Arg4 = 4; long long Arg5 = 20LL; verify_case(0, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 8; int Arg3 = 8; int Arg4 = 2; long long Arg5 = 16LL; verify_case(1, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 3; int Arg2 = 7; int Arg3 = 11; int Arg4 = 0; long long Arg5 = 0LL; verify_case(2, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 10; int Arg3 = 20; int Arg4 = 8; long long Arg5 = 56LL; verify_case(3, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 4; int Arg2 = 100; int Arg3 = 10; int Arg4 = 6; long long Arg5 = 564LL; verify_case(4, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { int Arg0 = 2; int Arg1 = 3; int Arg2 = 1000000000; int Arg3 = 1000000000; int Arg4 = 8; long long Arg5 = 999999988000000036LL; verify_case(5, Arg5, countCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	HyperKnight ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
