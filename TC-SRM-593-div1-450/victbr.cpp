#include <bits/stdc++.h>

using namespace std;
const int N = 1001000;

class MayTheBestPetWin{
	public:
		bool f[N];
		int n,sum1,sum2,ans;
		int calc(vector <int> A, vector <int> B){
			n = A.size();ans = 0x7fffffff;
			f[0] = 1;
			for (int i = 0;i < n;i++)
				for (int j = 900000;j >= 0;j--)
					f[j+A[i]+B[i]] |= f[j];
			for (int i = 0;i < n;i++){
				sum1 += A[i];
				sum2 += B[i];
			}
			for (int i = 0;i <= 1000000;i++)
				if (f[i]){
					ans = min(ans,max(sum2-i,i-sum1));
				}
			return ans;
		}
};
