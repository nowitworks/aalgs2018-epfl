#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

using edge = std::set<int>;
using cut = std::multiset<edge>;

struct subset {
  int parent;
  int rank;
};

struct sets {
  std::vector<subset> ss;

  sets(int n) {
    ss.reserve(n);

    for (int i = 0; i < n; i++) {
      ss.push_back({ i, 0 });
    }
  }

  int rank(int x) const {
    return ss[x].rank;
  }

  void rank(int x, int r) {
    ss[x].rank = r;
  }

  int parent(int x) const {
    return ss[x].parent;
  }

  void parent(int x, int p) {
    ss[x].parent = p;
  }

  void set_union(int x, int y) {
    x = find(x);
    y = find(y);

    if (rank(x) == rank(y)) {
      parent(y, x);
    } else {
      parent(x, y);
        if (rank(x) == rank(y)) {
          rank(y, rank(y) + 1);
        }
    }
  }

  int find(int x) {
    if (x != parent(x)) {
      parent(x, find(parent(x)));
    }

    return parent(x);
  }
};

struct solver {
  int n, m;

  // Edges
  std::vector<int> src;
  std::vector<int> dst;

  // Permutation
  std::vector<int> pi;

  // Cut
  cut solution;

  solver() {
    std::cin >> n;
    std::cin >> m;

    src.reserve(m);
    dst.reserve(m);
    pi.reserve(m);

    for (int i = 0; i < m; i++) {
      int s, d;

      std::cin >> s;
      std::cin >> d;

      src.push_back(s);
      dst.push_back(d);

      pi.push_back(i);
    }
  }

  void run() {
    std::random_shuffle(std::begin(pi), std::end(pi));

    solution.clear();

    sets vertices(n);

    for (int i = 0, j = 0; i < m && j < n - 2; i++) {
      int u = src[pi[i]], v = dst[pi[i]];

      if (vertices.find(u - 1) != vertices.find(v - 1)) {
        j++;
        vertices.set_union(u - 1, v - 1);
      }
    }

    for (int i = 0; i < m; i++) {
      int u = src[pi[i]], v = dst[pi[i]];

      if (vertices.find(u - 1) != vertices.find(v - 1)) {
        solution.insert(std::set<int>{u, v});
      }
    }
  }
};

int main () {
  solver solver;
  int n = solver.n;
  double constant = 2;
  int iterations = n * n * ceil(constant * log(n));

  std::unordered_map<int, std::set<cut>> sizes;
  sizes.reserve(iterations);

  for (int i = 0; i < iterations; i++) {
    solver.run();

    auto cut_size = solver.solution.size();
    auto it = sizes.find(cut_size);

    if (it != sizes.end()) {
      it->second.insert(solver.solution);
    } else {
      sizes[cut_size] = std::set<cut> { solver.solution };
    }
  }

  int min_size = std::min_element(std::begin(sizes), std::end(sizes), [&](auto &l, auto &r) -> bool {
      return l.first < r.first;
    })->first;

  int count = sizes[min_size].size();

  std::cout << min_size << " " << count << std::endl;

  return 0;
}
