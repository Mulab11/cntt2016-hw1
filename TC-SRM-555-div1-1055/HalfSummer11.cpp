#line 2 "MapGuessing.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 50
#define maxs 263000
typedef long long ll;
using namespace std;
string c; // = code
int n, len; // n是goal的长度，len是code的总长度
int m, tot, mask[maxn]; // m是指针运动范围的长度，tot是指针修改了的位置的个数，mask[i]表示指针活动范围中，左起第i个目前是否被修改，被修改成什么数字
// code对原串的修改，相当于把原串的一些位置“遮住”了，未被遮住的部分自然要和goal相同，被遮住的部分则可以任意决定。指针放在不同的开始位置，code执行不同的步数，会产生不同的遮罩，保留其中合法的遮罩，统计与goal串相异集合X能被任意一个遮罩遮住的初始串的个数，就是答案。
// 为了不重不漏的统计，让每个初始串对应的X在第一个能遮住它的遮罩处被统计到。
ll S[maxn], F[maxs]; // S[i]表示令指针活动范围左端从i开始，此时，所有合法的被修改位置集合（称为“遮罩”）中最大的一个（因为，随着code逐位执行，遮罩集合是增加/不变的，所以指针初始位置确定后，合法的遮罩之间是包含的关系，只需要记录下其中最大的一个，它就包含了剩下的所有遮罩）
// F[s]表示，初始串与目标串之间相异位置的集合为X，且对于s集合中的任意一个元素，它所代表的开始位置pos对应的合法遮罩S[pos], 满足X \in S[pos]，这样的初始串的个数。F可以容斥算出答案。
class MapGuessing {
	public:
		long long countPatterns(string goal, vector <string> code) {
			n = goal.size();
			c = "";
			for (int i = 0; i < code.size(); ++i) c = c + code[i];
			len = c.length();
			int pos = 0, l = 0, r = 0; // pos标记指针当前位置，l,r记录它活动的范围
			for (int i = 0; i < len; ++i) {
				if (c[i] == '<') --pos;
				if (c[i] == '>') ++pos;
				l = min(l, pos); r = max(r, pos);
			}
			pos = 1 - l; m = r - l + 1; // 将活动范围调整到[1, m],初始位置对应调整到pos
			if (n < m) return 0; // 指针无论如何会移出序列，不存在合法初始序列
			for (int i = 1; i <= m; ++i) mask[i] = -1;
			cl(S);
			for (int i = 0; i <= len; ++i) { // 执行code中的第i步前，当前被修改的位置信息存在mask中
				for (int j = 0; j + m - 1 < n; ++j) { // 尝试把这个mask放到序列的各个位置
					bool flag = 1;
					for (int k = 1; k <= m; ++k) // 检查是否能和goal相符
						if (mask[k] != -1 && mask[k] != (goal[j + k - 1] - '0')) flag = 0;
					if (flag) { // 若放在这个位置可以与goal相符，说明它是一个合法的“遮罩”，可以用于遮住初始串与目标串相异的位置集合X
						ll tmp = 0;
						for (int k = 1; k <= m; ++k)
							if (mask[k] != -1) tmp |= (1ll << (j + k - 1)); // 将这个遮罩压成tmp
						S[j] = max(S[j], tmp); // 更新以j为起始位置的遮罩的最大值
					}
				}
				if (i == len) break;
				if (c[i] == '<') --pos; // 执行第i步code
				if (c[i] == '>') ++pos;
				if (c[i] == '0') mask[pos] = 0;
				if (c[i] == '1') mask[pos] = 1;
			}
			tot = 0;
			for (int i = 1; i <= m; ++i)
				if (mask[i] != -1) ++tot;
			ll ans = 0;
			if (tot <= 18) { // 若遮罩最大不超过18，直接枚举指针放在每个位置时，初始串与目标串相异位置的集合s
				for (int i = 0; i < n; ++i) // 计算被S[i]第一个遮住的原串的个数
					for (ll s = S[i]; ; s = (s - 1ll) & S[i]) { // 相异集合首先是S[i]的子集
						bool flag = 1;
						for (int j = 0; j < i; ++j)
							if ((s | S[j]) == S[j]) { // 同时，不可以被之前的任意一个S遮住
								flag = 0; break;
							}
						if (flag)  ++ans;
						if (!s) break;
					}
			} else { // 否则，能够放遮罩的起始位置个数有限，枚举每个位置上的遮罩能否完全遮住X，计算出F[s]
				cl(F);
				for (int s = 0; s < (1 << (n - m + 1)); ++s) { // s表示S[i]能遮住X的i的集合
					ll now = (1ll << (ll)n) - 1ll;
					for (int i = 0; i < n - m + 1; ++i)
						if (s & (1 << i)) now &= S[i]; // X需要是S[i1],S[i2] ..S[ik]的交集now的子集
					F[s] = 1;
					for (int i = 0; i < n; ++i)
						if (now & (1ll << (ll)i)) F[s] <<= 1ll; 
				}
				for (int i = 0; i < n - m + 1; ++i) { // 计算能被S[i]遮住，但不能被S[0],S[1] .. S[i - 1]遮住的X的个数
					ll now = 0;
					for (int s = (1 << i); s < (1 << (i + 1)); ++s) { // 容斥掉能被S[i]遮住，也能被S[j1], S[j2] ..遮住的X
						if (__builtin_popcount(s) & 1)
							now += F[s];
						else
							now -= F[s];
					}
					ans += now;
				}
			}
			return ans;
		}
};

