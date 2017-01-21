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
const int N = 55;
ll stk[N];
class Suminator
{
		public:
				int findMissing(vector <int> program, int wantedResult){
						//$CARETPOSITION$
						int top=0;
						int n=program.size();
						for(int i=0;i<n;i++){
								if(program[i] == 0 || program[i] == -1){
										if(top >= 2){
												ll res = stk[top]+stk[top-1];
												stk[--top]=res;
												//        if(res > wantedResult)return -1;
										}else if(top == 0){
												stk[++top] = 0;
										}
								}else{
										stk[++top] = program[i];
								}
						}
						if(stk[top] == wantedResult)return 0;
						bool have[N];memset(have,0,sizeof(have));
						top = 0;
						for(int i=0;i<n;i++){
								if(program[i] == 0){
										if(top >= 2){
												ll res = stk[top] + stk[top-1];
												bool ok = have[top] || have[top-1];
												stk[--top] = res;
												//                if(res > wantedResult)return -1;
												have[top] = ok;
										}else if(top == 0){
												stk[++top] = 0;
												have[top] = 0;
										}
								}else if(program[i] == -1){
										stk[++top] = 0;
										have[top] = 1;
								}else{
										stk[++top] = program[i];
										have[top] = 0;
								}
						}
						if(have[top] == 0)return -1;
						else if(stk[top] >= wantedResult)return -1;
						else return wantedResult - stk[top];

				}
} ; 

