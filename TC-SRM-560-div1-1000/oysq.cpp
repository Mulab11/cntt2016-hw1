#line 2 "BoundedOptimization.cpp"  
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

const int N = 13;

int n, maxs;
int a[N + 9][N + 9];// a[i][j] = 1 表示存在 i * j
vector<int> p[3], lb, ub;
// p[0] 表示未确定的变量
// p[1] 表示等于下界的变量
// p[2] 表示等于上界的变量
double b[N + 9], x[N + 9];
// b[i] 表示已经确定的变量对未确定的第i个变量的系数的贡献
// x[i] 表示第i个变量的值
double ans;

void dfs(int id) {
	if(id == n) {
		for(int i = 0; i < SZ(p[0]); ++i)
			for(int j = i + 1; j < SZ(p[0]); ++j)
				if(!a[p[0][i]][p[0][j]])
					return ;// 未确定的变量之间的a[i][j]都要为1
		double sum = 0;
		for(int i = 0; i < SZ(p[1]); ++i) x[p[1][i]] = lb[p[1][i]], sum += lb[p[1][i]];// 等于下界的变量
		for(int i = 0; i < SZ(p[2]); ++i) x[p[2][i]] = ub[p[2][i]], sum += ub[p[2][i]];// 等于上界的变量
		for(int i = 0; i < SZ(p[0]); ++i) {
			b[i] = 0;
			for(int j = 0; j < SZ(p[1]); ++j)
				b[i] += a[p[0][i]][p[1][j]] * x[p[1][j]];// 等于上界的变量对第i个未确定变量的贡献
			for(int j = 0; j < SZ(p[2]); ++j)
				b[i] += a[p[0][i]][p[2][j]] * x[p[2][j]];// 等于下界的变量对第i个未确定变量的贡献
			sum += b[i] - b[0];// 第i个未确定的变量可以表示成x[p[0][i]] = x[p[0][0]] + b[i] - b[0]
		}
		if(sum > maxs) return ;
		if(SZ(p[0])) {// 以防除数为0
			x[p[0][0]] = (maxs - sum) / SZ(p[0]);
			for(int i = 1; i < SZ(p[0]); ++i) x[p[0][i]] = x[p[0][0]] + b[i] - b[0];// 求出未确定变量的值
			for(int i = 0; i < SZ(p[0]); ++i)
				if(x[p[0][i]] < lb[p[0][i]] || x[p[0][i]] > ub[p[0][i]])// 检测是否在上下界中
					return ;
		}
		double curans = 0;
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
				curans += a[i][j] * x[i] * x[j];// 统计当前方案的答案
		chkmax(ans, curans);// 更新全局答案
		return ;
	}
	for(int i = 0; i < 3; ++i) {
		p[i].pb(id);
		dfs(id + 1);
		p[i].pop_back();
	}
}

class BoundedOptimization {  
public:  
	double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum) {  
		memset(a, 0, sizeof a), ans = 0, lb = lowerBound, ub = upperBound, maxs = maxSum;
		std::string s;
		for(int i = 0; i < SZ(expr); ++i) s += expr[i];// 把expr拼起来
		for(int i = 0; i < SZ(s); ++i) {
			a[s[i] - 'a'][s[i + 1] - 'a']++;
			a[s[i + 1] - 'a'][s[i] - 'a']++;
			i += 2;
		}
		n = SZ(lb);
		int maxsum = 0;
		for(int i = 0; i < n; ++i) maxsum += ub[i];
		if(maxsum <= maxs) {// 当upperBound的和 <= maxSum时，显然只能把所有点取到上界
			for(int i = 0; i < n; ++i)
				for(int j = i + 1; j < n; ++j)
					ans += a[i][j] * ub[i] * ub[j];
			return ans;
		}
		dfs(0);
		return ans;
	}    
};  
