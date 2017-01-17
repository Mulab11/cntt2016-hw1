#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


class BigFatInteger{
	public:
		int ans,cnt;
		int minOperations(int A, int B){
			int u = (int)sqrt(A);
			for (int i = 2;i <= u+1;i++){
				if (A%i == 0) cnt++;else continue;//i不是质因子时要跳过 
				ll v = 0,z = 1;
				int tot = 0;
				while (A%i == 0){
					v++;A /= i;
				}
				v *= B;
				while (z+z <= v){
					tot++;z <<= 1;
				}
				if (z != v) tot++;
				ans = max(ans,tot);
			}
			if (A != 1){//注意要处理最后一个质因子 
				cnt++;
				ll v = B,z = 1;
				int tot = 0;
				while (z+z <= v){
					tot++;z <<= 1;
				}
				if (z != v) tot++;
				ans = max(ans,tot);				
			}
			return ans+cnt;
		}
};
