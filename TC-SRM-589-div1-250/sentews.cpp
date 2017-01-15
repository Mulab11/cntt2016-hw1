#include<cstdio>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
int gen[33]={},cnt[33]={};int n;
char s[222]={};
int find(int a)
{
	return gen[a]==a?a:gen[a]=find(gen[a]);
}
class GooseTattarrattatDiv1
{
public:
	int getmin(string S)
	{
		int n=S.size();
		for(int i=0;i<n;i++)
			s[i]=S[i];
		for(int i=0;i<26;i++)
			gen[i]=i;
		for(int i=0;i<n;i++)
			cnt[s[i]-'a']++;
		for(int i=0;i<n/2;i++)
		{
			int x=s[i]-'a',y=s[n-1-i]-'a';
			if(x!=y)
			{
				int fx=find(x),fy=find(y);
				if(fx!=fy)
					gen[fx]=fy;
			}
		}
		int codeforces=0;
		for(int i=0;i<26;i++)
		{
			if(gen[i]==i)
			{
				int a=0,b=0;
				for(int j=0;j<26;j++)
				{
					if(find(j)==i)
						a+=cnt[j],b=max(b,cnt[j]);
				}
				codeforces=codeforces+a-b;
			}
		}
		return codeforces;
	}
};
