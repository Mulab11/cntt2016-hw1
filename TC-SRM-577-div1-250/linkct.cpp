#include <bits/stdc++.h>
using namespace std;

class EllysRoomAssignmentsDiv1{
public:
	int score[555], n, r;
	double getAverage(vector <string> input){
		int i, j, self, sum = 0, part = 0, partCnt = 0;
		int fullCnt = 0; stringstream readin;
		for(i = 0; i < int(input.size()); ++ i)
			readin << input[i];
		for(n = 0; readin >> score[0]; score[++ n] = score[0]) ;
		for(self = score[1]; n % 20; score[++ n] = 0);
		sort(score + 1, score + 1 + n);
		for(i = n, r = n / 20; i; i -= r){
			if(score[i] >= self && score[i - r + 1] <= self)
				continue;
			if(score[i - r + 1]){
				++ fullCnt;
				for(j = i; j > i - r; -- j)
					sum += score[j];
			}else for(j = i; j > i - r; -- j){
				part += score[j];
				if(score[j]) ++ partCnt;
			}
		} if(!partCnt) return (sum * 1.0 / r + self) / (fullCnt + 1);
		return (1.0 * partCnt / r) * ((1.0 * sum / r + 1.0 * part / partCnt + self) / (fullCnt + 2))
			+ (1.0 * (r - partCnt) / r) * ((1.0 * sum / r + self) / (fullCnt + 1));
	}
};
