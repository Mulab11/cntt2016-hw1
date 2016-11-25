#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace Solve{
	const int maxn=55,mod=1000000007;
	int n,m;
	bool canuse[1<<16];
	int rel[maxn][2],use[maxn],top;
	int leg[17][1<<16],cnt[17];
	vector<int> sub[1<<16];
	int dp[maxn][1<<16];
	int size[maxn],head[maxn],list[maxn],nxt[maxn],tot;
	
	struct point{
		int id;
		int nxt[26];
	}nod[10000];
	int ccnt=1,root=1;
	
	int cont(int a){
		int ret=0;
		while(a){
			++ret;
			a^=a&(-a);
		}
		return ret;
	}
	
	bool check(const int sta){
		for (int i=0;i<m;++i) if (rel[i][0]!=rel[i][1]){
			if (sta&(1<<rel[i][0])) if (~sta&(1<<rel[i][1])) return false;
		}
		return true;
	}
	
	void add(int a,int b){
//		printf("%d->%d\n",a,b);
		tot++;
		nxt[tot]=head[a];
		head[a]=tot;
		list[tot]=b;
		return;
	}
	
	void insert(string &s,int id){
		int p=root;
		for (auto &i:s){
			int x=i-'a';
			if (!nod[p].nxt[x]) nod[p].nxt[x]=++ccnt;
			p=nod[p].nxt[x];
		}
		nod[p].id=id;
	}
	
	void dfs(int p,int fa){
		if (nod[p].id){
			add(fa,nod[p].id);
			for (int i=0;i<26;++i) if (nod[p].nxt[i]) dfs(nod[p].nxt[i],nod[p].id);
		}
		else for (int i=0;i<26;++i) if (nod[p].nxt[i]) dfs(nod[p].nxt[i],fa);
		return;
	}
	
	void solve(int p){
		size[p]=0;
		dp[p][0]=1;
		for (int i=head[p];i;i=nxt[i])
			solve(list[i]);
		
		for (int i=head[p];i;i=nxt[i]){
			size[p]+=size[list[i]];
			int tmp=min(size[p],top);
			for (int j=cnt[tmp]-1;j>=0;--j){
				int sta=leg[tmp][j];
				for (auto &k:sub[sta]){
					(dp[p][sta]+=(long long)dp[p][k]*dp[list[i]][sta^k]%mod)%=mod;
//					printf("dp[%d][%d]=%d, dp[%d][%d]=%d  %d:%d\n",p,k,dp[p][k],list[i],sta^k,dp[list[i]][sta^k],sta,dp[p][sta]);
				}
				dp[p][0]=1;
			}
		}
//		if (p==0) for (int j=cnt[top]-1;j>=0;--j){
//			int sta=leg[top][j];
//			printf("dp[%d][%d]=%d\n",p,sta,dp[p][sta]);
//		}
		if (p==0) return;
		++size[p];
		int tmp=min(size[p],top);
		for (int j=cnt[tmp]-1;j>=0;--j){
			int sta=leg[tmp][j];
			for (int t=0;t<top;++t) if (sta&(1<<t)){
				(dp[p][sta]+=dp[p][sta^(1<<t)])%=mod;
			}
//			printf("dp[%d][%d]=%d\n",p,sta,dp[p][sta]);
		}
		return;
	}
	long long frac(int a){
		long long ret=1;
		for (int i=2;i<=a;++i) ret=(ret*i)%mod;
		return ret;
	}
}

class SimilarNames{
	public:
		int count(vector<string> names, vector<int> info1, vector<int> info2){
			using namespace Solve;
			n=names.size();
			m=info1.size();
			for (int i=0;i<m;++i) use[top++]=info1[i],use[top++]=info2[i];
			sort(use,use+top);
			top=unique(use,use+top)-use;
			for (int i=0;i<m;++i){
				rel[i][0]=lower_bound(use,use+top,info1[i])-use;
				rel[i][1]=lower_bound(use,use+top,info2[i])-use;
			}
//			printf("xx %d\n",check(2)?1:0);
			for (int i=0;i<(1<<top);++i) if ((canuse[i]=check(i))){
				int j=cont(i);
//				printf("%d,%d:\n",i,j);
				for (int k=j;k<=top;++k){
//					printf("%d:",k);
					leg[k][cnt[k]++]=i;
//					for (int t=0;t<cnt[k];++t) printf(" %d",leg[k][t]);
//					puts("");
				}
				for (j=(i-1)&i;;j=(j-1)&i){
					if (canuse[j]&&canuse[i^j]) sub[i].push_back(j);
					if (!j) break;
				}
			}
			for (int i=0;i<n;++i) insert(names[i],i+1);
			dfs(root,0);
			solve(0);
			return dp[0][(1<<top)-1]*frac(n-top)%mod;
		}
};
