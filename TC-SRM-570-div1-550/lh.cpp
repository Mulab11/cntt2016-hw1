#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fir first
#define sec second
using namespace std;

class CentaurCompany{
	typedef pair<int,int> pii;
	static const int maxn=40;
	long long dp[maxn][2][maxn][maxn],fz[maxn][maxn];
	int head[maxn],list[maxn<<1],nxt[maxn<<1],tot;
	int tim[maxn][maxn],n;
	queue<pii> q;
	vector<pii> rec[maxn][2];
	
	int calc(int a,int b){
		return max(0,2*b-2-a);
	}
	
	void add(int a,int b){
		++tot;
		nxt[tot]=head[a];
		head[a]=tot;
		list[tot]=b;
		return;
	}
	
	void dfs(int p,int fa){
//		printf("p=%d\n",p);
		for (int i=head[p];i;i=nxt[i]) if (list[i]!=fa) dfs(list[i],p);
		dp[p][0][1][1]=1;
		q.push(pii(1,1));
		memset(tim,0,sizeof(tim));
		int v;
		for (int j=head[p];j;j=nxt[j]) if ((v=list[j])!=fa){
//			printf("work %d:\n",v);
			memset(fz,0,sizeof(fz));
			int sz=q.size();
			while(sz--){
				int a=q.front().fir,b=q.front().sec;
				q.pop();
				for (auto &x:rec[v][0]){
//					printf("0: (%d, %d) + (%d, %d)\n",a,b,x.fir,x.sec);
					fz[a+x.fir][b+x.sec-1]+=dp[p][0][a][b]*dp[v][0][x.fir][x.sec];
					if (tim[a+x.fir][b+x.sec-1]!=v){
						tim[a+x.fir][b+x.sec-1]=v;
						q.push(pii(a+x.fir,b+x.sec-1));
					}
				}
				for (auto &x:rec[v][1]){
					fz[a+x.fir][b+x.sec]+=dp[p][0][a][b]*dp[v][1][x.fir][x.sec];
					if (tim[a+x.fir][b+x.sec]!=v){
						tim[a+x.fir][b+x.sec]=v;
						q.push(pii(a+x.fir,b+x.sec));
					}
				}
			}
			memcpy(dp[p][0],fz,sizeof(fz));
		}
		while(!q.empty()){
			rec[p][0].push_back(q.front());
			q.pop();
		}
		
		
		dp[p][1][0][0]=1;
		q.push(pii(0,0));
		memset(tim,0,sizeof(tim));
		
		for (int j=head[p];j;j=nxt[j]) if ((v=list[j])!=fa){
			memset(fz,0,sizeof(fz));
			int sz=q.size();
			while(sz--){
				int a=q.front().fir,b=q.front().sec;
				q.pop();
				for (auto &x:rec[v][0]){
					fz[a+x.fir][b+x.sec]+=dp[p][1][a][b]*dp[v][0][x.fir][x.sec];
					if (tim[a+x.fir][b+x.sec]!=v){
						tim[a+x.fir][b+x.sec]=v;
						q.push(pii(a+x.fir,b+x.sec));
					}
				}
				for (auto &x:rec[v][1]){
					fz[a+x.fir][b+x.sec]+=dp[p][1][a][b]*dp[v][1][x.fir][x.sec];
					if (tim[a+x.fir][b+x.sec]!=v){
						tim[a+x.fir][b+x.sec]=v;
						q.push(pii(a+x.fir,b+x.sec));
					}
				}
			}
			memcpy(dp[p][1],fz,sizeof(fz));
		}
		while(!q.empty()){
			rec[p][1].push_back(q.front());
			q.pop();
		}
//		printf("return from %d\n",p);
		return;
	}
	
	public:
		double getvalue(vector<int> a, vector<int> b){
			int m=a.size();
			n=m+1;
			for (int i=0;i<m;++i){
				add(a[i],b[i]);
				add(b[i],a[i]);
			}
			dfs(1,0);
			long long ans=0;
			long long bas=1LL<<n;
//			printf("0:\n");
			for (auto &x:rec[1][0]){
				ans+=(calc(x.fir,x.sec))*dp[1][0][x.fir][x.sec];
//				printf("(%d,%d): %lld %d\n",x.fir,x.sec,dp[1][0][x.fir][x.sec],calc(x.fir,x.sec));
			}
//			puts("1:");
			for (auto &x:rec[1][1]){
				ans+=(calc(x.fir,x.sec))*dp[1][1][x.fir][x.sec];
//				printf("(%d,%d): %lld %d\n",x.fir,x.sec,dp[1][1][x.fir][x.sec],calc(x.fir,x.sec));
			}
			return (double)ans*2/bas;
		}
};
