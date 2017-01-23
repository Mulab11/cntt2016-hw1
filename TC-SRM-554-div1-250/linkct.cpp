#include <bits/stdc++.h>
using namespace std;

class TheBrickTowerEasyDivOne{
public:
	int find(int rc, int rh, int bc, int bh){
		return min(rc, bc) * (2 + int(rh != bh)) + int(rc != bc);
	}
};
