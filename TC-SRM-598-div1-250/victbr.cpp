#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 60;

class BinPacking{
	public:
		bool flag[N];
		int n,a[N],ans;
		int minBins(vector<int> inp){
			n = inp.size();
			for (int i = 0;i < n;i++)
				a[i] = inp[i];
			sort(a,a+n);
			for (int i = n-1;i >= 0;i--)
				if (!flag[i]){
					int tot = a[i];
					flag[i] = 1;
					for (int j = i-1;j >= 0;j--)
						if (!flag[j] && tot + a[j] <= 300){
							flag[j] = 1;
							tot += a[j];
						}
					ans++;
				}
			return ans;
		}
};
