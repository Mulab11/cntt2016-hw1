#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;


class ICPCBalloons
{
public:
	int minRepaintings(vector<int> cnt, string type, vector<int> C)
	{
		vector<int> A, B;
		for(int i = 0; i != (int) cnt.size(); ++i)
			(type[i] == 'M' ? A : B).push_back(cnt[i]);
		sort(A.begin(), A.end(), greater<int>());
		sort(B.begin(), B.end(), greater<int>());
		sort(C.begin(), C.end(), greater<int>());
		int ans = 1e9;
		int sum[2] = {};
		for(int i = 0; i != A.size(); ++i) sum[1] += A[i];
		for(int i = 0; i != B.size(); ++i) sum[0] += B[i];
		for(int s = 0; s != 1 << C.size(); ++s)
		{
			int cur = 0, a = 0, b = 0, left[2];
			memcpy(left, sum, 8);
			for(int i = 0; i != (int) C.size(); ++i)
			{
				int tmp = C[i] - min(C[i], ((s >> i) & 1)
									 ? (a != A.size() ? A[a++] : 0)
									 : (b != B.size() ? B[b++] : 0));
				cur += tmp,
				left[(s >> i) & 1] -= C[i];
			}
			if(left[0] >= 0 && left[1] >= 0) ans = min(ans, cur);
		}
		return ans == 1e9 ? -1 : ans;
	}
}	user;
