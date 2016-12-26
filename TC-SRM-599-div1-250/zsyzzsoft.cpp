#include <algorithm>
using namespace std;
const int maxn = 1000001, maxpower = 30;
int pr[maxn], nd[maxn], power[maxpower];
bool bpr[maxn];	
int prms;
class BigFatInteger
{
public:
	int minOperations(int a, int b)
	{
		power[0] = 1;
		for(int i = 1; i < maxpower; i++) 
			power[i] = power[i - 1] * 2;
		for(int i = 0; i < maxn; i++) 
			bpr[i] = true;
		for(int i = 2; i < maxn; i++)
		{
			if(bpr[i])
			{
				for(int j = 2; j * i < maxn; j++) 
					bpr[i * j] = false;
				pr[prms++] = i;
			}
		}
		int nowsum = a, ans = maxn;
		for(int i = 0; i < prms; i++)
		{
			int ns = 0;
			while((nowsum % pr[i]) == 0)
				ns++, nowsum /= pr[i];
			nd[i] = ns * b;
		}
		for(int i = 0; i < maxpower; i++)
		{
			int nans = i;
			for(int j = 0; j < prms; j++) 
			{
				nans += nd[j] / power[i];
				if(nd[j] % power[i])
					nans++;
			}
			if(ans > nans)
				ans = nans;
		}
		return ans;
	}
};