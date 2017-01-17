#include <bits/stdc++.h>

using namespace std;

class TheSquareRootDilemma{
	public:	
		bool bo[88888];
		int prime[88888],len,val[88888];
		int ans,a[88888];
		int countPairs(int N, int M){
			memset(a,0,sizeof(a));ans = 0;
			for (int i = 1;i*i <= 77777;i++)
				a[i*i] = 1;
			for (int i = 1;i <= 77777;i++) a[i] += a[i-1];
			make_prime(N);
			for (int i = 1;i <= N;i++)
				ans += a[M/val[i]];
			return ans;
		}
		void make_prime(int p){
			val[1] = 1;len = 0;
			memset(prime,0,sizeof(prime));
			memset(bo,0,sizeof(bo));
			for (int i = 2;i <= p;i++){
				if (bo[i] == 0) {prime[++len] = i;val[i] = i;}
				for (int j = 1;i*prime[j] <= p;j++){
					bo[i*prime[j]] = 1;
					if (val[i] % prime[j] == 0) 
						val[i*prime[j]] = val[i]/prime[j];
					else 
						val[i*prime[j]] =val[i]*prime[j];  
					if (i % prime[j] == 0) break;
				}
			}
		}
};
