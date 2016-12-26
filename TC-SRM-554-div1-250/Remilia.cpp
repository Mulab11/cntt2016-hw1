#include<bits/stdc++.h>

using namespace std;

struct TheBrickTowerEasyDivOne {
	int find(int rc, int rh, int bc, int bh) {
		if(rc==bc)
			if(rh==bh)return rc*2;
			else return rc*3;
		else
			if(rh==bh)return std::min(rc,bc)*2+1;
			else return std::min(rc,bc)*3+1;
	}
};