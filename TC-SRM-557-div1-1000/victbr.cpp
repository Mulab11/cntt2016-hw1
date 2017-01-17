/*
考虑高斯消元后从低位往高位还答案矩阵
显然，对于一个非自由元，最优解中当前位上一定只有1个0。
于是还原的过程确定。 
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

class XorAndSum{
	public:
		int n;
		long long maxSum(vector<long long> number){
			n = number.size();
			int p = 0;
			for (int i = 50;i >= 0;i--){
				ll u = 1;u <<= i;int k = -1;
				for (int j = p;j < n;j++)
					if (u & number[j]) {k = j;break;}
				if (k != -1){
					swap(number[k],number[p]);
					for (int j = 0;j < n;j++)
						if (p != j && (number[j] & u)) number[j] ^= number[p];
					p++;
				}
			}
			for (int i = 1;i < n;i++) number[0] ^= number[i];
			for (int i = 1;i < n;i++) number[i] ^= number[0];
			for (int i = 1;i < n;i++) number[0] += number[i];
			return number[0];
		}
}A;
