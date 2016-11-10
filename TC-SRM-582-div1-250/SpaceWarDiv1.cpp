#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

class SpaceWarDiv1{
	public:
	
	LL minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount) 
	{
		int n = magicalGirlStrength.size(), m = enemyStrength.size();
		sort( magicalGirlStrength.begin(), magicalGirlStrength.end() );  //给美少女排序 
		
		for( int i = 0; i < m; ++i ) // 给敌人按力量排序 
		{
			int big = enemyStrength[i], k = i;
			for( int j = i+1; j < m; ++j )
				if( enemyStrength[j] < big ) {
					big = enemyStrength[j]; k = j;
				}
			if( k != i ) {
				swap( enemyStrength[i], enemyStrength[k] );
				swap( enemyCount[i], enemyCount[k] );
			}
		}
		
		if( enemyStrength[m-1] > magicalGirlStrength[n-1] ) return -1; //判断无解 
		
		LL l = 0ll, r = 10000000000000001ll,mid,rest; bool can; // 二分， 注意最大值取够 
		while( l + 1 < r ) {
			rest = mid = ( l + r ) >> 1; can = true; 
			
			int p = n-1;
			for( int i = m-1; i >= 0; --i ) 
			{
				LL st = enemyStrength[i], cnt = enemyCount[i];
				while( cnt > 0 && p >= 0 && magicalGirlStrength[p] >= st ) { //让美少女丛强到弱在疲劳值范围内从强至弱消灭敌人 
					if( cnt >= rest ) {
						cnt -= rest;
						p --;
						rest = mid;
					}
					else
					{
						rest -= cnt;
						cnt = 0;
					}
				}
				if( cnt > 0 ) { // 有敌人不能消灭干净 此时不行 
					can = false; break;
				}
			}
			
			if( can ) r = mid;
			else l = mid;
		}
		return r; // 返回答案 
	}
	
};