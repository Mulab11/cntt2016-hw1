#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

const int MAXN = 77777 + 100;

class TheSquareRootDilemma
{
	public:
	int countPairs(int N, int M)
	{
		int ans = 0;
		for(int i = 1; i <= N; i++)
		{
			int a = i;
			for(int j = 2; j * j <= a; j++)
				while(a % (j * j) == 0)
					a /= (j * j);
			for(int j = 1; a * j * j <= M; j++)
				ans++;
		}
		return ans;
	}
};

