package karger

// Union-find
class Node(val id: Int) {
  var parent = this
  var rank = 0

  def findSet(): Node = {
    if (this != parent) {
      parent = parent.findSet()
    }

    parent
  }

  def ++(y: Node) {
    Node.link(this.findSet(), y.findSet())
  }

  def +(y: Int) {
    this ++ new Node(y)
  }

  override def toString: String = "Node(" + id + ")"
}

object Node {
  def link(x: Node, y: Node) {
    if (x.rank > y.rank) {
      y.parent = x
    } else {
      x.parent = y
      if (x.rank == y.rank) {
        y.rank += 1
      }
    }
  }
}

class Spec {
  def read = readLine.split(" ").map(_.toInt)

  val Array(n, m) = read
  val edges = for (_ <- 1 to m) yield {
    val Array(u, v) = read
    (u, v)
  }
}

class Solver(spec: Spec) {
  val vertices = for (i <- 1 to spec.n) yield new Node(i)
  val edges = scala.util.Random.shuffle {
    for ((u, v) <- spec.edges) yield {
      (vertices(u - 1), vertices(v - 1))
    }
  }.toList

  def run(): Set[(Int, Int)] = {
    for ((u, v) <- edges.take(spec.n - 2)) {
      if (u.findSet() != v.findSet()) {
        // Edge contraction
        u ++ v
      }
    }

    val cut = for {
      (u, v) <- edges.drop(spec.n - 2)
      if u.findSet() != v.findSet()
    } yield (u.id, v.id)

    cut.toSet
  }

}

object App {
  def main(args: Array[String]): Unit = {
    val spec = new Spec()
    val n = spec.n

    val cuts = for (_ <- 1 to (n * n * math.ceil(7 * math.log(n)).toInt)) yield {
      val solver = new Solver(spec)
      solver.run()
    }

    println(cuts.map(_.size).min)
  }
}

