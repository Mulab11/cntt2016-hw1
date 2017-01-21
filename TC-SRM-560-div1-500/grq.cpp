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

const int N=305,b=300;
bool vis[N][N];
int dep[N][N],step[N][N];
int next[N],u[3][2]={1,0,0,1,1,1};

struct node{
	int x,y;
}p[b*b+5],g[b*b+5];

int bfs(vi x,vi y,int k){
	memset(step,-1,sizeof(step));
	int n=x.size(),now=n;
	for(int i=1;i<=n;i++) p[i]=(node){x[i-1],y[i-1]};
	for(int i=1;i<=n;i++) step[p[i].x][p[i].y]=0;
	for(int stp=1;stp<=k;stp++){
		int tot=0;
		for(int i=1;i<=now;i++)
			for(int j=0;j<3;j++){
				int tx=p[i].x+u[j][0],ty=p[i].y+u[j][1];
				if(tx>b||ty>b) continue;
				if(~step[tx][ty]) continue;
				step[tx][ty]=stp;g[++tot]=(node){tx,ty};
			}
		now=tot;for(int i=1;i<=tot;i++) p[i]=g[i];
	}
}

class DrawingPointsDivOne{
public:
	int maxSteps(vector <int> x, vector <int> y){
		int n=x.size(),ans=1e9;
		
		for(int i=0;i<n;i++) x[i]+=75,y[i]+=75;
		bfs(x,y,b);
		memcpy(dep,step,sizeof(dep));
		
		int l=0,r=150;
		while(l<r){
			int mid=l+r+1>>1;
			vi x,y;x.clear();y.clear();
			for(int i=0;i<=b;i++)
				for(int j=0;j<=b;j++)
					if(dep[i][j]<0||dep[i][j]>mid) x.pb(b-i),y.pb(b-j);
			bfs(x,y,mid);
			int si=0;
			for(int i=0;i<=b;i++)
				for(int j=0;j<=b;j++)
					if(step[i][j]==-1) si++;
			if(si==n) l=mid; else r=mid-1;
		}
		if(r==150) return -1;
		return r;
	}
};
