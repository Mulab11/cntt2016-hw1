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

/*
摊成序列贪心：
a[i]个i，每段<=K，差值不超过2
*/

struct TheJediTest{
	int minimumSupervisors(VI a, int K){
		int la=0,ans=0,tot=0;
		for(int x:a){
			if(tot==3){
				la=0;++ans;tot=0;
			}
			if(x+la<K){
				if(la || x){
					la+=x;
					++tot;
				}
			}else{
				x+=la;
				ans+=x/K;
				la=x%K;
				tot=!!la;
			}
		}
		return ans+!!la;
	}
};