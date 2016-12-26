// by ξ
// program sky  :)

#include <vector>
#include <algorithm>

#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)

using namespace std;

int F[55];

struct SpellCards{
	int maxDamage(vector <int> le, vector <int> da){
		int n=le.size();
		rep(i,0,n)dto(j,n,le[i])F[j]=max(F[j],F[j-le[i]]+da[i]);//背包
		return *max_element(F,F+n+1);
	}
};