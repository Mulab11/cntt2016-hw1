#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class KnightCircuit2{
	public:
		int maxSize(int w, int h){
			if (w==1||h==1) return 1;
			if (w==2) return (h+1)/2;
			if (h==2) return (w+1)/2;
			if (h==3&&w==3) return 8;
			return h*w;
		}
};
