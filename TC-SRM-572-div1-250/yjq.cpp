#include <bits/stdc++.h>

using namespace std;

int n ; 

const int MAXN = 110 ; 
int cnt[MAXN] ; 
class NewArenaPassword {
		public:
				int minChange(string s, int k) {
						int n = s.length() ;
						int ans = 0 ;
						for(int i = 0; i < n - k; i ++) {
								memset(cnt, 0, sizeof cnt) ; 
								int sum = 0 ;
								for (int j = i; j < n; j += (n - k)) cnt[s[j] - 'a'] ++, sum ++ ; 
								int tmp = 0 ;
								for (int j = 0; j < 26; j ++) tmp = max(tmp, cnt[j]) ; 
								ans += sum - tmp;
						}
						return ans;
				}
} sol ;

int main() { 
		printf("%d\n", sol.minChange("topcoderopen", 5)) ; 
}
