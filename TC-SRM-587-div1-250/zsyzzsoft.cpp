#include <algorithm>
using namespace std;
class JumpFurther
{
public:
	int furthest(int n, int b)
	{
		for(int i = 1; i <= n; i++)
		{
			if(i * (i + 1) / 2 == b)
				return n * (n + 1) / 2 - 1; //不跳第一步 
		}
		return n * (n + 1) / 2;
	}
};