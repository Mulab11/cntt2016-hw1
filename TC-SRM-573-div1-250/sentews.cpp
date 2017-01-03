#include<algorithm>
using namespace std;
class TeamContest
{
	public:
	int worstRank(vector <int> strength)
	{
		int n=strength.size();
		int s[333]={};
		for(int i=0;i<n;i++)
			s[i]=strength[i];
		int sum=1;
		sort(s,s+3);
		sort(s+3,s+n);
		int tou=3,wei=n-1;
		int cmp=s[0]+s[2];
		while(tou<=wei)
		{
			if(s[tou]+s[wei]<=cmp)
			{tou++;continue;}
			if(tou+2<=wei)
			sum++,tou+=2,wei--;
			else
			break;
		}
		return sum;
	}
};
