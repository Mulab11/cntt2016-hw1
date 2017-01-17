#include <bits/stdc++.h>

using namespace std;
const int N = 1010000,mod = 1e9+9;
typedef long long ll;
class CharacterBoard{
	public:
		bool b[N];
		int G,n,m,len,ans;ll a[N<<1];
		map <int,char> q;
		int countGenerators(vector <string> fragment, int W, int i0, int j0){
			G = power(25,mod-2);
			n = fragment.size();
			m = fragment[0].size();
			
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++){
					ll u = (ll)i*W+j;//»á±¬int 
					for (int k = 1;k <= (int)sqrt(u);k++){
						if (u%k == 0){
							if (k < N) b[k] = 1;
							else a[++len] = k; 
							if (k*k != u) {
								if (u/k < N) b[u/k] = 1;
								else a[++len] = u/k;
							}
						}
					}
					u = (ll)i*W+j-m+1;
					for (int k = 1;k <= (int)sqrt(u);k++){
						if (u%k == 0){
							if (k < N) b[k] = 1;
							else a[++len] = k; 
							if (k*k != u) {
								if (u/k < N) b[u/k] = 1;
								else a[++len] = u/k;
							}
						}
					}
				}
			
			
			for (int i = 1;i < N;i++) if (b[i]) a[++len] = i;
			sort(a+1,a+len+1);
			int len2 = len;len = 1;
			for (int i = 2;i <= len2;i++)
				if (a[i] != a[i-1]) a[++len] = a[i];
			q.clear();
//			for (int i = 1;i <= len;i++) printf("%d ",a[i]);printf("\n");
			bool flag = 1;
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++){
					map <int,char> ::iterator it = q.find(0);
					if (it == q.end()) q[0] = fragment[0][0];
					else if (q[0] != fragment[i][j]) {flag = 0;break;}
				}
				
			if (flag) ans++;
			
			a[++len] = 1000000001;
//			cout << len<<endl;
//			printf("1 %d\n",ans);
			for (int i = 2;i <= len;i++){
//				printf("%d %d\n",a[i-1],a[i]);
				if (a[i] > W) a[i] = W+1;
				if (a[i] - a[i-1] > 1){
					int tot = power(26,a[i]-n*m);
					add(tot,mod-power(26,a[i-1]-n*m+1));
					tot = (ll) tot * G % mod;
					add(ans,tot);
				}
				if (a[i] > W) break;
				q.clear();
				bool flag = 1;int cnt = 0;
				for (int j = 0;j < n;j++){
					for (int k = 0;k < m;k++){
						int x = (ll)((ll)j*W+k)%a[i];
						map <int,char> ::iterator it = q.find(x);
						if (it == q.end()) {q[x] = fragment[j][k];cnt++;}
						else if (q[x] != fragment[j][k]) {flag = 0;break;}
					}				
					if (flag == 0) break;
				}
//				cout << a[i]<<' '<<cnt << endl;
				if (flag) add(ans,power(26,a[i]-cnt));
			}
			return ans;
		}
		void add(int &x,int y){
			x += y;
			while (x >= mod) x -= mod;
		}
		int power(int x,int y){
			int ans = 1;
			while (y){
				if (y&1) ans = (ll)ans*x%mod;
				x = (ll)x*x%mod;
				y >>= 1;
			}
			return ans;
		}
}A;
