#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

class AlternateColors2{
public:
	LL countWays(int n, int m){
		int i, n_, m_; LL ans = 0LL;
		for(i = 0; i <= n / 3; ++ i){
			//Minimum as red
			if(i != 0 && m <= i * 3 && m % 3 == 1)
				ans += n - 3 * i + 1;
			//Minimum as green or blue
			if(m <= i * 3){
				if(m % 3 == 1)
					ans += (n - 3 * i) * 2;
			}else{
				m_ = m - 3 * i, n_ = n - 3 * i;
				if(m_ & 1) ans += max(0, (2 * n_ - m_) / 2 - (m_ - 1) / 2) * 2;
				ans += (min((m_ - 1) / 2, (n_ - 1) / 2) + 1) * 2;
				//m -= 3 * i
				//r >= 1, r >= m / 2, r <= n_ - m_ / 2
				//m_ / 2 > b, n_ / 2 > b
			}
			if(i * 3 != n && ((m > i * 3) || (m % 3 == 1)))
				-- ans;
		} return ans;
	}
};
