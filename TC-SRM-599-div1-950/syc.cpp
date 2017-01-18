#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <vector>
#include <bitset>
#include <cstdio>
#include <string>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define REP(i,x,y)  for(int i=(int)x;i<=(int)y;i++)
#define FOR(i,x,y)  for(int i=(int)x;i< (int)y;i++)
#define PER(i,x,y)  for(int i=(int)x;i>=(int)y;i--)
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define md ((L+R)/2)
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
const	int P=1e9+7;
const	int inf=1e9;
const	ll Inf=1e16;
const	int N=55;
const	int M=1<<16;

inline int IN(){
	char ch=getchar();int x=0,f=0;
	for(;ch<48||ch>57;ch=getchar()) f=ch=='-';
	for(;ch>=48&&ch<=57;ch=getchar()) x=(x<<1)+(x<<3)+ch-48;
	return f?(-x):x;
}

int Pow(int x,int y,int p){
	int a=1;
	for(;y;y>>=1,x=(ll)x*x%p) if(y&1) a=(ll)a*x%p;
	return a;
}

int n, m, lst[N], tot, A[N], B[N], U, ID[M], val[M], cnt;
vector<int> con[N], e[N], valid[M];

#define Contain(x,y) (((x)>>(y))&1)

void pret(){
	U = 1 << tot;
	//预处理所有合法的状态
	FOR(i, 0, U){
		int flag = 1;
		//判断这个状态是否合法
		FOR(j, 0, m){
			int u = Contain(i, A[j]);
			int v = Contain(i, B[j]);
			//如果一个子树有A[j]而无B[j],那么他是不合法的.
			if(u && v)continue;
			if(!u && !v)continue;
			if(!u && v) continue;
			flag = 0;
			break;
		}
		if(flag){
			val[++cnt] = i;
			ID[i] = cnt;
		}
	}

	//预处理所有合法的转移.	
	REP(i, 1, cnt){
		int S = val[i];
		for(int T = S; ; T=(T - 1) & S){
			//判断转移T + (S ^ T) 是否合法
			//令U = S, V = S ^ T, 合法的只有 5 种
			//A in U, B in U
			//A in V, B in V
			//A notin S, B notin S
			//A notin S, B in U
			//A notin S, B in V
			int flag = 1;
			if(!ID[T] || !ID[S ^ T]) continue;
			if(flag){
				valid[i].pb(ID[T]);
			}
			if(T == 0) break;
		}
	}
}

int check(string u, string v){
	if(u.length() >= v.length()) return 0;
	FOR(i, 0, u.length()) if(u[i] != v[i]) return 0;
	return 1;
}

int f[N][M],G[M];

void dp(int x){
	//初始状态是空集
	f[x][1] = 1;
	FOR(i, 0, e[x].size()){
		int v = e[x][i];
		dp(v);
		memset(G, 0, sizeof G);
		//枚举所有合法状态
		REP(j, 1, cnt){
			//枚举这个状态的所有转移.
			FOR(k, 0, valid[j].size()){
				int u = valid[j][k];
				int t = ID[val[j] ^ val[u]];
				if(!t) continue;
				G[j] = (G[j] + (ll)f[v][u] * f[x][t]) % P;
			}
		}
		REP(j, 1, cnt) f[x][j] = G[j];
	}
	
	//在x上填入标号.
	if(x)
	PER(j, cnt, 1){
		int tmp = 0;
		FOR(i, 0, tot) if(!Contain(val[j], i) && (tmp = ID[val[j] ^ (1 << i)])){
			f[x][tmp] = (f[x][tmp] + f[x][j]) % P;
		}
	}
}

int fac(int n){
	int gt = 1;
	REP(i, 2, n) gt = (ll)gt * i % P;
	return gt;
}

struct SimilarNames{
	int count(vector<string> names, vector<int> info1, vector<int> info2){
		n = names.size();
		m = info1.size();
		FOR(i, 0, m){
			A[i] = info1[i];
			B[i] = info2[i];
			lst[tot++] = info1[i];
			lst[tot++] = info2[i];
		}
		sort(lst, lst + tot);
		tot = unique(lst, lst + tot) - lst;
		
		//将读入的特殊点都重新标号.
		FOR(i, 0, m){
			A[i] = lower_bound(lst, lst + tot, A[i]) - lst;
			B[i] = lower_bound(lst, lst + tot, B[i]) - lst;
		}
		
		pret();
		
		//预处理字母树.
		REP(i, 1, n){
			int fat = 0;
			//找到每个节点的父亲
			REP(j, 1, n) if(check(names[j - 1], names[i - 1])){
				if(!fat){
					fat = j;
					continue;
				}else{
					if(names[j - 1].length() > names[fat - 1].length()) fat = j;
				}
			}
			e[fat].pb(i);
		}
		
		dp(0);
		
		return (ll)f[0][cnt] * fac(n - tot) % P;
	}
}str;