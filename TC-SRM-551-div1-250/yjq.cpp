#include <bits/stdc++.h>

using namespace std; 

const int MAXN = 110 ;  

int suf[MAXN],  pre[MAXN] ;  

class ColorfulChocolates { 
		public:
				int maximumSpread(string cho,  int M) {
						int n = cho.size(); 
						for(int len = n; len; len --)
								for(int r = len - 1; r < n; r ++) {
										int l = r - len + 1; 
										for(char ch = 'A'; ch <= 'Z'; ch ++) { 
												int cl = 0, cr = 0; 
												memset(suf,  0,  sizeof suf) ; 
												memset(pre,  0,  sizeof pre) ;  
												for(int i = l - 1; i >= 0; i --) if (cho[i] == ch) suf[++ cl] = suf[cl - 1] + i; 
												for(int i = r + 1; i < n; i ++) if (cho[i] == ch) pre[++ cr] = pre[cr - 1] + i;  
												int mc = (1 << 30), sum = 0, co = 0, cc = 0, cs = 0; 
												for(int p = l; p <= r; p ++) if (cho[p] != ch) sum += p, co ++; 
												for(int p = l; p <= r; p ++) 
														if (cho[p] != ch) {
																if (cc <= cl && co - cc <= cr) mc = min(mc, cs - suf[cc] + pre[co - cc] - (sum - cs));  
																++ cc,  cs += p; 
														}
												if (cc <= cl && co - cc <= cr) mc = min(mc, cs - suf[cc] + pre[co - cc] - (sum - cs));  
												if (mc <= M) return len; 
										}
								}
				}
}; 
