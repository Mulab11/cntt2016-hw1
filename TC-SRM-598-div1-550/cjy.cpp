#include<bits/stdc++.h>
using namespace std;
class FoxAndFencing
{
	public:
		string WhoCanWin(int a,int b,int x,int y,int d)
		{
			if(a+x>=d||a>b&&a+x>b+b+y)return"Ciel";
			if(b+y>=d+a||b>a&&b+y>a+a+x)return"Liss";
			return"Draw";
		}
};
