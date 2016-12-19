#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

class LittleElephantAndString
{
public:
	int getNumber(string S, string T)
	{
		int cnt[26] = {};
		int N = S.size();
		reverse(S.begin(), S.end());
		reverse(T.begin(), T.end());
		for(int i = 0; i != N; ++i)
		{
			++cnt[S[i] - 'A'];
			--cnt[T[i] - 'A'];
		}
		for(int i = 0; i != 26; ++i)
			if(cnt[i]) return -1;
		int k = 0;
		for(int i = 0; i != N; ++i, ++k)
		{
			while(k != N && T[i] != S[k]) ++k;
			if(k == N) return N - i;
		}
		return 0;
	}
}	user;
