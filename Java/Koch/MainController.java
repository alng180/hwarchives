import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;

// The controller for the whole program
// Contains the action/mouse listeners responsible for reacting to the button presses
// and mouse clicks for the program
public class MainController implements ActionListener, MouseListener {
	
	private Model model;	// copy of the model
	private Frame frame;	// copy of the JFrame/GUI of the program
	
	// boolean to keep track of if the mouse has been clicked twice onto the MainPanel and if 
	// a new line should be drawn or not
	private boolean haveTwoPoints = true;
	
	// Constructor of the MainController class
	
	// @param model a copy of the model class
	// @param frame a copy of the JFrame/GUI of the program
	public MainController(Model model, Frame frame) {
		this.model = model;		// saves a copy of the model to this class
		this.frame = frame;		// saves a copy of the JFrame to this class
		
		frame.top.addMouseListener(this);	// adds a MouseListener to the top JPanel
		frame.bot.jb1.addActionListener(this);	// adds an ActionListener to the first JButton (jb1) for increasing Koch level
		frame.bot.jb2.addActionListener(this);	// adds an ActionListener to the second JButton (jb2) for decreasing the Koch level
	
	}

	@Override
	// method to handle mouseclicks onto the top JPanel
	
	// @param e the mouseevent sent by the MouseListener
	public void mousePressed(MouseEvent e) {
		Point p = e.getPoint();		// retrieves the coordinates (within the top JPanel) of the mouseclick
		
		// if haveTwoPoints is true, then there are two points for the program to draw a line in between
		// thus next mouse click means that user wishes to restart and change the start/end points
		if (haveTwoPoints) {		
			model.setfirstPoint(p);	// save the coordinates of the mouseclick as the "first point"
			haveTwoPoints = false;	// set haveTwoPoints to trigger the else statement
		} else {			
			model.setsecondPoint(p);	// save the coordinates of the mouseclick as the "second point"
			haveTwoPoints = true;		// reset haveTwoPoints
			model.setDegree(0);			// reset the Koch level to 0
			frame.top.repaint();		// repaint the JPanel to show the new line
		}
	}
	
	@Override
	// method to handle the buttons clicks
	
	// @param ae the actionevent sent by the ActionListener
	public void actionPerformed(ActionEvent ae) {
		int deg = model.getDegree();		// retrieve the current Koch level/degree from the model
		
		if (ae.getSource() == frame.bot.jb1) {	// if jb1 (Increase Koch level) was pressed
			deg++;								// increase koch level by one
			model.setDegree(deg);				// update the model of the Koch level change 
			model.startRecursion();				// tell model to calculate the coordinates of the curve based on the new Koch level
			frame.bot.updateLabel();			// update the JLabel to display the new Koch level
			
			if (deg == 8) {						// if the Koch degree is 8
				frame.top.highlevelWarning();	// warn the user that further increases will cause lag/freezes/crash
			}
			
			frame.top.repaint();				// update the Koch curve displayed in JPanel to reflect new Koch level
			
		} else if (ae.getSource() == frame.bot.jb2) {	// if jb2 (Decrease Koch leve was pressed)
			
			if (deg == 0) {								// if koch level is zero already
				frame.top.negativelevelWarning();		// warn user that Koch level cannot be lower than 0 and ignore button press
			
			} else {									// if koch level is nonzero
				deg--;									// decrease koch level by one
				model.setDegree(deg);					// update the model of the Koch level change
				model.startRecursion();					// tell model to calculate the coordinates of the curve based on the new Koch level
				frame.bot.updateLabel();				// update the JLabel to display the new Koch level
			}
		}
	}

	
	
	// Due to the implementation of the MouseListener interface,
	// the following methods must be "defined". However, as none of these 
	// methods are used or needed, they are left blank and should be ignored
	public void mouseEntered(MouseEvent arg0) {
	}

	public void mouseExited(MouseEvent arg0) {
	}
	
	public void mouseClicked(MouseEvent arg0) {	
	}

	public void mouseReleased(MouseEvent arg0) {
	}
	
}