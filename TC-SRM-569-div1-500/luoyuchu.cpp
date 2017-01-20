#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>
void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

class TheJediTest {
    public:
    int minimumSupervisors(vector<int> students, int K) {
		int S[3] = {0};
		int n = students.size();
		int z, Ans = 0;
		if (n == 1) return ((students[0] + K - 1) / K);//对于只有一层楼的情况
		if (n == 2) return ((students[0] + students[1] + K - 1) / K);//如果时两层楼，则集中在一起
		S[1] = students[0];
		S[2] = students[1];
		for (int i = 2; i < n; ++i) {//否则贪心选择
			S[0] = S[1];//S[]为第i-2,i-1,i层楼的剩余学生数量,
			S[1] = S[2];
			S[2] = students[i];
			Ans += (S[0] + K - 1) / K;//第i-2层的学生必须要安排
			z = (S[0] + K - 1) / K * K - S[0];//此时可用第i-1,i层的学生将其补成k的倍数，由于越集中越好，所以之后不用调整i-1,i层的学生
			for (int j = 1; j < 3; ++j) {
				if (S[j] <= z) {
					z -= S[j];
					S[j] = 0;
				}
				else S[j] -= z, z = 0;
			}
		}
		Ans += (S[1] + S[2] + K - 1) / K;//最后剩余的两层
        return Ans;
    }
};
