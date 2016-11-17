#include <string>
#include <vector>

class FoxAndChess {
  public:
    std::string ableToMove(std::string begin, std::string target);
};

std::string FoxAndChess::ableToMove(std::string begin, std::string target)
{
    std::vector<int> posl1;
    std::vector<int> posr1;
    std::vector<char> seq1;
    std::vector<int> posl2;
    std::vector<int> posr2;
    std::vector<char> seq2;
    for (int i = 0; i < (int)begin.size(); i++) {
        if (begin[i] == 'L') {
            posl1.push_back(i);
        } else if (begin[i] == 'R') {
            posr1.push_back(i);
        }
        if (begin[i] != '.') {
            seq1.push_back(begin[i]);
        }
    }
    for (int i = 0; i < (int)target.size(); i++) {
        if (target[i] == 'L') {
            posl2.push_back(i);
        } else if (target[i] == 'R') {
            posr2.push_back(i);
        }
        if (target[i] != '.') {
            seq2.push_back(target[i]);
        }
    }
    if (posl1.size() != posl2.size() || posr1.size() != posr2.size()) {
        // Not the same number of pawns
        return "Impossible";
    }
    if (seq1 != seq2) {
        // Pawns cannot cross each other
        return "Impossible";
    }
    for (int i = 0; i < (int)posl1.size(); i++) {
        if (posl1[i] < posl2[i]) {
            // L pawns cannot move right
            return "Impossible";
        }
    }
    for (int i = 0; i < (int)posr1.size(); i++) {
        if (posr1[i] > posr2[i]) {
            // R pawns cannot move left
            return "Impossible";
        }
    }
    return "Possible";
}
