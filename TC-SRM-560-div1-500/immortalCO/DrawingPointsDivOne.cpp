#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

#include <set>

#define fir first
#define sec second

int N;
bool old[150][150];
int cur[300][300];

bool pig(int pace)
{
	++pace;
	memset(cur, 0, sizeof cur);
	for(int x = 0; x != 150; ++x)
		for(int y = 0; y != 150; ++y) if(old[x][y])
			for(int i = 0; i != pace; ++i)
				for(int j = 0; j != pace; ++j)
					cur[x + i][y + j] = 1;
	for(int x = 299; x--; )
		for(int y = 299; y--; )
			cur[x][y] += cur[x + 1][y] + cur[x][y + 1] - cur[x + 1][y + 1];
	for(int x = 150; x--; )
		for(int y = 150; y--; )
		{
			int count = cur[x][y] - cur[x + pace][y] - cur[x][y + pace] + cur[x + pace][y + pace];
			if((count == pace * pace) != old[x][y])
				return 0;
		}
	return 1;
}

class DrawingPointsDivOne
{
public:
	int maxSteps(vector<int> px, vector<int> py)
	{
		N = px.size();
		if(px.size() == 1u) return -1;
		for(int i = 0; i != N; ++i)
			old[px[i] + 70][py[i] + 70] = 1;
		if(!pig(1)) return 0;
		int l = 1, r = 140, m;
		while(l != r)
		{
			m = (l + r + 1) >> 1;
			pig(m) ? l = m : r = m - 1;
		}
		return r == 140 ? -1 : l;
	}
}	user;
