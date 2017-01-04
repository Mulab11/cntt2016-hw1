#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class MagicMolecule
{
private:
	int n;
	vector<pair<int, int> > edge;
	bool choose[60];//if we choose Magic Atom #i
	int choosecnt, choosesum, ans;
	int power[60];//magicPower
	void search(int p)//consider constraint #p
	{
		if(choosesum < ans || choosecnt * 3 < n * 2)//worse than answer or not enough atoms
			return;
		if(p == edge.size())//all constraints have been satisfied
		{
			ans = choosesum;
			return;
		}
		if(!choose[edge[p].first] || !choose[edge[p].second])//constraint #p is already satisfied
		{
			search(p + 1);
			return;
		}
		choosecnt--;
		choose[edge[p].first] = false;
		choosesum -= power[edge[p].first];
		search(p + 1);
		choose[edge[p].first] = true;
		choosesum += power[edge[p].first];
		
		choose[edge[p].second] = false;
		choosesum -= power[edge[p].second];
		search(p + 1);
		choose[edge[p].second] = true;
		choosesum += power[edge[p].second];
		choosecnt++;
	}
public:
	int maxMagicPower(vector<int> magicPower, vector<string> magicBond)
	{
		n = magicPower.size();
		edge.clear();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < i; j++)
				if(magicBond[i][j] == 'N')//notice it's not 'Y'
					edge.push_back(make_pair(i, j));
		ans = -1;
		memset(choose, true, sizeof(choose));
		for(int i = 0; i < n; i++)
			choosesum += (power[i] = magicPower[i]);
		choosecnt = n;
		search(0);
		return ans;
	}
};

