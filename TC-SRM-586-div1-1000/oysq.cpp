#line 2 "StringWeight.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;
const int S = 26;
const int INF = 0x3f3f3f3f;

int f[N + 1][S + 1][S + 1];
// f[i][u][v] 表示前i个串，已经用了u种字母，其中还有v种字母可以用

class StringWeight {  
public:  
	int getMinimum(vector <int> L) {  
		memset(f, INF, sizeof f);
		f[0][0][0] = 0;
		int n = SZ(L), pre = 0, suf = 0;
		for(int i = 0; i < n; ++i) {
			suf += L[i];
			int k = std::min(26, L[i]);// 当前串用的字母种数
			for(int u = 0; u <= S; ++u)
				for(int v = 0; v <= u; ++v)
					if(f[i][u][v] < INF) {
						int val = f[i][u][v];
						for(int a = 0; a + u <= S && a <= k; ++a)// 枚举只在当前串出现的字母
							for(int b = 0; a + b + u <= S && a + b <= k; ++b)// 枚举在当前串第一次出现但不只在这里出现的字母
								for(int c = 0; c <= v && a + b + c <= k; ++c) {// 枚举在当前串最后一次出现但不知在这里出现的字母
									int d = k - a - b - c;// 既不是第一次出现也不是最后一次出现的字母数
									if(d <= v - c) {
										// 根据贪心的原理，c要尽量放前面，b要尽量放后面
										// 因为d是不计代价的，因此尽量用d，将a尽量压缩长度
										if(d) chkmin(f[i + 1][a + b + u][v + b - c], val - (2 * suf - b + 1) * b / 2 + (2 * pre + c + 1) * c / 2);
										else chkmin(f[i + 1][a + b + u][v + b - c], val - (2 * suf - b + 1) * b / 2 + (2 * pre + c + 1) * c / 2 + L[i] - a - b - c);
									}
								}
					}
			pre += L[i];
		}
		int ans = INF;
		for(int i = 0; i <= S; ++i) chkmin(ans, f[n][i][0]);// 统计答案
		return ans;
	}    
};  
#line 2 "StringWeight.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;
const int S = 26;
const int INF = 0x3f3f3f3f;

int f[N + 1][S + 1][S + 1];
// f[i][u][v] 表示前i个串，已经用了u种字母，其中还有v种字母可以用

class StringWeight {  
public:  
	int getMinimum(vector <int> L) {  
		memset(f, INF, sizeof f);
		f[0][0][0] = 0;
		int n = SZ(L), pre = 0, suf = 0;
		for(int i = 0; i < n; ++i) {
			suf += L[i];
			int k = std::min(26, L[i]);// 当前串用的字母种数
			for(int u = 0; u <= S; ++u)
				for(int v = 0; v <= u; ++v)
					if(f[i][u][v] < INF) {
						int val = f[i][u][v];
						for(int a = 0; a + u <= S && a <= k; ++a)// 枚举只在当前串出现的字母
							for(int b = 0; a + b + u <= S && a + b <= k; ++b)// 枚举在当前串第一次出现但不只在这里出现的字母
								for(int c = 0; c <= v && a + b + c <= k; ++c) {// 枚举在当前串最后一次出现但不知在这里出现的字母
									int d = k - a - b - c;// 既不是第一次出现也不是最后一次出现的字母数
									if(d <= v - c) {
										// 根据贪心的原理，c要尽量放前面，b要尽量放后面
										// 因为d是不计代价的，因此尽量用d，将a尽量压缩长度
										if(d) chkmin(f[i + 1][a + b + u][v + b - c], val - (2 * suf - b + 1) * b / 2 + (2 * pre + c + 1) * c / 2);
										else chkmin(f[i + 1][a + b + u][v + b - c], val - (2 * suf - b + 1) * b / 2 + (2 * pre + c + 1) * c / 2 + L[i] - a - b - c);
									}
								}
					}
			pre += L[i];
		}
		int ans = INF;
		for(int i = 0; i <= S; ++i) chkmin(ans, f[n][i][0]);// 统计答案
		return ans;
	}    
};  
