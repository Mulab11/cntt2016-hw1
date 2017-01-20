#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class BallsSeparating{
	public:
		int minOperations(vector<int> red, vector<int> green, vector<int> blue){
			int n=red.size();
			if (n<3) return -1;
			int ret=1000000000;
			for (int a=0;a<n;++a)
			for (int b=0;b<n;++b) if (a!=b)
			for (int c=0;c<n;++c) if (c!=a&&c!=b){
				int tmp=0;
				for (int i=0;i<n;++i) if (i==a) tmp+=green[i]+blue[i];
				else if (i==b) tmp+=red[i]+blue[i];
				else if (i==c) tmp+=red[i]+green[i];
				else tmp+=red[i]+green[i]+blue[i]-max({red[i],green[i],blue[i]});
				if (tmp<ret) ret=tmp;
			}
			return ret;
		}
};
