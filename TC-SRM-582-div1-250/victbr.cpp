#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60;
struct Node{
	int x;ll y;
	Node(){}
	Node(int x,ll y):x(x),y(y){}
};
bool operator < (const Node &a,const Node &b){
	return a.x < b.x;
}
class SpaceWarDiv1{
	public:
		int n,m;
		int a[N];
		Node b[N];
		long long minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount) {
				n = magicalGirlStrength.size();m = enemyCount.size();//m != n
				ll l = 0,r = 1,mid,mx;
				for (int i = 0;i < m;i++) r += enemyCount[i];
				for (int i = 0;i < n;i++) a[i] = magicalGirlStrength[i];
				for (int i = 0;i < m;i++) b[i] = Node(enemyStrength[i],enemyCount[i]);
				sort(a,a+n);
				sort(b,b+m);
				mx = r;
				mid = l + r >> 1;;
				while (l < r){
					if (check(mid)) r = mid;else l = mid+1;
					mid = l + r >> 1;
				}
				if (l == mx) l = -1;
				return l;
		}
		bool check(ll p){
			int i = n-1;
			ll atk = 0,hp = 0;
			for (int j = m-1;j >= 0;j--){
				hp += b[j].y;
				while (a[i] >= b[j].x && i >= 0) {atk += p;i--;}
				if (atk < hp) return 0;//无解当且仅当存在一个时刻atk<hp 
			}
			return 1;
		}
};

