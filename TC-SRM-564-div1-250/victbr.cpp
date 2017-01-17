#include <bits/stdc++.h>

using namespace std;

class KnightCircuit2{
	public:
		int maxSize(int w, int h){
			if (w >= 3 && h >= 4) return w*h;
			if (w >= 4 && h >= 3) return w*h;
			if (w == 3 && h == 3) return 8;
			if (w == 1 || h == 1) return 1;
			if (w == 2) return h+1>>1;
			return w+1>>1;
		}
};
