#include <algorithm>
using namespace std;
int n, w[500];
class EllysRoomAssignmentsDiv1
{
public:
	void Parse(const vector<string> &vec, int *arr, int &cnt)
	{
		string str;
		for(int i = 0; i < vec.size(); i++)
			str += vec[i];
		for(int i = 0; i < str.length(); i++)
		{
			if(str[i] == ' ')
				cnt++;
			else
				arr[cnt] = arr[cnt] * 10 + (str[i] - '0');
		}
		cnt++;
	}
	double getAverage(vector<string> ratings)
	{
		Parse(ratings, w, n);
		for(int i = 0; i < n; i++)
			w[i] *= 2;
		w[0]++;
		sort(w, w + n, [] (int a, int b)
		{
			return a > b;
		});
		int m = (n + 19) / 20;
		double ans = 0, sum = 0;
		for(int i = 0; i < n; i += m)
		{
			sum = 0;
			for(int j = i; j < i + m && j < n; j++)
			{
				if(w[j] & 1)
					sum += w[j] / 2; //自己所在的轮次 
			}
			if(sum)
				ans += sum; 
			else
			{
				for(int j = i; j < i + m && j < n; j++)
					sum += w[j] / 2;
				if(i + m <= n)
					ans += sum / m; //概率均等 
				else //最后一轮 
					ans = (double)(m - n % m) / m * ans / (n / m) * (n / m + 1) + (double)(n % m) / m * (ans + sum / (n % m));
			}
		}
		return ans / ((n + m - 1) / m);
	}
}; 