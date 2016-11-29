#include <algorithm>
using namespace std;
const int inf = 2147483647;
class MagicMolecule
{
public:
	int n, m, ans, id[50], w[50];
	long long e[50];
	void Dfs(int depth, long long st)
	{
		int p = n, sum = 0;
		for(int i = 0; i < n; i++)
		{
			if((st >> i) & 1)
				p--, sum += w[i];
		}
		if(sum <= ans || p > m)
			return;
		if(depth == n)
		{
			ans = sum;
			return;
		}
		if((st >> depth) & 1)
		{
			Dfs(depth + 1, st & e[depth]); //选择当前点，不与当前点连接的都必须不选 
			if(p < m)
				Dfs(depth + 1, st - (1LL << depth)); //不选当前点 
		}
		else
			Dfs(depth + 1, st); //当前点已经确定为不选 
	}
	int maxMagicPower(vector<int> magic_power, vector<string> magic_bond)
	{
		n = magic_power.size(), m = n / 3;
		for(int i = 0; i < n; i++)
			id[i] = i;
		for(int i = 0; i < n; i++) //打乱顺序 
			swap(id[i], id[rand() % (i + 1)]);
		for(int i = 0; i < n; i++)
			w[i] = magic_power[id[i]];
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				e[i] += (1LL << j) * (magic_bond[id[i]][id[j]] == 'Y');
			e[i] |= 1LL << i;
		}
		ans = -1;
		Dfs(0, (1LL << n) - 1);
		return ans;
	}
};