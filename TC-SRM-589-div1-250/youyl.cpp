#include<cstdio>
#include<string>
using namespace std;
struct GooseTattarrattatDiv1
{
	int fat[120],cnt[120],mx[120];
	inline int fnd(int x)// find root for DSU
	{
		if(fat[x]==x)return x;
		return fat[x]=fnd(fat[x]);
	}
	inline int getmin(string S)
	{
		int l=S.length();
		S=" "+S;
		for (int i=1;i<=l;i++)// count the number of each letter
		{
			cnt[S[i]-'a'+1]++;
		}
		for (int i=1;i<=26;i++)// initialize DSU
		{
			mx[i]=cnt[i];
			fat[i]=i;
		}
		for (int i=1;i<=l/2;i++)// join the letters
		{
			fat[fnd(S[i]-'a'+1)]=fnd(S[l+1-i]-'a'+1);
		}
		for (int i=1;i<=26;i++)// calculate the sum and the max value for each conponent
		{
			if(fnd(i)!=i)
			{
				cnt[fnd(i)]+=cnt[i];
				mx[fnd(i)]=max(mx[fnd(i)],mx[i]);
			}
		}
		int ans=0;
		for (int i=1;i<=26;i++)// calculate the answer
		{
			if(fnd(i)==i)ans+=cnt[i]-mx[i];
		}
		return ans;
	}
};