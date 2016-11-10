#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

int N, L;
vector<int> cnt[60];
bool del[60];

class StringGame
{
public:
	vector<int> getWinningStrings(vector<string> inp)
	{
		vector<int> ret;
		N = inp.size();
		L = inp[0].size();
		for(int i = 0; i != N; ++i)
		{
			cnt[i].resize(26);
			for(int j = 0; j != L; ++j)
				++cnt[i][inp[i][j] - 'a'];
		}
		for(int i = 0; i != N; ++i)
		{
			vector<int> Cnt = cnt[i];
			// 先做重复出现检查（其实也不用，为了节省常数……
			for(int j = 0; j != N; ++j)
				if(i != j && Cnt == cnt[j]) goto skipped;
			// 按位决定
			memset(del, 0, N); del[i] = 1;
			for(int j = 0; j != L; )
			{
				// 枚举这一位取哪一个字母
				for(int w = 0; w != 26; ++w) if(Cnt[w])
				{
					for(int k = 0; k != N; ++k) if(!del[k] && cnt[k][w] > Cnt[w]) goto failed;
					for(int k = 0; k != N; ++k) if(!del[k] && cnt[k][w] < Cnt[w]) del[k] = 1;
					j += Cnt[w], Cnt[w] = 0; goto nextstep;
				failed: continue;
				}
				goto skipped;
			nextstep: continue;
			}
			ret.push_back(i);
		skipped: continue;
		}
		return ret;
	}
}	user;
