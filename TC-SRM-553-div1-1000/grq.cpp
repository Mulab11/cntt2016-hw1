#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pli pair<ll,int>
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int INF=1e9+7,N=55;
const ll inf=1ll<<50;

struct node{
	int to,next;
	pli w;
}p[1005];
int n,m,head[N],tot,ti[N];
pli d[N],last[N];
bool vis[N];
queue<int> q;
inline void add(int x,int y,pair<ll,int> z){
//	printf("edge:%d %d %I64d\n",x,y,z.FF);
	p[++tot]=(node){y,head[x],z};head[x]=tot;
}
inline pli operator + (pli a,pli b){
	a.FF+=b.FF;a.SS+=b.SS;
	return a;
}
void clear(){
	memset(ti,0,sizeof(ti));
	memset(vis,0,sizeof(vis));
	while(!q.empty()) q.pop();
	for(int i=0;i<=n;i++) d[i]=mp(inf,0);
}
pair<bool,int> spfa(int s){
	clear();
	q.push(s);d[s]=mp(0,0);vis[s]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		vis[x]=0;
		if(ti[x]>=n+1) return mp(0,d[x].SS);
		for(int i=head[x];i;i=p[i].next){
			int y=p[i].to;pli w=p[i].w;
			if(w.FF+d[x].FF<d[y].FF){
				if(!vis[y]) last[y]=d[y],q.push(y),ti[y]++;vis[y]=1;
				d[y]=w+d[x];
			}
		}
	}
	return mp(1,0);
}
bool check(vi u1,vi v1,vi w1,vi u2,vi v2,vi w2,ll k,bool typ){
//	printf("%lld\n",k);
	int m;
	tot=0;memset(head,0,sizeof(head));
	for(int i=1;i<n;i++) add(i-1,i,mp(-1,0));
	add(n-1,0,mp(k-1,1));
	m=u2.size();
	for(int i=0;i<m;i++)
		if(u2[i]<v2[i]) add(v2[i],u2[i],mp(w2[i],0)); else add(v2[i],u2[i],mp(w2[i]-k,-1));
	m=u1.size();
	for(int i=0;i<m;i++)
		if(u1[i]<v1[i]) add(u1[i],v1[i],mp(-w1[i],0)); else add(u1[i],v1[i],mp(k-w1[i],1));
	pair<bool,int> g=spfa(0);
	bool x=g.FF;int y=g.SS;
//	if(typ) printf("%lld %d %d\n",k,x,y);
	if(x) return 1;
	if(!typ&&y<0) return 1;
	if(typ&&y>0) return 1;
	return 0;
}

class YamanoteLine{
public:
	long long howMany(int N, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2){
		ll upp,low,l,r;
		n=N;
//		check(s1,t1,l1,s2,t2,l2,6,1);
//		return 0;
		l=n,r=inf;
		while(l<r){
			ll mid=l+r>>1;
			if(check(s1,t1,l1,s2,t2,l2,mid,0)) r=mid; else l=mid+1;
		}
		low=r;
		l=n,r=inf;
		while(l<r){
			ll mid=l+r+1>>1;
//			if(n<=3) cerr<<l<<" "<<r<<" "<<mid<<endl;
			if(check(s1,t1,l1,s2,t2,l2,mid,1)) l=mid; else r=mid-1;
		}
		upp=r;
		if(upp-low>=(1ll<<45)) return -1;
		cout<<low<<" "<<upp<<endl;
		return max(0ll,upp-low+1);
	}
};
