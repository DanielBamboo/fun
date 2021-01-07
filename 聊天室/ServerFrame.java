
import java.awt.BorderLayout;
import java.awt.Dimension;
import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JScrollPane;

@SuppressWarnings("all")
public class ServerFrame extends JFrame {
	
	private String name = "";
	private JScrollPane sp = new JScrollPane();
	private JList lm = new JList();
	private DefaultListModel model = new DefaultListModel();
	private static ServerFrame frm;

	public ServerFrame() {
		this.setTitle("server");
		setSize(500, 500);
		this.getContentPane().setLayout(new BorderLayout());
		this.setLocation(300, 300);
		sp.setViewportView(lm);
		sp.setPreferredSize(new Dimension(100, 470));
		lm.setModel(model);
		this.getContentPane().add(sp, BorderLayout.NORTH);
		frm = this;

		// Create Socket server thread and launch
		ServerSock sock = new ServerSock();
		sock.start();
	}

	public static void outMessage(String msg) {
		//frm.model.addElement(msg);
		System.out.println(msg);
	}

	public static void main(String[] args) {
		System.out.println("Server Started. ");
		ServerFrame c = new ServerFrame();
		c.show();
	}
}