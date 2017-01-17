#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007,N = 1000000+10;

class TrafficCongestion {
	public:
		int f[N];
		int theMinCars(int treeHeight) {
			f[0] = 1;f[1] = 1;
			for (int i = 2;i <= treeHeight;i++)
				f[i] = add(add(f[i-1],f[i-2]),f[i-2]);		
			return f[treeHeight];
		}
		int add(int x,int y){
			x += y;
			while (x >= mod) x-= mod;
			return x;
		}
};
