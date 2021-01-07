
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

@SuppressWarnings("all")
public class ClientFrame extends JFrame {
	private String name = "";
	private JScrollPane sp = new JScrollPane();
	private JList lm = new JList();
	private DefaultListModel model = new DefaultListModel();
	private JPanel inputPanel = new JPanel();
	private JLabel label = new JLabel("msg:");
	private JTextField text = new JTextField();
	private JButton btn = new JButton("SEND");
	private JButton btnExit = new JButton("Exit");
	private ClientSock s = null;
	private static ClientFrame frm;

	public ClientFrame() {
		setSize(600, 330);
		this.getContentPane().setLayout(new BorderLayout());
		this.setLocation(300, 300);
		sp.setViewportView(lm);
		sp.setPreferredSize(new Dimension(100, 150));
		lm.setModel(model);
		this.getContentPane().add(sp, BorderLayout.NORTH);

		inputPanel.setLayout(new FlowLayout());
		inputPanel.add(label);
		inputPanel.add(text);
		inputPanel.add(btn);
		inputPanel.add(btnExit);
		text.setPreferredSize(new Dimension(340, 20));
		this.getContentPane().add(inputPanel);
		frm = this;

		btn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String content = text.getText();
				if(content.contains("exit")) {
					s.setAlive(false);
					s.sendMsg(content);
					Container frame = btn.getParent();
					do
						frame = frame.getParent();
					while(!(frame instanceof JFrame));
					((JFrame)frame).dispose();
				} else {
					s.sendMsg(content);
				}
			}
		});

		btnExit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String content = "exit";
				s.setAlive(false);
				s.sendMsg(content);
				Container frame = btnExit.getParent();
				do
					frame = frame.getParent();
				while(!(frame instanceof JFrame));
				((JFrame)frame).dispose();
			}
		});
	}

	public static void outMessage(String msg) {
		frm.model.addElement(msg);
	}

	//call the dialog procedure
	public void show() {
		super.show();
		UserDlg dlg = new UserDlg(this);
		dlg.show();
		name = dlg.getName();
		this.setTitle("client " + name);

		s = new ClientSock();
		s.regUser(name);
		s.start();
        s.startThreadSocket();
	}

	public static void main(String[] args) {
		ClientFrame c = new ClientFrame();
		c.show();
	}
}
