#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int cnt[60];

class BitwiseAnd
{
public:
	vector<ll> lexSmallest(vector<ll> a, int N)
	{
		if(!a.size())
			a.push_back((1ll << (N - 1)) - 1);
		else for(int i = 0; i != (int) a.size(); ++i)
			for(int j = i + 1; j != (int) a.size(); ++j)
			{
				if((a[i] & a[j]) == 0) return vector<ll>();
				for(int k = j + 1; k != (int) a.size(); ++k)
					if(a[i] & a[j] & a[k]) return vector<ll>();
			}
		for(int i = 0; i != (int) a.size(); ++i)
			for(int k = 0; k != 60; ++k) if(a[i] & (1ll << k))
				++cnt[k];
		while((int) a.size() < N)
		{
			// 考虑如何获得下一个数
			ll next = 0;
			// 枚举之前所有的数，考虑至少要有一个共同的位
			for(int i = 0; i != (int) a.size(); ++i)
				if((next & a[i]) == 0)
				{
					// 不满足，则添加 a[i] 具有的下一个没有出现 2 次的位置
					for(int k = 0; k != 60; ++k)
						if((a[i] & (1ll << k)) && cnt[k] < 2)
						{next |= 1ll << k, ++cnt[k]; break;}
					if((next & a[i]) == 0) return vector<ll>();
				}
			// 如果 next 的 1 太少，则不行，至少要补到 N - 1 位
			for(int k = 0; k != 60 && __builtin_popcountll(next) < N - 1; ++k)
				if(!cnt[k]) next |= 1ll << k, ++cnt[k];
			if(__builtin_popcountll(next) < N - 1) return vector<ll>();
			a.push_back(next);
		}
		sort(&*a.begin(), &*a.end());
		return a;
	}
}	user;
