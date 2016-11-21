#include<cstdio>
#include<queue>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct rec{
	int x1,y1,x2,y2;
	rec(int a=-1,int b=-1,int c=-1,int d=-1):x1(a),y1(b),x2(c),y2(d){};
};

class CoinsGame{
	static const int maxn=43,maxm=maxn*maxn*maxn*maxn,mod=1000000009;
	int n,m;
	bool mp[maxn][maxn];
	bool can[maxn*maxn][maxn*maxn];
	int head[maxn*maxn],list[maxm],nxt[maxm],d[maxn*maxn],tot;
	queue<rec> q;
	
	int num(int a,int b){
		return a*m+b;
	}
	
	bool check(int a,int b,int c,int d){
		if ((!mp[a][b])||(!mp[c][d])) return false;
		if ((a==0)^(c==0)) return true;
		if ((a==n-1)^(c==n-1)) return true;
		if ((b==0)^(d==0)) return true;
		if ((b==m-1)^(d==m-1)) return true;
		return false;
	}
	
	void insert(int a,int b,int c,int d){
		if (a==c&&b==d) return;
		if (a<0||a>=n||c<0||c>=n) return;
		if (b<0||b>=m||d<0||d>=m) return;
		if (mp[a][b]==false||mp[c][d]==false) return;
		if (!can[num(a,b)][num(c,d)]){
			can[num(a,b)][num(c,d)]=true;
			q.push(rec(a,b,c,d));
		}
		return;
	}
	
	bool ff(int a,int b){
		if (a<0||a>=n||b<0||b>=m) return false;
		return mp[a][b]==false;
	}
	
	void extend1(rec u){
		if (ff(u.x1-1,u.y1)){
			if (ff(u.x2-1,u.y2)){
				insert(u.x1+1,u.y1,u.x2+1,u.y2);
				insert(u.x1,u.y1,u.x2+1,u.y2);
				insert(u.x1+1,u.y1,u.x2,u.y2);
			}
			else{
				insert(u.x1+1,u.y1,u.x2+1,u.y2);
				insert(u.x1,u.y1,u.x2+1,u.y2);
			}
		}
		else{
			if (ff(u.x2-1,u.y2)){
				insert(u.x1+1,u.y1,u.x2+1,u.y2);
				insert(u.x1+1,u.y1,u.x2,u.y2);
			}
			else insert(u.x1+1,u.y1,u.x2+1,u.y2);
		}
		return;
	}
	
	void extend2(rec u){
		if (ff(u.x1+1,u.y1)){
			if (ff(u.x2+1,u.y2)){
				insert(u.x1-1,u.y1,u.x2-1,u.y2);
				insert(u.x1,u.y1,u.x2-1,u.y2);
				insert(u.x1-1,u.y1,u.x2,u.y2);
			}
			else{
				insert(u.x1-1,u.y1,u.x2-1,u.y2);
				insert(u.x1,u.y1,u.x2-1,u.y2);
			}
		}
		else{
			if (ff(u.x2+1,u.y2)){
				insert(u.x1-1,u.y1,u.x2-1,u.y2);
				insert(u.x1-1,u.y1,u.x2,u.y2);
			}
			else insert(u.x1-1,u.y1,u.x2-1,u.y2);
		}
		return;
	}
	
	void extend3(rec u){
		if (ff(u.x1,u.y1-1)){
			if (ff(u.x2,u.y2-1)){
				insert(u.x1,u.y1+1,u.x2,u.y2+1);
				insert(u.x1,u.y1,u.x2,u.y2+1);
				insert(u.x1,u.y1+1,u.x2,u.y2);
			}
			else{
				insert(u.x1,u.y1+1,u.x2,u.y2+1);
				insert(u.x1,u.y1,u.x2,u.y2+1);
			}
		}
		else{
			if (ff(u.x2,u.y2-1)){
				insert(u.x1,u.y1+1,u.x2,u.y2+1);
				insert(u.x1,u.y1+1,u.x2,u.y2);
			}
			else insert(u.x1,u.y1+1,u.x2,u.y2+1);
		}
		return;
	}
	
	void extend4(rec u){
		if (ff(u.x1,u.y1+1)){
			if (ff(u.x2,u.y2+1)){
				insert(u.x1,u.y1-1,u.x2,u.y2-1);
				insert(u.x1,u.y1,u.x2,u.y2-1);
				insert(u.x1,u.y1-1,u.x2,u.y2);
			}
			else{
				insert(u.x1,u.y1-1,u.x2,u.y2-1);
				insert(u.x1,u.y1,u.x2,u.y2-1);
			}
		}
		else{
			if (ff(u.x2,u.y2+1)){
				insert(u.x1,u.y1-1,u.x2,u.y2-1);
				insert(u.x1,u.y1-1,u.x2,u.y2);
			}
			else insert(u.x1,u.y1-1,u.x2,u.y2-1);
		}
		return;
	}
	
	long long power(long long a,int b){
		long long ret=1;
		while(b){
			if (b&1) ret=ret*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return ret;
	}
	
	int C[2000][2000];
	
	public:
		int ways(vector<string> board){
			n=board.size();
			m=board[0].length();
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j) mp[i][j]=(board[i][j]=='.');
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j)
			for (int x=0;x<n;++x)
			for (int y=0;y<m;++y) if (x!=i||y!=j){
				if (check(i,j,x,y)){
					can[num(i,j)][num(x,y)]=true;
					q.push(rec(i,j,x,y));
				}
			}
			while(!q.empty()){
				rec u=q.front();
				q.pop();
				extend1(u);
				extend2(u);
				extend3(u);
				extend4(u);
			}
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j) if (mp[i][j])
			for (int x=0;x<n;++x)
			for (int y=0;y<m;++y) if (mp[x][y]) if (i!=x||j!=y)
			if (can[num(i,j)][num(x,y)]) d[num(i,j)]++;
			long long ans=0;
			C[0][0]=1;
			for (int i=1;i<=1600;++i){
				C[i][0]=1;
				for (int j=1;j<=i;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
			}
			int cnt=0;
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j) if (mp[i][j]) ++cnt;
			for (int i=2;i<=cnt;++i){
				long long tmp=0;
//				printf("i=%d\n",i);
				for (int j=0;j<n*m;++j){
					tmp+=C[cnt-1][i-1];
					if (cnt-1-d[j]>=0) tmp=(tmp-C[cnt-1-d[j]][i-1]+mod)%mod;
//					printf("j=%d,d=%d,tmp=%lld\n",j,d[j],tmp);
				}
//				printf("all tmp=%lld\n",tmp);
				ans=(ans+tmp*power(i,mod-2))%mod;
			}
			return ans;
		}
};
