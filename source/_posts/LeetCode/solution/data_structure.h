#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <functional>
#include <future>
#include <iostream>
#include <list>
#include <memory>
#include <pthread.h>
#include <queue>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *build_list(vector<int> g) {
  ListNode dummy;
  ListNode *cur = &dummy;
  for (const auto &i : g) {
    cur->next = new ListNode(i);
    cur = cur->next;
  }
  return dummy.next;
}

void print_list(ListNode *head) {
  while (head) {
    std::cout << head->val;
    head = head->next;
    if (head)
      std::cout << "->";
  }
  std::cout << std::endl;
}

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

TreeNode *build_tree(vector<string> s) {
  s.insert(s.begin(), "");
  int n = s.size();
  function<TreeNode *(int)> dfs = [&](int i) -> TreeNode * {
    if (i < n) {
      if (s[i] == "null") return nullptr;
      TreeNode* node = new TreeNode(stoi(s[i]));
      node->left = dfs(i * 2);
      node->right = dfs(i * 2 + 1);
      return node;
    }
    return nullptr;
  };
  return dfs(1);
}

void print_tree(TreeNode* root) {
  queue<TreeNode*> q;
  q.push(root);
  string s;
  while (!q.empty()) {
    auto node = q.front();
    q.pop();
    if (node == nullptr) {
      s += "null,";
    } else {
      s += to_string(node->val);
      s += ",";
      q.push(node->left);
      q.push(node->right);
    }
  }
  cout << s << endl;
}

struct UnionFind {
  vector<int> parent;
  vector<int> rank;

  UnionFind(int n) {
    parent = vector<int>(n, 0);
    rank = vector<int>(n, 1);
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  void join(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py)
      return;
    if (rank[px] > rank[py])
      parent[py] = px;
    else if (rank[px] < rank[py])
      parent[px] = py;
    else {
      parent[py] = px;
      rank[px] += 1;
    }
  }
};

template <typename T> void print_data(T &&ret) {
  if constexpr (is_same_v<decay_t<T>, TreeNode *>) {
    print_tree(forward<T>(ret));
  } else if constexpr (is_same_v<decay_t<T>, vector<int>>) {
    for_each(begin(forward<T>(ret)), end(forward<T>(ret)),
             [](const auto &r) { cout << r << ","; });
    cout << endl;
  } else if constexpr (is_same_v<decay_t<T>, vector<vector<int>>>) {
    for_each(begin(ret), end(ret), [](const auto &r) {
      for_each(begin(r), end(r), [](const auto &w) { cout << w << ","; });
      cout << "\n";
    });
  } else if constexpr (is_same_v<decay_t<T>, ListNode *>) {
    print_list(forward<T>(ret));
  } else {
    cout << ret << endl;
  }
  cout << "================" << endl;
}