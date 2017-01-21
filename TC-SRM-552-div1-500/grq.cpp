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
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;

const int N=35,M=16005,inf=1e8;
int a[N][N],b[N][N],ans;
int k,n,m,now[M];

inline int geta(int p,int q,int x,int y){return a[x][y]-a[p-1][y]-a[x][q-1]+a[p-1][q-1];}
inline int getb(int p,int q,int x,int y){return b[x][y]-b[p-1][y]-b[x][q-1]+b[p-1][q-1];}
inline void change(int l,int r,int x,int k,int b){
	now[k]=max(now[k],b);
	if(l==r) return ;
	int mid=l+r>>1;
	if(x<=mid) change(l,mid,x,ls,b); else change(mid+1,r,x,rs,b);
}
inline int get(int l,int r,int x,int y,int k){
	if(l==x&&y==r) return now[k];
	int mid=l+r>>1,ans=-inf;
	if(x<=mid) ans=max(ans,get(l,mid,x,min(y,mid),ls));
	if(y>mid) ans=max(ans,get(mid+1,r,max(mid+1,x),y,rs));
	return ans;
}
inline void solve(int n,int m){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1],b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
	for(int i=1;i<=M-5;i++) now[i]=-inf;
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			for(int l=1;l<=i;l++)
				for(int r=1;r<=j;r++){
					int x=geta(l,r,i,j),y=getb(l,r,i,j);
					change(-900,900,y-x,1,x+y);
				}
		}
		for(int j=1;j<=m;j++){
			for(int l=i+1;l<=n;l++)
				for(int r=j;r<=m;r++){
					int x=geta(i+1,j,l,r),y=getb(i+1,j,l,r);
					ans=max(ans,x+y+get(-900,900,max(x-y-k,-900),min(x-y+k,900),1));
//					if(n==3||m==3) printf("%d %d %d %d: %d %d\n",i+1,j,l,r,x+y,get(-900,900,x-y-k,x-y+k,1));
				}
		}
	}
}

class FoxAndFlowerShopDivOne{
public:
	int theMaxFlowers(vector <string> flowers, int maxDiff){
		int c=clock();
		k=maxDiff;ans=-inf;
		n=flowers.size();m=flowers[0].size();
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(flowers[i][j]=='L') a[i+1][j+1]=1;
				else if(flowers[i][j]=='P') b[i+1][j+1]=1;
		solve(n,m);
		
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				if(flowers[j][i]=='L') a[i+1][j+1]=1;
				else if(flowers[j][i]=='P') b[i+1][j+1]=1;
		solve(m,n);
		cerr<<clock()-c<<endl;
		return max(-1,ans);
	}
};
