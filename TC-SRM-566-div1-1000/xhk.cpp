// BEGIN CUT HERE

// END CUT HERE
#line 5 "FencingPenguins.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const double pi=acos(-1);
const int mod=100007;

struct point
{double x,y;
};
struct point a[310],b[310];

int n,m,R,ans;
int used[310][310],c[310],f[310][310],g[310][310],h[310][310];
long long con[310][310];

double mul(point p0,point p1,point p2)
{return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

void update(int &i,int x)
{i=(i+x)-(i+x>=mod?mod:0);
}

int next(int i)
{return i==n?1:i+1;
}

int pre(int i)
{return i==1?n:i-1;
}

long long check(int i,int j,int k) //判断(a[i],a[j],a[k])三角形内部又有没有企鹅 
{if(i==j || i==k || j==k) return 0;
 return con[i][j]&con[j][k]&con[k][i];
}

void solve(int l,int r) //计算f/g/h[l][r] 
{int i,j,k,s;
 long long x;
 
 if(f[l][r]!=-1) return;
 if(l==r || next(l)==r)
 {	f[l][r]=1;
 	g[l][r]=0;
 	h[l][r]=(l!=r?1:0);
 	return;
 }
 f[l][r]=g[l][r]=h[l][r]=0;
 for(i=next(l);i!=r;i=next(i)) //计算g[l][r],h[l][r]
 {	if(check(l,next(l),i) || check(next(l),pre(i),i)) continue;
 	solve(i,r);
	if(i!=next(l))
	{	solve(next(l),pre(i));
		s=f[next(l)][pre(i)];
	}
	else
		s=1;
 	x=check(l,i,r);
 	//cout<<" hh "<<i<<" "<<flag<<" "<<con[1][3]<<" "<<con[3][4]<<" "<<con[4][1]<<endl;
 	if(used[i][l])
	{	if(x)
			update(g[l][r],(ll)s*(g[i][r]+h[i][r])%mod);
 		else
 			update(g[l][r],(ll)s*g[i][r]%mod);
 		if(!x)
			update(h[l][r],(ll)s*h[i][r]%mod);
	}
 }
 if(used[l][r]) f[l][r]=g[l][r];
 
 for(i=next(l);i!=r;i=next(i)) //计算f[l][r] 
 {	if(check(l,i,r)) continue;
	if(used[i][r])
	{	solve(i,r);
		if(i!=next(l))
		{	if(!check(l,pre(i),i))
			{	solve(l,pre(i));
				s=f[l][pre(i)];
			}
			else
				s=0;
		}
		else
			s=1;
		update(f[l][r],(ll)s*g[i][r]%mod);	
	}
 }
 if(!check(r,l,pre(r)))
 {	solve(l,pre(r));
 	update(f[l][r],f[l][pre(r)]);
 }
 if(!check(l,next(l),r) && !check(r,next(l),pre(r)) && used[l][r]) //一条边l~r对h[l][r]的贡献 
 {	solve(next(l),pre(r));
 	//update(f[l][r],f[next(l)][pre(r)]);
 	update(h[l][r],f[next(l)][pre(r)]);
 }
 
 //cout<<l<<" "<<r<<" ## "<<f[l][r]<<" "<<g[l][r]<<" "<<h[l][r]<<endl;
}

class FencingPenguins
{	public:
	int countWays(int numPosts, int radius, vector <int> X, vector <int> Y, string color)
	{	int i,j,k,s,s1,s2;
		long long x,y;
		
		n=numPosts;
		R=radius;
		for(i=1;i<=n;i++)
			a[i]=(point){R*cos((i-1)*2*pi/n),R*sin((i-1)*2*pi/n)};
		m=X.size();	
		for(i=1;i<=X.size();i++)
		{	b[i]=(point){X[i-1],Y[i-1]};
			if(color[i-1]<=90)
				c[i]=color[i-1]-65;
			else
				c[i]=26+color[i-1]-97;	
		}
		memset(used,0,sizeof(used));
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{	if(i==j) continue;
				x=0;
				y=0;
				for(k=1;k<=m;k++)
					if(mul(a[i],a[j],b[k])>0)
						x|=(1LL<<c[k]);
					else
						y|=(1LL<<c[k]);
				used[i][j]=((x&y)==0);
			}
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{	if(i==j) continue;
				con[i][j]=0;
				for(k=1;k<=m;k++)
					if(mul(a[i],a[j],b[k])>0)
						con[i][j]|=(1LL<<(k-1));
			}
		memset(f,-1,sizeof(f));
		memset(g,-1,sizeof(g));
		memset(h,-1,sizeof(h));	
		
		x=(1LL<<m)-1;
		for(i=1;i<=n;i++) x&=con[i][next(i)];
		if(x!=(1LL<<m)-1) return 0;
		
		ans=0;
		for(i=2;i<=n;i++)
			if(used[1][i])
			{	solve(i,1);
				if(i!=2)
				{	if(!check(1,2,i) && !check(2,pre(i),i))
					{	solve(2,pre(i));
						s=f[2][pre(i)];
					}
					else
						s=0;
				}
				else
					s=1;
				update(ans,(ll)s*g[i][1]%mod);
			}	
		if(!check(1,2,n))
		{	solve(2,n);
			update(ans,f[2][n]);
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arg1 = 10; int Arr2[] = {2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "R"; int Arg5 = 3; verify_case(0, Arg5, countWays(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 10; int Arr2[] = {2,-2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,-1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "RR"; int Arg5 = 1; verify_case(1, Arg5, countWays(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 8; int Arg1 = 10; int Arr2[] = {8,-8,-8,8}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,-1,1,-1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "BBBB"; int Arg5 = 25; verify_case(2, Arg5, countWays(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 8; int Arg1 = 10; int Arr2[] = {8,-8,-8,8}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,-1,1,-1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "RGBY"; int Arg5 = 50; verify_case(3, Arg5, countWays(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 6; int Arg1 = 5; int Arr2[] = {0,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-4,4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "rB"; int Arg5 = 6; verify_case(4, Arg5, countWays(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { int Arg0 = 3; int Arg1 = 5; int Arr2[] = {4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "y"; int Arg5 = 0; verify_case(5, Arg5, countWays(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_6() { int Arg0 = 200; int Arg1 = 100000; int Arr2[] = {1020,30203,2302,203,-12321,-21332,8823,-2133,2323}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-123,2131,4434,1223,43434,2323,4343,-213,-2325}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "YBYBWWBRr"; int Arg5 = 27547; verify_case(6, Arg5, countWays(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	FencingPenguins ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
