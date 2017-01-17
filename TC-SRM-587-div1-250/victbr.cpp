#include <bits/stdc++.h>

using namespace std;

class JumpFurther{
	public:
		int furthest(int n,int m){
			int sum = 0,ans = n*(n+1)/2;
			for(int i = 1;i <= n;i++){
				sum += i;
				if(sum == m) return ans-1;
			}
			return ans;
		}
};
