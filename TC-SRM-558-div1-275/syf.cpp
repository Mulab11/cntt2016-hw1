//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include <string>
#include <iostream>
using namespace std;

#define oo 1000000000

class Stamp {
public:
  int getMinimumCost(string desiredColor, int stampCost, int pushCost) {
	int N = desiredColor.size();
	int cost[N+1];
	int a[N];
	//convert character to int for convenience
	for (int i = 0; i < N; i++) {
		char c = desiredColor[i];
		if (c == '*') a[i] = 7;
		if (c == 'R') a[i] = 1;
		if (c == 'G') a[i] = 2;
		if (c == 'B') a[i] = 4;
	}

	int res = oo;
	//try all the posibility of length of the stamp
    for (int len = 1; len <= N; len ++) {
    	cost[0] = 0;
    	//dynamic program for the minimum cost
    	for (int i = 1; i <= N; i++) cost[i] = oo;

    	for (int i = 0; i < N; i++) {
 			//with each position i, we try to paint until the furthest position j as long as we can use just 1 color
    		int color = 7;
    		for (int j = i; j < N; j++) {
    			color &= a[j];
    			if (!color) break;
    			int seg = j - i + 1;
    			if (seg < len) continue;
                        if(cost[i] != oo)
                        {
    			cost[j + 1] = min(cost[j + 1], cost[i] + ((seg + len - 1) / len) * pushCost);
                        }
    		}
    	}
        if(cost[N] != oo)
        {
    	res = min(res, cost[N] + stampCost * len);
        }
    }

    return res;
  }
};