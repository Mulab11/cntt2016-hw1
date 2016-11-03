#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
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

int s[256];

struct LittleElephantAndString 
{
    int getNumber(string A, string B)
    {
    	int n=A.size();
    	for (int i=0;i<n;i++) s[A[i]]++;
    	for (int i=0;i<n;i++) s[B[i]]--;
    	for (int i='A';i<='Z';i++) if (s[i]) return -1;//如果字母个数不一样则无解
    	int k=n-1;
    	for (int i=n-1;i>=0;i--)
    	{
    		while (k>=0&&A[k]!=B[i]) k--;
    		if (k<0) return i+1;//找不到相同的字符
    		k--;
    	}
    	return 0;
    }
};
