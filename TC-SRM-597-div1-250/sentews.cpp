#include<cstdio>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
string a,b;
int f[55][55]={};int ans=1111111;
int cnt1[33]={},cnt2[33]={};
class LittleElephantAndString
{
public:
	int getNumber(string A, string B)
	{
		a=A,b=B;
		for(int i=0;i<a.size();i++)
			cnt1[a[i]-'A']++;
		for(int i=0;i<b.size();i++)
			cnt2[b[i]-'A']++;
		for(int i=0;i<26;i++)
			if(cnt1[i]!=cnt2[i])
				return -1;
		for(int i=1;i<=a.size()+1;i++)
			f[i][b.size()+1]=1;
		for(int i=a.size();i>0;i--)
			for(int j=b.size();j>0;j--)
			{
				f[i][j]=f[i+1][j]||(a[i-1]==b[j-1]&&f[i+1][j+1]);
				if(f[i][j])
					ans=min(ans,j);
			}
		return ans-1;
	}
};
