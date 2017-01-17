#include <bits/stdc++.h>

using namespace std;

class IncrementAndDoubling{
	public:
		int n,mx,sum;
		int getMin(vector <int> arr){
			n = arr.size();
			for (int i = 0;i < n;i++){
				int u = arr[i],tot = 0;
				while (u){
					if (u&1) sum++;
					tot++;
					u >>= 1;
				}
				mx = max(mx,tot);
			}
			if (mx == 0) return 0;//注意数据中可能有0 
			return mx+sum-1;
		}
};
