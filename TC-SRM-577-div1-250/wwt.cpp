#include <bits/stdc++.h>

using namespace std;

class EllysRoomAssignmentsDiv1
{
public:
	void decode(vector<string> r,vector<int> &a)
	{
		a.clear();
		int x = 0;
		for(auto p : r)
			for(auto q : p)
			{
				if (q == ' ') 
				{
					if (x) a.push_back(x);
					x = 0;
				} else
					x = x * 10 + q - 48;
			}
		if (x) a.push_back(x);
	}

	double getAverage(vector<string> ratings)
	{
		vector<int> a;
		decode(ratings,a);
		int my_rating = a[0],n = a.size();
		sort(a.begin(),a.end());
		reverse(a.begin(),a.end());
		int r = (n / 20) + bool(n % 20);
		double cur_ans = 0;//expected sum
		int cur_people = 0;//the number of people in the same room
		for(int i = 0;i < n;)
		{
			int j = min(i + r,n);
			double s = 0;
			for(int k = i;k < j;k ++) s += a[k];
			s /= (j - i); //expected rating
			if (j - i == r && j != n)
			{
				cur_people ++;
				if (my_rating <= a[i] && my_rating > a[j]) cur_ans += my_rating; else
					cur_ans += s;
			} else
			{
				if (my_rating <= a[i]) return (cur_ans + my_rating) / (cur_people + 1);
				//choose j-i rooms from r rooms,the probability that it chooses my room
				double p = 1.0 - (r - (j - i)) / double(r); // 1 - c(r-1,j-i)/c(r,j-i)
				return (cur_ans + s) / (cur_people + 1) * p + cur_ans / max(1,cur_people) * (1 - p);
			}
			i = j;
		}
	}
};
