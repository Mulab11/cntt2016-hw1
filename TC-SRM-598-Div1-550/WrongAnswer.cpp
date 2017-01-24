// WAonSystemTest
#include <string>
class FoxAndFencing{
public:
	std::string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d){
		// 1的必胜区间为[0,mov1+rng1]
		// 2的必胜区间为[0,mov2+rng2]
		if(d<=mov1+rng1)return"Ciel";
		// (1)对任意x>mov1+rng1，都可将x移到2的必胜区间外（显然包含了mov1+rng1>=mov2+rng2的所有情况）
		if(mov1+rng1+1+mov1>mov2+rng2){
			// 1.1 如果d能移到使对方只能移进1的必胜区间的位置（前提是mov1>mov2），1必胜
			if(mov1>mov2&&mov2+rng2+1+mov2<=mov1+rng1)return"Ciel";
			// 1.2 否则平局
			return"Draw";
		}
		// (2)如果d移不出2的必胜区间，1必败
		if(d+mov1<=mov2+rng2)return"Liss";
		// (3)如果d能移出区间，但会被对方移到d更小的位置，1必败
		if(mov2>mov1)return"Liss";
		// (4)否则平局
		return"Draw";
	}
};
