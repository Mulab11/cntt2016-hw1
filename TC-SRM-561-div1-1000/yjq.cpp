#include <bits/stdc++.h>

using namespace std ; 

const int MAXN = 2505 ; 
const int MAXM = 405  ;  


const int dx[4][2] = {{1 , 0} , {-1 , 0} , {0 , 1} , {0 , -1}} ; 

double ans , c[MAXM][MAXM] ; 

int seq[60][60] , tot ; 
int fn[MAXN] , to[MAXN << 3] ;  

int next[MAXN << 3] ,  d[MAXM][MAXM]  ;  
int po[MAXN] ,  siz[MAXN] ,  NanoApe ,  Claris  ,  Kpm ; 



int info[MAXN] ; 


void addedge(int u , int v) {
		to[++ tot] = v , next[tot] = fn[u] , fn[u] = tot ; 
}

void DfsTree(int top , int now , int pre , int dis) {
		if (top && info[now]) d[top][info[now]] = dis ; 
		siz[now] = bool(info[now]) ; 
		for(int i = fn[now] ; i ; i = next[i])
				if (to[i] != pre) DfsTree(top , to[i] , now , dis + 1) , siz[now] += siz[to[i]] ; 
		if (!top && pre)
				ans += 2 * (c[Claris][Kpm] - c[siz[now]][Kpm] - c[Claris - siz[now]][Kpm]) ;  
}

bool cmp(int s , int a , int b) {
		if (d[s][a] > d[a][b]) return 1 ; 
		if (d[s][a] == d[a][b]) {
				int x = s , y = a ; 
				if (x > y) swap(x , y) ; 
				if (a > b) swap(a , b) ; 
				if (x < a || x == a && y < b) return 1 ; 
		}
		return 0 ; 
}
class Orienteering {
		public:

				double expectedLength(vector<string> mp ,  int K) {
						Kpm = K ; 
						for(int i = 0 ; i <= 300 ; i ++) {
								c[i][0] = 1 ; 
								for(int j = 1 ; j <= i ; j ++) c[i][j] = c[i - 1][j - 1] + c[i - 1][j] ; 
						}
						ans = 0 ; 
						NanoApe = tot = Claris = 0 ; 
						memset(fn , 0 , sizeof fn) ; memset(info , 0 , sizeof info) ; 
						for(int i = 0 ; i < mp.size() ; i ++)
								for(int j = 0 ; j < mp[i].length() ; j ++)
										if (mp[i][j] != '#') {
												seq[i][j] = ++ NanoApe ; 
												if (mp[i][j] == '*') info[NanoApe] = ++ Claris , po[Claris] = NanoApe ; 
										}
						for(int i = 0 ; i < mp.size() ; i ++)
								for(int j = 0 ; j < mp[i].length() ; j ++)
										if (mp[i][j] != '#')
												for(int x = 0 ; x < 4 ; x ++) {
														int nx = i + dx[x][0] , ny = j + dx[x][1] ; 
														if (nx >= 0 && ny >= 0 && nx < mp.size() && ny < mp[i].length() && seq[nx][ny])
																addedge(seq[i][j] , seq[nx][ny]) ;  
												}
						DfsTree(0 , 1 , 0 , 0) ; 
						for(int i = 1 ; i <= Claris ; i ++)
								DfsTree(i , po[i] , 0 , 0) ; 
						for(int u = 1 ; u <= Claris ; u ++)
								for(int v = u + 1 ; v <= Claris ; v ++) {
										int flag = Claris - 2 ; 
										for(int i = 1 ; i <= Claris ; i ++)
												if (i != u && i != v)
														if (cmp(i , u , v) || cmp(i , v , u)) flag -- ;  
										if (Kpm >= 2) ans -= d[u][v] * c[flag][Kpm - 2] ; 
								}
						return ans / c[Claris][Kpm] ;  
				}
} ; 
