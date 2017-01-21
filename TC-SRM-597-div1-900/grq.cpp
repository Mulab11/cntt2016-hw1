#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int mod=1e9+7;

int f[1000005],gg[1000005];
int r,g,b,m;

void ch(int &x,int y){
	x+=y;if(x>=mod) x-=mod;
}
int exp(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=(ll)ans*x%mod;
		x=(ll)x*x%mod;y>>=1;
	}
	return ans;
}
inline int C(int x,int y){
	if(x<y) return 0;
	return (ll)f[x]*gg[y]%mod*gg[x-y]%mod;
}
int solve(int x){
	if(x<=0) return 0;
	int ans=0;
	for(int i=0;i<=x;i++){
		if(i>g||i>r) continue;
		if(i+x>g+r) continue;
		int t=(g+r-x-i)/2;
		if((g+r-x-i)!=t*2) continue;
		if(g<t+i||r<t+i) continue;
		ch(ans,(ll)C(t+x-1,x-1)*C(x-i,g-t-i)%mod*C(x,i)%mod*exp(2,i)%mod);
	}//枚举间隙数并计算对应的组合数 
	return ans;
}

class LittleElephantAndBoard{
public:
	int getNumber(int M, int R, int G, int B){
		f[0]=1;
		for(int i=1;i<=1000000;i++) f[i]=(ll)f[i-1]*i%mod;
		gg[1000000]=exp(f[1000000],mod-2);
		for(int i=999999;i>=0;i--) gg[i]=(ll)gg[i+1]*(i+1)%mod;//预处理组合数用到的阶乘逆元 
		m=M;r=R;g=G;b=B;
		if(m<r||m<g||m<b) return 0;
		r=m-r;g=m-g;b=m-b;
		if(r+g+b!=m) return 0;
		if(m==1) return 1;//特判m=1和颜色数不对的情况 
		int ans=0;
		ch(ans,solve(b)*2%mod);
		ch(ans,solve(b-1));
		ch(ans,solve(b+1));//分别算1个点贴边，2个点贴边和没有点贴边的情况 
		return ans*2%mod;
	}
};