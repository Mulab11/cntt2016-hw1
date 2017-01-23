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

const int inf=1<<30;
int n,to[30],a[30],go[30];
int cost[30][2];

inline int d(int k,int x,int y){
	if(!k) return y-x+(y<x?26:0);
	return x-y+(x<y?26:0);
} //clockwise 0

queue<int> q;
int check(int choose,int cn,int cp){
	memset(a,-1,sizeof(a));
	while(!q.empty())q.pop(); 
	for(int i=0;i<n;i++) if(~to[i]){a[i]=choose;q.push(i);break;}
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<n;i++){
			int k=-1;
			if(to[i]==-1||to[i]==to[x]) continue;
			if((go[i]&go[x])==go[x]||(go[i]&go[x])==go[i]) k=a[x]^1; else k=a[x];
			if(a[i]>=0&&k!=a[i]) return inf;
			if(a[i]==-1) a[i]=k,q.push(i);
		}
	}
	memset(cost,0,sizeof(cost));
	for(int i=0;i<n;i++){
		if(to[i]==-1) continue;
		cost[to[i]][a[i]]=max(cost[to[i]][a[i]],d(a[i],i,to[i]));
	}
	int ans=0;
	for(int i=0;i<n;i++){
		if(!cost[i][0]&&!cost[i][1]) continue;
		if(cost[i][0]+cost[i][1]>n) return inf;
		ans+=cost[i][0]*cn+cost[i][1]*cp;
	}
	return ans;
}
int vis[26];
bool check(){
	vi a;a.clear();memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++) if(~to[i]) a.pb(to[i]);
	int k=a[0],isok=1;vis[k]=1;
	for(int i=1;i<a.size();i++)
		while(k!=a[i]) k=(k+1)%n,vis[k]++;
	for(int i=0;i<n;i++) if(vis[i]>1){if(isok) isok=0; else return 0;}
	return 1;
}
int calc(int x,int cn){
	int ans=0;
	memset(cost,0,sizeof(cost));
	for(int i=0;i<n;i++){
		if(to[i]==-1) continue;
		bool isok=0;
		for(int j=0;j<n;j++)
			if(to[i]!=to[j]&&(go[j]&go[i])==go[i]) isok=1;
		cost[to[i]][0]=max(cost[to[i]][0],d(x,i,to[i])+isok*n);
	}
	for(int i=0;i<n;i++)
		ans+=cost[i][0];
	return ans*cn;
}

class NextAndPrev{
public:
	int getMinimum(int cn, int cp, string start, string goal){
		n=start.size();
		memset(go,0,sizeof(go));
		memset(to,-1,sizeof(to));
		memset(vis,0,sizeof(vis));
		for(int i=0;i<n;i++){
			int k=start[i]-'a';
			if(to[k]!=-1&&to[k]!=goal[i]-'a') return -1;
			to[k]=goal[i]-'a';
		}
		n=26;
		int isok=1,last=-1,cnt=0;
		for(int i=0;i<n;i++){
			if(to[i]==-1) continue;
			if(last>=0&&to[i]!=last) isok=0; 
			last=to[i];	go[i]=1<<i;
			vis[to[i]]=1;
			for(int j=i;j!=to[i];j=(j+1)%n) go[i]|=1<<j;
		}
		for(int i=0;i<n;i++) cnt+=vis[i];
		if(cnt==26){for(int i=0;i<n;i++) if(to[i]!=i) return -1;return 0;}
		if(isok){
			vi a;a.clear();
			for(int i=(last+1)%n;i!=last;i=(i+1)%n) if(to[i]>=0) a.pb(i);
			int ans=inf;
			for(int i=0;i<=a.size();i++){
				int tmp=0;
				if(i<a.size()) tmp+=cn*d(0,a[i],last);
				if(i) tmp+=cp*d(1,a[i-1],last);
				ans=min(ans,tmp);
			}
			return ans;
		}
		else{
			int ans=min(check(0,cn,cp),check(1,cn,cp));
			if(check()){
				ans=min(ans,calc(0,cn));
				for(int i=0;i<n;i++) go[i]^=(1<<n)-1;
				ans=min(ans,calc(1,cp));
			}
			if(ans<inf) return ans; 
			return -1;
		}
	}
};
