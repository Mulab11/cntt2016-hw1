#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

class JumpFurther
{
public:
	int furthest(int N, int bad)
	{
		int ans = 0;
		for(int skip = 0; skip <= N; ++skip)
		{
			int cur = 0;
			for(int i = 1; i <= N; ++i)
				if(i != skip && (cur += i) == bad) goto skipped;
			if(cur > ans) ans = cur;
		skipped: ;
		}
		return ans;
	}
}	user;
