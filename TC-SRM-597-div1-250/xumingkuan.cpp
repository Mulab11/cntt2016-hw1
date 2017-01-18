#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;

class LittleElephantAndString
{
private:
	int n;
	int f[55][55];//longest same string
	int cnt[30];
public:
	int getNumber(string A, string B)
	{
		memset(cnt, 0, sizeof(cnt));
		n = A.size();
		for(int i = 0; i < n; i++)
		{
			cnt[A[i] - 'A']++;
			cnt[B[i] - 'A']--;
		}
		for(int i = 0; i < 26; i++)
			if(cnt[i])
				return -1;
		int ptr = n - 1;
		for(int i = n - 1; i >= 0; i--, ptr--)
		{
			while(ptr >= 0 && B[i] != A[ptr])
				ptr--;
			if(ptr < 0)
				return i + 1;
		}
		return 0;
	}
};

