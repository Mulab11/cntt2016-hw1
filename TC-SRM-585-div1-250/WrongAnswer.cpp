#define ll long long
#define M 1000000007
class TrafficCongestion{
public:
	ll pow(ll a,ll n){ll b=1;for(;n;n>>=1)n%2?b=b*a%M:1,a=a*a%M;return b;}
	int theMinCars(int treeHeight){return(M+1)/3*(pow(M-1,treeHeight)+2*pow(2,treeHeight))%M;}
};
