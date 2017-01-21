#include <bits/stdc++.h>

using namespace std; 

int n ;  

typedef long long LL; 

const int MAXN = 60 ;  

vector<LL> tmp ;  


string Color ; 

string go; 


char s[MAXN] ;  

LL check(int st) {
		LL cov = 0, tmp = 0; 
		for(int i = 0; i < Color.length(); i ++)
		{
				if (Color[i] == '<') -- st; 
			   	else if (Color[i] == '>') ++ st;  
				else {
								cov |= (1LL << st); 
								s[st] = Color[i]; 
								bool flag = 1; 
								for(int j = 0; j < n; j ++) if ((cov & (1LL << j)) && s[j] != go[j]) {
										flag = 0 ; 
										break ; 
								}
								if (flag) tmp = cov; 
				}
		}
		return tmp;  
}


LL Dfs(int i, LL s) {
		if (!s) return (i == tmp.size());  
		if (i == tmp.size()) return (1LL << __builtin_popcountl(s));  
		return Dfs(i + 1, s) - Dfs(i + 1, s & tmp[i]); 
}

class MapGuessing {
		public:

				LL countPatterns(string str,  vector<string> vstr) {
						n = str.size(); 
						go = str; 
						for(int i = 0; i < vstr.size(); i ++)
								for(int j = 0; j < vstr[i].length(); j ++) Color = Color + vstr[i][j]; 
						int l = 0, r = 0, cur = 0; 
						for(int i = 0; i < Color.size(); i ++) {
								if (Color[i] == '<') -- cur; 
								if (Color[i] == '>') ++ cur; 
								l = max(l, -cur), r = max(r, cur); 
						}
						for(int i = l; i + r < n; i ++) tmp.push_back(check(i)); 
						return (1LL << n) - Dfs(0, (1LL << n) - 1); 
				}
}; 
