// by ξ
// program sky  :)

#include <vector>
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
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

const int N=1<<13;

int n,M,low[22],up[22],a[22],lg[N],cnt[N];
db c[22],key[22];
bool ok[N];

inline db Main(){
	db ans=0;
	rep(i,0,n)lg[1<<i]=i;
	rep(i,1,1<<n)cnt[i]=cnt[i>>1]+(i&1);// bit pret
	rep(i,0,1<<n){
		if(cnt[i]<=1){
			ok[i]=1;
		}else{
			int j=i&-i;
			ok[i]=ok[i-j];if(!ok[i])continue;
			j=lg[j];
			for(int k=i-(1<<j);k;){
				int p=k&-k;
				ok[i]=ok[i] && (a[lg[p]]>>j&1);
				if(!ok[i])break;
				k-=p;
			}
		}// if all b[i][j]=1
		if(!ok[i])continue;
		int S=(1<<n)-1-i;
		for(int T=S;;(--T)&=S){// T: use up;S-T: use low
			db tmp=0,m=M;
			rep(u,0,n)if(S>>u&1){
				key[u]=T>>u&1?up[u]:low[u];
				m-=key[u];
			}
			if(m<0){
				if(!T)break;
				continue;
			}
			// m: sum of y
			rep(u,0,n)if(i>>u&1){
				c[u]=0;
				rep(v,0,n)if((S>>v&1) && (a[u]>>v&1))c[u]+=key[v];
				tmp+=m+c[u];
			}
			tmp=(m-tmp)/cnt[i];// lambda of Lagrange's mm
			rep(u,0,n)if(i>>u&1)key[u]=tmp+m+c[u];
			if([=](){
				rep(u,0,n)if(key[u]<low[u] || key[u]>up[u])return 0;
				return 1;// satisfies the constraint
			}()){
				db cur=0;
				rep(u,0,n)rep(v,u+1,n)if(a[u]>>v&1)
					cur+=key[u]*key[v];
				if(cur>ans)ans=cur;// upd the ans
			}
			if(!T)break;
		}
	}
	return ans;
}

struct BoundedOptimization{
	db maxValue(vector<string> expr,VI lowerBound,VI upperBound,int maxSum){
		string s="";
		for(auto xx:expr)s+=xx;
		for(int i=0;i<SZ(s);i+=3){
			int u=s[i]-'a',v=s[i+1]-'a';
			a[u]|=1<<v;
			a[v]|=1<<u;
		}//read
		n=SZ(lowerBound);
		int tmp=0;
		rep(i,0,n)low[i]=lowerBound[i],up[i]=upperBound[i],tmp+=up[i];
		M=maxSum;
		if(tmp<=M)return [](){
			db ans=0;
			rep(i,0,n)rep(j,i+1,n)if(a[i]>>j&1)
				ans+=up[i]*up[j];
			return ans;
		}();// when sum up<=M
		return Main();
	}
};