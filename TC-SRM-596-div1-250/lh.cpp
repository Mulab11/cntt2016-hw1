#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class IncrementAndDoubling{
	public:
		int getMin(vector<int> A){
			int ret=0;
			for(;;){
				bool fl=true;
				for (auto &i:A){
					if (i&1){
						--i;
						++ret;
					}
				}
				for (auto &i:A){
					if (i) fl=false;
					i>>=1;
				}
				if (fl) break;
				++ret;
			}
			return ret;
		}
};
