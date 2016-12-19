#include <bits/stdc++.h>
using namespace std;
class Ear
{
	vector<int> toVectorInt(vector<string> inp)
	{
		stringstream str;
		for(int i = 0; i != (int) inp.size(); ++i) str << inp[i];
		vector<int> ret;
		for(int tmp; str >> tmp; ret.push_back(tmp))	;
		return ret;
	}
	struct Point
	{
		int x, y;
		Point operator - (const Point& p) {return (Point) {x - p.x, y - p.y};}
		long long operator * (const Point& p) {return (long long) x * p.y - (long long) y * p.x;}
	};
public:
	long long getCount(vector<string> inp0, vector<string> inp1, vector<string> inp2)
	{
		vector<int> a = toVectorInt(inp0), b = toVectorInt(inp1), c = toVectorInt(inp2);
		const int N = a.size(), M = b.size();
		assert((int) c.size() == M);
		sort(a.begin(), a.end());
		long long ans = 0; 
		// 枚举两个蓝色点
		for(int p = 0; p != M; ++p) for(int q = 0; q != M; ++q) if(c[p] > c[q])
		{
			int l = 0, r = 0; 
			Point point = (Point) {b[p], c[p]};
			Point vec = ((Point) {b[q], c[q]}) - point;
			// 分别求出左边和右边的方案
			for(int k = N, c = 0; k--; )
			{
				if(a[k] < b[p] && (((Point) {a[k], 0}) - point) * vec > 0) l += c;
				if(a[k] < b[q]) ++c;
			} 
			for(int k = 0, c = 0; k != N; ++k)
			{ 
				if(a[k] > b[p] && (((Point) {a[k], 0}) - point) * vec < 0) r += c;
				if(a[k] > b[q]) ++c;
			}
			ans += l * r;
		}
		return ans;
	}
}	user;