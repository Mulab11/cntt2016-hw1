#include <algorithm>
using namespace std;
const int inf = 2147483647;
class MagicMolecule
{
public:
	int n, m, ans, w[50];
	long long e[50];
	int Count(long long st)
	{
		int cnt = 0;
		for(int i = 0; i < n; i++)
			cnt += (st >> i) & 1;
		return cnt;
	}
	void Dfs(int depth, int sum, long long st)
	{
		int p = n - Count(st);
		if(p > m)
			return;
		if(depth == n)
		{
			ans = max(ans, sum);
			return;
		}
		if((st >> depth) & 1)
		{
			if(p < m)
				Dfs(depth + 1, sum - w[depth], st - (1LL << depth)); //不选当前点 
			Dfs(depth + 1, sum, st & e[depth]); //选择当前点，不与当前点连接的都必须不选 
		}
		else
			Dfs(depth + 1, sum - w[depth], st); //当前点已经确定为不选 
	}
	int maxMagicPower(vector<int> magic_power, vector<string> magic_bond)
	{
		n = magic_power.size(), m = n / 3;
		int sum = 0;
		for(int i = 0; i < n; i++)
			sum += w[i] = magic_power[i];
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				e[i] += (1LL << j) * (magic_bond[i][j] == 'Y');
			e[i] |= 1LL << i;
		}
		ans = -1;
		Dfs(0, sum, (1LL << n) - 1);
		return ans;
	}
};
