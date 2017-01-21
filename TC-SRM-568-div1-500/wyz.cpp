// BEGIN CUT HERE

// END CUT HERE
#line 5 "EqualSums.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;
#define P 1000000007

const int maxn=105;

class EqualSums {
	int n;
	int q[maxn],qh,qt;
	int b[maxn];
	bool vis[maxn];
	public:
	int count(vector <string> board){
		n=board.size();
		memset(vis,0,sizeof(vis));
		int ans0=1,ans1=1;
		qh=qt=0;
		for (int i=0;i<n;++i)if (!vis[i]){
			q[++qt]=i;
			vis[i]=1;
			b[i]=0;
			int l0=0,l1=1,r=P-1;
			while (qh<qt){
				int u=q[++qh];
				if (u<n){
					l0=max(l0,-b[u]);
					l1=max(l1,1-b[u]);
				}
				else r=min(r,b[u]);
				for (int i=0;i<n;++i){
					int v=i,b0;
					if (u<n){
						if (board[u][i]=='-') continue;
						b0=board[u][i]-48-b[u];
						v+=n;
					}
					else{
						if (board[i][u-n]=='-') continue;
						b0=board[i][u-n]-48-b[u];
					}
					if (vis[v]&&b[v]!=b0) return 0;
					if (vis[v]) continue;
					b[v]=b0;
					vis[v]=1;
					q[++qt]=v;
				}
			}
			ans0=1LL*ans0*max(0,r-l0+1)%P;
			ans1=1LL*ans1*max(0,r-l1+1)%P;
		}
		return (ans0-ans1+P)%P;
	}
};
