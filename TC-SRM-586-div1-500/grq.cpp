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

const int N=55,inf=1e9;
vi get(string s){
	int m=s.length();
	vi t;t.clear();
	for(int i=0;i<m;i++){
		int k=i,now=0;
		while(k<m&&s[k]>='0'&&s[k]<='9') now=now*10+s[k++]-'0'; 
		t.pb(now);i=k;
	}
	return t;
}
int n,m,head[N],tot,d[N],cnt[N];
vi a[N],x,y,l,r;
struct node{int to,next,w;}p[N*N*N];
bool vis[N];

inline void add(int x,int y,int w){
	p[++tot]=(node){y,head[x],w};head[x]=tot;
}
queue<int> q;
bool spfa(int x){
	memset(cnt,0,sizeof(cnt));
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++) d[i]=inf;
	while(!q.empty())q.pop();
	d[x]=0;q.push(x);vis[x]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		vis[x]=0;cnt[x]++;
		if(cnt[x]>n) return 0;
		for(int i=head[x];i;i=p[i].next){
			int y=p[i].to;
			if(d[y]>d[x]+p[i].w){
				d[y]=d[x]+p[i].w;
				if(!vis[y]) q.push(y),vis[y]=1;
			}
		}
	}
	return 1;
}
//spfa判负环 
bool check(){
	memset(head,0,sizeof(head));tot=0;
	for(int i=0;i<m;i++){
		int x=::x[i],y=::y[i],l=::l[i],r=::r[i];
		add(y,x,a[y][r+1]-1-a[x][l]);
		add(x,y,a[x][l+1]-1-a[y][r]);
	}//建图 
	for(int i=0;i<n;i++)
		if(!spfa(i)) return 0;
	return 1;
}

class History{
public:
	string verifyClaims(vector<string> dynasties, vector<string> battles, vector<string> queries){
		n=dynasties.size();;m=0;
		for(int i=0;i<n;i++) a[i]=get(dynasties[i]);
		x.clear();y.clear();
		l.clear();r.clear();
		string b="",ans="";
		for(int i=0;i<battles.size();i++) b=b+battles[i];
		for(int i=0;i<b.size();i++)
			if(b[i]!=' ') x.pb(b[i]-'A'),y.pb(b[i+3]-'A'),l.pb(b[i+1]-'0'),r.pb(b[i+4]-'0'),i+=4;
		//字符串处理 
		m=x.size()+1;
		for(int i=0;i<queries.size();i++){
			string t=queries[i];
			x.pb(t[0]-'A'),y.pb(t[3]-'A'),l.pb(t[1]-'0'),r.pb(t[4]-'0');
			if(check()) ans+='Y'; else ans+='N';
			x.pop_back();y.pop_back();
			l.pop_back();r.pop_back();
		}
		return ans;
	}
};

