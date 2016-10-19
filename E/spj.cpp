#include <bits/stdc++.h>
#define N 200005

using namespace std;

void WA(){puts("WA");for (;;);}

bool col[N];
int n;

int main(){
	freopen("input.txt","r",stdin);
	int tmp;
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		scanf("%d",&tmp);
		col[i]=tmp<0;
	}
	
	freopen("output.txt","r",stdin);
	scanf("%d",&tmp);
	while (scanf("%d",&tmp)!=EOF){
		col[tmp]^=1;
	}
	for (int i=1;i<=n;++i) if (col[i]) WA();
	puts("AC");
	return 0;
}
