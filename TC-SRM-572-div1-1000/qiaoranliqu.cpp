#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
map<int,int>mp;
const int inf=(int)1e9;
int i,j,m,n,p,k,ans=inf,dir;
vector<pair<int,int> >v;
class NextAndPrev{
	public:
		int getMinimum(int nextCost, int prevCost, string start, string goal)
		{
				if (start==goal) return 0; //如果初始解和终态相同,那么不需要移动即可. 
				for (i=0;i<26;++i) mp[i]=' ';
				for (i=0;i<(int)start.size();++i) 
				{
						int st=start[i]-'a',ed=goal[i]-'a';
						if (mp[st]==' ') mp[st]=ed;
						else if (mp[st]!=ed) return -1;
				}
				int GG=-1000000;
				for (i=0;i<26;++i) 
					if (mp[i]==' ') break;
					else 
					{
							int now=mp[i]-i;
							if (now<0) now+=26;
							if (GG==-1000000) GG=now;
							else if (GG!=now) break;
					}
				if (i==26) return -1;
				//一种特殊的情况:假设26种字母每个字母都要向前或向后移动相同的位置,那么是不可能移动的,所以不可能实现 
				for (i=0;i<26;++i) 
					if (mp[i]!=' ') v.pb(mk(i,mp[i]));
				m=v.size();
				for (k=0;k<m;++k) //枚举一个位置k将环断开 
				{ 
					for (j=0;j<m-1;++j) if (v[j].se>v[j+1].se) break; //要完成匹配那么所有点的匹配路径一定不能有交叉 
					if (j==m-1)
					{
							for (dir=-1;dir<=2;++dir) //考虑每个位置匹配的情况,有可能所有点都向前走;或者一些向前,一些向后;也可能是都向后匹配 
							{
									int now=0;
									for (j=0;j<m;++j) v[j].se+=dir*26;
									i=0;
									for (;i<m;i=j)
									{
										int low=v[i].se,high=v[i].se;
										for (j=i;j<m&&v[i].se==v[j].se;++j) //每个被匹配位置对应的点都必须是连续一段,只需要把最左最右的点并进来就行了 
											low=min(low,v[j].fi),high=max(high,v[j].fi);
										now+=(high-v[i].se)*prevCost+(v[i].se-low)*nextCost;
									}
									ans=min(ans,now);
									for (j=0;j<m;++j) v[j].se-=dir*26;
							}
					}
					v[0].fi+=26; //移动最后一个字符改变断点位置 
					sort(v.begin(),v.end()); 
				} 
				if (ans==inf) return -1;
				return ans;
		}
}MRT;

int main()
{
	cout<<MRT.getMinimum(639, 225, "abcdefghijklmnopqrstuvwxyz", "tuvwxyzabcdefghijklmnopqrs");
}
