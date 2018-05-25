import scala.collection.mutable.HashSet

object Karger extends App {
  val spec = new Spec()
  val n = spec.n
  val times = n * n * math.ceil(math.log(n)).toInt // O(n^2 * log(n))

  val cuts: HashSet[Vector[(Int, Int)]] = HashSet()

  for (_ <- 1 to times) {
    val solver = new Solver(spec)
    val cut = solver.run()

    cuts += cut
  }

  val minSize = cuts.minBy(_.size).size
  val count   = cuts.count(_.size == minSize)

  println(minSize + " " + count)
}

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
  def read = io.StdIn.readLine.split(" ").map(_.toInt)

  val Array(n, m) = read
  val edges = Vector.tabulate(m) { _ =>
    val Array(u, v) = read
    (u, v)
  }
}

class Solver(spec: Spec) {
  val vertices = for (i <- 1 to spec.n) yield new Node(i)

  var edges = spec.edges.map { case (u, v) =>
    (vertices(u - 1), vertices(v - 1))
  }

  def run(): Vector[(Int, Int)] = {
    for (_ <- 1 to spec.n - 2) {
      val (u, v) = pickEdge()
      u ++ v
      removeLoops()
    }

    edges.map(x => (x._1.id, x._2.id))
  }

  private def pickEdge(): (Node, Node) = {
    edges(util.Random.nextInt(edges.size))
  }

  private def removeLoops() {
    edges = edges filter {
      x => x._1.findSet() != x._2.findSet()
    }
  }

}
