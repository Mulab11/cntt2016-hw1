#include <cstdio>
#include <vector>
using namespace std;

class KingdomAndTrees{
	public:
		vector <int> h; int n;
		inline bool check(int limit){
			int i, last;
			for(i = last = 0; i < n; ++ i){
				if(h[i] <= last){ //Increase needed
					if(last + 1 - h[i] > limit) return false;
					++ last;
				}else last = max(last + 1, h[i] - limit); //Decrease needed
			} return true;
		}
		int minLevel(vector <int> h){
			n = h.size();
			int l = 0, r = 1000000000, mid;
			while(l < r){
				mid = (l + r) >> 1;
				this -> h = h;
				if(check(mid)) r = mid;
				else l = mid + 1;
			} return r;
		}
};
