#include<cstdio>
#include<vector>
#include<string>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TravellingPurchasingMan{
	private:
		static const int inf=1000000000,maxn=53,maxm=100;
		int n,m;
		int head[maxn],list[maxm<<1],nxt[maxm<<1],cost[maxm<<1],tot;
		int dis[1<<16][maxn],st[maxn],ed[maxn],tim[maxn];
		bool vis[1<<16][maxn];
		typedef pair<int,int> pii;
		queue<pii> q;
		
		int calc(int a){
			int ret=0;
			while(a){
				a-=a&(-a);
				++ret;
			}
			return ret;
		}
		
		string read(int &a,string tmp){
			int i=0;
			while(tmp[i]<'0'||tmp[i]>'9') ++i;
			a=tmp[i]-'0';
			++i;
			while(tmp[i]>='0'&&tmp[i]<='9') a=a*10-'0'+tmp[i++];
			return tmp.substr(i,tmp.length()-i);
		}
		
		void add(int a,int b,int c){
			nxt[++tot]=head[a];
			head[a]=tot;
			list[tot]=b;
			cost[tot]=c;
			return;
		}
		
	public:
	int maxStores(int N, vector <string> interestingStores, vector <string> roads){
		n=N;
		m=interestingStores.size();
		for (int i=0;i<m;++i)
			read(tim[i],read(ed[i],read(st[i],interestingStores[i])));
		for (int i=m;i<n;++i) st[i]=ed[i]=-1,tim[i]=inf;
		for (int i=0;i<(1<<m);++i)
		for (int j=0;j<n;++j) dis[i][j]=inf;
		q.push(pii(n-1,0));
		dis[0][n-1]=0;
		int a,b,c;
		for (int i=0;i<roads.size();++i){
			read(c,read(b,read(a,roads[i])));
			add(a,b,c);
			add(b,a,c);
		}
		while(!q.empty()){
			pii nn=q.front();
			q.pop();
			int u=nn.first,sta=nn.second;
			vis[sta][u]=false;
			if (u<m&&(~sta&(1<<u))&&dis[sta][u]<=ed[u]){
				int tt=sta^(1<<u);
				if (max(dis[sta][u],st[u])+tim[u]<dis[tt][u]){
					dis[tt][u]=max(dis[sta][u],st[u])+tim[u];
					if (!vis[tt][u]){
						vis[tt][u]=true;
						q.push(pii(u,tt));
					}
				}
			}
			for (int i=head[u];i;i=nxt[i]) if (dis[sta][list[i]]>dis[sta][u]+cost[i]){
				dis[sta][list[i]]=dis[sta][u]+cost[i];
				if (!vis[sta][list[i]]){
					vis[sta][list[i]]=true;
					q.push(pii(list[i],sta));
				}
			}
		}
		int ans=0;
		for (int i=0;i<(1<<m);++i){
			int tmp=calc(i);
			if (tmp>ans) for (int j=0;j<n;++j) if (dis[i][j]<inf){
				ans=tmp;
				break;
			}
		}
		return ans;
	}
};
