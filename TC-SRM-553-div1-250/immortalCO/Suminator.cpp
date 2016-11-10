#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

int N, arr[60], T, p;
ll S[60];

ll run(int v)
{
	arr[p] = v;
	T = 0;
	for(int i = 0; i != N; ++i)
		if(arr[i]) S[++T] = arr[i];
		else
		{
			ll a = (T ? S[T--] : 0);
			ll b = (T ? S[T--] : 0);
			S[++T] = a + b;
		}
	return T ? S[T--] : 0;
}

class Suminator
{
public:
	int findMissing(vector<int> vec, const int res)
	{
		N = vec.size();
		for(int i = 0; i != N; ++i) if((arr[i] = vec[i]) == -1) p = i;
		
		// 0?
		if(run(0) == res) return 0;
		// 如果非 0，答案应该是单调的
		unsigned l = 1, r = 2e9;
		while(l != r)
		{
			unsigned m = (l + r) >> 1;
			(run(m) >= res) ? r = m : l = m + 1;
		}
		return run(l) == res ? l : -1;
	}
}	user;
