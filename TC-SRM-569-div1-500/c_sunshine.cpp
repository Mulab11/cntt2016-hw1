#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class TheJediTest
{
	public:
	int minimumSupervisors(vector<int> students,int K)
	{
		int n=students.size(),ans=0,tmp,tmp2;
		for(int i=0;i<n;i++)
		{
			ans+=(students[i]+K-1)/K;
			tmp=(K-students[i]%K)%K;//The capacity of this floor.
			if(i+1<n)//Children in next floor can come.
			{
				tmp2=min(students[i+1],tmp);
				tmp-=tmp2,students[i+1]-=tmp2;
			}
			//Children in floor i,i+1,i+2 can go to floor i+1 to be managed.
			if(i+2<n)students[i+2]-=min(students[i+2],tmp);
		}
		return ans;
	}
};

