// BEGIN CUT HERE

// END CUT HERE
#line 5 "CoinsGame.cpp"
#include <bits/stdc++.h>
#define ll long long
#define P 1000000009

using namespace std;
const int K=4;
const int dx[K]={1,0,-1,0};
const int dy[K]={0,1,0,-1};
struct node{int a[K],x,y;void refresh(){sort(a,a+K);}};
inline bool operator <(const node &u,const node &v){
	for (int i=0;i<K;++i) if (u.a[i]!=v.a[i]) return u.a[i]<v.a[i];
	return 0;
}
inline bool operator !=(const node &u,const node &v){
	for (int i=0;i<K;++i) if (u.a[i]!=v.a[i]) return 1;
	return 0;
}


const int maxr=42;
const int maxn=1605;


#define dec(x,y) if(((x)-=(y))<0)(x)+=P

class CoinsGame{
	int r,c;
	int label[maxn][maxn];
	node a[maxn];
	int cnt[maxn];
	int stamp,laststamp;
	public:
	int ways(vector <string> board){
		r=board.size();
		c=board[0].size();
		memset(label,0,sizeof(label));
		laststamp=0;stamp=1;
		cnt[1]=0;
		for (int i=1;i<=r;++i)for (int j=1;j<=c;++j)
			if (board[i-1][j-1]=='#') label[i][j]=-1;
			else ++cnt[1],label[i][j]=1;
		int ret=1;
		for (int i=0;i<cnt[1];++i) ret=2*ret%P;
		dec(ret,1);
		
		for (;stamp!=laststamp;){
			laststamp=stamp;
			int m=0;
			for (int i=1;i<=r;++i)
				for (int j=1;j<=c;++j)if (label[i][j]>0){
					++m;
					a[m].x=i;a[m].y=j;
					for (int k=0;k<K;++k){
						a[m].a[k]=label[i+dx[k]][j+dy[k]];
						if (a[m].a[k]<0) a[m].a[k]=label[i][j];
					}
//					a[m].refresh();
				}
			
			sort(a+1,a+m+1);
			stamp=0;
			for (int i=1;i<=m;++i){
				if (i==1||a[i]!=a[i-1]) ++stamp;
				label[a[i].x][a[i].y]=stamp;
			}
		}
		
		memset(cnt,0,sizeof(cnt));
		for (int i=1;i<=r;++i)for (int j=1;j<=c;++j)if (label[i][j]>0)
			++cnt[label[i][j]];
		
		for (int j=1;j<=stamp;++j){
			int tmp=1;
			for (int i=0;i<cnt[j];++i) tmp=2*tmp%P;
			dec(tmp,1);
			dec(ret,tmp);
		}
		
		return ret;
	}
};
