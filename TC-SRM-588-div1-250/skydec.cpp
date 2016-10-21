#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)((x).size()))
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
const int N=55;
int f[N][N];//f[i][j]表示上一首歌是第i首，一共唱了j首歌所需要的最短时间
pii a[N];int n,T;
int Main(){
	sort(a+1,a+1+n);
	//根据题目的性质，显然按照tone[i]的大小升序或者降序最优
	memset(f,63,sizeof f);
	rep(i,1,n){
		f[i][1]=a[i].se;
		rep(j,1,i)rep(k,1,i-1){
			f[i][j]=min(f[i][j],f[k][j-1]+a[i].se+abs(a[i].fi-a[k].fi));
			//直接暴力枚举前一首歌是什么，转移一下即可。
		}
	}
	int ans=0;
	rep(i,1,n)rep(j,1,n)if(f[i][j]<=T)ans=max(ans,j);
	//统计答案
	return ans;
}
class GUMIAndSongsDiv1{
	public:
	int maxSongs(vector<int> duration,vector<int> tone, int T){
		::T=T;n=tone.size();
		rep(i,1,n)a[i]=pii(tone[i-1],duration[i-1]);
		//预处理，pair以tone[i]为第一关键字
		return Main();
	}
};
int main(){
}




