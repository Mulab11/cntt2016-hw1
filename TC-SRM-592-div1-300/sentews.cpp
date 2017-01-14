#include<algorithm>
#include<string>
int n;
using namespace std;
int f[111]={};
int cnt[11]={};
class LittleElephantAndBalls
{
public:
	int getNumber(string S)
	{
		int codeforces=0;
		int n=S.size();
		for(int i=0;i<S.size();i++)
			switch(S[i])
			{
			case 'R':
				f[i]=1;break;
			case 'G':
				f[i]=2;break;
			case 'B':
				f[i]=4;break;
			}
		int k=0;
		for(int i=0;i<n;i++)
		{
			int temp=f[i];
			if(++cnt[temp]<3)codeforces+=k++;
			else codeforces+=k;
		}
		return codeforces;
	}
};
