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

class TomekPhone
{
	private:
	vector <int> keyNumbers;
	public:
	int minKeystrokes(vector<int> frequencies, vector<int> keySizes)
	{
		keyNumbers.clear();
		for(int i = 0; i < keySizes.size(); i++)
			for(int j = 1; j <= keySizes[i]; j++)//we need j keystrokes to type the j-th letter on button i
				keyNumbers.push_back(j);
		if(keyNumbers.size() < frequencies.size())
			return -1;
		sort(frequencies.begin(), frequencies.end(), greater <int> ());
		sort(keyNumbers.begin(), keyNumbers.end());
		//greedy: the more frequently the letter appears, the fewer keystrokes to type it
		int ans = 0;
		for(int i = 0; i < frequencies.size(); i++)
			ans += frequencies[i] * keyNumbers[i];
		return ans;
	}
};

