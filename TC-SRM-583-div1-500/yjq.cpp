#include <bits/stdc++.h>

using namespace std ;

int n ;

const int MAXN = 110 ; 

int f[MAXN] ;

class TurnOnLamps {
		public :
				int minimize(vector<int> fa, string a, string b) { 
						n = fa.size() ; 
						for (int i = n; i; i --) {
								if (b[i - 1] == '1') f[i] += ((f[i] & 1) ^ (a[i - 1] == '0')) ;
							    f[fa[i - 1]] += f[i] ; 
						}
						f[0] += (f[0] & 1) ; 
						return f[0]  / 2;
				}
} ; 	

