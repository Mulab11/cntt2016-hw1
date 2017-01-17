#include <bits/stdc++.h>

using namespace std;

class NewArenaPassword{
	public:
		int b[30];
		int minChange(string s, int K){
			int ans = 0,n = s.size();
			if (K <= n/2){
				for (int i = 0;i < K;i++)
					if (s[i] != s[n-K+i]) ans++;
				return ans;
			}
			else{
				memset(b,0,sizeof(b));
				for (int i = 0;i < n-K;i++){
					int mx = 0,cnt = 0;
					for (int j = i;j < n;j += n-K){
						cnt++;
						b[s[j]-'a']++;
						mx = max(mx,b[s[j]-'a']);
					}
					ans += cnt-mx;
					for (int j = i;j < n;j += n-K)
						b[s[j]-'a']--;					
				}
				return ans;
			}
		}
};
