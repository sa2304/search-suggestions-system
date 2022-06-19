#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<string>> suggestedProducts(vector<string> &products, string searchWord) {
    // FIXME
    return {};
  }
};

void TestSuggestedProducts(vector<string> &products, string searchWord,
                           const vector<vector<string>> &expected_results) {
  Solution s;
  string expected;
  {
    stringstream out;
    for (const auto &results: expected_results) {
      for (const auto &name: results) {
        out << name << ' ';
      }
    }
    expected = out.str();
  }
  {
    stringstream out;
    for (const auto &results: s.suggestedProducts(products, searchWord)) {
      for (const auto &name: results) {
        out << name << ' ';
      }
    }
    assert(expected == out.str());
  }
}

void RunTests() {
  {
    vector<string> products{"mobile", "mouse", "moneypot", "monitor", "mousepad"};
    vector<vector<string>> expected_results
        {{"mobile", "moneypot", "monitor"}, {"mobile", "moneypot", "monitor"}, {"mouse", "mousepad"},
         {"mouse", "mousepad"}, {"mouse", "mousepad"}};
    TestSuggestedProducts(products, "mouse"s, expected_results);
  }
  {
    vector<string> products{"havana"};
    vector<vector<string>> expected_results{{"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}};

    TestSuggestedProducts(products, "havana"s, expected_results);

  }
  {
    vector<string> products{"bags", "baggage", "banner", "box", "cloths"};
    vector<vector<string>>
        expected_results{{"baggage", "bags", "banner"}, {"baggage", "bags", "banner"}, {"baggage", "bags"}, {"bags"}};

    TestSuggestedProducts(products, "bags"s, expected_results);
  }
}
int main() {
  RunTests();
  std::cout << "Ok!" << std::endl;
  return 0;
}
