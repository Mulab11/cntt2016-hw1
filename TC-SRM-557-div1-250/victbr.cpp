#include <bits/stdc++.h>

using namespace std;

class FoxAndMountainEasy{
	public:
		string possible(int n, int h0, int hn, string history){
			int m = history.size();
			for (int i = 0;i < m;i++){
				if (history[i] == 'U') h0++;else h0--;
				if (h0 < 0){h0++;n--;}
			}
			if (n < 0) return "NO";
			hn -= h0;
			hn = abs(hn);
			if  (hn <= n-m && (n-m-hn) % 2 == 0) return "YES";
			else return "NO";
		}
};
