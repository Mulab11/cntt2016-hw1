#include <bits/stdc++.h>

using namespace std;


class SpaceWarDiv1 {
public:
	long long minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount) {
		vector<int>mg;
		int n=magicalGirlStrength.size();
		for(int i=0;i<n;++i)mg.push_back(magicalGirlStrength[i]);
		int m=enemyStrength.size();
		vector<pair<int,long long> >sb;
		for(int i=0;i<m;++i)
			sb.push_back(make_pair(enemyStrength[i],enemyCount[i]));
		sort(mg.begin(),mg.end());
		sort(sb.begin(),sb.end());//按战斗力排序 
		if(mg[n-1]<sb[m-1].first)return -1;//最大的也打不赢 
		long long l=0,r=1000000000000000000ll,mid;
		while(l<r){
			mid=(l+r)>>1;
			bool flag=0;
			long long cnt=sb[0].second;
			for(int i=0,j=0;i<n&&j<m;++i){
				long long res=mid;
				while(j<m&&mg[i]>=sb[j].first&&res>=cnt){//还能打 
					res-=cnt;
					++j;
					if(j<m)cnt=sb[j].second;
					else flag=1;//打完了 
				}
				if(j<m&&mg[i]>=sb[j].first)cnt-=res;//还能打但打不完 
			}
			if(flag)r=mid;else l=mid+1;
		}
		return l;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
