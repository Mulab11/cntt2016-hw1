/*
	some ... analysis(?)
*/
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
int to[27];
vector<PI> arr;
class NextAndPrev {
	public:
	int getMinimum(int nxt, int prv, string a, string b) {
		memset(to, -1, sizeof to); arr.clear();
		if (a == b) return 0;
		string t = b; sort(t.begin(), t.end());
		t.resize(unique(t.begin(), t.end()) - t.begin());
		if (t == "abcdefghijklmnopqrstuvwxyz") return -1; // spj
		int n = a.size();
		rep(i, 0, n - 1){
			int p = a[i] - 'a', q = b[i] - 'a';
			if (to[p] != -1 && to[p] != q) return -1;
			to[p] = q;
		}
		rep(i, 0, 25) if (~to[i]) arr.push_back(PI(i, to[i]));
		int ret = 1e9; n = arr.size();
		rep(i, 0, 25){
			sort(arr.begin(), arr.end());
			bool ok = 1;
			rep(j, 1, n - 1) if (arr[j].second < arr[j - 1].second) {ok = 0; break;} // no cross plz
			if (ok){
				rep(j, -2, 2){ // rotate all for j cycles
					int ans = 0, k = 0, p = 0;
					for (PI& t : arr) t.second += j * 26; // rotate
					while(k < n){
						while (arr[p].second == arr[k].second && p < n) ++p; // find a segment of the same 'to'
						ans += max(0, arr[k].second - arr[k].first) * nxt + max(0, arr[p - 1].first - arr[k].second) * prv; // direction : nxt or prv
						k = p;
					}
					ret = min(ret, ans);
					for (PI& t : arr) t.second -= j * 26; // redo
				}
			}
			arr[0].first += 26;
		}
		return ret == 1e9 ? -1 : ret;
	}
};

/*
	ONIGOROSHIAAAAAAAAAAAA
*/
