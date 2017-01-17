#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

struct LittleElephantAndBalls 
{
    int getNumber(string s)
    {
    	int N=s.size(),ans=0;
    	int s1=0,s2=0,s3=0;
    	for (int i=0;i<N;i++)
    	{
    		ans+=min(s1,2)+min(s2,2)+min(s3,2);
    		if (s[i]=='R') s1++;
    		if (s[i]=='G') s2++;
    		if (s[i]=='B') s3++;
    	}
    	return ans;
    }
};
