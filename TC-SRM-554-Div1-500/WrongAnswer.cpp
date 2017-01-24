#include <vector>
using namespace std;
class TheBrickTowerMediumDivOne{
public:
	vector<int> s[48]; // 从小到大存储每种数值的下标
	bool vis[48]; // vis[i]表示i是否已用过
	vector <int> find(vector <int> heights){
		vector<int> L,R;
		for(int i=0;i<heights.size();i++)s[heights[i]].push_back(i);
		int pos=47;
		for(int i=0;i<heights.size();i++)if(!vis[i]){ // 从前往后考虑第i位应填的数
			for(;pos>heights[i];pos--) // 将比heights[i]大的全部放到右边，同时保证字典序最小
				for(int j=s[pos].size()-1;j>=0&&!vis[s[pos][j]];j--)vis[s[pos][j]]=1,R.push_back(s[pos][j]);
			vis[i]=1;
			L.push_back(i); // 将i放到第i位
		}
		for(int i=R.size()-1;i>=0;i--)L.push_back(R[i]);
		return L;
	}
};
