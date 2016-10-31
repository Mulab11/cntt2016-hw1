#include <map>
#include <cmath>
#include <ctime>
#include <bitset>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define REP(i, x, y)  for(int i = (int)x; i <= (int)y; i ++)
#define FOR(i, x, y)  for(int i = (int)x; i <  (int)y; i ++)
#define PER(i, x, y)  for(int i = (int)x; i >= (int)y; i --)
#define fi first
#define se second
#define mk make_pair
#define pb push_back
using namespace std;
typedef double db;
typedef long long LL;
typedef pair<int, int> PII;
const	int N = 155;
const	int inf = 1e9;
const	LL Inf = 1e15;
const	int P = 1e9 + 7;

int n, m, ind[15][15], S;
string iss;
struct edge{
	int u, v, w;
	edge(int uu = 0, int vv = 0, int ww = 0){
		u = uu;
		v = vv;
		w = ww;
	}
};
vector<edge> ev, eev;

void adde(int u, int v, int w){
	ev.pb(edge(u, v, w));
}

int inv[N], vis[N], idx[N], pre[N];

int solve(int rt){
	//用朱-刘算法计算最小树形图.
	int res = 0;
	for(;;){
		memset(inv, 0x3f, sizeof inv);
		memset(vis, 0, sizeof vis);
		memset(idx, 0, sizeof idx);
		memset(pre, 0, sizeof pre);
		eev.clear();
		FOR(i, 0, ev.size()){
			int u = ev[i].u, v = ev[i].v, w = ev[i].w;
			//对于每个点(环),找到最小的入边.
			if(w < inv[v]) inv[v] = w, pre[v] = u;
		}
		inv[rt] = 0;
		pre[rt] = rt;
		int tim = 0;
		REP(i, 1, n){
			//一个点没有入边,无解.
			if(inv[i] == inv[0]) return -1;
			res += inv[i];
		}
		int tn = 0;
		REP(i, 1, n){
			//开始找环
			++tim;
			int u = i;
			for(;vis[u] == 0;u = pre[u]) vis[u] = tim;
			//没有找到环
			if(u == rt || vis[u] != tim) continue;
			//找到了环,把每个点所在的环标记一下.
			++tn;
			for(int v = pre[u]; v != u; v = pre[v]) idx[v] = tn;
			idx[u] = tn;
		}
		//没有环,算法结束.
		if(!tn) return res;
		//把不在环上的点标记一下.
		REP(i, 1, n) if(!idx[i]) idx[i] = ++tn;
		//把点和边给缩起来.
		//如果 (u,v,w) 这条边不是环边,那么其边权要修改为 w' = w - inv[v].
		FOR(i, 0, ev.size()){
			int u = ev[i].u, v = ev[i].v, w = ev[i].w;
			w -= inv[v];
			u = idx[u];
			v = idx[v];
			if(u != v){
				eev.pb(edge(u, v, w));
				continue;
			}
		}
		n = tn;
		rt = idx[rt];
		ev = eev;
	}
	return res;
}

struct FoxTheLinguist{
	int minimalHours(int nn, vector<string> courseInfo){
		//利用题目给出的条件建图.
		S = ++n;
		FOR(i, 0, nn) REP(j, 0, 9) ind[i][j] = ++n;
		FOR(i, 0, nn) REP(j, 1, 9) adde(ind[i][j], ind[i][j - 1], 0);
		FOR(i, 0, nn) adde(S, ind[i][0], 0);
		m = courseInfo.size();
		iss = "";
		FOR(i, 0, m) iss = iss + courseInfo[i];
		m = iss.size();
		FOR(i, 0, m){
			int j = i;
			while(j < m && iss[j] != ' ') ++j;
			int uid = ind[iss[i] - 'A'][iss[i + 1] - '0'];
			i += 4;
			int vid = ind[iss[i] - 'A'][iss[i + 1] - '0'];
			i += 3;
			int wid = (iss[i] - 48) * 1000 + (iss[i + 1] - 48) * 100 + (iss[i + 2] - 48) * 10 + iss[i + 3] - 48;
			adde(uid, vid, wid);
			i = j;
		}
		//用朱-刘算法计算最小树形图.
		return solve(S);
	}
} stu;

int main(){
	return 0;
}