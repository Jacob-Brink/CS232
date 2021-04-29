/*
  student: Jacob Brink
  date: 4/29/2021
  lab: networking

  https://docs.oracle.com/javase/tutorial/networking/sockets/readingWriting.html
*/

import java.net.*;
import java.util.Scanner;
import java.io.*;

public class ClientTest {

    public static boolean checkRotation(String rotationResponse, String sentRotation) {       
	if (rotationResponse != null) {
	    if (rotationResponse.equals(sentRotation)) {
		return true;
	    } else {	
		System.out.println("The server gave back an incorrect rotation!");
	    }
	}	
	return false;
    }
    
    public static void prompt() {
	try (Socket sock = new Socket(host, port);
	     DataOutputStream send = new DataOutputStream(sock.getOutputStream());
	     BufferedReader recv = new BufferedReader(new InputStreamReader(sock.getInputStream()));) {	    

	Scanner scan = new Scanner(System.in);
	boolean rotationStepComplete = false;
	int rotation = -1;
	while (true) {
	    
	    System.out.print(rotationStepComplete ? "Enter text: " : "Enter rotation:");

	    String input = scan.nextLine();
	    
	    if (input.equals("quit"))
		break;

	    if (rotationStepComplete) {
		send.writeBytes(input+"\n");
		send.flush();

		String results = recv.readLine();
		System.out.println("Server says: " + results);
	    } else {
		send.writeBytes(input+"\n");
		send.flush();

		String results = recv.readLine();
		System.out.println("Server says: " + results);
		
		if (checkRotation(results, input)) {
		    rotationStepComplete = true;
		}
	    }
	}
	} catch (Exception e) {
	    System.out.println(e);
	};
    }

    public static String host;
    public static int port;
    
    public static void main(String []args) {
	System.out.println("Welcome");
	host = args[0];
	port = Integer.parseInt(args[1]);
	prompt();
    }
}
