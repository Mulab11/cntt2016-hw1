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

bool solve(ll n)
{
	if (n%2==1) return 0;
	int p=1;
	while (n%2==0) {p^=1;n/=2;}
	if (n>1) return 1; else return p;
}

struct TheNumberGameDivOne 
{
    string find(long long n)
    {
    	if (solve(n)) return "John"; else return "Brus";
    }
};
