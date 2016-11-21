#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class FoxAndMp3{
	private:
		vector<string> ans;
		char use[20];
		int lim;
		void search(int pre){
			if (ans.size()>=50) return;
			sprintf(use,"%d.mp3",pre);
			ans.push_back(use);
			for (int i=0;i<10;++i){
				long long tmp=pre*10ll+i;
				if (tmp>lim) break;
				search(tmp);
			}
			return;
		}
	public:
		vector <string> playList(int n){
			if (n<=50){
				char s[20];
				for (int i=1;i<=n;++i){
					sprintf(s,"%d.mp3",i);
					ans.push_back(s);
				}
				sort(ans.begin(),ans.end());
				return ans;
			}
			else{
				lim=n;
				for (int i=1;i<10;++i) search(i);
				return ans;
			}
		}
};
