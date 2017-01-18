#line 2 "Suminator.cpp"
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
#define maxn 60
typedef long long ll;
using namespace std;
int n, top; // n是序列长度，top是栈顶
ll sta[maxn]; // 题中所说的栈
bool cont[maxn]; // 标记栈中某个位置是否包含了-1标记的数
class Suminator {
	public:
		int findMissing(vector <int> pro, int wanted) {
			top = 0;
			n = pro.size();
			for (int i = 0; i < n; ++i) {
				if (pro[i] <= 0) { // 尝试把-1标记的数赋成0
					if (top > 1) {
						sta[top - 1] += sta[top];
						--top;
					}
				} else {
					sta[++top] = pro[i];
				}
			}
			if (sta[top] == wanted) return 0;
			top = 0; cl(cont); // 否则，-1标记的数会被压到栈中，用cont标记它目前在栈的哪个位置
			for (int i = 0; i < n; ++i) {
				if (pro[i] == 0) {
					if (top > 1) {
						sta[top - 1] += sta[top];
						cont[top - 1] |= cont[top]; // top - 1的位置现在包含了原本top - 1位置与top位置的数……
						cont[top] = 0; --top;
					}
				} else {
					++top;
					if (pro[i] == -1) {
						cont[top] = 1;
						sta[top] = 0;
					} else {
						sta[top] = pro[i];
					}
				}
			}
			if (!cont[top]) { // 如果答案里不包含-1标记的数
				if (sta[top] == wanted) return 1;
				return -1;
			}
			if (sta[top] < wanted) return wanted - sta[top]; // 否则，检查是否能加上一个正数达到wanted
			return -1;
		}
};
