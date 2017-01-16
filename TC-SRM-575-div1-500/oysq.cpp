#line 2 "TheSwapsDivOne.cpp"  
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

int n;
std::string s;

double a[2][2];

void mult(double a[2][2], double b[2][2]) {
	double c[2][2] = {0};
	for(int k = 0; k < 2; ++k)
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				c[i][j] += a[i][k] * b[k][j];
	memcpy(a, c, sizeof c);
}

class TheSwapsDivOne {  
public:  
	double find(vector <string> sequence, int k) {  
		s.clear();
		for(int i = 0; i < SZ(sequence); ++i) s += sequence[i];
		n = SZ(s);
		double pr = n * (n - 1) / 2;
		// pr 表示总对数
		// 矩阵乘法求出f, g
		// f 表示从i经过k次操作到j的概率(i != j)
		// g 表示从i经过k次操作到i的概率
		a[0][0] = 1 - 1 / pr, a[0][1] = (n - 1) / pr;
		a[1][0] = 1 / pr, a[1][1] = 1 - (n - 1) / pr;
		double r[2][2] = {{1, 0}, {0, 1}};
		while(k) {
			if(k & 1) mult(r, a);
			mult(a, a), k >>= 1;
		}
		double f = r[1][0], g = r[1][1], ret = 0, pr2 = n * (n + 1) / 2;
		// pr2 表示总序列数
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) {// 枚举每个元素的最后位置计算贡献
				double p = (j + 1) * (n - j) / pr2;
				if(i != j) ret += p * (s[i] - '0') * f;
				else ret += p * (s[i] - '0') * g;
			}
		return ret;
	}  	  
};  
