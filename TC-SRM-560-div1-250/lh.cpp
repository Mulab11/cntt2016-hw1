#include<queue>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TomekPhone{
	priority_queue<int,vector<int>,greater<int> > q;
	public:
	int minKeystrokes(vector<int> frequencies, vector<int> keySizes){
		int n=keySizes.size(),m=frequencies.size();
		for (int i=0;i<n;++i){
			for (int j=1;j<=keySizes[i];++j) q.push(j);
		}
		sort(frequencies.begin(),frequencies.end());
		reverse(frequencies.begin(),frequencies.end());
		int ans=0;
		for (int i=0;i<m;++i){
			if (q.empty()) return -1;
			ans+=q.top()*frequencies[i];
			q.pop();
		}
		return ans;
	}
};
