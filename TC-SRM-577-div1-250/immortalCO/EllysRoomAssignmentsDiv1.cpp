#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

#include <sstream>

class EllysRoomAssignmentsDiv1
{
public:
	double getAverage(vector<string> vec)
	{
		stringstream ss;
		for(int i = 0; i != (int) vec.size(); ++i) ss << vec[i];
		vector<int> list;
		int tmp;
		while(ss >> tmp) list.push_back(tmp);
		int my = list[0];
		sort(list.begin(), list.end());
		int R = (list.size() + 19) / 20;
		
		int pos = -1, cnt = 0;
		vector<int> layer[50];
		bool frog = (list.size() % R) == 0;
		while(list.size())
		{
			for(int i = 0; i != R && list.size(); ++i)
			{
				layer[cnt].push_back(list.back());
				list.back() == my ? pos = cnt : 0;
				list.pop_back();
			}
			++cnt;
		}
		if(frog)
		{
			double sum = 0;
			for(int i = 0; i != cnt; ++i)
			{
				if(i == pos) continue;
				double tmp = 0;
				for(int j = 0; j != (int) layer[i].size(); ++j)
					tmp += layer[i][j];
				sum += tmp / R;
			}
			return (sum + my) / cnt;
		}
		else if(pos + 1 != cnt)
		{
			double sum = 0;
			for(int i = 0; i + 1 != cnt; ++i)
			{
				if(i == pos) continue;
				double tmp = 0;
				for(int j = 0; j != (int) layer[i].size(); ++j)
					tmp += layer[i][j];
				sum += tmp / R;
			}
			double ans = 0;
			for(int j = 0; j != R; ++j)
			{
				if(j < (int) layer[cnt - 1].size()) ans += (sum + my + layer[cnt - 1][j]) / cnt;
				else ans += (sum + my) / (cnt - 1);
			}
			return ans / R;
		}
		else
		{
			double sum = 0;
			for(int i = 0; i + 1 != cnt; ++i)
			{
				double tmp = 0;
				for(int j = 0; j != (int) layer[i].size(); ++j)
					tmp += layer[i][j];
				sum += tmp / R;
			}
			return (my + sum) / cnt;
		}
		
	}
}   user;
