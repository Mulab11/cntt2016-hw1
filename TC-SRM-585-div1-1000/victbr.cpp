#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 58585+10;

struct Node{
	int x,y;
	Node(){}
	Node(int x,int y):x(x),y(y){}
};
Node operator + (const Node &a,const Node &b){
	return Node(a.x+b.x,a.y+b.y);
}
Node operator - (const Node &a,const Node &b){
	return Node(a.x-b.x,a.y-b.y);
}
ll cross(const Node &a,const Node &b){
	return (ll)a.x*b.y-(ll)a.y*b.x;
}


class EnclosingTriangle {
	public:
		ll ans,suf[N<<2];
		int n,len,l[N<<2],r[N<<2];
		Node nod[N<<2],poi[30];
		long long getNumber(int m, vector <int> x, vector <int> y) {
			n = x.size();
			for (int i = 0;i < m;i++)
				nod[++len] = Node(i,0);
			for (int i = 0;i < m;i++)
				nod[++len] = Node(m,i);
			for (int i = m;i > 0;i--)
				nod[++len] = Node(i,m);
			for (int i = m;i > 0;i--)
				nod[++len] = Node(0,i);
			for (int i = 0;i < n;i++) 
				poi[i+1] = Node(x[i],y[i]);
				
			for (int i = 1;i <= len;i++){
				l[i] = max(l[i-1],i+1);
				while (1){
					bool flag = 1;
					for (int j = 1;j <= n;j++){
						if (cross(nod[l[i]]-nod[i],poi[j]-nod[i]) < 0){
							flag = 0;
							break;
						}
					}
					if (flag) l[i]++;
					else break;
					if (l[i] > len) break;//注意不要把len、n和m打混 
				}
				l[i]--;
				r[i] = max(r[i-1]-1,l[i]-1);//因为后面r[i]先+1再判断，所以这里要-1. 
				while (r[i] <= len){
					r[i]++;
					if (r[i] > len) break;
					bool flag = 1;
					for (int j = 1;j <= n;j++){
						if (cross(nod[i]-nod[r[i]],poi[j]-nod[r[i]]) < 0){ 
							flag = 0;
							break;
						}
					}
					if (flag) break;
				}
			}
			for (int i = len;i >= 1;i--)
				suf[i] = suf[i+1]+l[i];
			int t = 2;
			for (int i = 1;i <= len;i++){
			if (l[l[i]] <= len)
				ans += max(l[l[i]]-max(r[i],l[i]+1)+1,0);
				while ((t <= len && l[t] <= r[i]-1) || t <= i)
					t++;
				if (t <= l[i]-1){
					ans += suf[t]-suf[l[i]];
					ans -= (ll)(r[i]-1)*(l[i]-t);
				}
			}
			return ans;
		}
};
