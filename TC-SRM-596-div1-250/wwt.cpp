#include <bits/stdc++.h>

using namespace std;

class IncrementAndDoubling
{
public:
	int getMin(vector<int> desiredArray)
	{
		//假设数组中只有一个数，那么显然最后ans=2^a+2^b+...这样的形式，那么最小代价就是最高位+1的个数
		//同理，假如一个数组有多个数，那么要*2的次数就是所有数最高位的max，+1的次数就是总共1的个数
		int a = 0,b = 0;
		for(auto p : desiredArray)
		{
			int cr = 0;
			for(;p;p /= 2,++ cr)
				b += (p & 1);
			a = max(a,cr - 1);
		}
		return a + b;
	}
};
