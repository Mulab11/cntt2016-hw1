#include <algorithm>
using namespace std;
class ColorfulWolves
{
public:
	int n, f[50][50];
	int getmin(vector<string> color_map)
	{
		n = color_map.size();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				f[i][j] = 1000000000;
		}
		for(int i = 0; i < n; i++) //建图 
		{
			for(int j = 0, k = 0; j < n; j++)
			{
				if(color_map[i][j] == 'Y')
					f[i][j] = k++;
			}
		}
		for(int k = 0; k < n; k++) //最短路 
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
		return f[0][n - 1] < 1000000000 ? f[0][n - 1] : -1;
	}
};
