#include <bits/stdc++.h>

using namespace std;

int n ; 

const int MAXN = 60 ; 

int s[MAXN], cnt[MAXN][MAXN], vis[MAXN] ; 

class FoxAndHandle {
		public:
				string lexSmallestName(string str) {
						n = str.length() ;
						for(int i = 0; i < n; i ++)
								s[i] = str[i] - 'a';
						for(int i = 0; i < n; i ++) {
								for(int j = 0; j < 26; j ++)
										cnt[i + 1][j] = cnt[i][j];
								cnt[i + 1][s[i]]++;
						}
						string ans;
						for(int i = 0, j = 0, k; i < n / 2; i ++) {
								for(int i = 0; i < 26; i++) {
										if(vis[i] >= (cnt[n][i] >> 1) ) continue;
										for(k = j; k < n && s[k] != i; k ++);
										bool flag = 1;
										for(int c = 0; c < 26 && flag; c ++) {
												if ((cnt[k][c] - vis[c] > cnt[n][c] / 2)) flag = 0 ; 
										}
										if (!flag) continue;
										vis[i] ++ ;
										ans += i + 'a' ;
										j = k + 1 ;
										break;
								}
						}
						return ans;
				}
} sol ;

int main() { 
		cout << sol.lexSmallestName("ccieliel") << endl ; 

}
