#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define maxn 1010
typedef long long ll;
using namespace std;
int c[maxn], cnt; // cnt表示A的不同质因子个数，c[i]保存第i个质因子的出现次数
void deprime(int n) {
	cnt = 0;
	for (int i = 2; i * i <= n; ++i) 
		if (n % i == 0) {
			c[++cnt] = 0;
			while (n % i == 0) {
				++c[cnt]; n /= i;
			}
		}
	if (n > 1) c[++cnt] = 1;
}
class BigFatInteger {
	public:
		int minOperations(int A, int B) {
			int ret = 0, mx = 0;
			deprime(A); // 将A分解质因数
			ret += cnt; // 需要cnt次第一种操作,乘入所有出现过的质因子
			for (int i = 1; i <= cnt; ++i) 
				mx = max(mx, int(ceil(log2(c[i] * B)))); // 第二种操作的次数，由出现次数最多的质因子出现的次数决定
			ret += mx;
			return ret;
		}
};
