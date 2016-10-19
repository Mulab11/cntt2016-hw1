#include <bits/stdc++.h>

using namespace std;

int main(){
	srand((unsigned int)time(0));
	freopen("input.txt","w",stdout);
	int n=9-rand()%3;
	printf("%d\n",n);
	for (int i=1;i<=n;++i) printf("%d\n",rand()%2*2-1);
	for (int i=1;i<n;++i)
		printf("%d %d\n",i+1,rand()%i+1);
	return 0;
}
