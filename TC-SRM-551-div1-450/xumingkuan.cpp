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

class ColorfulWolves
{
	private:
	int f[60];
	priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > q;
	public:
	int getmin(vector<string> colormap)
	{
		const int n = colormap.size();
		memset(f, 63, sizeof(f));
		f[0] = 0;
		q.push(make_pair(0, 0));
		while(!q.empty())//dijkstra
		{
			int now = q.top().second;
			if(f[now] != q.top().first)
			{
				q.pop();
				continue;
			}
			q.pop();
			int cnt = 0;
			for(int i = 0; i < n; i++)
				if(colormap[now][i] == 'Y')
				{
					if(f[i] > f[now] + cnt)
						q.push(make_pair(f[i] = f[now] + cnt, i));
					cnt++;
				}
		}
		return f[n - 1] > 10101010 ? -1 : f[n - 1];
	}
};

