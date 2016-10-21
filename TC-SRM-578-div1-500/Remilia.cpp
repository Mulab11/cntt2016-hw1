// by ξ
// program sky  :)

#include <set>
#include <vector>
#include <stdio.h>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define mk make_pair
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

multiset<int> Set;

const int mo=1e9+7;

inline void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}

string s;
int n,m,l[333],r[333],f[333][333];
VI li[333];

//把字符串转化成整数
inline void gao(int *a){
	int i=0,j=0;m=0;
	for(;j<s.length();++j)
		for(int &x=a[++m];j<s.length() && s[j]^' ';)
			x=(x<<3)+(x<<1)+s[j++]-48;
}

inline int Main(){
	For(i,1,m)++l[i],++r[i];
	For(i,1,m){
		li[r[i]].pb(l[i]);
		Set.insert(l[i]);
	}
	Set.insert(n);
	//维护当前最小的左端点
	int an=1;
	For(i,1,n){
		int t=*Set.begin();
		f[i][0]=1;
		rep(j,1,t)inc(f[i][j],f[j][j-1]);//临界点左边的情况
		rep(j,t,i)inc(f[i][j],f[j][t-1]);//临界点右边的情况
		rep(j,1,i)inc(f[i][j],f[i][j-1]);//前缀和优化
		inc(an,f[i][i-1]);//统计答案
		for(int x:li[i])Set.erase(Set.find(x));//删除右端点为i的线段
	}
	return an;
}

struct WolfInZooDivOne{
	int count(int N, vector <string> L, vector <string> R){
		n=N;
		s="";for(auto x:L)s+=x;gao(l);
		s="";for(auto x:R)s+=x;gao(r);
		//读入数据
		return Main();
	}
};