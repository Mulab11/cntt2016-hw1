#include <bits/stdc++.h>

using namespace std;

class KnightCircuit2
{
public:
	int maxSize(int w, int h)
	{
		if (w > h) swap(w,h);
		if (w == 1) return 1;
		if (w == 2) return (h + 1) / 2;
		if (w == 3 && h == 3) return 8;
		//w = 3,h=4就能全部走完
		return w * h; //假如一个状态能走完，那么多加一行或一列都是可以走完的。
	}
};
