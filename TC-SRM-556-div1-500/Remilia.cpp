// by ξ
// program sky  :)

#include <vector>
#include <complex>
#include <stdio.h>
#include <cassert>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define SZ(A) (int(A.size()))
#define pb push_back
#define mk make_pair
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef complex<db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

int n;
bool ok[55][55][5];
string A,M,dp[55][55][5];

int cmp(char a,char b){
	// 比大小
	return a<b?0:a==b?1:2;
}

int pcmp(int a,int b){
	// 拼起来比大小
	return a==1?b:a;
}

void upd(int i,int j,int k,string xx){
	// dp更新
	if(ok[i][j][k])
		dp[i][j][k]=min(dp[i][j][k],xx);
	else
		ok[i][j][k]=1,dp[i][j][k]=xx;
}

string Main(){
	n=SZ(A);
	rep(i,0,n)ok[i][0][1]=1;
	rep(L,0,n)For(i,0,n-L)For(ty,0,2)
	if(ok[i][L][ty]){
		// 放一个字符在后面
		if(i+L<n){
			upd(i,L+1,pcmp(ty,cmp(A[L],M[i+L])),dp[i][L][ty]+A[L]);
		}
		// 放一个字符在前面
		if(i && L){
			upd(i-1,L+1,pcmp(cmp(A[L],M[i-1]),ty),A[L]+dp[i][L][ty]);
		}
	}
	if(ok[0][n][1])return dp[0][n][1];
	if(ok[0][n][2])return dp[0][n][2];
	return "";
}

struct LeftRightDigitsGame2{
	string minNumber(string a,string m){
		A=a;M=m;
		return Main();
	}
};