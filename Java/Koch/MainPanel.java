import java.awt.*;
import java.awt.Graphics.*;
import javax.swing.*;

// The Top/Main JPanel for the program
// responsible for displaying/drawing the Koch curve to the user
public class MainPanel extends JPanel {
	public JPanel panel;		// instance of the MainPanel JPanel
	private Model model;		// copy of the model
	
	// Constructor for the MainPanel class
	
	// @param m copy of the model
	public MainPanel(Model m) {
		this.model = m;		// saves a copy of the model 
	}
	
	// the paintComponent method responsible for the graphics/drawing for the class
	
	// @param g the standard java graphics package
	public void paintComponent(Graphics g) {
		super.paintComponent(g);	
		Point first = model.getfirstPoint();	// retrieve the first/starting point of the line from the model 
		Point second = model.getsecondPoint();	// retrieve the second/end point of the line from the model
		
		if (model.getDegree() == 0) {			// if Koch level is zero
			g.drawLine(first.x, first.y, second.x, second.y);	// draw a straight line between two points
		} else {								// if Koch level is greater than zero
			drawShape(g);								// call the drawShape method to draw the whole Koch curve
		}
	}
	
	// uses the JOptionPane class to create a popup window to notify that the user attempted to decrease the Koch
	// level below 0
	public void negativelevelWarning() {
		JOptionPane.showMessageDialog(panel, "Warning! Cannot Have Negative Koch Level!");
	}
	
	// uses the JOptionPane class to create a popup window to notify the user that further increases in the 
	// Koch level may lag/freeze/crash the program
	public void highlevelWarning() {
		JOptionPane.showMessageDialog(panel, "Warning! Koch Levels Higher Than This Will Lag and May Crash Program");
	}
	
	// drawShape method is responsible for using the coordinates determined by the model to draw the 
	// whole Koch curve
	
	// @param g the standard java graphics package
	public void drawShape(Graphics g) {
		int pointcount = model.getpointCount();		// retrieve the number of points
		
		Point[] coords = new Point[pointcount];		// create an array of points to hold the calculated points
		coords = model.getPoints();					// and copy the array of points over from the model
		
		int count = 1;								// counter used to keep track of where in the array drawShape is
		
		Point previous = coords[0];					// point to keep track of previous point (starts with the first/start point / coord[0])
		Point current = new Point(0,0);				// point to keep track of current point
		
		while (count < pointcount) {				// while array hasn't been completely traversed
			current = (coords[count]);				// retrieve next/current point
			count++;								// increment counter
			g.drawLine(previous.x,previous.y,current.x,current.y);		// draw line from previous point to current point
			previous = current;						// save the current point as the previous point in preparation for the next point
		}
		repaint();									// update/refresh the graphics/drawing in the JPanel
	}
}