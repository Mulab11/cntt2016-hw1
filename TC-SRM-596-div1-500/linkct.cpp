#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long int LL;

class BitwiseAnd{
	public:
		vector <LL> lexSmallest(vector <LL> subs, int n){
			vector <LL> emp, ans = subs;
			ans.resize(n);
			int m = subs.size(), i, j, k;
			bool used[65]; LL v;
			memset(used, false, sizeof(used));
			for(i = 0; i < m; ++ i){
				for(k = 0; k < 60; ++ k)
					if(subs[i] & (1LL << k)) //Mark all bits occupied by elements in subs
						used[k] = true;
				for(j = i + 1; j < m; ++ j){
					if((subs[i] & subs[j]) == 0LL)
						return emp;
					for(k = j + 1; k < m; ++ k)
						if(subs[i] & subs[j] & subs[k])  //Check whether the given subset is erroneous
							return emp;
				}
			}
			for(i = 0; i < m; ++ i)
				for(j = i + 1; j < m; ++ j){
					v = subs[i] & subs[j];
					subs[i] ^= v, subs[j] ^= v;
				}
			for(i = 1; i <= n - m; ++ i){
				for(j = 0; j < m; ++ j){
					//Find a suitable bit between the new element and an existing element
					if(!subs[j]) return emp;
					for(k = 0; !(subs[j] & (1LL << k)); ++ k) ;
					subs[j] ^= 1LL << k, ans[m + i - 1] |= 1LL << k;
				}
				for(j = i + 1; j <= n - m; ++ j){
					//Find a suitable bit between two new elements
					for(k = 0; k < 60; ++ k)
						if(!used[k]) break;
					if(k == 60) return emp;
					used[k] = true;
					ans[m + i - 1] |= 1LL << k;
					ans[m + j - 1] |= 1LL << k;
				}
			} sort(ans.begin(), ans.end());
			return ans;
		}
};

int main(){
	return 0;
}
