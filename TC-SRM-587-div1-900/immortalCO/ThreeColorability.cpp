#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

#define IL __inline__ __attribute__((always_inline))
#define RG register
vector<string> FAIL;
int B, p[60][60], P;
struct Bitset
{
	uint val[80];
	IL void set(RG int i) {val[i >> 5] |= 1 << (i & 31);}
	IL void flip(RG int i) {val[i >> 5] ^= 1 << (i & 31);}
	IL bool test(RG int i) {return (val[i >> 5] >> (i & 31)) % 2;}
	IL void copy(RG const Bitset& e)
	{
		memcpy(val, e.val, B << 2);
	}
	IL void clear()
	{
		memset(val, 0, B << 2);
	}
	IL void operator ^= (RG const Bitset& s)
	{
		for(RG int i = 0; i != B; ++i) val[i] ^= s.val[i];
	}
} G[2510], e;
bool have[2510];

// 动态高斯消元，添加方程
bool add()
{
	for(int i = 0; i != P; ++i) if(e.test(i))
	{
		if(!have[i]) {G[i].copy(e); return have[i] = 1;}
		e ^= G[i];
	}
	return !e.test(P);
}

class ThreeColorability
{
public:
	vector<string> lexSmallest(vector<string> inp)
	{
		// 似乎可以解一个异或方程组
		const int N = inp.size(), M = inp[0].size();
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != M; ++j)
				if(inp[i][j] == '?') p[i][j] = P++;
				else p[i][j] = (inp[i][j] == 'N' ? -1 : -2);
		B = P / 32 + 1;
		
		// 列方程，这里只有基本方程
		const int X[] = {-1, 0, -1, 0};
		const int Y[] = {-1, -1, 0, 0};
		for(int i = 1; i != N; ++i) for(int j = 1; j != M; ++j)
		{
			e.clear();
			for(int k = 0; k != 4; ++k)
			{
				const int x = i + X[k];
				const int y = j + Y[k];
				if(p[x][y] >= 0) e.set(p[x][y]);
				else if(p[x][y] == -2) e.flip(P);
			}
			if(!add()) return FAIL;
		}
		// 解方程
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != M; ++j)
				if(inp[i][j] == '?')
				{
					e.clear();
					e.set(p[i][j]);
					inp[i][j] = 'N';
					if(add()) continue;
					e.clear();
					e.set(p[i][j]);
					e.set(P);
					inp[i][j] = 'Z';
					if(add()) continue;
					return FAIL;
				}
		return inp;
	}
}	user;
