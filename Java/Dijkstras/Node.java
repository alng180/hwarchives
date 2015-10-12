public class Node {
	public int id;
	public int cost;
	public int path;
	public boolean visited;
	public Node prev;
	
	public Node() {
		this.id = 0;
		this.cost = 0;
		this.path = 10000;
		this.visited = false;
		this.prev = null;
	}
}
