// BEGIN CUT HERE

// END CUT HERE
#line 5 "CharacterBoard.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

typedef map<int,int> map0;
typedef set<int> set0;

map0 s;
set0 s2;

class CharacterBoard{
	#define P 1000000009
	int fast_pow(int x,int y){
		int ret=1;
		while (y){
			if (y&1) ret=1LL*ret*x%P;
			x=1LL*x*x%P;
			y=y>>1;
		}
		return ret;
	}
	int r,c;
	public:
	int countGenerators(vector <string> fragment, int W, int i0, int j0){
		r=fragment.size();
		c=fragment[0].size();
		s.clear();
		for (int dltX=0;dltX<r;++dltX)for (int dltY=dltX?-c+1:1;dltY<c;++dltY){
//			printf("%lld %lld\n",dltX,dltY);
			bool found=0;
			for (int i=0;i+dltX<r&&!found;++i)for (int j=max(0,-dltY);j+dltY<c&&j<c&&!found;++j)
				if (fragment[i][j]!=fragment[i+dltX][j+dltY]) found=1;
			ll num=1LL*dltX*W+dltY;
			for (ll i=1;i*i<=num;++i)if (num%i==0){
				map0::iterator it=s.find(i);
				if (it==s.end()) s.insert(make_pair(i,found?-1:0));
				else if (found) (it->second)=-1;
				ll j=num/i;
				if (j==i||j>W) continue;
				it=s.find(j);
				if (it==s.end()) s.insert(make_pair(j,found?-1:0));
				else if (found) (it->second)=-1;
			}
		}
		int last=0,ret=0;
		ll inv25=fast_pow(25,P-2);
		s.insert(make_pair(W+1,-1));
		for (map0::iterator it=s.begin();it!=s.end();++it){
			int l=it->first;
//			printf("%d %d\n",it->first,it->second);
			if (it->second>=0){
				int left=r*c;
				s2.clear();
				for (int i=0;i<r;++i)for (int j=0;j<c;++j){
					int now=(1LL*i*W+j)%l;
					if (s2.find(now)==s2.end()) s2.insert(now);
					else --left;
				}
//				printf("%d\n",left);
				(ret+=fast_pow(26,l-left))%=P;
			}
			if (last+1<l) ret=(inv25*fast_pow(26,last+1-r*c)%P*(fast_pow(26,l-last-1)-1)+ret)%P;
			last=l;
		}
		return ret;
	}
};
