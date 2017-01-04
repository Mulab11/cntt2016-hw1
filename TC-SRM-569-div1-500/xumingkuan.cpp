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
using namespace std;
class TheJediTest
{
private:
	inline void remove(int &a, int b, int &c)//remove b students from a (to c)
	{
		if(b > a)
			b = a;
		a -= b, c += b;
	}
public:
	int minimumSupervisors(vector<int> students, int K)
	{
		int n = students.size(), ans = 0, now;
		students.push_back(0);
		students.push_back(0);//make it possible to access students[n + 1]
		for(int i = 0; i < n; i++)//greedy
		{
			ans += students[i] / K;//stay at floor i
			if(!(now = students[i] % K))//move students[i] % K to floor i + 1
				continue;
			remove(students[i + 1], K - now, now);//greedily choose students to stay at floor i + 1
			remove(students[i + 2], K - now, now);//greedily choose students to move to floor i + 1
			ans++;
		}
		return ans;
	}
};

