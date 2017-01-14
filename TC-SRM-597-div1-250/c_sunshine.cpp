#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class LittleElephantAndString
{
	public:
	int getNumber(string A,string B)
	{
		//It is impossible if they have different alphabets.
		int cnt[26];
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<A.size();i++)
			cnt[A[i]-'A']++,cnt[B[i]-'A']--;
		for(int i=0;i<26;i++)
			if(cnt[i])return -1;
		//We can change if a suffix of B is a subsequence of A.
		//So we pick the length of the suffix and check it.
		int ans=A.size();
		for(int i=B.size()-1,j=A.size();i>=0;i--)
		{
			for(j--;j>=0&&A[j]!=B[i];j--);
			if(j==-1)break;
			ans=i;
		}
		return ans;
	}
};

