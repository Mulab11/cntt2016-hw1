#include <bits/stdc++.h>
typedef long long int LL;
using namespace std;

class FoxPaintingBalls{
	LL theMax(LL R, LL G, LL B, int n){
		LL need = n * LL(n + 1) / 6, ret = min(min(R / need, G / need), B / need); //Approximately n*(n+1)/6 balls of each color are needed for a triangle
		if(n % 3 == 1) ret = min(ret, (R + G + B) / (3 * need + 1)); //Constraints of the extra ball
		return ret;
	}
};
