#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

class NewArenaPassword
{
	public:
	bool vis[444]={};
	int cnt[333]={},cntt=0;
	int maxx=0;
	int minChange(string oldPassword, int K)
	{
		int temp=0;
		int step=oldPassword.size()-K;
		if(step==0)
		return 0;
		for(int i=0;i<oldPassword.size();i++)
		{
			if(vis[i])
				continue;
			cntt=0;maxx=0;
			for(int j=0;j<26;j++)
				cnt[j]=0;
			for(int j=i;j<oldPassword.size();j=j+step)
				cnt[oldPassword[j]-'a']++,cntt++,vis[j]=1;
			for(int j=0;j<26;j++)
				if(maxx<cnt[j])
					maxx=cnt[j];
			temp+=cntt-maxx;
		}
		return temp;
	}
};
