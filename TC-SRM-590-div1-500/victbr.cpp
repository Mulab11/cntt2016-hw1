#include <bits/stdc++.h>

using namespace std;

class XorCards{
	public:
		int n,b[60],len;
		long long f[60],pwer2[60],a[60],ans;
		long long numberOfWays(vector<long long> number, long long limit){
			
			n = number.size();ans = 0;
			for (int i = 1;i <= n;i++) a[i] = number[i-1]; 			
			pwer2[0] = 1;for (int i = 1;i <= 50;i++) pwer2[i] = pwer2[i-1]<<1;
			
			len = 0;
			while (limit){
				b[++len] = limit&1;
				limit>>=1;
			}
			while (len < 50) b[++len] = 0;//不足50为补至50位。
			for (int i = len;i >= 1;i--)
				if (b[i] == 1) Gauss(i);
			Gauss(0);
			
			return ans;
		}
		void Gauss(int p){//高斯消元
        //p==0时，计算等于m的方案数，p!=0时计算小于m的方案数。
			for (int i = len;i > p;i--){
				f[len-i+1] = 0;long long u = (long long)1<<i>>1;
				for (int j = 1;j <= n;j++){
					f[len-i+1] <<= 1;
					if (a[j]&u) f[len-i+1] |= 1;
				}
				f[len-i+1] <<= 1;f[len-i+1] |= b[i];
			}
			
			if (p){
				f[len-p+1] = 0;long long u = (long long)1<<p>>1;
				for (int j = 1;j <= n;j++){
					f[len-p+1] <<= 1;
					if (a[j]&u) f[len-p+1] |= 1;
				}
				f[len-p+1] <<= 1;
			}
			else p = 1; 
			
			int last = 1;
			for (int i = n;i >= 1;i--){
				long long u = (long long)1<<i;
				
				for (int j = last;j <= len-p+1;j++) 
					if (f[j]&u){
						swap(f[j],f[last]);
						break;
					}
				if (f[last]&u){
					for (int j = 1;j <= len-p+1;j++) 
						if ((f[j]&u) && (j != last)) {					
							f[j] ^= f[last];
						}
					last++;
				}
			}
			for (int i = 1;i <= len-p+1;i++) if (f[i] == (long long)1) return;//判断是否无解
			ans += pwer2[n-last+1];//last-1为非自由元个数，所以有n-last+1个自由元
		}		
};
