#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
typedef long long int LL;

class SparseFactorial{
	public:
		void solve(int p, int c, int s, vector <LL> &res){ //Construct answer for s=p^c in res
			int i, j, k, modv; LL K;
			res.clear(); res.resize(s);
			for(k = 0; k < p * c; ++ k){
				K = LL(k) * k, modv = K % s;
				for(i = K % p; i < s; i += p){ //Enumerate all suitable i for k^2
					if(res[i] > 0) continue;
					j = (i - modv + s) % s;
					if(j == 0) res[i] = -c; //Calculate the number of p in i-k^2
					else while(j % p == 0)
						j /= p, -- res[i];
					if(res[i] <= -c) res[i] = K + 1;
				}
			}
			for(i = 0; i < s; ++ i)
				if(res[i] <= 0LL) res[i] = 1e13;
		}
		LL getCount(LL l, LL r, LL m){
			int m_ = m, i, j, p, s, c, cur;
			LL ret = 0LL, low;
			vector <LL> ans[3];
			ans[0].push_back(0);
			for(i = 2, cur = 1; m_ != 1; ++ i)
				if(m_ % i == 0LL){
					for(p = s = i, c = 1, m_ /= i; m_ % i == 0; ++ c, m_ /= i, s *= i);
					solve(p, c, s, ans[1]); //Solve the problem for every separate p^c
					ans[2].resize(cur * s);
					for(j = 0; j < cur * s; ++ j)
						ans[2][j] = max(ans[0][j % cur], ans[1][j % s]); //Merge the answer
					ans[0].swap(ans[2]), cur *= s;
				}
			for(i = 0, -- l; i < m; ++ i){
				low = ans[0][i] / m * m + i;
				if(low < ans[0][i]) low += m;
				if(r >= low) ret += (r - low) / m + 1;
				if(l >= low) ret -= (l - low) / m + 1;
			} return ret;
		}
};
int main(){
}
