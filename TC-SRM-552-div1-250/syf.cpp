//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cassert>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
class FoxPaintingBalls
{
    public:
    long long theMax(long long R, long long G, long long B, int N){
        if(N == 1)return R+G+B;
        ll total = 1LL*N*(N + 1) / 2;
        ll least = total / 3;
        ll maxn = min(min(R,G),B) / least;
        if(total % 3 == 0)return maxn;
        ll answer = 0,left = 0,right = maxn;	//预处理
		
        while(left <= right){	//二分答案
//            cout << "L: "<<l<<" R: "<<r<<endl;
            ll mid = (left + right) >> 1;
            ll r = R - mid * least,g = G - mid * least,b = B - mid * least;
            if((r + g + b) >= mid){	//判断
                answer = mid;
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        return answer;
	}
};