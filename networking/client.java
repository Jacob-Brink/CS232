/*
  student: Jacob Brink
  date: 4/29/2021
  lab: networking

  https://docs.oracle.com/javase/tutorial/networking/sockets/readingWriting.html
*/

import java.net.*;
import java.util.Scanner;
import java.io.*;


public class Client {


    /* checkRotation
     * @params: server rotation response and our sent rotation
     * @returns: true if server response is good, false if server's response fails
     */
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

    /* prompt
     * @params: none
     * @description: sends user's messages to ceasar cipher server and returns server's response
     */
    public static void prompt() {

	// Here we open resources in the try with statement so all resources opened are closed correctly
	try (Socket sock = new Socket(host, port);
	     DataOutputStream send = new DataOutputStream(sock.getOutputStream());
	     BufferedReader recv = new BufferedReader(new InputStreamReader(sock.getInputStream()));) {	    

	
	Scanner scan = new Scanner(System.in);
	boolean rotationStepComplete = false;
	int rotation = -1;
	
	// the prompt for the user
	while (true) {
	    
	    System.out.print(rotationStepComplete ? "Enter text: " : "Enter rotation:");

	    String input = scan.nextLine();
	    
	    if (input.equals("quit"))
		break;

	    if (rotationStepComplete) {
		sendReceive(send, recv, input); // send text to server and get output back
	    } else {

		try {
		    int rotationInput = Integer.parseInt(input);
		    if (rotationInput > 25 || rotationInput < 1) {
			System.out.println("Rotation given is not between 1 and 25");
			continue;
		    }
		} catch (Exception e) {
		    System.out.println("Rotation must be a number");
		    continue;
		}

		String results = sendReceive(send, recv, input);
				
		
		if (checkRotation(results, input)) {
		    rotationStepComplete = true; // if response is valid, proceed to ceasar cipher text sending and receiving (sometimes the example server gave back incorrect numbers)
		}
	    }
	}
	} catch (Exception e) {
	    System.out.println(e);
	};
    }

    /* sendReceive
     * @params: send stream, receive stream, and the data to send
     * @returns: returns result or throws an error
     */
    public static String sendReceive(DataOutputStream send, BufferedReader recv, String data) throws Exception {
	send.writeBytes(data+"\n");
	send.flush();
	String results = recv.readLine();
	System.out.println("\n\tServer says: " + results + "\n");
	return results;
    }
    
    public static String host;
    public static int port;
    
    public static void main(String []args) {
	System.out.println("Welcome to the ceasar cipher!");
	host = args[0];
	port = Integer.parseInt(args[1]);
	prompt();
    }
}
