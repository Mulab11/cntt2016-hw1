#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;


class SpaceWarDiv1
{
public:
	ll minimalFatigue(vector<int> A, vector<int> b, vector<ll> c)
	{
		vector<pair<int, ll> > B;
		for(int i = 0; i != (int) b.size(); ++i)
			B.push_back(make_pair(b[i], c[i]));
		sort(A.begin(), A.end()); reverse(A.begin(), A.end());
		sort(B.begin(), B.end()); reverse(B.begin(), B.end());
		if(A.front() < B.front().first) return -1;
		long long l = 0, r = 1ll << 62;
		while(l != r)
		{
			const ll m = (l + r) >> 1;
			vector<pair<int, ll> > C = B;
			for(int i = 0; i != (int) A.size(); ++i)
			{
				ll cur = m;
				for(int j = 0; j != (int) C.size(); ++j)
					if(A[i] >= C[j].first)
					{
						ll t = min(cur, C[j].second);
						C[j].second -= t;
						cur -= t;
					}
			}
			for(int j = 0; j != (int) C.size(); ++j) if(C[j].second) goto failed;
			r = m;
			continue;
		failed: l = m + 1;
		}
		return l;
	}
}	user;
