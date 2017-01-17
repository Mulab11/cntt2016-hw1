#include <bits/stdc++.h>

using namespace std;

class TheBrickTowerEasyDivOne{
	public:
        int find(int rc, int rh, int bc, int bh){
        	int ans = min(rc,bc);
        	if (bh != rh){
        		if (rc != bc) return ans*3+1;
        		else return ans*3;
			}
			else{
				if (rc != bc) return ans*2+1;
				return ans*2;
			}
		}
};
