#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;

class FindPolygons
{
	public:
	vector<pair<pair<int,int>,int > > P;
	double minimumPolygon(int L)
	{
		//For each triad (a,b,c) satisfying a^2+b^2=c^2, a+b=c \pmod 2.
		//So it is impossible to create a grid polygon with perimeter L if L is odd.
		if(L&1)return -1;
		//Don't forget it is impossible when L=2, too.
		if(L==2)return -1;
		//If L is even, it is clear that we can create a rectangle with the minimum difference L/2 mod 2
		//The only remaining work is to check if it can be a triangle
		int ans=L+1;
		//Find all possible segments for sides.
		for(int c=1;c<=L/2;c++)
			for(int a=1;a<=c;a++)
			{
				int b=int(sqrt(c*c-a*a)+.5);
				if(a*a+b*b==c*c)
					P.push_back(make_pair(make_pair(a,b),c));
			}
		//cout<<P.size()<<endl;
		//We can prove that any triangle has an angle that can be in one quartile.
		//So it is enough to pick each pair of segments in the first quartile.
		for(int i=0;i<P.size();i++)
			for(int j=i+1;j<P.size();j++)
			{
				int A=P[i].second,B=P[j].second,C,a,b;
				a=P[i].first.first-P[j].first.first;
				b=P[i].first.second-P[j].first.second;
				C=int(sqrt(a*a+b*b)+.5);
				//The if the length of last side of the triangle is integer.
				if(a*a+b*b==C*C&&A+B+C==L&&L>2*max(A,max(B,C)))
					ans=min(ans,max(max(A,B),C)-min(min(A,B),C));//Update the answer.
			}
		if(ans<=L)return ans;
		//Otherwise return L/2 mod 2.
		L/=2;
		return L&1;
	}
};

