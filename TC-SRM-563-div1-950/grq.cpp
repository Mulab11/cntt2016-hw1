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

const int u[4][2]={1,0,0,1,-1,0,0,-1},N=55,mod=1e9+9;
int n,m,k,num[N][N],pw[N*N];
vector<string> a;
vector<pii> pos;
vi now,last;
map<ll,int> gg;

inline bool check(){
	for(int i=0;i<k;i++)
		if(last[i]!=now[i]) return 1;
	return 0;
}
inline void ch(int &x,int y){
	x+=y;
	if(x>=mod) x-=mod;
}
class CoinsGame{
public:
	int ways(vector <string> board){
		a=board;
		n=a.size();m=a[0].size();k=0;
		memset(num,0,sizeof(num));
		pos.clear();now.clear();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(a[i][j]=='.') num[i][j]=k++,pos.pb(mp(i,j));
		for(int i=0;i<k;i++) now.pb(1);
		pw[0]=1;for(int i=1;i<=k;i++) pw[i]=pw[i-1]*2%mod;
		do{
			last=now;int cnt=0;
			gg.clear();now.clear();
			for(int i=0;i<k;i++){
				int x=pos[i].FF,y=pos[i].SS;
				ll tp=0;
				for(int j=0;j<4;j++){
					int tx=x+u[j][0],ty=y+u[j][1];
					if(tx>=0&&ty>=0&&tx<n&&ty<m){
						if(a[tx][ty]=='#') tx=x,ty=y;
						tp=tp*2005+last[num[tx][ty]];
					}
					else tp*=2005;
				}
				if(!gg[tp]) gg[tp]=++cnt;
				now.pb(gg[tp]);
			}
		}while(check());
		sort(now.begin(),now.end());
		int ans=pw[k]-1,cnt=0;
//		for(int i=0;i<k;i++) printf("%d ",now[i]);puts("");
		for(int i=0;i<k;i++)
			if(i&&now[i]!=now[i-1]) ch(ans,mod-pw[cnt]+1),cnt=1;
			else cnt++;
		ch(ans,mod-pw[cnt]+1);
		return ans;
	}
};
