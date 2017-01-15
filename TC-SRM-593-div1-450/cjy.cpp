#include<bits/stdc++.h>
using namespace std;
set<int> S={0};
vector<int> r,e;
int A,B,i,R;
class MayTheBestPetWin
{
	public:
		int calc(vector<int> a,vector<int> b)
		{
			for(i=0;i<a.size();i++)
			{
				A+=a[i];B+=b[i];r=e;
				for(auto x : S)r.push_back(x+a[i]+b[i]);
				S.insert(r.begin(),r.end());
			}
			R=B;
			for(auto x : S)R=min(R,max(B-x,x-A));
			return R;
		}
};
