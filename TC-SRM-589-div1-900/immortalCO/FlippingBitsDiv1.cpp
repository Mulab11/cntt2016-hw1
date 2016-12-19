#include <bits/stdc++.h>
#define RG register
#define IL inline
#define For(i, a, b) for(RG int i = a, ___u = b; i <= ___u; ++i)
#define Rep(i, a, b) for(RG int i = b, ___d = a; i >= ___d; --i)
#define dmin(a, b) ((a) < (b) ? (a) : (b))
#define cmin(a, b) ((a) > (b) ? (a) = (b) : (a))
#define cmax(a, b) ((a) < (b) ? (a) = (b) : (a))
#define ddel(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))
#define dabs(x) ((x) > (0) ? (x) : -(x))
using namespace std;
typedef double db;

#define Class FlippingBitsDiv1
#define func getmin

namespace pb_ds
{
	const int MAXN = 310;
	int full[30];
	bool input[MAXN], *str[MAXN];
	int len[MAXN], arr[MAXN];
	int f[MAXN][2];
	
#define diff(n, a, b) (__builtin_popcount(((a) ^ (b)) & full[n]))
#define get(s, i) (((s) >> (i)) % 2)
}
using namespace pb_ds;

class Class
{
public:
	int func(vector<string> vec, RG int m)
	{
		For(i, 0, 25) full[i] = (1 << i) - 1;
		string buff;
		For(i, 0, vec.size() - 1) buff += vec[i];
		RG int n = buff.size();
		For(i, 0, n - 1) input[i] = (buff[i] == '1');
		RG int nPart = ceil(1.0 * n / m) + 0.5;
		
		For(i, 0, nPart - 1)
		{
			str[i] = input + i * m;
			len[i] = dmin(m, n - i * m);
			///*lgg*/printf("i = %d len = %d\n", i, len[i]);
		}
		
		RG int ans = 1e9;
		if(m <= sqrt(n))
			//if(1)
		{
			For(i, 0, nPart - 1) For(j, 0, len[i] - 1)
			if(str[i][j]) arr[i] |= 1 << j;
			For(set, 0, full[m])
			{
				f[0][0] = diff(len[0], arr[0], set);
				f[0][1] = diff(len[0], ~arr[0], set);
				For(i, 1, nPart - 1)
				{
					f[i][0] = dmin(f[i - 1][0], f[i - 1][1] + 1) + diff(len[i], arr[i], set);
					f[i][1] = dmin(f[i - 1][1], f[i - 1][0] + 1) + diff(len[i], ~arr[i], set);
				}
				
				cmin(ans, f[nPart - 1][0]);
				cmin(ans, f[nPart - 1][1]);
			}
		}
		else For(set, 0, full[nPart])
		{
			///*lgg*/printf("set = %d\n", set);
			///*lgg*/For(j,0,nPart-1)For(k,0,len[j]-1)printf("%d",str[j][k]^get(set,j));puts("");
			RG int cur = 0;
			For(i, 0, nPart - 1)
			if(get(set, i) != get(set, i - 1))
				++cur;
			For(i, 0, m - 1)
			{
				int cnt[2] = {0, 0};
				For(j, 0, nPart - 1) if(i < len[j])
					++cnt[str[j][i] ^ get(set, j)];
				///*lgg*/printf("bit %d cnt = %d %d\n", i, cnt[0], cnt[1]);
				cur += dmin(cnt[0], cnt[1]);
			}
			///*lgg*/printf("cur = %d\n", cur); //getchar(); assert(cur >=2);
			cmin(ans, cur);
		}
		return ans;
	}
};
