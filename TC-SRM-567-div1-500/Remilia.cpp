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

int n,m,cnt[55][33];
bool used[33];
vector<string> S;
VI res;

VI Main(){
	// 统计出现次数
	rep(i,0,n){
		rep(j,0,m){
			++cnt[i][S[i][j]-'a'];
		}
	}
	LL all=1ll<<n;--all;
	// 判断每个是否可行
	rep(i,0,n){
		LL mask=1ll<<i;
		rep(j,0,26)used[j]=0;
		for(;mask^all;){
			bool flag=0;
			// 每次放满一种字符，前提是这种字符是剩下的串中出现次数最多的
			rep(c,0,26)if(!used[c] && [=](){
				rep(j,0,n)if((mask>>j&1)==0){
					if(cnt[i][c]<cnt[j][c])return 0;
				}
				return 1;
			}()){
				// mask记录已经击败的串
				flag=1;
				used[c]=1;
				rep(j,0,n)if((mask>>j&1)==0 && cnt[i][c]>cnt[j][c])mask|=1ll<<j;
				break;
			}
			if(!flag)break;
		}
		if(mask==all)res.pb(i);
	}
	return res;
}

struct StringGame{
	VI getWinningStrings(vector<string> ss){
		n=SZ(ss);
		m=SZ(ss[0]);
		S=ss;
		return Main();
	}
};