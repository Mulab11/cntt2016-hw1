#include <algorithm>
using namespace std;
struct Pair
{
	long long a, b;
	Pair() {a = b = 0; }
	Pair(long long _b) {a = 0, b = _b; }
	Pair(long long _a, long long _b) {a = _a, b = _b; }
	Pair operator + (const Pair &_p) const
	{
		return Pair(a + _p.a, b + _p.b);
	}
};
class Suminator
{
public:
	
	Pair Simulate(const vector<int> &program) //模拟 
	{
		Pair stack[200];
		int l = 100;
		for(int i = 0; i < program.size(); i++)
		{
			if(program[i] > 0)
				stack[l++] = Pair(program[i]);
			else if(program[i] == 0)
				stack[l - 2] = stack[l - 2] + stack[l - 1], l--;
			else
				stack[l++] = Pair(1, 0);
		}
		return stack[l - 1];
	}
	int findMissing(vector<int> program, int result)
	{
		for(int i = 0; i < program.size(); i++)
		{
			if(program[i] == -1)
			{
				program[i] = 0;
				if(Simulate(program).b == result) //置为0 
					return 0;
				program[i] = -1;
			}
		}
		Pair ans = Simulate(program); //置为其它数 
		if(ans.a == 0)
			return ans.b == result ? 1 : -1;
		return result - ans.b > 0 ? result - ans.b : -1;
	}
};
