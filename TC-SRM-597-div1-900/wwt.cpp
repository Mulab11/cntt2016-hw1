#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1000005,Mo = int(1e9) + 7;
typedef long long LL;

int Fac[MAXN],Rev[MAXN],Po[MAXN],Cur[2],Ch[3],M,R,G,B;

LL C(int n,int m)
{
	if (n < m) return 0;
	return Fac[n] * 1ll * Rev[m] % Mo * Rev[n - m] % Mo;
}

int Pow(int a,int b)
{
	if (!b) return 1;
	LL mid = Pow(a,b >> 1);
	mid = mid * mid % Mo;
	if (b & 1) mid = mid * a % Mo;
	return mid;
}

int Calc(int g) //两种球，分成g段，相邻不能相同
{
	int tmp = 0;
	for(int e = 0;e <= g;e ++)//枚举偶数段段数
	{
		int y = Cur[0] - e,z = Cur[1] - e;
		if (y < 0 || z < 0) continue;
		if ((g - e + y - z) & 1) continue;
		int oy = (g - e + y - z) / 2,oz = g - e - oy; //分别求出奇数段中有多少是A开头，有多少是B开头
		if (oy < 0 || oz < 0) continue;
		tmp = (tmp + C(g,e) * C(g - e,oy) % Mo * Po[e] % Mo * C(y - oy + g - 1,g - 1) % Mo) % Mo;//偶数段A,B都可以开头
	}
	return tmp;
}

int Solve(int od)
{
	int tmp = 0;
	for(int i = 0,c = 0;i < 3;i ++)
		if (i != od) Cur[c ++] = Ch[i];
	for(int i = Ch[od] - 1;i <= Ch[od];i ++)//枚举开头和结尾是否相同，对应其分的段数
		tmp = (tmp + Calc(i)) % Mo;
	return tmp;
}

class LittleElephantAndBoard
{
public:
	int getNumber(int m, int R, int G, int B)
	{
		M = m,Ch[0] = R,Ch[1] = G,Ch[2] = B;
		Ch[0] = M - Ch[0],Ch[1] = M - Ch[1],Ch[2] = M - Ch[2]; //把每一列少的那一个当成那一列对应的元素，那么就变成3种球排一排的问题了
		Fac[0] = Po[0] = 1;
		for(int i = 1;i <= M;i ++) Fac[i] = Fac[i - 1] * 1ll * i % Mo,Po[i] = Po[i - 1] * 2ll % Mo;
		Rev[M] = Pow(Fac[M],Mo - 2);
		for(int i = M;i;i --) Rev[i - 1] = Rev[i] * 1ll * i % Mo;
		int ans = 0;
		ans = ((Solve(0) + Solve(1)) % Mo + Solve(2)) % Mo; //枚举放开头是哪个
		return ans * 2ll % Mo;
	}
};
