#include <bits/stdc++.h>

using namespace std;

class TriangleXor{
	public:
		int theArea(int n){
			double ans = 0,flag = -1;
			ans = (double)n*(n+1)/2;
			for (int i = n;i >= 1;i--){
				ans += flag*i*n*(double)n/(n-i+n+1);//面积要除2,面积要算两次，所以抵消。 
				flag *= -1;
			}
		//	cout << ans << endl;
			return (int)ans;//答案要强转整型 
		}
};
