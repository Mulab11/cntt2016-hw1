#line 2 "UnknownTree.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define son e[i].t
#define oo 0x3f3f3f3f
#define maxn 60
#define mo 1000000009ll
#define vi vector<int>
#define it map<int, vi> :: iterator
using namespace std;
map<int, vi> _A, _B, _C, D;
int calc(vi a, bool rt)
{
	if (rt) a.pb(0); // 已有落脚点
	int n = a.size(), ret = 1, j;
	sort(a.begin(), a.end());
	if (a[0] == 0 && n <= 1) return 1; // 只有一个点且是个落脚点
	if (a[0] != 0 || a[1] == 0) return 0; // 没有落脚点或者出现多个落脚点
	for (int i = 1; i < n; ++ i){
		j = lower_bound(a.begin(), a.end(), a[i]) - a.begin(); // 每个点,可以直接长在落脚点上,也可以长在某个离落脚点比它更近的点上
		ret = 1ll * ret * j % mo;
	}
	return ret;
}
bool b[maxn]; // b[i] = 1表示i点在M - R上,否则在L - M上
int solve(int mid, int del, vi L, vi M, vi R) // 计算L - M = mid, M - R = del,且点i到L/M/R的距离分别是L[i],M[i],R[i]时的答案个数
{
	D.clear(); // 下标存所有点在链L - R上的落脚点,D[i]里存所有落脚点位于位置i的点,它们到位置i的距离
	int len = mid + del, ret = 1, dep, pos, n = L.size(); // len为L - R长度
	if (mid <= 0 || del <= 0) return 0;
	for (int i = 0; i < n; ++ i){
		dep = L[i] + R[i] - len; /
		if (dep % 2) return 0;
		dep /= 2; pos = L[i] - dep; // dep是点到其落脚点的距离,pos是落脚点到L的距离
		if (M[i] != dep + abs(pos - mid)) return 0; // 验证
		if (dep < 0 || pos < 0 || pos > len || (b[i] && pos < mid) || (! b[i] && pos > mid) || (i == 0 && ! b[i] && pos == mid)) return 0; // 判断合法性.最后一条是为了防止重复计算0长在M上的情况
		D[pos].pb(dep);
	}
	bool rt;
	for (it i = D.begin(); i != D.end(); ++ i){
		rt = ((i -> fr) == 0 || (i -> fr) == len || (i -> fr) == mid); // rt = 1表示这个落脚点已经有了(是L/M/R)
		ret = 1ll * ret * calc(i -> sc, rt) % mo; // 乘上这个落脚点的方案数
	}
	return ret;
}
int chain(vi L, vi M, vi R, bool fir) // 考虑三个关键点位于一条链上的情况,L存储点到左边的关键点的距离,M存点到中间的关键点的距离,R存点到右边的关键点的距离.fir = 1表示0号点在M - R上
{
	int n = L.size(), mid = 0, del = 0, ret = 0; // mid表示L - M的距离,del表示M-R的距离.ret是该种情况的答案
	bool vmid = 0, vdel = 0; // vmid表示mid的大小是否能被确定
	b[0] = fir; // b[i] = 1表示i点在M - R上,否则在L - M上
	if (! fir){
		del = R[0] - M[0]; vdel = 1; // 0在L - M上,可以算出M - R的距离
		for (int i = 1; i < n; ++ i)
			if (R[i] - M[i] == del) b[i] = 0; else b[i] = 1, mid = L[i] - M[i], vmid = 1; // i在L - M上 等价于 R[i] - M[i] == del.若不在,则可以确定L - M的距离
		for (int i = 1; i < n; ++ i) 
			if (b[i] && L[i] - M[i] != mid) return 0; // 验证是否合法
	}else{ // 同理
		mid = L[0] - M[0]; vmid = 1;
		for (int i = 1; i < n; ++ i)
			if (L[i] - M[i] == mid) b[i] = 1; else b[i] = 0, del = R[i] - M[i], vdel = 1;
		for (int i = 1; i < n; ++ i)
			if (! b[i] && R[i] - M[i] != del) return 0;
	}
	int del2 = -1, mid2 = -1;
	if (! vdel){ // 所有的点都在M - R上
		del = oo; for (int i = 0; i < n; ++ i) del = min(del, M[i] + R[i]); // 一种情况是,存在点位于M - R之间的链上,此时min(M[i] + R[i])就是M - R长度
		bool flag = 1; int tmp = abs(M[0] - R[0]); for (int i = 1; i < n; ++ i) if (abs(M[i] - R[i]) != tmp) flag = 0; // 另一种情况是,所有的点全都长在R上或者M上,M - R = abs(M[i] - R[i]) 
		if (flag && abs(tmp) > 0){ del2 = abs(tmp); ret = (ret + solve(mid, del2, L, M, R)) % mo;}
	}
	if (! vmid){ // 所有的点都在L - M上,同理
		mid = oo; for (int i = 0; i < n; ++ i) mid = min(mid, L[i] + M[i]);
		bool flag = 1; int tmp = abs(L[0] - M[0]); for (int i = 1; i < n; ++ i) if (abs(L[i] - M[i]) != tmp) flag = 0;
		if (flag && abs(tmp) > 0){ mid2 = abs(tmp); ret = (ret + solve(mid2, del, L, M, R)) % mo;}
	}
	ret = (ret + solve(mid, del, L, M, R)) % mo; // 处理普通的情况
	return ret;
}
int Y(vi A, vi B, vi C, int c) // 计算三个点形成一个Y字的情况,c是枚举出的Y字中心点
{
	int n = A.size(), lenA = A[c], lenB = B[c], lenC = C[c], ret = 1; // lenA表示c - A的距离
	_A.clear(); _B.clear(); _C.clear(); D.clear(); // _A存长在c - A上的点的信息(落脚点+悬挂长度)
	int tmp, dis1, dis2, dep, pos;
	for (int i = 0; i < n; ++ i){
		tmp = (A[i] - B[i] == lenA - lenB) + (A[i] - C[i] == lenA - lenC) + (B[i] - C[i] == lenB - lenC); // 第一个式子为真,表示这个点长在c - C上
		if (tmp != 1 && tmp != 3) return 0; // tmp = 1,表示它就在某个分支上,tmp = 3,表示它长在c上.其它的情况不合法
		if (tmp == 3){
			dep = A[i] - lenA; if (dep < 0) return 0;
			D[0].pb(dep); // 存长在c上的点的dep
		}else{
			if (A[i] - B[i] == lenA - lenB){ // 长在c - C上
				dis1 = (A[i] + B[i] - lenA - lenB); 
				if (dis1 % 2) return 0; else dis1 /= 2; // dis1为它到c的距离
				dep = dis1 + C[i] - lenC; 
				if (dep % 2) return 0; else dep /= 2; // dep为它到落脚点的距离
				pos = dis1 - dep; if (dep < 0 || pos < 0 || pos > lenC) return 0; // 落脚点位置为pos
				_C[pos].pb(dep);
			}
			if (A[i] - C[i] == lenA - lenC){
				dis1 = (A[i] + C[i] - lenA - lenC); 
				if (dis1 % 2) return 0; else dis1 /= 2;
				dep = dis1 + B[i] - lenB; 
				if (dep % 2) return 0; else dep /= 2;
				pos = dis1 - dep; if (dep < 0 || pos < 0 || pos > lenB) return 0;
				_B[pos].pb(dep);
			}
			if (B[i] - C[i] == lenB - lenC){
				dis1 = (B[i] + C[i] - lenB - lenC); 
				if (dis1 % 2) return 0; else dis1 /= 2;
				dep = dis1 + A[i] - lenA; 
				if (dep % 2) return 0; else dep /= 2;
				pos = dis1 - dep; if (dep < 0 || pos < 0 || pos > lenA) return 0;
				_A[pos].pb(dep);
			}
		}
	}
	bool rt;
	for (it i = D.begin(); i != D.end(); ++ i) ret = 1ll * ret * calc(i -> sc, rt) % mo; // 长在c上的点的方案数
	for (it i = _A.begin(); i != _A.end(); ++ i) ret = 1ll * ret * calc(i -> sc, (i -> fr == lenA)) % mo; // 长在c - C上的点的方案数
	for (it i = _B.begin(); i != _B.end(); ++ i) ret = 1ll * ret * calc(i -> sc, (i -> fr == lenB)) % mo;
	for (it i = _C.begin(); i != _C.end(); ++ i) ret = 1ll * ret * calc(i -> sc, (i -> fr == lenC)) % mo;
	return ret;
}
class UnknownTree
{
	public:
		int getCount(vector <int> A, vector <int> B, vector <int> C)
		{
			int n = A.size(), ret = 0, t;
			for (int i = 0; i <= 1; ++ i){
				ret = (ret + chain(A, B, C, i)) % mo; // 链的情况:枚举中间点 + 枚举0号点的位置
				ret = (ret + chain(A, C, B, i)) % mo;
				ret = (ret + chain(B, A, C, i)) % mo; 
			}
			for (int i = 0; i < n; ++ i) ret = (ret + Y(A, B, C, i)) % mo; // Y的情况:枚举中心点
			return ret;
		}
};
