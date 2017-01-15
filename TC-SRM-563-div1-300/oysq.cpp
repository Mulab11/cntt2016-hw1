#line 5 "FoxAndHandle.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

struct FoxAndHandle {
    string lexSmallestName(string S) {
		int cnt[26] = {0};// 每个字母出现次数
		std::set<std::pair<char, int> > s;// 字典序从小到大存储每个元素
		for(int i = 0; i < SZ(S); ++i) s.insert(mp(S[i], i)), cnt[S[i] - 'a']++;
		for(int i = 0; i < 26; ++i) cnt[i] >>= 1;// S中出现了两次要求的串，因此要/2
		std::string ret;
		for(int i = 0, last = -1; i < SZ(S) / 2; ++i) {
			int pos = -1, cur[26] = {0};
			for(int j = SZ(S) - 1; j > last; --j) {
				// 检查位置j之后每个字母的数量能否满足要求
				cur[S[j] - 'a']++;
				bool flag = true;
				for(int k = 0; k < 26; ++k)
					if(cur[k] < cnt[k]) {
						flag = false;
						break;
					}
				if(flag) {
					pos = j;// 能满足要求的右边界
					break;
				}
			}
			// last表示上次的选择，相当于左边界
			for(std::set<std::pair<char, int> >::iterator j = s.begin(); j != s.end(); ++j)
				if(j->se > last && j->se <= pos && cnt[j->fi - 'a']) {
					// 更新答案
					last = j->se;
					ret += j->fi;
					cnt[j->fi - 'a']--;
					break;
				}
			s.erase(mp(S[last], last));
		}
		return ret;
    }
};
