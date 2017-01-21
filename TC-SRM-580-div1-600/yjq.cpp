#include <bits/stdc++.h>

using namespace std ;

const int MAXN = 51 * 51 + 10 ; 

typedef vector<string> VS ; 
int s[MAXN], t[MAXN], id = 0, p[MAXN]; 

int f[MAXN], g[MAXN] ; 

bool cmps(int x,int y) {
		return s[x] < s[y] ;
}

bool cmpt(int x,int y) {
		return t[x] < t[y] ;
}
class ShoutterDiv1 {
		public : 
		int count (VS s1000, VS s100, VS s10, VS s1, VS t1000, VS t100, VS t10, VS t1) {
				int len = s1000.size() ; 
				for (int i = 0;i < len;i ++) {
						int tlen = s1000[i].length() ;
					    for (int j = 0;j < tlen;j ++) {
								id ++ ; 
								s[id] = (s1000[i][j] - '0') * 1000 + (s100[i][j] - '0') * 100 + (s10[i][j] -  '0') * 10 + s1[i][j] - '0' ; 
								t[id] = (t1000[i][j] - '0') * 1000 + (t100[i][j] - '0') * 100 + (t10[i][j] - '0') * 10 + t1[i][j] - '0' ; 
						}
				}
				int ans = 0 ;  
				for (int i = 1;i <= id;i ++) p[i] = i ; 
				sort(p + 1, p + id + 1, cmpt) ; 
				int nowmin = 100000 ; 
				for (int i = id ;i ;i --) {
						nowmin = min(nowmin , s[p[i]]) ; 
						if (i > 1 && nowmin > t[p[i - 1]]) return -1 ; 
						int curmax = 0, curp = 0;  
						int cnt =0 ;  
						for (int j = 1;j <= id;j ++) {
								if (s[j] <= t[p[i]]) {
										cnt ++ ;
									    if (t[j] > curmax) curmax = t[j], curp = j ; 
								}
						}
						if (cnt == id) g[p[i]] = 0 ;
						else if (curmax == t[p[i]]) return -1 ; 
						else g[p[i]] = g[curp] + 1;  
				}
				sort(p + 1, p + id + 1, cmps) ; 
				for (int i = 1;i <= id;i ++) {
						int curmin = 100000, curp = 0, cnt = 0 ;
						for (int j = 1;j <= id;j ++) {
								if (t[j] >= s[p[i]]) {
										cnt ++ ;
										if (s[j] < curmin) curmin = s[j], curp = j  ;
								}
						}
						if (cnt == id) f[p[i]] = 0 ; 
						else if (curmin == s[p[i]]) return -1 ; 
						else f[p[i]] = f[curp] + 1; 
				}
				for (int i = 1;i <= id;i ++) {
						int nowmin = f[i] + g[i] ; 
						for (int j = 1;j <= id;j ++) {
								if (s[j] <= s[i] && t[j] >= t[i]) {
										nowmin = min(nowmin, 1 + f[j] + g[j]) ; 
								}
								else if (s[j] <= t[i] && t[j] >= t[i]) {
										nowmin = min(nowmin, 1 + f[i] + g[j]) ; 
								}
								else if (t[j] >= s[i] && s[j] <= s[i]) {
										nowmin = min(nowmin, 1 + f[j] + g[i]) ; 
								}
						}
						ans += nowmin; 
				}
				return ans ; 
		}
} ;



