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
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=2000005,mod=1e9+7,w=0,o=1;
int n,tot,pre[2][N],suf[2][N],sum[N>>1];
struct node{int x,num;}p[N];
bool cmp(node a,node b){return a.x<b.x;}
char s[N];
set<int> st;
set<int>::iterator it;
inline void ch(int &x,int y){
	x+=y;if(x>=mod) x-=mod;
}
int get(int x,int y){
	if(x&1) x++;if(y&1) y--;
	if(x>y) return 0;
	return (sum[y>>1]-(x?sum[(x>>1)-1]:0)+mod)%mod;
}
void prepare(){
	int x1=0,x2=0;
	for(int i=1;i<=n;i++){
		pre[w][i]=x1;pre[o][i]=x2;
		if(s[i]=='w') x1=i; else if(s[i]=='o') x2=i;
	}
	x1=n+1,x2=n+1;
	for(int i=n;i>=1;i--){
		suf[w][i]=x1;suf[o][i]=x2;
		if(s[i]=='w') x1=i; else if(s[i]=='o') x2=i;
	}
	for(int i=1;i<=n;i++)
		if(s[i]=='o'){
			int len=i-max(pre[o][i],pre[w][i])-1;
			if(len) p[++tot]=(node){i+len,i};
		}
	sort(p+1,p+tot+1,cmp);
	st.clear();
}
int solve(){
	prepare();sum[0]=1;
	int pt=0;
	for(int i=1;i<=n;i++){
		if(s[i-1]=='o'&&i-max(pre[o][i-1],pre[w][i-1])-2) st.insert(i-1);
		while(pt<tot&&p[pt+1].x==i) st.erase(p[++pt].num);
		if(i&1) continue;

		sum[i>>1]=sum[(i>>1)-1];
		if(s[i]=='w') continue;
		int tmp=get(max(pre[w][i],pre[o][i]),i-1),k=pre[w][i],j;
		if(k) ch(tmp,get(max(pre[o][k],2*k-i),min(k-1,(2*min(suf[o][k],i)-i-2))));
		for(it=st.begin(),j=*it;it!=st.end();j=*++it){
			if(suf[w][j]<=i) continue;
			tmp=(tmp+get(max(pre[o][j],pre[w][j]),2*j-i-2))%mod;
		}
		ch(sum[i>>1],tmp);
	}
	return get(n,n);
}

class WolfDelaymasterHard{
public:
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd){
		for(int i=1;i<=N;i++) s[i]='?';				// Concatenation of N '?'s
		ll x = w0;
		for(int i=0;i<wlen;i++){
			s[x+1] = 'w';				// Rewrite the x-th (0-based) character of s
			x = (x * wmul + wadd) % N;
		}
		x = o0;
		for(int i=0;i<olen;i++){
			s[x+1] = 'o';				// Rewrite the x-th (0-based) character of s
			x = (x * omul + oadd) % N;
		}
		n=N;
		return solve();
	}
};

