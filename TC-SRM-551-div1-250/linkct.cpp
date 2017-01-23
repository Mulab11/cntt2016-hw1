#include <cstdio>
#include <string>
#include <vector>
using namespace std;
const int SIGMA = 26;

class ColorfulChocolates{
	public:
		inline int f(int x){return x * (x + 1) / 2;}
		int maximumSpread(string str, int maxSwap){
			int i, j, k, mid, sum, ans = 0;
			vector <int> pos[SIGMA];
			for(i = 0; i < int(str.length()); ++ i)
				pos[str[i] - 'A'].push_back(i);
			for(i = 0; i < SIGMA; ++ i){
				if(pos[i].empty()) continue;
				for(j = k = mid = 0, sum = pos[i][0]; j < int(pos[i].size()); ++ j){
					if(mid - j < k - mid) sum -= 2 * pos[i][mid ++];
					for(; k + 1 < int(pos[i].size()); ++ k){
						sum += pos[i][k + 1];
						if(mid - j < k + 1 - mid)
							sum -= 2 * pos[i][mid ++];
						if(sum - (((k - j) & 1) * pos[i][mid]) - f(mid - j) - f(k + 1 - mid) > maxSwap){
							sum -= pos[i][k + 1];
							if((mid - j) - (k - mid) > 1)
								sum += 2 * pos[i][-- mid];
							break;
						}
					} ans = max(ans, k - j + 1);
					if(j == k) sum -= pos[i][j], ++ mid;
					else sum += pos[i][j];
				}
			} return ans;
		}
};
