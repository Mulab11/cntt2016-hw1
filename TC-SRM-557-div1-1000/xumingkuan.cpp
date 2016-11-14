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

class XorAndSum
{
	private:
	long long a[60];//xian xing ji(linear basis), sorted in ascending order
	int n;//size of a[]
	void insert(long long x)
	{
		for(int i = ++n; i >= 1; i--)
			if(a[i - 1] > x)
				a[i] = a[i - 1];
			else
			{
				a[i] = x;
				break;
			}
	}
	public:
	long long maxSum(vector<long long> number)
	{
		n = 0;
		a[0] = 0;
		for(int i = 0; i < number.size(); i++)
		{
			long long now = number[i];
			for(int j = n; j >= 1; j--)
				if((now ^ a[j]) < now)
					now ^= a[j];
			if(now)
				insert(now);
		}
		long long num = 0;
		for(int i = n; i >= 1; i--)
			if((num ^ a[i]) > num)
				num ^= a[i];
		long long ans = num * (number.size() - n + 1);//max value
		for(int i = 1; i < n; i++)//choose other (n - 1) independent bases
		{
			long long tmp = num ^ a[i];
			for(int j = i - 1; j >= 1; j--)
				if((tmp ^ a[j]) > tmp)
					tmp ^= a[j];
			ans += tmp;
		}
		return ans;
	}
};

