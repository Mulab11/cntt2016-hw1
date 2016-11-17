#include <string>

class TheNumberGame {
  public:
    std::string determineOutcome(int A, int B);
};

std::string TheNumberGame::determineOutcome(int A, int B)
{
    // Manao wins if B or reversed B is a substring of A
    std::string sa = std::to_string(A);
    std::string sb = std::to_string(B);
    if (sa.find(sb) != std::string::npos || sa.find(std::string(sb.rbegin(), sb.rend())) != std::string::npos) {
        return "Manao wins";
    } else {
        return "Manao loses";
    }
}
