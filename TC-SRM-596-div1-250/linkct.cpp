#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

inline int getSize(int x){ //Get the number of doubling operations required
	int ret = 0;
	while(x) x >>= 1, ++ ret;
	return ret ? (ret - 1) : 0;
}
class IncrementAndDoubling{
	public:
		int getMin(vector <int> arr){
			int i, mx = 0, ans = 0;
			for(i = 0; i < int(arr.size()); ++ i){
				mx = max(mx, arr[i]);
				ans += __builtin_popcount(arr[i]); //Summing up 1s in all elements
			} return ans + getSize(mx);
		}
};
int main(){
	return 0;
}
