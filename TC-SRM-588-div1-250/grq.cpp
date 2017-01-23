#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=55;
struct node{int dur,tone;}p[N];
bool cmp(node a,node b){return a.tone<b.tone;}
int n,ans;
priority_queue<int> q;

class GUMIAndSongsDiv1{
public:
	int maxSongs(vector<int> duration, vector<int> tone, int T){
		n=tone.size();ans=0;
		for(int i=0;i<n;i++) p[i]=(node){duration[i],tone[i]};
		sort(p,p+n,cmp);
		for(int i=0;i<n;i++){
			int sum=0,now=0,cnt=0;
			for(int j=i;j<n;j++){
				sum=p[j].tone-p[i].tone;
				if(sum>T) break;
				q.push(p[j].dur);now+=p[j].dur;cnt++;
				while(sum+now>T){now-=q.top();q.pop();cnt--;}
				ans=max(ans,cnt);//去除最大的使其合法 
			}
			while(!q.empty()) q.pop();
		}//枚举最大最小tone
		return ans;
	}
};

