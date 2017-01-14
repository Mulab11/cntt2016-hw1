#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

class FoxAndHandle
{
	public:
	
	char cnt[55][26],re[26];
	string S;
	bool can(string str)
	{
		int pos=0,cur;
		//Match the current string.
		for(cur=0;cur<S.size()&&pos<str.size();cur++)
			if(S[cur]==str[pos])
				pos++;
		if(pos<str.size())return 0;
		//For each letter, check if the original string has enough letters after matching the current string.
		for(int j=0;j<26;j++)
			if(cnt[cur][j]<re[j])return 0;
		return 1;
	}
	
	string lexSmallestName(string S)
	{
		this->S=S;
		//cnt[i][j] : the number of letter "j"s in range [i,S.size()-1]
		for(int i=S.size()-1;~i;i--)
			for(int j=0;j<26;j++)
				cnt[i][j]=cnt[i+1][j]+(S[i]-'a'==j);
		for(int i=0;i<26;i++)
			re[i]=cnt[0][i]/2;
		string ans,tmp;
		//Fill in the letters one by one.
		for(int i=0;i<S.size()/2;i++)
		{
			for(int j=0;j<26;j++)//Pick each letter in increasing order and check if it can be filled in next position.
				if(re[j])
				{
					tmp=ans;
					tmp+='a'+j;
					re[j]--;
					if(can(tmp))
					{
						ans=tmp;
						break;
					}
					else re[j]++;
				}
		}
		return ans;
	}
	
};

