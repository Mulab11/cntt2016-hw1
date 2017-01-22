/*
	Brute force.
*/

#include <bits/stdc++.h>
using namespace std;
class EelAndRabbit {
	public:
	int getmax(vector <int> l, vector <int> t) {
		int time[128], tn = 0, n = l.size(), ret = 0;
		for (int i = 0; i < n; ++i) // Find all the possible time
			time[tn++] = t[i], time[tn++] = t[i] + l[i];
		sort(time, time + tn); tn = unique(time, time + tn) - time; // This can be deleted
		for (int i = 0; i < tn; ++i) for (int j = 0; j < i; ++j){ // Go over pairs of times
			int t1 = time[i], t2 = time[j], cnt = 0;
			for (int k = 0; k < n; ++k){ // Check & count
				int T1 = t[k], T2 = t[k] + l[k];
				if ((T1 <= t1 && t1 <= T2) || (T1 <= t2 && t2 <= T2)) ++cnt;
			}
			if (ret < cnt) ret = cnt;
		}
		return ret;
	}
};

/*
	The 2016 ACM-ICPC Asia CHINA-Final Contest
		2016.12.10 - 12.11
*/
