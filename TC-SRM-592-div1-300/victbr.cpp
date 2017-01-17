#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

class LittleElephantAndBalls{
	public:
		int cnt[256+10],n,ans,k;
		int getNumber(string s){
			n = s.size();
			for (int i = 0;i < n;i++){
				ans += k;
				if (cnt[s[i]] < 2) k++;
				cnt[s[i]]++;
			}
			return ans;
		}
};
