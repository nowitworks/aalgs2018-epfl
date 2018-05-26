#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

struct subset {
  int parent;
  int rank;
};

struct sets {
  std::vector<subset> ss;

  sets(int n) {
    ss.reserve(n);

    for (int i = 0; i < n; i++) {
      ss[i].parent = i;
      ss[i].rank = 0;
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
  std::vector<int> solution_src;
  std::vector<int> solution_dst;

  solver() {
    std::cin >> n;
    std::cin >> m;

    src.reserve(m);
    dst.reserve(m);
    pi.reserve(m);

    for (int i = 0; i < m; i++) {
      std::cin >> src[i];
      std::cin >> dst[i];
      pi[i] = i;
    }

  }

  void run() {
    std::random_shuffle(std::begin(pi), std::end(pi));

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
        solution_src.push_back(u);
        solution_dst.push_back(v);
      }
    }
  }
};

int main () {
  solver solver;
  int n = solver.n;

  // using cut = std::pair<std::vector<int>, std::vector<int>>;
  // std::unordered_map<cut, int> sizes;

  std::vector<int> sizes;
  sizes.reserve(n * n * ceil(log(n)));

  for (int i = 0; i < n * n * ceil(log(n)); i++) {
    solver.run();
    sizes[i] = solver.solution_src.size();

    // auto cut_ = std::make_pair(solver.solution_src, solver.solution_dst);
    // sizes[cut_] = solver.solution_src.size();
  }

  std::cout << *std::min_element(std::begin(sizes), std::end(sizes)) << std::endl;

  return 0;
}
