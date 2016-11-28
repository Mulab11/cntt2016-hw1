#include <algorithm>
#include <memory.h>
using namespace std;
const double inf = -1.0;
class BoundedOptimization
{
	int n, sum, low[13], high[13], c[13][13];
	double ans, val[13];
public:
	void EnumBound(int depth)
	{
		if(depth == n)
		{
			double w[13];
			memset(w, 0, sizeof(w));
			for(int i = 0; i < n; i++) 
			{
				for(int j = i + 1; j < n; j++)
				{
					if(!c[i][j])
					{
						if(val[i] == inf && val[j] == inf) //未达边界的变量一定形成一个团 
							return;
						continue;
					}
					if(val[i] != inf) //计算一次项系数 
						w[j] += val[i];
					else if(val[j] != inf)
						w[i] += val[j];
				}
			}
			double cur = 0, tmp = sum;
			int tot = 0;
			for(int i = 0; i < n; i++)
			{
				if(val[i] == inf)
					tmp -= w[i], tot++;
				else
					tmp -= val[i];
			}
			if(!tot)
				return;
			for(int i = 0; i < n; i++)
			{
				if(val[i] == inf)
				{
					w[i] += tmp / tot; //根据拉格朗日乘数法，最优取值应为一次项系数的一个整体偏移 
					if(w[i] < low[i] || w[i] > high[i])
						return;
				}
				else
					w[i] = val[i];
			}
			for(int i = 0; i < n; i++) //计算答案 
			{
				for(int j = i + 1; j < n; j++)
					cur += c[i][j] * w[i] * w[j];
			}
			ans = max(ans, cur);
		}
		else
		{
			EnumBound(depth + 1);
			val[depth] = low[depth];
			EnumBound(depth + 1);
			val[depth] = high[depth];
			EnumBound(depth + 1);
			val[depth] = inf;
		}
	}
	double maxValue(vector<string> _expr, vector<int> _low, vector<int> _high, int _sum)
	{
		n = _low.size();
		sum = _sum;
		for(int i = 0; i < n; i++)
			low[i] = _low[i], high[i] = _high[i];
		string expr;
		for(int i = 0; i < _expr.size(); i++)
			expr += _expr[i];
		int len = expr.length();
		memset(c, 0, sizeof(c));
		for(int i = 0; i < len; i += 3)
			c[expr[i] - 'a'][expr[i + 1] - 'a'] = c[expr[i + 1] - 'a'][expr[i] - 'a'] = 1;
		for(int i = 0; i < n; i++)
			val[i] = inf;
		ans = 0;
		EnumBound(0); //枚举到达边界的变量 
		return ans;
	}
};
