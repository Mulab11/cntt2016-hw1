#include <bits/stdc++.h>

using namespace std;

const int maxn = 50,maxs = 2505,mo = int(1e9) + 7;

int f[2][maxn][maxn][maxs];

class LittleElephantAndPermutationDiv1
{
public:
	int getNumber(int N, int K)
	{
		f[0][0][0][0] = 1;
		int cur = 0,sum = 0;
		for(int i = N;i;sum += 2 * i,i --) 
		//从后往前dp，记录f[i][ap][bp][sum]表示A还有ap个数没有匹配，B还有bp个数没有匹配，当前的f为sum
		//由于我们只关心匹配的情况，所以最后乘n!就好了。转移就相当于枚举A[i]和B[i]是和对面一个大数匹配，还是自己新建一个匹配
		//新建匹配时要更新sum
		{
			cur ^= 1;
			memset(f[cur],0,sizeof f[cur]);
			for(int ac = 0;ac <= N - i;ac ++)
				if (ac > i) continue; else
					for(int bc = 0;bc <= N - i;bc ++)
						if (bc > i) continue; else
							for(int s = 0;s <= sum && s <= N * N;s ++)
							{
								int tmp = f[cur ^ 1][ac][bc][s];
								if (!tmp) continue;
								for(int pa = -1;pa < 2;pa ++)
									if (!pa) continue; else
										for(int pb = -1;pb < 2;pb ++)
										{
											if (!pb) continue;
											if (ac + pb < 0 || bc + pa < 0) continue; //不合法
											int ns = s;
											if (pa == 1) ns += i;//新建了一个匹配，权值为i
											if (pb == 1) ns += i;
											if (ns > N * N) continue;
											int ntmp = tmp;
											if (pa == -1) ntmp = ntmp * 1ll * bc % mo;//有bc个位置可以选
											if (pb == -1) ntmp = ntmp * 1ll * ac % mo;//同理
											int nac = ac,nbc = bc;
											if (pa == -1) nbc --; else nac ++;
											if (pb == -1) nac --; else nbc ++;
											(f[cur][nac][nbc][ns] += ntmp) %= mo;
										}
								(f[cur][ac][bc][s + i] += tmp) %= mo;
							}
		}
		int v = 0;
		for(int i = K;i <= N * N;i ++) v = (v + f[cur][0][0][i]) % mo;
		for(int i = 1;i <= N;i ++) v = v * 1ll * i % mo;
		return v;
	}
};
