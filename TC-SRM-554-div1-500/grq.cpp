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

const int mod=1234567891;
int n,C,K,N,r,g[20],si[20],sum;
int tot,known,now[10],col[20][10],num[20][20];
inline void ch(int &x,int y){x=((ll)x+(ll)y)%mod;}
inline void mu(int &x,int y){x=(ll)x*y%mod;}
struct matrix{
	int a[125][125];
	void clear(){memset(a,0,sizeof(a));}
	void e(){clear();for(int i=0;i<=N;i++) a[i][i]=1;}
}one;
matrix operator * (matrix a,matrix b){
	matrix tmp;tmp.clear();
	for(int i=0;i<=N;i++)
		for(int j=0;j<=N;j++)
			for(int k=0;k<=N;k++)
				ch(tmp.a[i][j],(ll)a.a[i][k]*b.a[k][j]%mod);
	return tmp;
}
matrix exp(matrix x,ll y){
	matrix ans;ans.e();
	while(y){
		if(y&1) ans=ans*x;
		x=x*x;y>>=1;
	}
	return ans;
}
void print(matrix one){
	for(int i=0;i<=N;i++){
		for(int j=0;j<=N;j++)
			printf("%d ",one.a[i][j]);
		puts("");
	}
}
void print(int *a){for(int i=1;i<=4;i++) printf("%d ",a[i]);puts("");}
void pre(int x,int y){
	if(x==5){
		memcpy(col[++n],now,sizeof(now));
		si[n]=0;for(int i=1;i<=4;i++) if(now[i]==now[i%4+1]) si[n]++;
		if(si[n]>K) n--;
		return;
	}
	for(int i=1;i<=y+1&&i<=C;i++)
		now[x]=i,pre(x+1,max(y,i));
}
int lab(int *tmp){
	for(int i=1;i<=n;i++){
		bool isok=0;for(int j=1;j<5;j++) if(col[i][j]!=tmp[j]) isok=1;
		if(!isok) return i;
	}
	return 0;
}
void dfs(int x,int y){
	if(x==9){
		int cnt=1,tmp[10],maxx=0;
		for(int i=known+1;i<=y;i++) mu(cnt,C-i+1);
		for(int i=5;i<=8;i++){
			int t=0;
			for(int j=5;j<i;j++) if(now[j]==now[i]) t=tmp[j-4];
			if(!t) t=++maxx;tmp[i-4]=t;
		}
		int l=lab(tmp),t=si[l];if(!l) return;
		for(int i=1;i<=4;i++) if(now[i]==now[i+4]) t++;
//		if(r==1&&K>=si[r]+t) print(now+4);
		for(int i=si[r];i+t<=K;i++) ch(one.a[num[l][i+t]][num[r][i]],cnt);
		return;
	}
	for(int i=1;i<=y+1&&i<=C;i++)
		now[x]=i,dfs(x+1,max(y,i));
}

class TheBrickTowerHardDivOne{
public:
	int find(int CC, int KK, long long H){
		C=CC;K=KK;one.clear();
		n=N=0;pre(1,0);
		for(int i=1;i<=n;i++) for(int j=0;j<=K;j++) num[i][j]=++N;
		for(int i=1;i<=n;i++){
			memcpy(now,col[i],sizeof(now));
			known=0;
			for(int j=1;j<5;j++) known=max(known,now[j]);
			r=i;
//			puts("------------------");print(now);
			dfs(5,known);
		}
		for(int i=0;i<=N;i++) one.a[0][i]=1;
		matrix ans=exp(one,H);
		int res=0;
		for(int i=1;i<=n;i++){
			int t=1,maxx=0;
			for(int j=1;j<=4;j++) maxx=max(maxx,col[i][j]);
			for(int j=1;j<=maxx;j++) mu(t,C-j+1);
			ch(res,(ll)ans.a[0][num[i][si[i]]]*t%mod);
		}
//		debug(clock());
		return res;
	}
};
