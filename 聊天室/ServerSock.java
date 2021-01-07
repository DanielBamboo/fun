
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class ServerSock extends Thread {

	private static ServerSocket s = null;
	private static ArrayList allOut = new ArrayList();

	@Override
	public void run() {
		try {
			s = new ServerSocket(6666);
			while(true) {
				Socket s1 = s.accept();
				OutputStream s1_out = s1.getOutputStream();
				allOut.add(s1_out);
				InputStream s1_in = s1.getInputStream();

				//when get the message(input byte stream)

				//call the thread
				ServerSockThread one = new ServerSockThread(s1_in, s1_out);
				one.start();
			}
		} catch(IOException e) {
			System.err.println("error");
		}
	} 

	// send messages to all cliends
	public static void out(OutputStream s, String msg) {
		for (int i =0; i < allOut.size(); i++) {
			try {
				((OutputStream)allOut.get(i)).write(msg.getBytes());
			} catch(IOException e) {
				e.printStackTrace();
			}
		}
	}
}