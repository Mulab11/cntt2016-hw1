#include <bits/stdc++.h>
using namespace std;
struct ColorfulChocolates {
  int maximumSpread(string, int);
};
int ColorfulChocolates::maximumSpread(string s, int swaps) {
	int n = s.size(), i, j, L, R, ans = 0;
	// 枚举聚在一起的颜色
	for (char c='A';c<='Z';c++) {
		int m = 0, p[55];
		// 拿出来
		for (i=0;i<n;i++)
		if (s[i] == c) p[m++] = i;
		// 枚举哪一段区间最后要并在一起
		for (L=0;L<n;L++)
		for (R=L;R<n;R++) {
			int len = R-L+1;
			if (len > m) break;
			// 移动的代价即坐标差的绝对值
			for (i=0;i<m-len+1;i++) {
				int aaa = 0;
				for (j=i;j<i+len;j++) aaa += abs(p[j]-(L+j-i));
				if (aaa <= swaps)
				if (len > ans) ans = len;
			}
		}
	}
	return ans;
}