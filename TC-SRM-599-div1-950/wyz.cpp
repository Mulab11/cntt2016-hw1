// BEGIN CUT HERE

// END CUT HERE
#line 5 "SimilarNames.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int P=1000000007;
const int maxn=62;
const int maxt=10;

#define lowbit(u) ((u)&-(u))

inline bool cmp(const string &u,const string &v){
	return u.length()<v.length();
}

inline int count_1(int j){
	int ret=0;
	for (;j;j-=lowbit(j)) ++ret;
	return ret;
}

class SimilarNames{
	int bin[maxt+1],fact[maxn],c[maxn][maxn];
	int cnt_info;
	int a[maxt],b[maxt];
	int n,t,stamp;
	int fa[maxn];
	int reach[1<<maxt^1];
	int sum[1<<maxt^1],ulk[1<<maxt^1][maxt];
	
	bool avl[1<<maxt^1];
	vector<int> mask;
	int cnt_mask;
	vector<int> edg[1<<maxt^1];
	
	void precompute(){
		for (int i=0;i<=8;++i) bin[i]=1<<i;
		for (int i=fact[0]=1;i<=n;++i) fact[i]=(ll)fact[i-1]*i%P;
		for (int i=0;i<=n;++i){
			c[i][0]=1;
			for (int j=1;j<=i;++j) c[i][j]=(c[i-1][j]+c[i-1][j-1])%P;
		}
		
		for (int i=0;i<bin[t];++i){
			avl[i]=1;
			for (int j=0;j<cnt_info;++j)
				if ((i&bin[a[j]])&&b[j]<t&&(i&bin[b[j]])==0){
					avl[i]=0;
					break;
				}
			if (avl[i]) mask.push_back(i);
		}
		cnt_mask=mask.size();

		memset(reach,0,sizeof(reach));
		for (int i=0;i<cnt_info;++i)
			if (b[i]>=t) reach[bin[a[i]]]|=bin[b[i]-t];
		
		for (int i=0;i<bin[t];++i)if (avl[i]){
			for (int j=0;j<t;++j)if (i&bin[j])
				reach[i]|=reach[bin[j]];
			sum[i]=count_1(i)+count_1(reach[i]);
			
			for (int j=0;j<t;++j){
				int now=0;
				for (int k=0;k<t;++k)
					if (k!=j&&(i&bin[k])) now|=reach[bin[k]];
				ulk[i][j]=count_1((reach[bin[j]]&now)^reach[bin[j]]);
			}
		}

		for (int i=0;i<cnt_mask;++i)
			for (int j=i+1;j<cnt_mask;++j)
				if ((mask[i]&mask[j])==0&&(reach[mask[i]]&reach[mask[j]])==0){
					edg[mask[i]].push_back(mask[j]);
					edg[mask[j]].push_back(mask[i]);
				}
		edg[0].push_back(0);
	}

	int dp[maxn][1<<maxt^1];
	int f[1<<maxt^1];
	int size[maxn];
	
	void doit(){
		#define to (j|bin[k])
		#define tmp (ulk[j|bin[k]][k])
		memset(dp,0,sizeof(dp));
		for (int i=0;i<=n;++i){
			dp[i][0]=1;
			if (fa[i]<0) fa[i]=n;
		}
		memset(size,0,sizeof(size));
		for (int u=n-1;u>=0;--u) size[fa[u]]+=(++size[u]);
		for (int u=n-1;u>=0;--u){
			for (int i=mask.size()-1;i>=0;--i){
				int j=mask[i];
				if (dp[u][j]==0) continue;
				for (int k=0;k<t;++k)if (to!=j&&avl[to])
					(dp[u][to]+=(ll)dp[u][j]*c[size[u]-sum[to]+tmp][tmp]%P*fact[tmp]%P)%=P;
			}
			memset(f,0,sizeof(f));
			for (int i=mask.size()-1;i>=0;--i){
				int j=mask[i];
				if (dp[u][j]==0) continue;
				for (int k=0;k<edg[j].size();++k)
					(f[j^edg[j][k]]+=(ll)dp[u][j]*dp[fa[u]][edg[j][k]]%P)%=P;
			}
			memcpy(dp[fa[u]],f,sizeof(f));
		}
	}

	
	int id[maxn];
	bool vis[maxt*2];
	public:
	int count(vector <string> names, vector <int> info1, vector <int> info2){
		n=names.size();
		cnt_info=info1.size();
//		printf("%d\n",cnt_info);
		stamp=0;
		memset(id,-1,sizeof(id));
		for (int i=0;i<cnt_info;++i){
			if (id[info1[i]]==-1) id[info1[i]]=stamp++;
			a[i]=id[info1[i]];
//			printf("%d\n",a[i]);
		}
		t=stamp;
		for (int i=0;i<cnt_info;++i){
			if (id[info2[i]]==-1) id[info2[i]]=stamp++;
			b[i]=id[info2[i]];
//			printf("%d\n",b[i]);
		}

		for (int i=0;i<t;++i){
			memset(vis,0,sizeof(vis));
			vis[i]=1;
			for (int kk=0;kk<cnt_info;++kk)
				for (int j=0;j<cnt_info;++j)if (vis[b[j]]){
					if (a[j]==i) return 0;
					vis[a[j]]=1;
				}
		}

		sort(names.begin(),names.end(),cmp);
		memset(fa,-1,sizeof(fa));
		for (int i=0;i<n;++i)
			for (int j=i-1;j>=0;--j){
				bool found=0;
				for (int k=0;k<names[j].length()&&!found;++k)
					if (names[i][k]!=names[j][k]) found=1;
				if (!found){fa[i]=j;break;}
			}
		
		precompute();

		doit();

		return (ll)dp[n][bin[t]-1]*fact[n-stamp]%P;
	}

	void debug(){
		for (int u=n-1;u>=0;--u){
			printf("%d's father is %d\n",u,fa[u]);
		}
		for (int i=0;i<mask.size();++i)printf("%d\n",mask[i]);
		printf("%d\n",dp[5][2]);
		printf("%d\n",dp[1][8]);
		printf("%d\n",sum[2]);
		printf("%d\n",lowbit(reach[2])+count_1(2));
//		for (int i=0;i<t;++i)printf("%d\n",code[i]);
	}
};

//this is for test
/*
int main(){
	SimilarNames test;
	vector<string> a;
	a.push_back("aya");
	a.push_back("saku");
	a.push_back("emi");
	a.push_back("ayane");
	a.push_back("sakura");
	a.push_back("emika");
	a.push_back("sakurako");

	vector<int> b,c;
	b.push_back(0);b.push_back(1);b.push_back(3);b.push_back(5);
	c.push_back(1);c.push_back(2);c.push_back(4);c.push_back(6);

//test.count(a,b,c);
	printf("%d\n",test.count(a,b,c));
	test.debug();
//	test.run_test(-1);
	return 0;
}
*/
//test end
