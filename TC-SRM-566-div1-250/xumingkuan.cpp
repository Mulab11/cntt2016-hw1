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
#include <queue>
using namespace std;
class PenguinSledding
{
	private:
	bool e[60][60];//edge
	int deg[60];//degree
	public:
	long long countDesigns(int numCheckpoints, vector<int> checkpoint1, vector<int> checkpoint2)
	{
		memset(e, false, sizeof(e));
		memset(deg, 0, sizeof(deg));
		for(int i = 0; i < checkpoint1.size(); i++)//build graph
		{
			e[checkpoint1[i]][checkpoint2[i]] = e[checkpoint2[i]][checkpoint1[i]] = true;
			deg[checkpoint1[i]]++;
			deg[checkpoint2[i]]++;
		}
		long long ans = checkpoint1.size() + 1;//1 edge, empty
		for(int i = 1; i <= numCheckpoints; i++)//stars
			ans += (1ll << deg[i]) - 1 - deg[i];
		for(int i = 1; i <= numCheckpoints; i++)//triangles
			for(int j = i + 1; j <= numCheckpoints; j++)
				if(e[i][j])
					for(int k = j + 1; k <= numCheckpoints; k++)
						if(e[i][k] && e[j][k])
							ans++;
		return ans;
	}
};

