#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

#include <sstream>
int N, T;
vector<string> ans;

string make(int n)
{
	stringstream o;
	o << n;
	o << ".mp3";
	return o.str();
}

void dfs(ll i)
{
	if(i > N || !T) return;
	if(i) ans.push_back(make(i)), --T;
	for(int d = !i; d <= 9; ++d)
		dfs(i * 10 + d);
}

class FoxAndMp3
{
public:
	vector<string> playList(int n)
	{
		N = n;
		T = min(N, 50);
		dfs(0);
		return ans;
	}
}	user;
