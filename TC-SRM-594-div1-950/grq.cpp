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
#define upt(step) {ans=min(ans,step);return;}
using namespace std;

int w,ans;
char vis[3005][3005];
inline bool check(int n,int x,int y){
	return (x-1)*w+y<=n;
}
void dfs(int pre,int next,int step){
	if(vis[pre][next]&(1<<step)) return;
//	if(!next) printf("%d %d %d\n",pre,next,step);
	vis[pre][next]|=1<<step;
	if(!pre&&!next) upt(step);
	if(!pre&&(w==1||next+1<=w)) upt(step+1);
	if(!next&&(pre<w||w==1||pre%w==0)) upt(step+1);
	if(pre==w-1&&next<w) upt(step+1);
	if(step==2) return;
	int n=pre+next+1,row=(n-1)/w+1,r=pre/w+1;
	for(int i=1;i<r;i++)
		for(int j=1;j<=w;j++)
			dfs(pre-i*j,next,step+1);
	dfs(pre,w-pre%w-1,step+1);
	int sum=0;
	for(int i=1;i<=pre%w;i++){
		sum+=check(n,row,i);
		sum+=row-r-1;
		for(int j=0;j<=r;j++)
			dfs(pre-i*j,next-sum,step+1);
	}
	sum=0;
	for(int i=pre%w+2;i<=w;i++){
		sum+=check(n,row,i);
		sum+=row-r;
		for(int j=0;j<r;j++)
			dfs(pre-(i-pre%w-1)*j,next-sum,step+1);
	}
}

class FoxAndAvatar{
public:
	int minimalSteps(int n, int width, int x){
		memset(vis,0,sizeof(vis));
		w=width;ans=4;
		dfs(x-1,n-x,0);
		return ans;
	}
};
