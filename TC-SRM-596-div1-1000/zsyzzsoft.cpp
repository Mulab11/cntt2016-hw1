#include <algorithm>
#include <memory.h>
using namespace std;
const int maxn = 1000001;
long long prms = 0, prm[7][2]; 
bool bpr[maxn];
int lst[7][maxn];
short nums[7][maxn];
class SparseFactorial
{
public:
	long long getCount(long long lo, long long hi, long long divisor)
	{
		long long nows = divisor;
		for(long long i = 0; i < maxn; i++)
			bpr[i] = true;
		for(long long i = 2; i < maxn; i++) //质因数分解 
		{
			if(!bpr[i])
				continue;
			for(long long j = 2; i * j < maxn; j++)
				bpr[i * j] = false;
			if(nows % i == 0)
			{
				prm[prms][0] = i;
				prm[prms][1] = 0;
				while(!(nows % i)) 
					prm[prms][1]++, nows /= i;
				prms++;
			}
		}
		memset(nums, 0, sizeof(nums));
		memset(lst, -1, sizeof(lst));
		for(long long i = 0; i < prms; i++) //预处理模每个质数所需的最小数 
		{
			long long nows = 1;
			for(long long j = 0; j < prm[i][1]; j++)
				nows *= prm[i][0];	
			for(long long j = 0; j < prm[i][0] * prm[i][1]; j++)
			{
				for(long long k = (j * j) % prm[i][0]; k <= nows; k += prm[i][0])
				{
					long long nowsum = k - j * j;
					if(nums[i][k] >= prm[i][1])
						continue;
					while(!(nowsum % prm[i][0]))
					{
						nums[i][k]++;
						if(nums[i][k] >= prm[i][1])
						{
							lst[i][k] = j;
							break;
						}
						nowsum /= prm[i][0];
					}
				}
			}
		}
		long long ans = 0;
		for(long long i = 0; i < divisor; i++) //计算答案 
		{
			long long least = 0;
			bool flag = false;
			for(long long j = 0; j < prms; j++)
			{
				long long nows = 1;
				for(long long k = 0; k < prm[j][1]; k++)
					nows *= prm[j][0];
				least = max(least, (long long)(lst[j][i % nows]));
				if(lst[j][i % nows] == -1)
					flag = true;
			}
			if(flag) 
				continue;
			long long mins = least * least;
			mins = max(mins + 1, lo);
			if(i < mins % divisor)
				mins += divisor;
			mins -= mins % divisor;
			mins += i;
			long long maxs = hi - hi % divisor + i;
			if(maxs > hi) 
				maxs -= divisor;
			if(mins <= maxs)
				ans += (maxs - mins) / divisor, ans++;
		}
		return ans;
	}
};