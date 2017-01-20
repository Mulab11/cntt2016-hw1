// BEGIN CUT HERE

// END CUT HERE
//#line 5 "FencingPenguins.cpp"
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
#define mo 100007ll
#define add(a,b) a=(a+b)%mo
using namespace std;
const double pi=acos(-1);
struct point
{
	double x,y;
	friend double operator *(point a,point b){return a.x*b.y-a.y*b.x;}
	friend point operator -(point a,point b){return (point){a.x-b.x,a.y-b.y};}
}a[255],po[255];
bool pendright(point p,point d1,point d2)
{
	p=p-d1;d2=d2-d1;
	return p*d2>0;//??
}
int dr[255][255],pp[255];
long long f[255][255],g[255][255][2];
bool del[255][255];
class FencingPenguins
{
        public:
        int countWays(int ds, int r, vector <int> x_, vector <int> y_, string color)
        {
			int n=x_.size();
			for (int i=0;i<n;i++) a[i+1]=(point){(double)x_[i],(double)y_[i]};
			color=" "+color;
			double dlt=2*pi/ds,now=0;
			for (int i=1;i<=ds;i++)
			{
				po[i]=(point){r*cos(now),r*sin(now)};
				now+=dlt;
			}
			for (int i=1;i<=ds;i++)
			for (int j=i+1;j<=ds;j++)
			{
				memset(pp,0,sizeof(pp));
				bool pd=true;
				for (int k=1;k<=n;k++)
				if (pendright(a[k],po[i],po[j]))
				{
					dr[i][j]++;
					if (pp[color[k]]==-1) pd=false;
					pp[color[k]]=1;
				}
				else
				{
					if (pp[color[k]]==1) pd=false;
					pp[color[k]]=-1;
				}
				if (!pd) del[i][j]=true;
				if ((j==i+1)&&(dr[i][j])) return 0;
			}
			if (dr[1][ds]!=n) return 0;
			/*for (int i=1;i<=ds;i++)
			for (int j=1;j<=ds;j++)
			{
				cout<<dr[i][j]<<' ';
				if (j==ds) cout<<endl;
			}*/
			/*RST(F, G); DWN(s, n, 0){
 
            F[s][s] = F[s+1][s] = F[s][s+1] = 1;
            G[0][s][s+1] = 1, G[1][s][s+1] = 0;
 
            FOR(t, s+2, n){ //  // A[][] 表示对角线逆时针区域内有多少个企鹅。。
 
                if (A[s][t] == A[s+1][t-1] && !del[s][t]){
                    INC(G[0][s][t], F[s+1][t-1]);
                }
                FOR(i, s+1, t) if (A[i][t] == A[i+1][t-1] && !del[i][t]){
                    INC(G[0][s][t], pdt(G[0][s][i], F[i+1][t-1]));
                    INC(G[1][s][t], pdt(G[A[s][t] == A[s][i] + A[i+1][t]][s][i], F[i+1][t-1]));
                }
 
                if (A[s][t] == A[s+1][t]){
                    INC(F[s][t], F[s+1][t]);
                }
                FOR_1(i, s+1, t) if (A[s][t] == A[s][i] + A[i+1][t] && !del[s][i]){
                    INC(F[s][t], pdt(G[1][s][i], F[i+1][t]));
                }
            }*/
            for (int i=1;i<=ds;i++) {f[i][i]=f[i][i+1]=f[i+1][i]=1;g[i][i+1][0]=1;}
            for (int d=2;d<ds;d++)
            for (int i=1;i<=ds-d;i++)
            {
            	int j=i+d;
            	if ((!del[i][j])&&(dr[i][j]==dr[i+1][j-1])) add(g[i][j][0],f[i+1][j-1]);
            	for (int k=i+1;k<j;k++) if ((!del[k][j])&&(dr[k][j]==dr[k+1][j-1]))
            	{
            		add(g[i][j][0],g[i][k][0]*f[k+1][j-1]);
            		//add(g[i][j][1],g[i][k][1]*f[k+1][j-1]);
            		//if (dr[i][j]>dr[i][k]+dr[k][j]) add(g[i][j][1],g[i][k][0]*f[k+1][j-1]);
            			add(g[i][j][1],g[i][k][dr[i][j]==dr[i][k]+dr[k+1][j-1]]*f[k+1][j-1]);
            	}
            	if (dr[i][j]==dr[i+1][j]) add(f[i][j],f[i+1][j]);
            	for (int k=i+1;k<=j;k++) if (!del[i][k])
            	{
            		//if (dr[i][j]!=dr[i][k]+dr[k+1][j]) add(f[i][j],g[i][k][0]*f[k+1][j]);
            		//add(f[i][j],g[i][k][1]*f[k+1][j]);
            			if (dr[i][j]==dr[i][k]+dr[k+1][j]) add(f[i][j],g[i][k][1]*f[k+1][j]);
            	}
            }
            
            /*for (int s=ds;s>=1;s--)
			{
 
		        //f[s][s] = f[s+1][s] = f[s][s+1] = 1;
		        //g[s][s+1][0] = 1, g[s][s+1][1] = 0;
	 
		        for (int t=s+2;t<=ds;t++)
		        { 
	 
		            if (dr[s][t] == dr[s+1][t-1] && !del[s][t]) add(g[s][t][0], f[s+1][t-1]);
		            
		            for (int i=s+1;i<t;i++) if (dr[i][t] == dr[i+1][t-1] && !del[i][t])
		            {
		                add(g[s][t][0], g[s][i][0]*f[i+1][t-1]);
		                add(g[s][t][1], g[s][i][dr[s][t] == dr[s][i] + dr[i+1][t]]*f[i+1][t-1]);
		            }
	 
		            if (dr[s][t] == dr[s+1][t]) add(f[s][t], f[s+1][t]);
		            
		            for (int i=s+1;i<=t;i++) if (dr[s][t] == dr[s][i] + dr[i+1][t] && !del[s][i])
		                add(f[s][t], g[s][i][1]*f[i+1][t]);
		     	}
			}*/
            return f[1][ds];
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
{
        FencingPenguins ___test;
        ___test.run_test(6);
        return 0;
}
// END CUT HERE
