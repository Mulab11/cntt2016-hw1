#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <queue>
#include <map>
#include <set>
using namespace std;

class EllysRoomAssignmentsDiv1
{
private:
	vector<int> concatenate(const vector<string> &vec)
	{
		static char buf[10101];
		char *head = buf, *tail = buf;
		for(int i = 0; i < vec.size(); i++)
			tail += sprintf(tail, "%s", vec[i].c_str());
		vector<int> ret;
		while(1)
		{
			char ch = *head++;
			if(head > tail)
				return ret;
			while(ch < '0' || ch > '9')
			{
				ch = *head++;
				if(head > tail)
					return ret;
			}
			int tmp = 0;
			while(ch >= '0' && ch <= '9')
			{
				tmp = tmp * 10 + ch - '0';
				ch = *head++;
			}
			ret.push_back(tmp);
		}
		return ret;
	}
	vector<int> rating;
public:
	double getAverage(vector<string> ratings)
	{
		rating = concatenate(ratings);
		int elly = rating[0];
		sort(rating.begin(), rating.end(), greater<int>());
		int N = rating.size();//simulate the algorithm in the description of this problem
		int R = (N - 1) / 20 + 1;
		int num = N / R;
		int sum = 0;
		for(int i = 0; i < num; i++)
		{
			int now = 0;
			for(int j = 0; j < R; j++)
			{
				now += rating[i * R + j];
				if(rating[i * R + j] == elly)//rank (i * R + j) is Elly, as no two ratings in the list are equal
				{
					now = 0;
					break;
				}
			}
			sum += now;
		}
		int sum2 = 0;
		for(int i = num * R; i < N; i++)
		{
			sum2 += rating[i];
			if(rating[i] == elly)//Elly has one of the lowest ratings...
				return ((double)sum / R + elly) / (num + 1);
		}
		double ans1 = ((double)sum / R + elly) / num;//if Elly's room has num people
		double ans2 = (N % R ? ((double)sum / R + (double)sum2 / (N % R) + elly) / (num + 1) : 0);//if Elly's room has (num + 1) people
		return ans1 * ((double)(R - N % R) / R) + ans2 * ((double)(N % R) / R);
	}
};

