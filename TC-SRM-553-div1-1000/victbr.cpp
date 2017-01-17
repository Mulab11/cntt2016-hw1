#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60,M = 210; 

struct Edge{
	int end,next,sum;
	ll dis;
};

class YamanoteLine {  
	public:  
		ll inf;
		int m1,m2,first[N],efn,n;
		int ss1[N],ss2[N],tt1[N],tt2[N],ll1[N],ll2[N];
		Edge edge[M];
		long long howMany(int nn, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2)  {  
			n = nn;
			inf = 1000000000;inf = inf * 50+100;
			m1 = s1.size();m2 = s2.size();
			
			for (int i = 0;i < m1;i++) ss1[i] = s1[i]+1,tt1[i] = t1[i]+1,ll1[i] = l1[i];
			for (int i = 0;i < m2;i++) ss2[i] = s2[i]+1,tt2[i] = t2[i]+1,ll2[i] = l2[i];
			
			ll L = ef1(1,inf);
			ll R = ef2(1,inf);
			//cout << L << ' ' << R << endl;
			if (R == inf) return -1;
			if (R < L) return 0;
			return R-L+1;
		}
		ll ef1(ll l,ll r){
			ll mid = (l + r) >> 1;
			while (l < r){ 
				if (check1(mid)) r = mid;else l = mid+1;
				mid = (l + r) >> 1;
			}
			return l;
		}
		ll ef2(ll l,ll r){
			ll mid = (l + r + 1) >> 1;
			while (l < r){
				if (check2(mid)) l = mid;else r = mid-1;
				mid = (l + r + 1) >> 1;
			}
			return l;
		}
		void addedge(int x,int y,ll z,int w){
			edge[++efn].end = y;
			edge[  efn].dis = z;
			edge[  efn].sum = w;
			edge[  efn].next = first[x];
			first[x] = efn;
			//printf("%d %d %lld\n",x,y,z);
		}
		void init(ll x){
			memset(first,0,sizeof(first));
			efn = 0;
			for (int i = 1;i < n;i++)
				addedge(i+1,i,-1,0);
			addedge(1,n,x-1,1);
//			addedge(n,1,-x,-1);
			for (int i = 0;i < m1;i++){
				if (tt1[i] > ss1[i]) addedge(tt1[i],ss1[i],-ll1[i],0);
				else addedge(tt1[i],ss1[i],x-ll1[i],1);
			}
			for (int i = 0;i < m2;i++){
				if (tt2[i] > ss2[i]) addedge(ss2[i],tt2[i],ll2[i],0);
				else addedge(ss2[i],tt2[i],(ll)ll2[i]-x,-1);
			}
			//exit(0);
		}
		bool check1(ll x){
			/*
				x在左边界左侧时为假 
				无解时为假 
			*/
			init(x);
			return spfa(x,0);
		}
		bool check2(ll x){
			/*
				x在有边界右侧时为假
				无解时为假 
			*/ 
			init(x);
			return spfa(x,1);
		}
		bool spfa(ll x,int opt){
			static int e[N],d2[N],cnt[N];
			static ll d[N];
			static bool bo[N];
			memset(cnt,0,sizeof(cnt));
			memset(e,0,sizeof(e));
			memset(bo,0,sizeof(bo));
			memset(d2,0,sizeof(d2));
			for (int i = 1;i <= n;i++) d[i] = inf*10;
			int t = 1,w = 1;e[1] = 1;d[1] = 0;bo[1] = 1;cnt[1] = 1;
			while (w%(n+1)+1 != t){
				int u = e[t];
				if (cnt[u] > n){
					if (d2[u] == 0) return 0;
					if (opt == 0){
						if (d2[u] > 0) return 0;
						return 1;
					}
					else{
						if (d2[u] > 0) return 1;
						return 0;
					}
				}
				for (int h = first[u];h;h = edge[h].next){
					int v = edge[h].end;
					if (d[u] + edge[h].dis < d[v]){
						 d[v] =  d[u] + edge[h].dis;
						d2[v] = d2[u] + edge[h].sum;
						if (!bo[v]) {
							cnt[v]++;
							bo[v] = 1;
							(w%=n+1)++;
							e[w] = v;
						}
					}
				}
				bo[u] = 0;
				(t%=(n+1))++;
				//cout << t << ' ' << w <<' '<<x << endl;
			}
			return 1;
		}
};
