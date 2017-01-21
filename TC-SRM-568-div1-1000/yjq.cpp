#include <bits/stdc++.h>

using namespace std ;

#define N 55
int T,n,m,i;bool ans;

vector<int> a ; 

namespace SMALL{
		int cnt[N],l[N],r[N],col[N];bool g[N][N];
		inline bool cross(int x,int y){
				if(l[x]<l[y]&&l[y]<r[x]&&r[x]<r[y])return 1;
				if(l[y]<l[x]&&l[x]<r[y]&&r[y]<r[x])return 1;
				return 0;
		}
		bool dfs2(int x,int y){
				if(~col[x])return col[x]==y;
				col[x]=y;
				for(int i=0;i<m;i++)if(g[x][i])if(!dfs2(i,3-y))return 0;
				return 1;
		}
		inline void check(){
				int i,j;
				for(i=0;i<m;i++)l[i]=r[i]=-1;
				for(i=0;i<n;i++)if(~l[a[i]])r[a[i]]=i;else l[a[i]]=i;
				for(i=0;i<m;i++)for(j=0;j<m;j++)g[i][j]=0;
				for(i=0;i<m;i++)for(j=i+1;j<m;j++)if(cross(i,j))g[i][j]=g[j][i]=1;
				for(i=0;i<m;i++)col[i]=-1;
				for(i=0;i<m;i++)if(col[i]<0)if(!dfs2(i,1))return;
				ans=1;
		}
		void dfs(int x){
				if(ans)return;
				if(x==n){
						check();
						return;
				}
				if(~a[x])dfs(x+1);
				else{
						for(int i=0;i<m;i++)if(cnt[i]==2){
								a[x]=i,cnt[i]--;
								dfs(x+1);
								a[x]=-1,cnt[i]++;
								break;
						}
						for(int i=0;i<m;i++)if(cnt[i]==1){
								a[x]=i,cnt[i]--;
								dfs(x+1);
								a[x]=-1,cnt[i]++;
						}
				}
		}
		inline bool solve(){
				for(i=0;i<m;i++)cnt[i]=2;
				for(i=0;i<n;i++)if(~a[i])cnt[a[i]]--;
				ans=0;
				dfs(0);
				return ans;
		}
}
namespace BIG{
		int cnt,l[N],r[N],d[N],f[N],s[N],ed,g[N],v[N*N],w[N*N],nxt[N*N],col[N];
		inline void add(int x,int y,int z){
				v[++ed]=y;w[ed]=z;nxt[ed]=g[x];g[x]=ed;
				v[++ed]=x;w[ed]=z;nxt[ed]=g[y];g[y]=ed;
		}
		inline bool cross(int x,int y){
				if(l[x]<l[y]&&l[y]<r[x]&&r[x]<r[y])return 1;
				if(l[y]<l[x]&&l[x]<r[y]&&r[y]<r[x])return 1;
				return 0;
		}
		bool dfs2(int x,int y){
				if(~col[x])return col[x]==y;
				col[x]=y;
				for(int i=g[x];i;i=nxt[i])if(!dfs2(v[i],y^w[i]))return 0;
				return 1;
		}
		inline void check(){
				int i;
				for(ed=i=0;i<=n;i++)g[i]=0,col[i]=-1;
				add(0,n,0);
				for(i=0;i<cnt;i++){
						add(l[i]-1,l[i],0);
						add(r[i]-1,r[i],0);
						add(l[i]-1,r[i],d[i]?s[r[i]]^s[l[i]-1]:0);
				}
				for(i=0;i<=n;i++)if(col[i]<0)if(!dfs2(i,0))return;
				ans=1;
		}
		void dfs(int x,int A,int B){
				if(ans)return;
				if(x==cnt){
						check();
						return;
				}
				if(!(f[x]&A))d[x]=0,dfs(x+1,A|(1<<x),B);
				if(!(f[x]&B))d[x]=1,dfs(x+1,A,B|(1<<x));
		}
		inline bool solve(){
				int i,j;
				for(i=1;i<=n;i++)s[i]=s[i-1]^(a[i-1]==-1);
				for(i=0;i<m;i++)l[i]=r[i]=-1;
				for(i=0;i<n;i++)if(~a[i]){if(~l[a[i]])r[a[i]]=i;else l[a[i]]=i;}
				for(cnt=i=0;i<m;i++)if(~l[i]){
						l[cnt]=l[i]+1,r[cnt]=r[i]+1;
						cnt++;
				}
				if(!cnt)return 1;
				for(i=0;i<cnt;i++)f[i]=0;
				for(i=0;i<cnt;i++)for(j=0;j<cnt;j++)if(i!=j&&cross(i,j))f[i]|=1<<j;
				ans=0;
				dfs(0,0,0);
				return ans;
		}
}

class DisjointSemicircles {
	public:
		string getPossibility(vector<int> labels) {
				a = labels ; 
				n = labels.size() ; 
				m = n / 2 ; 
				int t = 0 ;
				for (i = 0; i < n; i ++) if (a[i] < 0) t ++ ; 
				bool ans = (t <= 12 ? SMALL :: solve() : BIG :: solve()) ; 
				return ans ? "POSSIBLE" : "IMPOSSIBLE" ;
		}

} ;

