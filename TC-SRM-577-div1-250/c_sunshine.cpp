#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class EllysRoomAssignmentsDiv1
{
	public:
	double getAverage(vector<string> ratings)
	{
		string in_s;
		for(int i=0;i<ratings.size();i++)in_s+=ratings[i];
		vector<int> rating;
		int my;
		for(int i=0;i<in_s.size();i+=5)
		{
			int r=(in_s[i]-'0')*1000+(in_s[i+1]-'0')*100+(in_s[i+2]-'0')*10+(in_s[i+3]-'0')*1;
			if(i==0)my=r;
			rating.push_back(r);
		}
		int R=(rating.size()+19)/20;
		double ans=0;
		sort(rating.begin(),rating.end(),greater<int>());
		for(int i=0;i*R+R<=rating.size();i++)
		{
			double sum=0;
			if(my<=rating[i*R]&&my>=rating[i*R+R-1])//This group contains i.
				sum=my*R;
			else//This group does not contain i.
				for(int j=0;j<R;j++)
					sum+=rating[i*R+j];
			ans+=sum/R;
		}
		int cnt=rating.size()/R;
		ans/=cnt;
		if(rating.size()%R==0)return ans;
		if(my<=rating[cnt*R])
			return (ans*cnt+my)/(cnt+1);
		int L=rating.size()%R;
		double sum=0;//Sum of extra contestants' rating
		for(int i=1;i<=L;i++)
			sum+=rating[rating.size()-i];
		sum/=L;
		//The possibility that Elly's room contains another contestant is L/R
		return ((double)L/R)*(ans*cnt+sum)/(cnt+1)+(1.0-(double)L/R)*ans;
	}
};

