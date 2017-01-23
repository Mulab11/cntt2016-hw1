// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndAvatar.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
int n,m,col;
int used[3010],f[3010][3010];
short a[3010][3010];

int calc(int l,int r,int x,int y,int x1,int y1) //求前面l个，后面r个(x,y)到(x1,y1)矩形和 
{int N,w,ret;

 if(x>x1 || y>y1) return 0;
 N=(l+1+r-1)/m+1;
 w=(l+1+r-1)%m+1;
 ret=(x1-x+1)*(y1-y+1);
 if(x1==N)
 {	if(y>w)
 		ret-=(y1-y+1);
 	else if(y1>w)
 		ret-=(y1-w);
 }
 return ret;
}

int solve(int l,int r,int lim) //最多递归lim次 
{int i,j,s,w,ret,N,x,y;

 //cout<<l<<" "<<r<<endl;
 if(f[l][r]!=-1) return f[l][r];
 if(lim<0) return 4;
 if(l==0 && r==0) return f[l][r]=0;
 if(l==0) //特判ans=1的情况 
 {	if(r<m)
 		return f[l][r]=1;
 	else if(m==1)
	 	return f[l][r]=1;	
 }
 else if(r==0)
 {	if(l<m || l%m==0)
 		return f[l][r]=1;
 	else if(m==1)
	 	return f[l][r]=1;	
 }
 else if(l==m-1 && r<m)
 	return f[l][r]=1;
 if(lim==1) return inf;
 
 N=(l+1+r-1)/m+1;
 x=l/m+1;
 y=l%m+1;
 ret=4;
 for(i=1;i<x;i++) //删除x前面的矩形 
 	for(j=1;j<=m;j++)
 		ret=min(ret,solve(l-i*j,r,lim-1)+1);
 ret=min(ret,solve(l,r-calc(l,r,x+1,1,N,m),lim-1)+1); //删除x后面的矩形 
 ret=min(ret,solve(l,r-calc(l,r,x,y+1,N,m),lim-1)+1);
 for(i=1;i<=x;i++) //删除x左边的矩形 
 	for(j=1;j<y;j++)
 		ret=min(ret,solve(l-i*j,r-calc(l,r,x+1,1,N,j),lim-1)+1);		
 for(i=1;i<=x;i++) //删除x右边的矩形 
 	for(j=1;j<=m-y;j++)
		ret=min(ret,solve(l-(i-1)*j,r-calc(l,r,x,y+1,N,y+j),lim-1)+1);
 //if(ret==1) cout<<l<<" "<<r<<endl;	
 //assert(ret>1);
 return f[l][r]=ret;
}

class FoxAndAvatar
{	public:
	int minimalSteps(int N, int width, int X)
	{	int i,j,x;
		
		n=N;
		m=width;
		x=X;
		memset(f,-1,sizeof(f));

		solve(x-1,n-x,3);

		if(f[x-1][n-x]<=3)
			return f[x-1][n-x];
		else
			return 4;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 3; int Arg3 = 1; verify_case(0, Arg3, minimalSteps(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 2; int Arg2 = 3; int Arg3 = 2; verify_case(1, Arg3, minimalSteps(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 13; int Arg1 = 3; int Arg2 = 8; int Arg3 = 3; verify_case(2, Arg3, minimalSteps(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 54; int Arg1 = 6; int Arg2 = 28; int Arg3 = 4; verify_case(3, Arg3, minimalSteps(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; int Arg3 = 0; verify_case(4, Arg3, minimalSteps(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	FoxAndAvatar ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
