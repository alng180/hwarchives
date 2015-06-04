import java.awt.*;

// class that is responsible for holding most of the data/information in the program and does the 
// recursion necessary to calculate the coordiantes of the Koch curve
public class Model {
	
	private Point firstPoint, secondPoint;	// start/end points of the line
	private Point[] points;					// an array of points where the coordinates of the koch curve will be saved
	private int numberofpoints;					// counter to keep track of number of coordinates
	
	private int KochDegree;					// integer to keep track of the current Koch level/degree 
	
	double constant = 3.14159/3.0;		// constant used in the calculation of the peak coordinate of Koch curve (pi/3)
	
	// Constructor for the model
	
	public Model() {
		KochDegree = 0;						// set starting Koch level as 0
		firstPoint = new Point(100, 100);	// set initial first point as (100,100)
		secondPoint = new Point(200, 100);	// set initial second poitn as (200,200)
		
	}
	
	// getter method to retrieve the first/starting point from this class
	public Point getfirstPoint() {
		return firstPoint;
	}
	
	// setter method to set the first/starting point 
	
	// @param p the first/starting point to be set
	public void setfirstPoint(Point p) {
		firstPoint = p;
	}
	
	// getter method to retrieve the second/end point from this class
	public Point getsecondPoint() {
		return secondPoint;
	}
	
	// setter method to set the second/end point
	
	// @param p the second/end point to be set
	public void setsecondPoint(Point p) {
		secondPoint = p;
	}
	
	// getter method to retrieve the current koch level/degree of the program
	public int getDegree() {
		return KochDegree;
	}
	
	// setter method to set the current koch level/degree in the program
	
	// @param newDegree the koch level/degree to be set
	public void setDegree(int newDegree) {
		KochDegree = newDegree;
	}
	
	// method that sets up and kicks off the private recursion method responsible for calculating
	// the coordinates of the Koch curve
	public void startRecursion() {
		points = new Point[10000000];		// create a large array ready to accept the coordinates
		// (NOTE: will CRASH due to outofBoundsException after Koch level 10 (need ~16 mill coordinates for level 11)
		
		points[0] = firstPoint;				// set the first element of the array to firstPoint
		numberofpoints = 1;						// reset/start the point counter
		
		recursePoints(KochDegree, firstPoint, secondPoint);		// start the recursion
	}
	
	// getter method to retrieve the array of coordinates
	public Point[] getPoints() {
		return points;
	}
	
	// getter method to retrieve the number of points/coordinates in the Points array
	public int getpointCount() {
		return numberofpoints;
	}
	
	// the main recursion method used to calculate the coordinates of the Koch curve
	
	// @param KochDegree the current koch level/degree of the program
	// @param start the start point of the line segment
	// @param end the end point of the line segment
	private void recursePoints(int KochDegree, Point start, Point end) {
		
		Point onethird = new Point(0,0);		// the one-thirds point of the line (relative to start point)
		Point twothird = new Point(0,0);		// the two-thirds point of the line (relative to start point)
		Point peak = new Point(0,0);			// the point of the peak in the center of the line segment
		
		int thirdsegmentX = (end.x-start.x)/3;		// calculate the one third point wrt to the x axis
		int thirdsegmentY = (end.y-start.y)/3;		// calculate the one third point wrt to the y axis
	
		// base case
		if (KochDegree == 0) {
			points[numberofpoints] = new Point(end);		// save the ending point of the line segment
			numberofpoints++;								// increment point counter
		
		// else or recursive case
		} else {
			// calculate and set the coordinates of the onethird and twothird points of the line segment
			onethird.setLocation(thirdsegmentX + start.x, thirdsegmentY + start.y);
			twothird.setLocation(end.x - thirdsegmentX, end.y - thirdsegmentY);
			
			// calculate the coordinate of the peak point in the line segment
			double peakX = onethird.x + (twothird.x - onethird.x) * Math.cos(constant) - (onethird.y - twothird.y) * Math.sin(constant);
			double peakY = onethird.y - (twothird.x - onethird.x) * Math.sin(constant) - (onethird.y - twothird.y) * Math.cos(constant);
			peak.setLocation((int)peakX, (int)peakY);
			
			// recurse for each of the four sub-line segments that make up this line segment
			recursePoints(KochDegree-1,start,onethird);
			recursePoints(KochDegree-1,onethird,peak);
			recursePoints(KochDegree-1,peak,twothird);
			recursePoints(KochDegree-1,twothird,end);
		}
	}
}