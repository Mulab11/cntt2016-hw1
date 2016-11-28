#include <algorithm>
using namespace std;
bool e[50][50];
class PenguinSledding
{
public:
	long long countDesigns(int n, vector<int> u, vector<int> v)
	{
		for(int i = 0; i < u.size(); i++)
			e[u[i] - 1][v[i] - 1] = e[v[i] - 1][u[i] - 1] = 1;
		long long ans = u.size() + 1; //孤立边或无边 
		for(int i = 0; i < n; i++) //三阶完全图 
		{
			for(int j = i + 1; j < n; j++)
			{
				for(int k = j + 1; k < n; k++)
					ans += e[i][j] && e[j][k] && e[k][i];
			}
		}
		for(int i = 0; i < n; i++) //星状图 
		{
			int sum = 0;
			for(int j = 0; j < n; j++)
				sum += e[i][j];
			ans += (1LL << sum) - (sum + 1);
		}
		return ans;
	}
};
