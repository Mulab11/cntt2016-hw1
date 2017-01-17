#include <bits/stdc++.h>

using namespace std;

const int N = 60;

struct Node{
	int x,y;
	Node(){}
	Node(int x,int y):x(x),y(y){}
};
bool operator < (const Node &a,const Node &b){
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}

class TheBrickTowerMediumDivOne{
	public:
		int n,val[N];
		Node a[N];
		
        vector<int> find(vector<int> height){
        	vector <int> ans;
			n = height.size();
        	int len = 0,cnt = 0;
        	val[0] = height[0];ans.push_back(0);
        	for (int i = 1;i < n;i++)
        		if (height[i] <= val[len]) {
        			len++;
        			val[len] = height[i];
        			ans.push_back(i);
				}
				else{
					a[cnt++] = Node(height[i],i);
				}
        	sort(a,a+cnt);
        	for (int i = 0;i < cnt;i++)
        		ans.push_back(a[i].y);
        	return ans;
        }
};
