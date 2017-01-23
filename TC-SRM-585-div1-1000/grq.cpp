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

const int N=55,M=300005;
struct node{int x,y;};
ll operator * (node a,node b){return (ll)a.x*b.y-(ll)a.y*b.x;}
node operator - (node a,node b){return (node){a.x-b.x,a.y-b.y};}
int n,m,f[M],g[M];
ll sum[M];
node p[N],b[M];

int check(node a,node b){
	bool x=0,y=0;
	for(int i=0;i<n;i++)
		if((a-p[i])*(b-p[i])>0) x=1; 
		else if((a-p[i])*(b-p[i])<0) y=1;
	if(!x&&!y) return 1;
	if(x&&y) return 2;
	if(x) return 0;return 3;
}
class EnclosingTriangle{
public:
	long long getNumber(int M, vector<int> x, vector<int> y){
		n=x.size();m=0;
		for(int i=0;i<n;i++) p[i]=(node){x[i],y[i]};
		for(int i=0;i<M;i++) b[m++]=(node){0,i};
		for(int i=0;i<M;i++) b[m++]=(node){i,M};
		for(int i=M;i;i--) b[m++]=(node){M,i};
		for(int i=M;i;i--) b[m++]=(node){i,0};
		for(int i=0;i<m;i++){
			f[i]=max(f[i-1],i+1);
			while(f[i]+1<m&&check(b[i],b[f[i]+1])&1) f[i]++;
			g[i]=max(g[i-1],f[i]);
			while(g[i]<m&&check(b[i],b[g[i]])>1) g[i]++;
//			if(n==1) printf("%d:%d %d\n",i,f[i],g[i]);
		}
		f[m-1]=m-1;
		sum[0]=f[0];
		for(int i=1;i<m;i++) sum[i]=sum[i-1]+f[i];
		ll ans=0;int k=0;
		for(int i=0;i<m-1;i++){
			k=max(k,i+1);
			while(k<m&&k<=f[i]&&f[k]<g[i]) k++;
			if(k>=m-1) break;
			if(f[i]==g[i]) ans--;
			ans+=sum[f[i]]-sum[k-1]-(ll)(g[i]-1)*(f[i]-k+1);
		}
		return ans;
	}
};

