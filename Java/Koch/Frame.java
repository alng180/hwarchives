import java.awt.*;
import java.awt.Graphics.*;

import javax.swing.*;

// Creates a JFrame that will act as the container for the two JPanels
// for the graphics part of the program.

// Also acts as the primary View class for the program.
public class Frame extends JFrame {

	public BottomPanel bot;		// set variable name for the Bottom Panel
	public MainPanel top;		// set variable name for the Top/Main Panel
	
	// Constructor for the Frame Class
	// @param model a copy of the model 
	public Frame(Model m) {
		JFrame f = new JFrame("Koch Curve App");	// create/instantiate new JFrame
		bot = new BottomPanel(m);					// create/instantiate the Bottom JPanel
		top = new MainPanel(m);						// create/instantiate the Top/Main JPanel
		f.setBackground(Color.GRAY);				// sets the Background color of the JFrame to Gray
		f.setLayout(new BorderLayout());			// sets the Layout of the JFrame to use BorderLayout

		top.setBackground(Color.WHITE);				// set the Background color of the Top/Main JPanel to white
		top.setPreferredSize(new Dimension(500,500));	// set the standard size of the Top/Main JPanel
		
		f.add(bot.getPanel(), BorderLayout.PAGE_END);	// add the Bottom JPanel to the bottom of the JFrame
		f.add(top, BorderLayout.CENTER);			// add the Top/Main JPanel to the center/top of JFrame
	
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);	// set the program to exit when jframe is closed
		f.pack();			// size the Frame to fit the two JPanels
		f.setVisible(true);	// show the JFrame and all of the JPanels it holds
	}
	
	
	// standard paint method for the JFrame
	// @param g the standard graphics Java package
	public void paint(Graphics g) {
		super.paint(g);
	}
	
}