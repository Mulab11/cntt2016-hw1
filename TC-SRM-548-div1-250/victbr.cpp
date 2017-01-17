#include <bits/stdc++.h>

using namespace std;

class KingdomAndTrees{
	public: 
		vector < int > a;
		int minLevel(vector <int> heights){
			int l = 0,r = 0;
			for (int i = 0;i < heights.size();i++)
				r = max(r,heights[i]);
			a = heights;
			r += heights.size();
			int mid = (l + r) >> 1;
			while (l < r){
				if (check(mid)) r = mid;
				else l = mid + 1;
				mid = (l + r) >> 1;
			}
			return mid;
		}
		bool check(int x){
			int last = max(a[0]-x,1);
			for (int i = 1;i < a.size();i++){
				if ( a[i]+x < last+1) return 0;
				last = max(last+1,a[i]-x);
			}
			return 1;
		}
};
