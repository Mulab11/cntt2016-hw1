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

const int mod=1e9+9;
set<int> s;
set<int>::iterator it;
vector<string> a;
int n,m,w;
inline void ch(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int exp(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=(ll)ans*x%mod;
		x=(ll)x*x%mod;y>>=1;
	}
	return ans;
}
void push(ll x){if(x<=w) s.insert((int)x);}
void add(ll x){
	for(ll d=1;d*d<=x;d++)
		if(x%d==0){
			push(d);
			if(d*d!=x) push(x/d);
		}
}
struct node{int x;char c;}p[1005];
bool cmp(node a,node b){return a.x<b.x;}
int check(int x){
	int k=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			p[++k]=(node){((ll)i*w%x+j)%x,a[i][j]};
	sort(p+1,p+k+1,cmp);
	int cnt=0;
	for(int i=1;i<=k;i++){
		int r=i;cnt++;
		while(r<k&&p[r+1].x==p[i].x){
			r++;
			if(p[r].c!=p[i].c) return -1;
		}i=r;
	}
	return cnt;
}

class CharacterBoard{
public:
	int countGenerators(vector<string> frag, int W, int x0, int y0){
		a=frag;n=a.size();m=a[0].size();
		s.clear();w=W;
		for(int i=0;i<n;i++)
			for(int j=-m+1;j<m;j++){
				ll t=(ll)i*w+j;
				if(t<0) continue;
				add(t);
			}
		int ans=0;
		if(n*m<=w) ans=(ll)(exp(26,w-n*m+1)-1)*exp(25,mod-2)%mod;
		for(it=s.begin();it!=s.end();it++){
			int i=*it,t=check(i);
			if(~t) ch(ans,exp(26,i-t));
			if(i>=n*m) ch(ans,mod-exp(26,i-n*m));
		}
		return ans;
	}
};
