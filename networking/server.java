import java.net.*;
import java.util.Scanner;
import java.io.*;

public class Server {

    static class CeasarWorker extends Thread {

	private Socket socket;
    
	public CeasarWorker(Socket socket) {
	    this.socket = socket;
	}

	private void sendMessage(DataOutputStream send, String data) throws IOException {
	    send.writeBytes(data+"\n");
	    send.flush();
	}

	private String shiftString(String input, int shift) {
	    String shiftedString = "";
	    for (int i = 0; i < input.length(); i++) {
		char character = input.charAt(i);
		if (Character.isLetter(character)) {
		    int num = ((int) character);
		    int startingNumber = 0;
		    
		    if (num >= 65 && num <= 90) { // uppercase range
			startingNumber = 65;
		    } else { // lowercase letters
			startingNumber = 97;
		    }

		    int shifted = (num + shift - startingNumber) % 26 + startingNumber;
		    character = (char) shifted;
		}

		shiftedString += character;
		
	    }
	    return shiftedString;
	}
	
	public void run() {

	    boolean gettingRotation = true;
	    
	    try (DataOutputStream send = new DataOutputStream(this.socket.getOutputStream());
	     BufferedReader recv = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));) {

		String results = null;
		int rotation = -1;
		
		while ((results = recv.readLine()) != null) {
		    
		    if (gettingRotation) {
			try {
			    int rotationInput = Integer.parseInt(results);
			    if (rotationInput <= 25 && rotationInput >= 1) {
				sendMessage(send, results);
				gettingRotation = false;
				rotation = rotationInput;
			    } else {
				sendMessage(send, "Invalid rotation #, please supply a number between 1 and 25");
			    }
			} catch (Exception e) {
			    sendMessage(send, "Rotation # must be an Integer!");
			}
		    } else {
			sendMessage(send, shiftString(results, rotation));
		    }

		}

		recv.close();
		send.close();
		this.socket.close();
		
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
