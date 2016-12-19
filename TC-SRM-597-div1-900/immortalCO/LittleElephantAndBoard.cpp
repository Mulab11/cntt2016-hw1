//pb_ds 20160711
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;
#define RG register
//#define IL inline
#define IL __inline__ __attribute__((always_inline))
#define For(i, a, b) for(RG int i = a, ___u = b; i <= ___u; ++i)
#define Dor(i, a, b) for(RG int i = b, ___d = a; i >= ___d; --i)
#define Rep(i, a, b) for(RG int i = a, ___u = b; i != ___u; ++i)
#define dmin(a, b) ((a) < (b) ? (a) : (b))
#define dmax(a, b) ((a) > (b) ? (a) : (b))
typedef long long ll;
typedef unsigned uint;

namespace pb_ds
{
	const int MaxN = 2000010;
	const int mod = 1e9 + 7;
	int inv[MaxN], fac[2][MaxN];
	
	IL int comb(RG int n, RG int m)
	{
		if(n < 0 || m < 0 || m > n) return 0;
		return (ll) fac[0][n] * fac[1][m] % mod * fac[1][n - m] % mod;
	}
}

class	LittleElephantAndBoard
{
public:
	IL int 	getNumber(RG int n, RG int AB, RG int BC, RG int AC)
	{
		using namespace pb_ds;
		inv[0] = fac[0][0] = fac[1][0] =
		inv[1] = fac[0][1] = fac[1][1] = 1;
		For(i, 2, n << 1)
		{
			inv[i] = mod - (ll) (mod / i) * inv[mod % i] % mod;
			fac[0][i] = (ll) fac[0][i - 1] * i % mod;
			fac[1][i] = (ll) fac[1][i - 1] * inv[i] % mod;
			///*lgg*/assert((ll) fac[0][i] * fac[1][i] % mod == 1);
		}
		if(AB > n || BC > n || AC > n) return 0;
		AB = n - AB;
		BC = n - BC;
		AC = n - AC;
		RG int Ans = 0, Cur, Cnt, Tnc = AB + AC + 1;
		For(_AB, bool(AB), AB)
		{
			For(_AC, dmax(bool(AC), _AB - 1), dmin(AC, _AB + 1))
			{
				Cnt = AB - _AB + AC - _AC;
				if(Cnt > BC) continue;
				Cur = 2;
				if(_AB == _AC) Cur <<= 1;
				if(AB) Cur = (ll) Cur * comb(AB - 1, _AB - 1) % mod;
				if(AC) Cur = (ll) Cur * comb(AC - 1, _AC - 1) % mod;
				Cur = (ll) Cur * comb(Tnc - Cnt, BC - Cnt) % mod;
				(Ans += Cur) %= mod;
				///*lgg*/printf("_AB = %d _AC = %d cur = %d\n", _AB, _AC, Cur);
			}
		}
		return Ans;
	}
};
