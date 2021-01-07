
import java.lang.Thread;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.IOException;


public class ServerSockThread extends Thread {
	private InputStream inData;
	private OutputStream os;
	private String name = "";

	public ServerSockThread(InputStream s1_in, OutputStream s1_out) {
		this.inData = s1_in;
		os = s1_out;
	}

	@Override
	public void run() {
		try {
			while(true) {
				byte[] b = new byte[2048];
				int len = inData.read(b);

				String str = new String(b, 0, len);
				
				if(str.charAt(0) == 'r') {
					name = str.substring(2);
					ServerFrame.outMessage("reg: " + name);
					ServerSock.out(os, "reg: " + name);
				} else {
					str = str.substring(2);
					ServerFrame.outMessage(name + ":" + str);
					ServerSock.out(os, name + ":" + str);
				}
			}
		}catch(IOException e) {
			e.printStackTrace();
		}
	}
}