
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JTextField;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;


public class UserDlg extends JDialog {
	private JLabel label = new JLabel();
	private JTextField name = new JTextField();
	private JButton btn = new JButton("OK");

	public UserDlg(Frame frm) {
		super(frm);
		this.setTitle("input username: ");
		this.setModal(true);
		this.getContentPane().setLayout(new FlowLayout());
		setSize(300, 80);
		this.setLocation(400, 500);
		this.getContentPane().add(label);
		name.setPreferredSize(new Dimension(100, 20));
		this.getContentPane().add(name);
		this.getContentPane().add(btn);
		btn.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				UserDlg.this.dispose();
			}
		});
	}

	public String getName() {
		return name.getText();
	}

	@SuppressWarnings("deprecation")
	public static void main(String[] args) {
		UserDlg c = new UserDlg(null);
		c.show();
	}
}