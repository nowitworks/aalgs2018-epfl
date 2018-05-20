#include <iostream>
#include <memory>


template <typename T>
class set {
public:
  T t;
  std::shared_ptr<set> parent;
  int rank;

  // make-set
  set(T &t): t(t), rank(0), parent(std::make_shared(this)) {
  }

  void link(set &that) {
    if (this->rank > that->rank) {
      that->parent = std::make_shared(this);
    } else {
      this->parent = std::make_shared(that);

      if (this->rank == this->rank) {
        that->rank = this->rank + 1;
      }
    }
  }

  // union
  void set_union(set &that) {
    find_set(this).link(find_set(that));
  }

  // find-set
  set &find_set() const {
    if (this != *parent) {
      parent = std::make_shared(parent->find_set());
    }
    return *parent;
  }

};

int main () {
  std::cout << "Hello world!" << std::endl;

  int nedges, nvertices;

  std::cin >> nvertices;
  std::cin >> nedges;


  std::cout << nvertices << nedges << std::endl;

  return 0;
}
