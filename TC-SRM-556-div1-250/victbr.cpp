#include <bits/stdc++.h>

using namespace std;

class XorTravelingSalesman{
	public:
		int n,e[60*1024],d[60*1024];
		bool b[60][1400];
		int maxProfit(vector <int> cityValues, vector <string> roads){
			n = cityValues.size();
			memset(b,0,sizeof(b));
			b[0][cityValues[0]] = 1;
			int t = 1,w = 1;e[1] = 0;d[1] = cityValues[0];
			while (t <= w){
				int u = e[t],s = d[t];
				for (int i = 0;i < n;i++)
					if (roads[u][i] == 'Y'){
						int x = i,y = s^cityValues[i];
						if (b[x][y] == 0){
							b[x][y] = 1;
							e[++w] = x;
							d[  w] = y;
						}
					}
				t++;
			}
			for (int i = 1023;i >= 0;i--)
				for (int j = 0;j < n;j++)
					if (b[j][i]) return i;
			return -1;
		}
};
