#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair <int, int> pii;
const int dx[3] = {1, 0, 0}, dy[3] = {0, 0, 1};

class FindPolygons{
public:
	struct Tri{
		int i, j, k;
		Tri(){}
		Tri(int a, int b, int c): i(a), j(b), k(c) {}
	}legal[20005];
	int n, table[100003], sqr[5005]; vector <pii> tri[5005];
	double minimumPolygon(int L){
		if(L <= 2 || (L & 1)) return -1;
		int i, i2, j, cur, tmp, L_ = L >> 1, L2 = L_ * L_, cnt = 0;
		int u, v, ans = 4, ansd = (L >> 1) & 1, x, y, k, mx, mn;
		for(i = 1; i <= L; ++ i) sqr[i] = i * i;
		for(i = 1; i <= L_; ++ i)
			table[i * i % 100003] = i;
		for(i = 1; i <= L_; ++ i)
			for(j = 1, i2 = i * i; (cur = i2 + j * j) <= L2; ++ j){
				tmp = table[cur % 100003];
				if(tmp * tmp == cur)
					tri[tmp].push_back(pii(i, j)), ++ n;
			}
		for(i = 1; i <= L_; ++ i){
			vector <pii> &now1 = tri[i];
			for(j = 1; j <= L_; ++ j){
				vector <pii> &now2 = tri[j];
				mx = max(i, j), mn = min(i, j);
				for(u = 0; u < int(now1.size()); ++ u)
					for(v = 0; v < int(now2.size()); ++ v){
						for(k = 0; k < 3; ++ k){
							++ cnt;
							x = now1[u].fi + (dx[k] ? now2[v].fi : - now2[v].fi);
							y = now1[u].se + (dy[k] ? now2[v].se : - now2[v].se);
							if(x < 0 || y < 0) continue;
							cur = sqr[x] + sqr[y];
							tmp = table[cur % 100003];
							if(sqr[tmp] == cur && i + j + tmp == L && max(mx, tmp) != L_ && (ans > 3 || ansd > max(mx, tmp) - min(mn, tmp)))
								ans = 3, ansd = max(mx, tmp) - min(mn, tmp);
						}
					}
			}
		}
		for(i = 1; i <= L_; ++ i){
			vector <pii> &now1 = tri[i];
			for(u = 0; u < int(now1.size()); ++ u){
				for(j = 1; i + j + now1[u].se <= L; ++ j){
					mn = min(i, j), mx = max(i, j);
					cur = sqr[abs(now1[u].fi - j)] + sqr[now1[u].se];
					tmp = table[cur % 100003];
					if(sqr[tmp] == cur && i + j + tmp == L && max(mx, tmp) != L_ && (ans > 3 || ansd > max(mx, tmp) - min(mn, tmp)))
						ans = 3, ansd = max(mx, tmp) - min(mn, tmp);
				}
			}
		}
		return ansd;
	}
};
