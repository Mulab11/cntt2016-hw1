#include <bits/stdc++.h>
using namespace std;

class SurveillanceSystem{
public:
	string getContainerInfo(string box, vector <int> reports, int L){
		int i, j, k, n = box.length(), tot, cover[55];
		vector <int> occur[55], cnt(L + 1); string status;
		for(i = 0; i < n; ++ i) status += '-';
		for(i = 0; i + L <= n; ++ i){
			for(j = tot = 0; j < L; ++ j)
				if(box[i + j] == 'X') ++ tot;
			occur[tot].push_back(i);
		}
		for(i = 0; i < int(reports.size()); ++ i)
			++ cnt[reports[i]];
		for(i = 0; i <= L; ++ i){
			if(!cnt[i]) continue;
			memset(cover, 0, sizeof(cover));
			for(j = 0; j < int(occur[i].size()); ++ j)
				for(k = 0; k < L; ++ k)
					++ cover[occur[i][j] + k];
			for(j = 0; j < n; ++ j)
				if(cover[j] > int(occur[i].size()) - cnt[i])
					status[j] = '+';
				else if(cover[j] && status[j] != '+') status[j] = '?';
		} return status;
	}
};
