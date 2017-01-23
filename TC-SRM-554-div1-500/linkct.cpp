#include <bits/stdc++.h>
using namespace std;

vector <int> h;
bool cmp1(const int &a, const int &b){
	if(h[a] != h[b]) return h[a] > h[b];
	return a < b;
}
bool cmp2(const int &a, const int &b){
	if(h[a] != h[b]) return h[a] < h[b];
	return a < b;
}
class TheBrickTowerMediumDivOne{
public:
	int n; vector <int> res, tmp; bool vis[55];
	vector <int> find(vector <int> ht){
		h = ht;
		int i, j, l, r; res.resize(n = h.size());
		for(i = 0; i < n; ++ i) tmp.push_back(i);
		sort(tmp.begin(), tmp.end(), cmp1);
		for(i = j = l = 0, r = n; i < n && j < n; ++ i){
			if(vis[i]) continue;
			while(tmp[j] != i)
				vis[res[-- r] = tmp[j ++]] = true;
			vis[res[l ++] = tmp[j ++]] = true;
		}
		sort(res.begin() + l, res.end(), cmp2);
		return res;
	}
};
