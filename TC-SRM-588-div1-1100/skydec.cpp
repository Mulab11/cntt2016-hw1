#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
#include<string>
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
int n,id[N][N];
int head[N*N],np[N*N*2],p[N*N*2],tot;
inline void add(int a,int b){
	if(!a||!b)return;
	++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;
}
int A,B;
int fa[N*N],q[N*N],dep[N*N];
int sdep[N*N];
bool checkit(int S){
	//检测，以S为根，是否A的深度比B大至少2，且至少有3棵子树深度大于等于3
	memset(fa,0,sizeof fa);
	q[q[0]=1]=S;
	rep(i,1,n)dep[i]=sdep[i]=0;
	rep(i,1,q[0]){
		int x=q[i];
		for(int u=head[x];u;u=np[u])if(p[u]^fa[x]){
			fa[p[u]]=x;q[++q[0]]=p[u];
			dep[p[u]]=dep[x]+1;
			sdep[p[u]]=dep[p[u]];
		}
	}
	per(i,q[0],1){
		int x=q[i];
		sdep[fa[x]]=max(sdep[fa[x]],sdep[x]);
	}
	if(dep[A]<dep[B]+2)return 0;
	int cnt=0;
	for(int u=head[S];u;u=np[u])if(sdep[p[u]]>=3)cnt++;
	return cnt>=3;
}
class GameInDarknessDiv1{
	public:
	string check(vector <string> a){
		//把网格图转化成一棵树
		int n=a.size();
		int m=a[0].size();
		rep(i,0,n-1)rep(j,0,m-1){
			if(a[i][j]!='#'){
				id[i][j]=++::n;
			}
			if(a[i][j]=='A')A=id[i][j];
			if(a[i][j]=='B')B=id[i][j];
		}
		rep(i,0,n-1)rep(j,0,m-1){
			if(i)add(id[i][j],id[i-1][j]);
			if(j)add(id[i][j],id[i][j-1]);
			if(i+1<n)add(id[i][j],id[i+1][j]);
			if(j+1<m)add(id[i][j],id[i][j+1]);
		}
		rep(i,1,::n)if(checkit(i))return "Bob wins";
		return "Alice wins";
	}
};
int main(){
}


