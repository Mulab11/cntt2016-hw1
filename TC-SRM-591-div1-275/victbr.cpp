#include <bits/stdc++.h>

using namespace std;

const int N = 100010; 

class TheTree{
    public:
		int n,ans,b; 
		int maximumDiameter(vector<int> a){
			n = a.size();
			if (a[n-1] > 1) b = n;else b = n-1;
			for (int i = n-1;i >= 1;i--){
				ans = max(ans,n+b-i-i);
				if (a[i-1] <= 1) b = i-1;
			}
			return ans; 
		}
};
			


