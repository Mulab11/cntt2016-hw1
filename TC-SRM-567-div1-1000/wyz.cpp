// BEGIN CUT HERE

// END CUT HERE
#line 5 "Mountains.cpp"
#include <bits/stdc++.h>
#define ll long long
#define P 1000000009

using namespace std;
const int maxw=50;
int W;
struct Mask{int h[maxw];Mask(){memset(h,0,sizeof(h));}};
inline bool operator <(const Mask &u,const Mask &v){
	for (int i=0;i<W;++i)
		if (u.h[i]<v.h[i]) return 1;
		else if (u.h[i]>v.h[i]) return 0;
	return 0;
}
void add(Mask &res,const Mask &u,const int pos,const int height){
	res=u;
	for (int i=max(0,pos-height);i<W&&i<pos+height;++i)
		res.h[i]=max(res.h[i],height-abs(i-pos));
}

const int maxn=12;
typedef map<Mask,int> map0;

#define inc(x,y) if(((x)+=(y))>=P)x-=P;

class Mountains{
	int n;
	map0 dp[maxn];
	void trans(map0 &to,const Mask &now,int cnt,int _l,int _r,int _height){
		for (int i=0;i<W;++i){
			Mask v;
			add(v,now,i,_height);
			bool found=0;
			for (int j=0;j<W;++j)
				if ((_l<=j&&j<=_r)^(now.h[j]!=v.h[j])){
					found=1;
					break;
				}
			if (found) continue;
			map0::iterator it=to.find(v);
			if (it==to.end()) to.insert(make_pair(v,cnt));
			else inc(it->second,cnt);
		}
	}
	public:
	int countPlacements(vector <int> heights, vector <string> visibility){
		W=visibility[0].size();
		n=heights.size();
		dp[n].insert(make_pair(Mask(),1));
		for (int i=n;i;--i){
			int l=W,r=-1;
			for (int j=0;j<W;++j)
				if (visibility[i-1][j]=='X')
					l=min(l,j),r=max(r,j);
			for (map0::iterator it=dp[i].begin();it!=dp[i].end();++it)
				trans(dp[i-1],it->first,it->second,l,r,heights[i-1]);
		}
		int ret=0;
		for (map0::iterator it=dp[0].begin();it!=dp[0].end();++it)
			(ret+=it->second)%=P;
		return ret;
	}
};
