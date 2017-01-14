#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<sstream>
#include<vector>
using namespace std;
typedef long long LL;

vector <int> get_vi(vector<string> str)
{
	stringstream s;
	for(int i=0;i<str.size();i++)s<<str[i];
	vector<int> res;
	int u;
	while(s>>u)res.push_back(u);
	return res;
}

class Ear
{
	public:
	int n,m;
	vector<int> rx,bx,by;
	
	LL getCount(vector<string> _redX,vector<string> _blueX,vector<string> _blueY)
	{
		rx=get_vi(_redX);
		bx=get_vi(_blueX);
		by=get_vi(_blueY);
		sort(rx.begin(),rx.end());
		n=rx.size(),m=bx.size();
		LL res=0;
		//Pick all possible points pair (P,Q).
		for(int p=0;p<m;p++)
			for(int q=0;q<m;q++)
				if(by[p]>by[q])
				{
					int i,j,c1,c2;
					//Find right most red point B
					for(i=-1;i<n-1&&rx[i+1]<bx[q];i++);
					//Find right most red point A
					for(j=-1;j<n-1&&rx[j+1]<bx[p]&&(bx[q]-rx[j+1])*by[p]-(bx[p]-rx[j+1])*by[q]>0;j++);
					//Calculate the sum of the arithmetic progression
					c1=(i-j+i)*(j+1)/2;
					//Find left most red point C
					for(i=n;i>0&&rx[i-1]>bx[q];i--);
					//Find left most red point D
					for(j=n;j>0&&rx[j-1]>bx[p]&&(bx[q]-rx[j-1])*by[p]-(bx[p]-rx[j-1])*by[q]<0;j--);
					//Calculate the sum of the arithmetic progression
					c2=(j-i+n-1-i)*(n-j)/2;
					res+=c1*c2;
				}
		return res;
	}
};

