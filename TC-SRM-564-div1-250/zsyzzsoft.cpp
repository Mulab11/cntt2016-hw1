#include <algorithm>
using namespace std;
class KnightCircuit2
{
public:
	int maxSize(int w, int h)
	{
		if(w > h)
			swap(w, h);
		if(w > 3)
			return w * h; //绝大多数情况都可以填满整个棋盘 
		if(w == 3)
			return h > 3 ? w * h : 8;
		if(w == 2)
			return (h + 1) / 2;
		return 1;
	}
};
