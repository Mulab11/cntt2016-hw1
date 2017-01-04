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
using namespace std;
class FoxAndMp3
{
private:
	vector<string> ans;
	int n;
	string to_string(int num)
	{
		static char buf[20];
		sprintf(buf, "%d.mp3", num);
		return string(buf);
	}
	void search(int num)//search mp3s with prefix num
	{
		if(ans.size() == 50 || ans.size() == n)
			return;
		ans.push_back(to_string(num));
		for(int i = 0; i <= 9 && (long long)num * 10 + i <= n; i++)//in lexicographic order
			search(num * 10 + i);
	}
public:
	vector<string> playList(int n)
	{
		ans.clear();
		this->n = n;
		for(int i = 1; i <= 9 && i <= n; i++)//the first digit
			search(i);
		return ans;
	}
};

