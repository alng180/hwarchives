import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

// This JPanel will contain the Increase/Decrease Buttons and the JLabel that displays
// the current Koch level of the Program
public class BottomPanel extends JPanel {
	
	private JPanel panel;	// instance of the BottomPanel JPanel
	private Model model;	// copy of the model 
	public JButton jb1;		// the JButton that is responsible for increasing the Koch level
	public JButton jb2;		// the JButton that is responsible for decreasing the Koch level
	public JLabel label;	// the JLabel that displays the current Koch Level
	
	// Constructor for the class
	// @param m a copy of the model
	public BottomPanel(Model m) {
		this.model = m;	// saves a copy of the Model m into this JPanel
		
		panel = new JPanel();	// instantiates the JPanel
		
		panel.setBackground(Color.GRAY);	// set the Background color to gray
		panel.setLayout(new FlowLayout());	// set the JPanel to use the FlowLayout
		
		label = new JLabel("Current Koch Level = " + model.getDegree());	// create a new JPanel
		jb1 = new JButton("Increase Koch Level");	// creates a JButton (jb1) that will increase the Koch level by one when pressed
		panel.add(jb1);						// add JButton jb1 (first to be added to be placed on the left side of the JPanel)
		panel.add(label);						// add JLabel label (second to be added to be placed in the middle of the JPanel)
		jb2 = new JButton("Decrease Koch Level");	// create a JButton (jb2) that will decrease the Koch level by one when pressed
		panel.add(jb2);						// add JButton jb2 (third to be added to be palced on the right side of the JPanel)
	}
	
	// method that will be called whenever the Koch level changes in order to update
	// the JLabel in this JPanel to display the new Koch level
	public void updateLabel() {
		label.setText("Current Koch Level = " + model.getDegree());	// set the text of the JLabel to display the updated Koch level
	}
	
	// getter method to pass the BottomPanel JPanel back up to the frame
	public JPanel getPanel() {
		return panel;
	}
}