#include <algorithm>
using namespace std;
class MapGuessing
{
public:
	int n, len;
	string code;
	long long goal_state;
	vector<long long> state;
	long long Check(int x)
	{
		long long ret = 0, st = 0, val = 0;
		for(int i = 0; i < len; i++)
		{
			if(code[i] == '<')
				x--;
			else if(code[i] == '>')
				x++;
			else
			{
				st |= 1LL << x;
				if(code[i] - '0' != ((val >> x) & 1))
					val ^= 1LL << x;
				if((goal_state & st) == val)
					ret = st; //可以达到目标状态 
			}
			if(x < 0 || x >= n)
				return -1;
		}
		return ret;
	}
	void Dfs(int depth, long long st, int sig, long long &ans)
	{
		if(depth == state.size())
		{
			long long tmp = 1;
			for(int i = 0; i < n; i++)
			{
				if((st >> i) & 1)
					tmp <<= 1;
			}
			ans += tmp * sig; //容斥原理 
		}
		else if(st) //交集不为空 
		{
			Dfs(depth + 1, st, sig, ans);
			Dfs(depth + 1, st & state[depth], -sig, ans);
		}
	}
	long long countPatterns(string goal, vector<string> code_vector)
	{
		n = goal.length();
		code = "";
		for(int i = 0; i < code_vector.size(); i++)
			code += code_vector[i];
		len = code.length();
		goal_state = 0;
		for(int i = 0; i < n; i++)
			goal_state += (long long)(goal[i] - '0') << i;
		for(int i = 0; i < n; i++)
		{
			long long tmp = Check(i); //枚举起点，检查是否合法 
			if(tmp >= 0)
				state.push_back(tmp);
		}
		long long ans = 1LL << n;
		Dfs(0, ans - 1, -1, ans);
		return ans;
	}
};
