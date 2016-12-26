#include <algorithm>
#include <memory.h>
using namespace std;
const int maxn = 60;
int pl[maxn][maxn], pls[2][maxn];
long long power[maxn];
bool canpl[maxn], ins[maxn];
int opl[maxn], opls[2];
class BitwiseAnd
{
public:
	int Judge(long long a, int b)
	{
		return (a / power[b]) % 2;
	}
	vector<long long> lexSmallest(vector<long long> subset, int n)
	{
		vector <long long> empty;
		int m = subset.size();
		for(int i = 0; i < maxn; i++)
			canpl[i] = true;
		power[0] = 1;
		for(int i = 1; i < maxn; i++) //预处理2的幂 
			power[i] = 2 * power[i - 1];
		memset(ins, false, sizeof(ins));
		for(int i = 0; i < m; i++) //特判初始无解 
			for(int j = 0; j < m; j++)
				if(!(subset[i] & subset[j]))
					return empty;
		for(int i = 0; i < m; i++) 
			for(int j = i + 1; j < m; j++)
				for(int k = 0; k < maxn; k++)
					if(Judge(subset[i], k) && Judge(subset[j], k))
					{
						if(!ins[k])
							canpl[k] = false, ins[k] = true;
						else 
							return empty;
					}
		memset(pls, 0, sizeof(pls));
		for(int i = 0; i < m; i++) //预处理位置
			for(int k = 0; k < maxn; k++)
				if(canpl[k] && Judge(subset[i], k))
					pl[i][pls[1][i]++] = k, ins[k] = true;
		for(int i = 0; i < maxn; i++)
			if(!ins[i]) 
				opl[opls[1]++] = i;
		opls[0] = 0;
		for(int i = m; i < n; i++) //加入新元素 
		{
			for(int j = 0; j < i; j++)
			{
				if(pls[0][j] >= pls[1][j])
					return empty;
				else
					pl[i][pls[1][i]++] = pl[j][pls[0][j]++];
			}
			pls[0][i] = pls[1][i];
			for(int j = 0; j < n - i - 1; j++)
			{
				if(opls[0] >= opls[1])
					return empty;
				else
					pl[i][pls[1][i]++] = opl[opls[0]++];
			}
		}
		for(int i = 0; i < m; i++) //计算答案 
			empty.push_back(subset[i]);
		for(int i = m; i < n; i++)
		{
			long long nows = 0;
			for(int j = 0; j < pls[1][i]; j++)
				nows += power[pl[i][j]];
			empty.push_back(nows);
		}
		sort(empty.begin(), empty.end());
		return empty;
	}
};