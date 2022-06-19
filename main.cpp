#include <cassert>
#include <iostream>
#include <optional>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class Trie {
 public:
  vector<string> GetSuggestions(string_view prefix, int limit) const {
    const Node *node = &root_;
    for (char c: prefix) {
      if (node->children.count(c)) {
        node = node->children.at(c);
      } else {
        return {};
      }
    }
    vector<string> result;
    GetAllKeys_(node, result, limit);

    return result;
  }

  void Insert(string value) {
    Node *node = &root_;
    for (char c: value) {
      if (!node->children.count(c)) {
        node->children[c] = new Node{};
      }
      node = node->children.at(c);
    }
    node->value = move(value);
  }

 private:
  struct Node {
    map<char, Node *> children;
    optional<string> value;
  } root_;

  void GetAllKeys_(const Node *root, vector<string> &result, int limit) const {
    if (result.size() < limit && root->value) {
      result.push_back(*root->value);
    }
    for (const auto&[c, node]: root->children) {
      GetAllKeys_(node, result, limit);
    }
  }
};

class Solution {
 public:
  vector<vector<string>> suggestedProducts(vector<string> &products, string searchWord) {
    Trie trie;
    for (const auto &p: products) {
      trie.Insert(p);
    }

    vector<vector<string>> result;
    for (int i = 1; i <= searchWord.length(); ++i) {
      result.push_back(trie.GetSuggestions(searchWord.substr(0, i), 3));
    }

    return result;
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
