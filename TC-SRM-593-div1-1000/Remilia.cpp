// by ξ
// program sky  :)

#include <deque>
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

const int mo=1e9+7;

void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}
void dec(int &x,int y){if((x-=y)<0)x+=mo;}

char s[2000010];

int n,sum,len[2000010],dp[1000010],he[1000010],ne[1000010];
bool DEL[1000010],inq[1000010];
deque<int> Q;

// 插删维护队列元素的dp值之和

void del(int x){
	// 永久删除一个点
	if(DEL[x/2])return;
	DEL[x/2]=1;
	if(inq[x/2])dec(sum,dp[x/2]),inq[x/2]=0;
}

void ins(int x){
	// 把一个点插入队列
	if(DEL[x/2] || inq[x/2])return;
	if(!SZ(Q) || x>Q.back())Q.pb(x);else Q.push_front(x);
	inq[x/2]=1;
	inc(sum,dp[x/2]);
}

int Main(){
	if(s[1]=='o' || n&1)return 0;
	dto(i,n-1,0)len[i]=s[i+1]=='o'?0:len[i+1]+1;
	For(i,0,n/2)he[i]=-1;
	// 挂链
	for(int i=0;i<=n;i+=2)if(len[i]+i/2<=n/2){
		ne[i/2]=he[len[i]+i/2];
		he[len[i]+i/2]=i/2;
	}
	dp[0]=1;ins(0);
	int wei=0;
	for(int i=2;i<=n;i+=2){
		// 后半段的限制
		if(s[i]=='w')wei=i;else if(s[i-1]=='w')wei=i-1;else{
			if(2*wei-i>=0)ins(2*wei-i);
		}
		for(;SZ(Q) && (Q.front()<2*wei-i || DEL[Q.front()/2]);){
			int u=Q.front();
			if(!DEL[u/2])inq[u/2]=0,dec(sum,dp[u/2]);
			Q.pop_front();
		}
		dp[i/2]=sum;
		// 前半段的限制
		for(int e=he[i/2];~e;e=ne[e])del(2*e);
		ins(i);
	}
	return dp[n/2];
}

struct WolfDelaymasterHard{
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd){
		n=N;
		For(i,1,n)s[i]='?';
		LL x=w0;
		int i;
		for(i=0;i<wlen;i++){
			s[x+1] = 'w';
			x = (x * wmul + wadd) % N;
		}
		x = o0;
		for(i=0;i<olen;i++){
			s[x+1] = 'o';
			x = (x * omul + oadd) % N;
		}
		return Main();
	}
};