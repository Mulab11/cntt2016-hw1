/*
	Greedy.
	If we can't gain all the steps, then give up in the first turn.
*/

#include <bits/stdc++.h>
using namespace std;

class JumpFurther {
	public:
	int furthest(int N, int badStep) {
		int ret = 0;
		for (int i = 1; i <= N; ++i) ((ret += i) == badStep) && --ret;
		return ret;
	}
};

/*
	Aimai ni shitai nosa
	Kirai ni natte shimaetara seikou
	Baibai wo shitai nosa
	Boku de itatte tanoshiku nainda
		- Streaming heart
*/
