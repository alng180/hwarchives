// Simple Dijkstras Algorithm Program


public class dijkstras {
   // main
	public static void main(String[] args) {
      
      // 2d matrix representing the distances between all nodes
		int[][] matrix = {{100, 5, 3, 100, 100, 100, 100}, 
							{100, 100, 2, 100, 3, 100, 1}, 
							{100, 100, 100, 7, 7, 100, 100}, 
							{2, 100, 100, 100, 100, 6, 100}, 
							{100, 100, 100, 2, 100, 1, 100}, 
							{100, 100, 100, 100, 100, 100, 100}, 
							{100, 100, 100, 100, 1, 100, 100}};
		
		Node[] nodelist = new Node[7];
		for (int i = 0; i < 7; i++) {
			nodelist[i] = new Node();
		}
		nodelist[0].path = 0;
		int nodepointer = 0;
		int minDist = 100;
		int[] distance = new int[7];
		Node temp;
		
      // for all 7 nodes
		for (int i = 0; i < 7; i++) {
			minDist = 100;
         // find next unvisited node with shortest distance to current node
			for (int j = 0; j < 7; j++) {
				if (nodelist[j].path < minDist && nodelist[j].visited == false) {
					nodepointer = j;
					minDist = nodelist[j].path;
					nodelist[j].id = j;
				}
			}
			
         // check if the move from current node to next node is the new "shortest" path
			for (int k = 0; k < 7; k++) {
				if (k != nodepointer) {
					int costTo = matrix[nodepointer][k];
					nodelist[k].cost = costTo;
					if (costTo != 100) {
						int currCost = nodelist[nodepointer].path;
						if (currCost + costTo < nodelist[k].path) {
							distance[k] = currCost + costTo;
							nodelist[k].path = currCost + costTo;
							nodelist[k].prev = nodelist[nodepointer];
						}
					}

				}
			}
			
         // has visited node
			nodelist[nodepointer].visited = true;
		}
		
		int[] patharray = new int[7];
		for (int i = 0; i < 7; i++) {
			patharray[i] = -1;
		}
		
      // determine path from node 0 to node x (currently set to 4)
		Node temp2 = nodelist[4];
                int tempid = temp2.id;
		int count = 0;
		while(temp2.prev != null) {
			patharray[count] = temp2.id;
			count++;
			temp2 = temp2.prev;
		}
		
		// output distances from node 0 to all nodes
		for (int i = 0; i < 7; i++) {
			System.out.println("Distance from: 0 to " + i + " is: " + distance[i]);			
		}
		
		// output path from node 0 to node x
      System.out.println("Path from Node 0 to Node " + tempid);
		for (int i = 0; i < 7; i++) {
			if (patharray[i] < 0) {
				break;
			}
			System.out.print(patharray[i] + "-");
		}
	}
}
