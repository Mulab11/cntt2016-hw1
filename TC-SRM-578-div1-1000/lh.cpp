#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class DeerInZooDivOne{
	static const int maxn=55;
	int f[maxn][maxn];
	int head[maxn],list[maxn<<1],nxt[maxn<<1],tot;
	bool mk[maxn];
	int dep[maxn],pr[maxn],vis[maxn],tim;
	int l[maxn],r[maxn],sl[maxn],t1,t2;
	int map[maxn][maxn];
	bool debug;
	
	void add(int a,int b){
		tot++;
		nxt[tot]=head[a];
		head[a]=tot;
		list[tot]=b;
		return; 
	}
	
	void dfs(int p,int fa,int now){
		if (p==now) return;
		mk[p]=true;
		for (int i=head[p];i;i=nxt[i]) if (list[i]!=fa) dfs(list[i],p,now);
		return;
	}
	
	void dfs1(int p,int fa){
		for (int i=head[p];i;i=nxt[i]) if (mk[list[i]]==mk[p]&&list[i]!=fa){
			dep[list[i]]=dep[p]+1;
			dfs1(list[i],p);
		}
		return;
	}
	
	bool zeng(int p){
		if (vis[p]==tim) return false;
//		printf("visit %d\n",p);
		vis[p]=tim;
		for (int i=1;i<=t2;++i){
			int tmp=l[p]+r[i]-map[p][i];
			if (tmp==0){
				if (pr[i]==0||zeng(pr[i])){
					pr[i]=p;
					return true;
				}
			}
			else sl[i]=min(sl[i],tmp);
		}
		return false;
	}
	
	int KM(){
		if (t1==0||t2==0) return 0;
//		printf("KM(%d,%d)\n",t1,t2);
		memset(r,0,sizeof(r));
		memset(pr,0,sizeof(pr));
		for (int i=1;i<=t1;++i){
			l[i]=map[i][1];
			for (int j=2;j<=t2;++j) if (map[i][j]>l[i]) l[i]=map[i][j];
		}
//		for (int i=1;i<=t1;++i,puts(""))
//		for (int j=1;j<=t2;++j) printf("%d ",map[i][j]);
		for (int i=1;i<=t1;++i){
//			printf("i=%d\n",i);
//			for (int j=1;j<=t2;++j) printf("pr[%d]=%d\n",j,pr[j]);
//			for (int j=1;j<=t1;++j) printf("l[%d]=%d, r[%d]=%d\n",j,l[j],j,r[j]);
			for (int j=1;j<=t2;++j) sl[j]=100000000;
			memset(vis,0,sizeof(vis));
			tim=0;
			for(;;){
				++tim;
				if (zeng(i)) break;
				else{
					int d=100000000;
					for (int j=1;j<=t2;++j) if(vis[pr[j]]!=tim) if (d>sl[j]) d=sl[j];
					for (int j=1;j<=t1;++j) if (vis[j]==tim) l[j]-=d;
					for (int j=1;j<=t2;++j) if (vis[pr[j]]==tim) r[j]+=d;
					else sl[j]-=d;
//					printf("d=%d\n",d);
//					for (int j=1;j<=t2;++j) printf("pr[%d]=%d\n",j,pr[j]);
//					for (int j=1;j<=t1;++j) printf("l[%d]=%d, r[%d]=%d\n",j,l[j],j,r[j]);
					if (d==0) return 0;
				}
			}
		}
		int ret=0;
		for (int i=1;i<=t1;++i) ret+=l[i];
		for (int i=1;i<=t2;++i) ret+=r[i];
		return ret;
	}
	
	void ask(int u,int v){
//		if (debug) printf("ask(%d,%d)\n",u,v);
		for (int i=head[u];i;i=nxt[i]) if (dep[list[i]]>dep[u]&&mk[list[i]]){
			for (int j=head[v];j;j=nxt[j]) if (dep[list[j]]>dep[v]&&!mk[list[j]]){
				ask(list[i],list[j]);
			}
		}
		t1=t2=0;
		for (int i=head[u];i;i=nxt[i]) if (dep[list[i]]>dep[u]&&mk[list[i]])
			l[++t1]=list[i];
		for (int j=head[v];j;j=nxt[j]) if (dep[list[j]]>dep[v]&&!mk[list[j]])
			r[++t2]=list[j];
		if (t1>t2){
			for (int i=1;i<=t1;++i) swap(l[i],r[i]);
			swap(t1,t2);
		}
		for (int i=1;i<=t1;++i)
		for (int j=1;j<=t2;++j) map[i][j]=f[l[i]][r[j]];
		f[u][v]=f[v][u]=KM()+1;
		return;
	}
	
	public:
		int getmax(vector<int> a, vector<int> b){
//			t1=t2=3;
//			for (int i=1;i<=t1;++i){
//				for (int j=1;j<=3;++j) map[i][j]=4-j;
//			}
//			
//			return KM();
			int n=a.size()+1;
			for (int i=0;i<n-1;++i) add(a[i],b[i]),add(b[i],a[i]);
			int ans=1;
			for (int i=1;i<n;++i){
				memset(mk,0,sizeof(mk));
				dfs(0,-1,i);
				for (int j=0;j<n;++j) if (mk[j]){
					memset(f,0,sizeof(f));
					dep[j]=dep[i]=1;
					dfs1(j,-1);
					dfs1(i,-1);
					if (j==4&&i==15) debug=true;
					else debug=false;
//					printf("check(%d,%d)\n",j,i);
					ask(j,i);
					ans=max(ans,f[j][i]);
				}
			}
			return ans;
		}
};
