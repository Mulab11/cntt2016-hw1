// BEGIN CUT HERE

// END CUT HERE
//#line 5 "TheBrickTowerHardDivOne.cpp"
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
#define mo 1234567891ll
using namespace std;
const int dt[15][5]={{0,0,0,0,4},

					 {1,0,0,0,2},
					 {0,1,0,0,2},
					 {0,0,1,0,2},
					 {0,0,0,1,2},
					 
					 {0,0,1,1,2},
					 {0,1,0,1,2},
					 
					 {0,1,1,0,0},//can 7
					 
					 {0,0,1,2,1},
					 {1,2,0,0,1},
					 {0,1,0,2,1},
					 {1,0,2,0,1},
					 
					 {0,1,2,0,0},//can 12
					 {1,0,0,2,0},//can 13
					 
					 {0,1,2,3,0}};//can 14
int co,mx,mi[22],all,col[10],nw,od;
long long h,f[155],g[155],fac[5010],nifac[5010];
int gnum(int s,int k){return s*(mx+1)+k;}
bool getwei(int s,int w){return s&mi[w];}
long long pl(int n,int m){if (n<m) return 0;return fac[n]*nifac[n-m]%mo;}
struct mat
{
	long long a[155][155];
	friend mat operator *(mat x,mat y)
	{
		mat ans;memset(ans.a,0,sizeof(ans.a));
		for (int i=0;i<=all;i++)
		for (int j=0;j<=all;j++)
		for (int k=0;k<=all;k++)
			ans.a[i][j]=(ans.a[i][j]+x.a[i][k]*y.a[k][j])%mo;
		return ans;
	}
}sig;
mat getmi(mat a,long long x)
{
	/*if (x==1) return a;
	mat ans=getmi(a,x>>1);
	ans=ans*ans;
	if (x&1) ans=ans*a;
	return ans;*/
	mat ans;memset(ans.a,0,sizeof(ans.a));for (int i=0;i<=all;i++) ans.a[i][i]=1;
	while (x)
	{
		if (x&1) ans=ans*a;
		a=a*a;
		x>>=1;
	}
	return ans;
}
long long getmi(long long a,long long x)
{
	if (!x) return 1;
	long long ans=getmi(a,x>>1);
	ans=ans*ans%mo;
	if (x&1) ans=ans*a%mo;
	return ans;
}
int find(int p[])
{
	for (int i=0;i<=14;i++)
	{
		bool bo=true;
		for (int j=0;j<=3;j++)
		for (int k=j+1;k<=3;k++)
			if ((dt[i][j]==dt[i][k])!=(p[j]==p[k])) bo=false;
		if (bo) return i;
	}
	assert(0);
}
void search(int now,int nc)
{
	if (now==8)
	{
		//if ((col[0]==0)&&(col[1]==1)&&(col[2]==1)&&(col[3]==0)&&(col[4]==1)&&(col[5]==2)&&(col[6]==2)&&(col[7]==1)) {cout<<od<<' '<<nw<<' '<<co<<endl;assert(0);}
		if (od+nw>co) return;
		int add=0;
		for (int i=0;i<=3;i++) if (col[i]==col[i+4]) add++;
		if (col[4]==col[5]) add++;
		if (col[4]==col[6]) add++;
		if (col[7]==col[5]) add++;
		if (col[7]==col[6]) add++;
		int tp1=find(col),tp2=find(col+4);
				
		for (int k=0;k<=mx-add;k++)
		{
			//for (int dd=0;dd<=7;dd++) cout<<col[dd]<<' ';cout<<endl;
			sig.a[gnum(tp1,k)][gnum(tp2,k+add)]=(sig.a[gnum(tp1,k)][gnum(tp2,k+add)]+pl(co-od,nw))%mo;
			sig.a[gnum(tp1,k)][all]=(sig.a[gnum(tp1,k)][all]+pl(co-od,nw))%mo;
			//cout<<sig.a[7][7]<<endl;
		}
		return;
	}
	for (int i=0;i<=nc;i++)
	{
		col[now]=i;
		if (i==nc) {if (now<=3) od++;else nw++;}
		search(now+1,nc+(i==nc));
		if (i==nc) {if (now<=3) od--;else nw--;}
	}
}
class TheBrickTowerHardDivOne
{
        public:
        int find(int co_, int mx_, long long h_)
        {
        	co=co_;mx=mx_;h=h_;all=gnum(14,mx)+1;//cout<<all<<endl;
        	mi[0]=1;for (int i=1;i<=20;i++) mi[i]=mi[i-1]<<1;
        	fac[0]=nifac[0]=1;for (int i=1;i<=5000;i++) {fac[i]=fac[i-1]*i%mo;nifac[i]=getmi(fac[i],mo-2);}
			search(0,0);//cout<<sig.a[7][7]<<endl;
			sig.a[all][all]=1;
			long long sum=0;
			for (int i=0;i<=14;i++)
			{
				int cnt=1;
				if (dt[i][1]!=dt[i][0]) cnt++;
				if ((dt[i][2]!=dt[i][1])&&(dt[i][2]!=dt[i][0])) cnt++;
				if ((dt[i][3]!=dt[i][2])&&(dt[i][3]!=dt[i][1])&&(dt[i][3]!=dt[i][0])) cnt++;
				if ((dt[i][4]<=mx)&&(cnt<=co))
				{
					f[gnum(i,dt[i][4])]=pl(co,cnt);//cout<<co<<' '<<c[co][dt[i][4]<<endl;
					f[all]+=pl(co,cnt);
					//sum=(sum+f[gnum(i,dt[i][4])])%mo;
					//cout<<gnum(i,dt[i][4])<<' '<<f[gnum(i,dt[i][4])]<<endl;
				}
				//sum=(sum+f[all])%mo;
			}
			if (h==1) return f[all];
			sig=getmi(sig,h-1);
			for (int i=2;i<=2;i++)
			{
				for (int j=0;j<=all;j++) {g[j]=f[j];f[j]=0;}
				for (int j=0;j<=all;j++)
				for (int k=0;k<=all;k++)
					f[k]=(f[k]+g[j]*sig.a[j][k])%mo;
				//for (int j=0;j<all;j++) sum=(sum+f[j])%mo;
				//sum=(sum+f[all])%mo;
			}
			return f[all];
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 0; long long Arg2 = 2LL; int Arg3 = 4; verify_case(0, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 7; long long Arg2 = 19LL; int Arg3 = 1; verify_case(1, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 3; long long Arg2 = 1LL; int Arg3 = 14; verify_case(2, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 7; long long Arg2 = 47LL; int Arg3 = 1008981254; verify_case(3, Arg3, find(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        TheBrickTowerHardDivOne ___test;
        ___test.run_test(3);
        return 0;
}
// END CUT HERE
