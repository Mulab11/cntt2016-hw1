#include <bits/stdc++.h>
using namespace std;

class TheSquareRootDilemma{
public:
	int countPairs(int n, int m){
		int i, j, ans = 0; bool hasSquare[80005];
		memset(hasSquare, false, sizeof(hasSquare));
		if(n > m) swap(n, m);
		for(i = 2; i <= n / i; ++ i)
			for(j = i; j <= n; j += i)
				hasSquare[j] = true; //Label all numbers containing square factor
		for(i = 1; i <= n; ++ i)
			if(!hasSquare[i])
				ans += int(sqrt(n / i * 1.0) + 1e-8) * int(sqrt(m / i * 1.0) + 1e-8);
		return ans;
	}
};
