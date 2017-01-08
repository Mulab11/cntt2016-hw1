#include<algorithm>
#include<vector>
using namespace std;
int m,n;long long f[66]={};
int cnt[77]={};
class BitwiseAnd
{
public:
	vector<long long> lexSmallest(vector<long long> subset, int N)
	{
		vector <long long >codeforces;
		m=subset.size();
		n=N;
		for(int i=0;i<m;i++)
			f[i]=subset[i];
		for(int i=0;i<m-1;i++)
			for(int j=i+1;j<m;j++)
				if((f[i]&f[j])==0)
					return codeforces;
		for(int i=0;i<m-2;i++)
			for(int j=i+1;j<m-1;j++)
				for(int k=j+1;k<m;k++)
					if((f[i]&f[j]&f[k])>0)
						return codeforces;
		for(int i=0;i<m;i++)
			for(int j=0;j<60;j++)
				if(f[i]&(1LL<<j))
					cnt[j]++;
		for(int i=0;i<m;i++)
			codeforces.push_back(f[i]);
		while(m<n)
		{
			long long temp=0;
			for(int i=0;i<m;i++)
			{
				for(int j=0;j<60;j++)
					if((f[j]>>j&1)&&cnt[j]==1)
					{
						temp|=1LL<<j;
						cnt[j]++;
						break;
					}
				if(!(f[i]&temp))return {};
			}
			int rem=n-m-1;
			for(int i=0;i<60&&rem;i++)
				if(cnt[i]==0)
					temp|=1LL<<i,cnt[i]++,rem--;
			if(rem)return {};
			codeforces.push_back(temp);
			f[m++]=temp;
		}
		sort(codeforces.begin(),codeforces.end());
		return codeforces;
	}
};
