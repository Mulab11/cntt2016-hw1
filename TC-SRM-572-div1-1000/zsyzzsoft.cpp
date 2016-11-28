#include <algorithm>
using namespace std;
const int inf = 2147483647;
class NextAndPrev
{
public:
	int dest[26];
	int Work(int next_cost, int prev_cost)
	{
		int ans = dest[0] * next_cost;
		for(int i = 1, j = dest[0], p = j; i < 26; i++) //其它字符的转移均可被唯一确定 
		{
			if(dest[i] < 0)
				continue;
			int k = j / 26 * 26 + dest[i];
			if(k < j) //目标位置必须满足单调性 
				k += 26;
			if(k >= dest[0] + 26)
				return inf;
			if(k != j)
				ans += k < i ? (i - k) * prev_cost : (k - i) * next_cost;
			else if(k < i)
				ans += (i - p) * prev_cost;
			j = k;
			p = max(i, j);
		}
		return ans;
	}
	int getMinimum(int next_cost, int prev_cost, string start, string goal)
	{
		for(int i = 0; i < 26; i++)
			dest[i] = -1;
		for(int i = 0; i < start.length(); i++)
		{
			for(int j = i + 1; j < start.length(); j++)
			{
				if(start[i] == start[j] && goal[i] != goal[j])
					return -1;
			}
		}
		for(int i = 0; i < start.length(); i++)
			dest[(int)start[i] - 'a'] = goal[i] - 'a';
		if(start == goal)
			return 0;
		int tot = 0;
		for(int i = 0; i < 26; i++)
			tot += dest[i] >= 0;
		if(tot == 26)
			return -1;
		int ans = inf;
		for(int i = 0; i < 26; i++)
		{
			if(dest[0] >= 0) //枚举某一个字符的转移 
				ans = min(ans, Work(next_cost, prev_cost));
			for(int j = 1; j < 26; j++)
				swap(dest[j - 1], dest[j]);
			for(int j = 0; j < 26; j++)
				dest[j] = dest[j] < 0 ? -1 : (dest[j] + 25) % 26;
		}
		for(int i = 0; i < 13; i++) //反转序列再继续枚举 
			swap(dest[i], dest[25 - i]);
		for(int i = 0; i < 26; i++)
			dest[i] = dest[i] < 0 ? -1 : 25 - dest[i];
		for(int i = 0; i < 26; i++)
		{
			if(dest[0] >= 0)
				ans = min(ans, Work(prev_cost, next_cost));
			for(int j = 1; j < 26; j++)
				swap(dest[j - 1], dest[j]);
			for(int j = 0; j < 26; j++)
				dest[j] = dest[j] < 0 ? -1 : (dest[j] + 25) % 26;
		}
		return ans < inf ? ans : -1;
	}
};
