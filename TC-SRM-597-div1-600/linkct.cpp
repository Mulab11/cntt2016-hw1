#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

class ConvexPolygonGame{
public:
	vector <double> border[200005];
	int l[200005], r[200005], s[200005], top;
	string winner(vector <int> x, vector <int> y){
		int n = x.size(), i, j, sum = 0, cnt = 0;
		for(i = 0; i < n; ++ i) x[i] += 100000, y[i] += 100000;
		for(i = 0; i < n; ++ i){
			if(x[i] == x[(i + 1) % n]){
				border[x[i]].push_back(min(y[i], y[(i + 1) % n]));
				border[x[i]].push_back(max(y[i], y[(i + 1) % n]));
			}else for(j = min(x[i], x[(i + 1) % n]); j <= max(x[i], x[(i + 1) % n]); ++ j)
				border[j].push_back(y[i] + double(y[i] - y[(i + 1) % n]) / (x[i] - x[(i + 1) % n]) * (j - x[i]));
		}
		for(i = 0; i <= 200000; ++ i){
			if(border[i].empty()) continue;
			sort(border[i].begin(), border[i].end());
			l[i] = int(border[i][0] - 1e-8) + 1;
			r[i] = int(border[i].back() + 1e-8);
			for(j = 0; j < n; ++ j)
				if(x[j] == i){
					if(y[j] == l[i]) ++ l[i];
					if(y[j] == r[i]) -- r[i];
				}
			if(l[i] > r[i]) continue;
			sum += r[i] - l[i] + 1, ++ cnt;
			if(sum > 200001) return "Masha";
		} if(cnt == 1) return "Petya";
		for(i = top = 0; i <= 200000; ++ i){
			if(border[i].empty() || l[i] > r[i]) continue;
			if(r[i] - l[i] > 0) return "Masha";
			s[++ top] = i;
			if(top >= 3 && LL(r[s[top]] - r[s[top - 1]]) * (s[top - 1] - s[top - 2]) != LL(r[s[top - 1]] - r[s[top - 2]]) * (s[top] - s[top - 1]))
				return "Masha";
		} return "Petya";
	}
};
