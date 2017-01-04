#include <bits/stdc++.h>

using namespace std;

const int mo = int(1e9) + 7;

int f[55][2];

class DefectiveAddition
{
public:
	int count(vector <int> cards, int n)
	{
		int m = cards.size();
		for(int i = 0;i < m;i ++)
			if (cards[i] > cards[0]) swap(cards[0],cards[i]);
		if (!cards[0])
			return n == 0;
		int bit;
		for(bit = 1;bit * 2 <= cards[0];bit <<= 1); //最高位为bit
		if (n >= (bit << 1)) return 0;
		memset(f,0,sizeof f);
		f[1][0] = 1;
		//假设最大的数最高位选0，其他数要满足最高位的异或等于n的这一位
		for(int i = 1;i < m;i ++)
			for(int od = 0;od < 2;od ++)
			{
				f[i + 1][od] = (f[i + 1][od] + f[i][od] * 1ll * (min(cards[i],bit - 1) + 1)) % mo; //最高位为i为0
				if (cards[i] >= bit)
					f[i + 1][od ^ 1] = (f[i + 1][od ^ 1] + f[i][od] * 1ll * (cards[i] - bit + 1)) % mo;//最高位为1
			}
		int ans = 0;
		if (n & bit) ans = f[m][1]; else ans = f[m][0];
		cards[0] -= bit;
		n ^= bit;
		//最高位选1
		ans = (ans + count(cards,n)) % mo;
		return ans;
	}
};
