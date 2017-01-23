#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<bits/stdc++.h>
using namespace std;

const double pi=acos(-1);

struct Complex
{double x,y;
};
struct Complex a[110],b[110];

Complex operator +(Complex A,Complex B){return (Complex){A.x+B.x,A.y+B.y};}
Complex operator -(Complex A,Complex B){return (Complex){A.x-B.x,A.y-B.y};}
Complex operator *(Complex A,Complex B){return (Complex){A.x*B.x-A.y*B.y,A.x*B.y+A.y*B.x};}
Complex csqrt(Complex A) //复数开根 
{double ang,l;
 Complex ret;
 ang=atan2(A.y,A.x)/2;
 l=sqrt(A.x*A.x+A.y*A.y);
 l=sqrt(l);
 ret.x=l*cos(ang);
 ret.y=l*sin(ang);
 return ret;
}

const double eps=1e-6;
int n,m;
int f[110],g[110],h[110];
vector<int> ans;

void dft(Complex A[],int N,int flag) //点值 
{Complex w,wn,now;
 static Complex B[110];
 int i,j;
  
 w=(Complex){1,0};
 wn.x=cos(2*pi/N);
 wn.y=flag*sin(2*pi/N);
 //wn.y=sin(2*pi/N);
 for(i=0;i<N;i++)
 {	B[i]=(Complex){0,0};
 	now=(Complex){1,0};
 	for(j=0;j<N;j++)
 	{	B[i]=B[i]+(now*A[j]);
 		now=now*w;
 	}
 	w=w*wn;
 }
 for(i=0;i<N;i++) A[i]=B[i];
 if(flag==-1)
 {	for(i=0;i<N;i++)
 	{	A[i].x/=N;
 		A[i].y/=N;
 	}
 }
}

int check() //验算是否合法 
{int i,j,flag;
 
 for(i=1;i<n/2;i++)
 	if(f[i]!=f[n-i]) return 0;
 for(i=0;i<n;i++) h[i]=0;
 for(i=0;i<n;i++)
 	for(j=0;j<n;j++)
 		h[(i+j)%n]+=f[i]*f[j];
 for(i=0;i<n;i++)
 	if(h[i]!=g[i]) return 0;	 	
 if(ans.empty()) return 1;	
 flag=1;
 i=0;
 while(i<n && f[i]==ans[i]) i++;
 return i<n && f[i]<ans[i];
}

class SplittingFoxes2
{	public:
	vector <int> getPattern(vector <int> amount)
	{	int i,j;
		
		n=amount.size();
		for(i=0;i<n;i++)
		{	a[i]=(Complex){(double)amount[i],0};
			g[i]=amount[i];
		}
		dft(a,n,1);
		m=n/2+1;
		ans.clear();
		for(i=0;i<(1<<m);i++)
		{	for(j=0;j<n;j++) //枚举平方根正负 
			{	b[j]=csqrt(a[j]);
				if(i&(1<<min(j,n-j)))
				{	b[j].x*=-1;
					b[j].y*=-1;
				}
			}
			dft(b,n,-1);
			for(j=0;j<n;j++)
				//if(fabs(b[j].y)<eps)
					f[j]=(int)(b[j].x+0.5);
			if(check())
			{	ans.clear();
				for(j=0;j<n;j++) ans.push_back(f[j]);
			}
		}
		if(ans.empty())
			ans.push_back(-1);
		return ans;
	}
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {2,0,1,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 0, 0, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getPattern(Arg0)); }
	void test_case_1() { int Arr0[] = {1,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0, 1, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getPattern(Arg0)); }
	void test_case_2() { int Arr0[] = {2,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getPattern(Arg0)); }
	void test_case_3() { int Arr0[] = {10,0,8,0,10,0,8,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 0, 2, 0, 1, 0, 2, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getPattern(Arg0)); }
	void test_case_4() { int Arr0[] = {35198,27644,22185,26896,34136,26896,22185,27644}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 59, 90, 76, 22, 76, 90, 59 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, getPattern(Arg0)); }
	void test_case_5() { int Arr0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, getPattern(Arg0)); }

// END CUT HERE
};

// BEGIN CUT HERE
int main()
{	SplittingFoxes2 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
