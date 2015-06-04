import javax.swing.SwingUtilities;

// Main Class
public class KochMain {

	// Main Method that Starts the Whole Program
	public static void main(String[] args) {
//	    SwingUtilities.invokeLater(new Runnable() {
//	    	public void run() {
	    		Model m = new Model();	// Start the model
	    		Frame f = new Frame(m);	// Start the Frame that will form the container for the remaining graphics
	    		MainController col = new MainController(m, f);	// Start the controller for the whole program
//	    	}
//	});
}
}