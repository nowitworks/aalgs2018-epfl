#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <set>
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
      // FIXME
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

    solution_src.clear();
    solution_dst.clear();

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

// FIXME: Takes account order of vectors
std::size_t hash_cut(std::vector<int> const &src, std::vector<int> const &dst) {
  std::size_t seed = src.size();

  for(auto &i: src) {
    seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }

  for(auto &i: dst) {
    seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }

  return seed;
}

int main () {
  solver solver;
  int n = solver.n;

  std::unordered_map<std::size_t, int> sizes;
  sizes.reserve(n * n * ceil(log(n)));

  for (int i = 0; i < n * n * ceil(log(n)); i++) {
    solver.run();

    auto key = hash_cut(solver.solution_src, solver.solution_dst);
    sizes[key ] = solver.solution_src.size();
  }

  int min_size = std::min_element(std::begin(sizes), std::end(sizes), [&](auto &l, auto &r) -> bool {
      return l.second < r.second;
    })->second;

  int count = std::count_if(std::begin(sizes), std::end(sizes), [&](auto &x) -> bool {
      return x.second == min_size;
    });

  // FIXME: For some reason we seem to be outputting double the count
  std::cout << min_size << " " << count << std::endl;

  return 0;
}
