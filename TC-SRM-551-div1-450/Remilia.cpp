// by ξ
// program sky  :)

#include <bits/stdc++.h>

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

const int inf=5e8;

int n,a[88][88];
struct ColorfulWolves{
	int getmin(vector<string> A){
		n=SZ(A);
		rep(i,0,n)rep(j,0,n)a[i][j]=i==j?0:inf;
		rep(i,0,n){
			int cnt=0;
			rep(j,0,n)if(A[i][j]=='Y'){
				a[i][j]=cnt++;// 一种颜色变成另一种的代价
			}
		}
		rep(k,0,n)rep(i,0,n)rep(j,0,n)a[i][j]=min(a[i][j],a[i][k]+a[k][j]);// floyd
		return a[0][n-1]==inf?-1:a[0][n-1];
	}
};