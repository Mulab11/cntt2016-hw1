#include<bits/stdc++.h>
using namespace std;
const int N=20+5;
class TheJediTest
{
	public:
		int minimumSupervisors(vector <int> students,int k)
		{
			int a[N]={0};
			//a[i]表示第i层有多少是来自第i-1层的 
			int ans=0;
			for(int i=0,tmp;i<students.size();++i)
			{
				ans+=(a[i]+students[i])/k;
				
				if(tmp=(a[i]+students[i])%k)//如果当前第i层的人数不是k的倍数 
					if(i+1<students.size())//如果它还有它的第i+1层 
						if(tmp<=students[i])a[i+1]=tmp;//如果第i层的人数可以把多出来的这部分扔到下一层的话 
						else//用第i+1层的人尽量填满第i层 
						{
							students[i+1]-=min(students[i+1],k-tmp);
							++ans;
						}
					else ++ans;//如果已经没有i+1层的话，多出来的这部分就只能自力更生了！ 
			}
			
			return ans;
		}
};