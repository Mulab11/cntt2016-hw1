#include <bits/stdc++.h>
using namespace std;

class JumpFurther{
public:
	int furthest(int n, int bad){
		int i, j;
		for(i = 1, j = 0; i <= n; ++ i)
			if((j += i) == bad) -- j;
		return j;
	}
};
