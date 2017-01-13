#include <cmath>
using namespace std;

class JumpFurther
{
private:
	int getBadStepNumber(int badStep)//the number of the choice on which Jiro might jump onto the broken step
	{
		int ret = (int)sqrt(badStep * 2);
		return badStep == ret * (ret + 1) / 2 ? ret : -1;
	}
public:
	int furthest(int N, int badStep)
	{
		int num = getBadStepNumber(badStep);
		return N * (N + 1) / 2 - (num >= 1 && num <= N);
	}
};

