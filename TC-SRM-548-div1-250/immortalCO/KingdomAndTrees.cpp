#include <vector>
using namespace std;

#define dmin(a, b) ((a) < (b) ? (a) : (b))
class KingdomAndTrees
{
public:
	int minLevel(vector<int> vec)
	{
		int l = 0, r = 1e9, m;
		int n = vec.size(), *a = vec.data();
		while(l != r)
		{
			m = (l + r) >> 1;
			int last = 0;
			for(int i = 0; i != n; ++i)
			{
				if(last < a[i]) last = a[i] - dmin(a[i] - last - 1, m);
				else if(last + 1 - a[i] > m) goto failed;
				else ++last;
			}
			r = m;
			continue;
			failed: l = m + 1;
		}
		return l;
	}
}	user;