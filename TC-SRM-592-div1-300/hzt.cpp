#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#define Rep(i, x, y) for (int i = x; i <= y; i ++)
#define Dwn(i, x, y) for (int i = x; i >= y; i --)
#define RepE(i, x) for(int i = pos[x]; i; i = g[i].nex)
using namespace std;
typedef long long ll;
typedef double db;
int num[300];
class LittleElephantAndBalls {
public:
	int getNumber(string s) {
		int n = s.size(), ans = 0, k = 0;
		Rep(i, 0, n - 1) {
			ans += k;
			num[ s[i] ] ++;
			k += (num[ s[i] ] <= 2); // k代表当前加入小球可获得的分数
		}
		return ans;
	}
};
