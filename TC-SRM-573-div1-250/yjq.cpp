#include <bits/stdc++.h>

using namespace std;

class TeamContest {
		public:
				int worstRank(vector<int> info) {
						int sum = min(min(info[0], info[1]), info[2]) + max(max(info[0], info[1]), info[2]);

						int ans = 0, tmp = 0 ; 

						int l = 3, r = info.size() - 1; 

						sort(info.data() + l, info.data() + r + 1);
						while(l < r) {
								while(l + 1 < r && info[l] + info[r] <= sum) l ++, tmp ++;
								tmp = min(tmp, ans) ;
							    if (r - 1 == l) break ; 	
								if(ans >= tmp + r - l - 1) break;
								ans ++ ;
								l ++, r -- ; 
						}
						return ++ ans ; 
				}
} ; 
