#include <bits/stdc++.h>

using namespace std;

class LittleElephantAndIntervalsDiv1
{
public:
	long long getNumber(int M, vector <int> L, vector <int> R)
	{
		static bool ap[55];
		static int mark[1005];
		memset(mark,255,sizeof mark);
		for(int i = 0;i < L.size();i ++)
			for(int j = L[i];j <= R[i];j ++)
				mark[j] = i; //一个位置只和最后一个涂他的stage有关
		memset(ap,0,sizeof ap);
		int co = 0;
		for(int i = 1;i <= M;i ++)
			if (mark[i] != -1 && !ap[mark[i]]) ++ co,ap[mark[i]] = 1;//统计能影响这个序列的stage的个数
		return (1ll << co);//stage间独立
	}
};
