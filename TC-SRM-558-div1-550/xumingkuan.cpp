#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
const int MAXN = 310;
char buf[10101];
char *head, *tail;
inline bool inputnum(int &ret)
{
	ret = 0;
	char ch = *head++;
	if(head > tail)
		return false;
	while(ch < '0' || ch > '9')
	{
		ch = *head++;
		if(head > tail)
			return false;
	}
	while(ch >= '0' && ch <= '9')
	{
		ret = ret * 10 + ch - '0';
		ch = *head++;
	}
	return true;
}
class Ear
{
	private:
	int nr, nb, red[MAXN];
	int sum[10101];//sum[i] = number of red points in [1, i]
	pair <int, int> blue[MAXN];//first = y, second = x
	void copy_into_buf(vector <string> vec)
	{
		head = tail = buf;
		for(int i = 0; i < vec.size(); i++)
			tail += sprintf(tail, "%s", vec[i].c_str());
	}
	public:
	long long getCount(vector<string> redX, vector<string> blueX, vector<string> blueY)
	{
		nr = nb = 0;
		copy_into_buf(redX);
		while(inputnum(red[++nr]));
		--nr;
		copy_into_buf(blueX);
		while(inputnum(blue[++nb].second));
		--nb;
		copy_into_buf(blueY);
		for(int i = 1; i <= nb; i++)
			inputnum(blue[i].first);
		memset(sum, 0, sizeof(sum));
		for(int i = 1; i <= nr; i++)
			sum[red[i]]++;
		for(int i = 1; i <= 10001; i++)
			sum[i] += sum[i - 1];
		sort(blue + 1, blue + nb + 1);//sort by y (y is distinct)
		long long ans = 0;
		for(int i = 1; i <= nb; i++)//enumerate point P
			for(int j = 1; j < i; j++)//enumerate point Q
			{
				int st = blue[i].second, ed = blue[j].second + (blue[j].second - blue[i].second) * blue[j].first / (blue[i].first - blue[j].first);
				if(st > ed)//x is distinct
					swap(st, ed);//A and B aren't in [st, ed]
				if(st < 1)
					st = 1;
				if(ed > 10000)
					ed = 10000;
				const int A = sum[st - 1], B = sum[blue[j].second - 1] - sum[st - 1], C = sum[ed] - sum[blue[j].second], D = sum[10000] - sum[ed];//number of point A B C D
				ans += (long long)(A * (A - 1) / 2 + A * B) * (D * (D - 1) / 2 + D * C);
			}
		return ans;
	}
};

