
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ConnectException;
import java.net.Socket;

//reg == register

public class ClientSock extends Thread {
	private Socket s1;
	private InputStream is;
	private OutputStream out;
    private Thread thread;
    private boolean alive;

    public void setAlive(boolean alive) {
        this.alive = alive;
    }

	public ClientSock() {
		try {
			//Socket s1 = new Socket("192.168.2.102", 6666);
            Socket s1 = new Socket("121.37.233.193", 6666);
			is = s1.getInputStream();
            out = s1.getOutputStream();
            alive = true;
		} catch (ConnectException connExc) {
            connExc.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
	}

	public void regUser(String name) {
		name = "r:" + name;
		try {
			out.write(name.getBytes());
		} catch (IOException e) {
            e.printStackTrace();
        }
	}
	
	public void sendMsg(String msg) {  //��Ա����
        msg = "m:" + msg;
        try {
            out.write(msg.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

	@Override
    public void run() {  //重写方法
        try {
            while (true) {
                byte[] b = new byte[2048];
                int len = is.read(b);
                String str = new String(b, 0, len);
                ClientFrame.outMessage(str);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void startThreadSocket() {
        try {
            //if(!s1.getKeepAlive())
            //      s1.setKeepAlive(true);
            //if(!s1.getOOBInline())
            //    s1.setOOBInline(true);
            final String socketContent = "$$$$$$";
            thread = new Thread(new Runnable() {
                @Override
                public void run() {
                    while(true) {
                        try {
                            Thread.sleep(20 * 1000);
                            out.write(socketContent.getBytes("UTF-8"));
                            out.flush();

                            if(!alive) {
                                break;
                            }
                        } catch(Exception e) {
                            e.printStackTrace();
                        }
                    }
                }
            });
            thread.start();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}
