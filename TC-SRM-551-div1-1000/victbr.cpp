#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 50,M = 1310000,mod = 1e9+7,inf = 1000100000;

struct Node{
	int x,y;
	Node(){}
	Node(int x,int y):x(x),y(y){}
};
/*
bool operator < (const Node &a,const Node &b){
	return a.y == b.y ? a.x < b.x : a.y < b.y;
};
*/
int add(int x,int y){
	x += y;
	while (x >= mod) x -= mod;
	return x;
}
bool cmp1(const Node &a,const Node &b){
	return a.x < b.x;
};
bool cmp2(const Node &a,const Node &b){
	return a.y == b.y ? a.x < b.x : a.y < b.y;
};
class SweetFruits{
	public:
		Node a[M],b[M];
		int A[N][N],D[N][N];
		int fact[N],inv[N],finv[N],sum;
		int ans,n,cnt[N],tree[N],c[N],MaxS;
		int countTrees(vector<int> sweetness,int maxSweetness){
			n = sweetness.size();
			MaxS = maxSweetness;
			init();
			for (int i = 0;i < n;i++) {c[i] = sweetness[i];if (c[i] >= 0) sum++;}
			MeetintheMiddle();
			MatrixTree();
			for (int i = 0;i <= n;i++)
				ans = add(ans,(ll)cnt[i]*tree[i]%mod);
			return ans;
		}
		void MeetintheMiddle(){
			int m = n/2,pointer[N],first[N];
			memset(pointer,-1,sizeof(pointer));
			memset(first,-1,sizeof(first));
			for (int i = 0;i < (1<<m);i++){
				int tot = 0,sum = 0;
				for (int j = 0;j < m;j++)
					if ((1<<j) & i) {
						if (c[j] == -1) tot -= inf;
						else tot += c[j];
						sum++;
					}
				a[i] = Node(tot,sum);				 
			}
			for (int i = 0;i < (1<<(n-m));i++){
				int tot = 0,sum = 0;
				for (int j = 0;j < n-m;j++)
					if ((1<<j) & i) {
						if (c[j+m] == -1) tot -= inf;
						else tot += c[j+m];
						sum++;
					}
				b[i] = Node(tot,sum);
			}
			sort(a,a+(1<<m),cmp1);
			sort(b,b+(1<<(n-m)),cmp2);
		//	for (int i = 0;i < (1<<m);i++) printf("%d ",a[i].x);printf("\n");
		//	for (int i = 0;i < (1<<(n-m));i++) printf("%d ",b[i].x);printf("\n");
			for (int i = 0;i < (1<<(n-m));i++){
				if (b[i].x >= 0) pointer[b[i].y] = i;
				if (first[b[i].y] == -1 && b[i].x >= 0) first[b[i].y] = i;
			}
			for (int i = 0;i < (1<<m);i++){
				if (a[i].x < 0) continue;
				for (int j = 0;j <= n-m;j++){
					if (pointer[j] < 0) break;
					while (pointer[j] >= first[j] && b[pointer[j]].x+a[i].x > MaxS){
						pointer[j]--;
						if (pointer[j] < 0) break;
					}
					if (pointer[j] < 0) break;
		//			printf("%d %d %d %d\n",a[i].y,j,pointer[j],first[j]);
					cnt[a[i].y+j] = add(cnt[a[i].y+j],pointer[j]-first[j]+1);
				}	
			}
		}
		void MatrixTree(){
			for (int i = 0;i <= n;i++){
				tree[i] = Cal(i);
				for (int j = 0;j < i;j++)
					tree[i] = add(tree[i],mod-(ll)C(i,j)*tree[j]%mod);
			}
		}
		void init(){
			fact[0] = 1;
			for (int i = 1;i <= n;i++)
				fact[i] = (ll) fact[i]*i%mod;
			inv[1] = 1;
			for (int i = 2;i <= n;i++)
				inv[i] = mod-(ll)mod/i*inv[mod%i]%mod;
			finv[0] = 1;
			for (int i = 1;i <= n;i++)
				finv[i] = (ll)finv[i-1]*inv[i]%mod;
		}
		int C(int x,int y){
			if (x < y) return 0;
			return (ll)fact[x]*finv[y]%mod*finv[x-y]%mod;
		}
		int Cal(int p){
			memset(A,0,sizeof(A));
			memset(D,0,sizeof(D));
			if (p > sum) return 0;
			for (int i = 1;i <= n;i++)
				for (int j = 1;j <= n;j++)
					if (i != j){
						if (i <= p && j <= p) A[i][j] = 1;
						else if (i > sum || j > sum) A[i][j] = 1;
					}
			for (int i = 1;i <= n;i++){
				int tot = 0;
				for (int j = 1;j <= n;j++) if (A[i][j]) tot++;
				D[i][i] = tot; 
			}
			for (int i = 1;i <= n;i++)
				for (int j = 1;j <= n;j++)
					D[i][j] = add(D[i][j],mod-A[i][j]);	
			return Gauss();
		}
		int Gauss(){
			int sum = 1;
			for (int i = 1;i < n;i++){
				int k = 0;
				for (int j = i;j < n;j++)
					if (D[j][i]){k = j;break;}
				if (k != i) sum = mod-sum;
				if (k == 0) return 0;	
				for (int j = 1;j < n;j++)
					swap(D[i][j],D[k][j]);
				for (int j = 1;j < n;j++)
					if (i != j && D[j][i] != 0){
						int u = D[j][i]*pow(D[i][i],mod-2);
						for (int k = 1;k < n;k++)
							D[j][k] = add(D[j][k],mod-(ll)D[i][k]*u%mod);
					}	
			}
			
			for (int i = 1;i < n;i++) sum = (ll)sum*D[i][i]%mod;
			return sum;
		}
		int pow(int x,int y){
			int ans = 1;
			while (y){
				if (y&1) ans = (ll)ans*x%mod;
				x = (ll)x*x%mod;
				y >>= 1;
			}
			return ans;
		}
};
