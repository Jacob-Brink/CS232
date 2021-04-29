import java.net.*;
import java.util.Scanner;
import java.io.*;

public class Server {

    static class CeasarWorker extends Thread {

	private Socket socket;
    
	public CeasarWorker(Socket socket) {
	    this.socket = socket;
	}

	public void run() {
	    System.out.println("Someone connected!");
	    try (DataOutputStream send = new DataOutputStream(this.socket.getOutputStream());
	     BufferedReader recv = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));) {
		while (true) {
		    String results = recv.readLine();
		    send.writeBytes(results+"\n");
		    send.flush();
		}
		
	    } catch (Exception e) {
		System.out.println(e);
	    }
	}    
    
    }

    
    // inspired by https://www.infoworld.com/article/2853780/socket-programming-for-scalable-systems.html
    public static void main(String []args) {
	int port = Integer.parseInt(args[0]);
	try (ServerSocket serverSocket = new ServerSocket( port )) {

	    System.out.println("Listening on port " + port);


	    while (true) {
		try {
		    Socket socket = serverSocket.accept();
		    CeasarWorker worker = new CeasarWorker(socket);
		    worker.start();
		} catch (Exception e) {

		}
	    }
	    

	} catch (Exception e) {
	    System.out.println(e);
	}
    }
    
}
