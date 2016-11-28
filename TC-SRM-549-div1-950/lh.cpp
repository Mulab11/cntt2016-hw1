#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class CosmicBlocks{
	static const int maxn=17;
	vector<int> num;
	bool mp[maxn][maxn];
	int col[maxn][maxn],cnt[maxn],hei[maxn],mx;
	int toT[maxn],fromS[maxn],n,S,T;
	int head[maxn],list[200],nxt[200],flow[200],tot;
	
	bool check1(int sta){
		memset(cnt,0,sizeof(cnt));
		mx=0;
		for (int i=0;i<n;++i){
			hei[i]=sta%n;
			col[hei[i]][cnt[hei[i]]++]=i;
			if (hei[i]>mx) mx=hei[i];
			sta/=n;
		}
		for (int i=0;i<mx;++i) if (cnt[i]==0) return false;
		return true;
	}
	
	bool check2(int sta){
		memset(mp,0,sizeof(mp));
		for (int i=0;i<n;++i){
			if (hei[i]!=0) fromS[i]=num[i];
			toT[i]=num[i];
		}
		for (int i=1;i<=mx;++i){
			for (int a=0;a<cnt[i];++a)
			for (int b=0;b<cnt[i-1];++b){
				if (sta&1){
					mp[col[i][a]][col[i-1][b]]=true;
					fromS[col[i][a]]--;
					toT[col[i-1][b]]--;
				}
				sta>>=1;
			}
		}
		for (int i=0;i<n;++i){
			if (hei[i]!=0){
				if (fromS[i]<0) return false;
				if (fromS[i]==num[i]) return false;
			}
			if (toT[i]<0) return false;
		}
		return true;
	}
	
	int id[maxn];
	int in[maxn];
	bool check3(){
		memset(in,0,sizeof(in));
		for (int i=0;i<n;++i)
		for (int j=0;j<n;++j) if (mp[i][j]) in[j]++;
		for (int i=0;i<n;++i){
			if (in[id[i]]) return false;
			for (int j=0;j<n;++j) if (mp[id[i]][j]) in[j]--;
		}
		return true;
	}
	
	void add(int a,int b,int f){
		tot++;
		nxt[tot]=head[a];
		head[a]=tot;
		list[tot]=b;
		flow[tot]=f;
		return;
	}
	
//	bool de;
	
	void adde(int a,int b,int f){
//		if (de) printf("%d->%d %d\n",a,b,f);
		add(a,b,f);
		add(b,a,0);
		return;
	}
	
	int que[maxn<<2],dis[maxn];
	bool tell(){
		int h=0,t=0;
		memset(dis,0,sizeof(dis));
		dis[S]=1;
		que[t++]=S;
		while(h<t){
			int u=que[h++];
//			if (de) printf("u=%d,dis=%d\n",u,dis[u]);
			for (int i=head[u];i;i=nxt[i]) if (flow[i]&&!dis[list[i]]){
				dis[list[i]]=dis[u]+1;
				que[t++]=list[i];
			}
		}
		return dis[T]>0;
	}
	
	int dinic(int p,int f){
		if (p==T) return f;
		int ret=0,tmp;
		for (int i=head[p];i&&f;i=nxt[i]){
//			if (de) printf("%d->%d %d\n",p,list[i],flow[i]);
			if (flow[i]&&dis[list[i]]==dis[p]+1){
				tmp=dinic(list[i],min(f,flow[i]));
				flow[i]-=tmp;
				flow[i^1]+=tmp;
				ret+=tmp;
				f-=tmp;
			}
		}
		if (f) dis[p]=-1;
		return ret;
	}
	
	public:
		int getNumOrders(vector<int> blockTypes, int minWays, int maxWays){
			num=blockTypes;
			n=num.size();
			S=n*2;
			T=S+1;
			int ans=0;
			int ss=1;
			for (int i=0;i<n;++i) ss*=n;
			for (int i=0;i<ss;++i) if (check1(i)){
//				printf("i=%d:",i);
//				for (int j=0;j<n;++j) printf(" %d",hei[j]);
//				puts("");
				int sum=0;
				for (int a=1;a<=mx;++a) sum+=cnt[a]*cnt[a-1];
				for (int sta=0;sta<(1<<sum);++sta) if (check2(sta)){
//					if (mx==2){
//						printf("sta=%d\n",sta);
//						de=true;
//					}
//					else de=false;
					memset(head,0,sizeof(head));
					tot=1;
					for (int j=0;j<n;++j){
						if (hei[j]!=0){
							adde(S,j+n,fromS[j]);
							for (int k=0;k<n;++k) if (mp[j][k]) adde(j+n,k,1000000);
						}
						adde(j,T,toT[j]);
					}
					int tmp=0;
					while(tell()) tmp+=dinic(S,1000000000);
//					if (de) printf("tmp=%d\n",tmp);
					for (int j=0;j<n;++j) if (hei[j]!=0) tmp-=fromS[j];
//					if (de) return 0;
					if (tmp<0) continue;
					int cntt=0;
					for (int j=0;j<n;++j) id[j]=j;
					do{
						if (check3()) ++cntt;
						if (cntt>maxWays) break;
					}while(next_permutation(id,id+n));
					if (cntt>=minWays&&cntt<=maxWays) ++ans;
				}
			}
			return ans;
		}
};
