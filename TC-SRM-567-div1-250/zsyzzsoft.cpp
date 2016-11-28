#include<algorithm>
using namespace std;
int prime[77780], top, cnt;
bool isp[77780];
int Ans, t, s;
class TheSquareRootDilemma
{
public:
	int countPairs(int n, int m)
	{
		for(int i = 2; i <= n; i++)
		{
			if(isp[i] == 0)
			{
				for(int j = 2 * i; j <= n; j += i)
					isp[j] = 1;
			}
		}
		for(int i = 2; i <= n; i++)
		{
			if(isp[i] == 0)
				prime[++top] = i;
		}
		for(int i = 2; i <= n; i++)
		{
			s = 1;
			t = i;
			for(int j = 1; j <= top; j++)
			{
				cnt = 0;
				while(t % prime[j] == 0)
					t /= prime[j], cnt++;
				if(cnt % 2 == 1)
					s *= prime[j];
			}
			Ans += (int)(sqrt((m / s)));
		}
		return Ans + (int)sqrt(m);
	}
};
