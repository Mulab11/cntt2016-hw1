#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

class TheBrickTowerMediumDivOne
{
public:
	vector<int> find(vector<int> inp)
	{
		// 答案是输入的所有数的和去掉一个最小的
		// ret[0] 一定可以是 0
		// 策略：刚开始取从大到小一连串能取的，然后再从小到大
		const int N = inp.size();
		vector<int> ret;
		vector<pair<int, int> > arr;
		int min = 100000;
		for(int i = 0; i != N; ++i)
			if(inp[i] <= min) min = inp[i], ret.push_back(i);
			else arr.push_back(make_pair(inp[i], i));
		sort(arr.begin(), arr.end());
		for(int i = 0; i != (int) arr.size(); ++i)
			ret.push_back(arr[i].second);
		return ret;
	}
}	user;
