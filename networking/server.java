/*
  Ceasar Cipher Server
  student: Jacob Brink
  date: 4/29/2021
  lab: networking

  Sources used: https://docs.oracle.com/javase/tutorial/networking/sockets/readingWriting.html
*/

import java.net.*;
import java.util.Scanner;
import java.io.*;
import java.util.Date;
import java.text.SimpleDateFormat;

public class Server {

	// CeasarWorker handles one connected socket to the server
	static class CeasarWorker extends Thread {

		private Socket socket;

		public CeasarWorker(Socket socket) {
			this.socket = socket;
		}

		/*
		 * sendMessage
		 * 
		 * @params: send stream, data string
		 * 
		 * @description: sends data to the client socket
		 */
		private void sendMessage(DataOutputStream send, String data) throws IOException {
			send.writeBytes(data + "\n");
			send.flush();
		}

		/*
		 * shiftString
		 * 
		 * @params: input, shift (rotation)
		 * 
		 * @returns: string that has only the letters shifted by given shift
		 */
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

		/*
		 * run method
		 * 
		 * @description: this is run when this thread is created and follows the ceasar
		 * 	cipher protocol (get rotation from client, then translate further client
		 * 	messages by that rotation)
		 */
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
								break;
							}
						} catch (Exception e) {
							sendMessage(send, "Rotation # must be an Integer!");
						}
					} else {
						sendMessage(send, shiftString(results, rotation));
					}

				}

				this.socket.close();

			} catch (Exception e) {
				System.out.println(e);
			}
		}

	}

	// Used this for reference
	// https://www.infoworld.com/article/2853780/socket-programming-for-scalable-systems.html
	/*
	 * main
	 * 
	 * @description: starts server on specified port and creates a thread for each
	 * client connection
	 */
	public static void main(String[] args) {
		int port = Integer.parseInt(args[0]);
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		try (ServerSocket serverSocket = new ServerSocket(port)) {

			System.out.println("Listening on port " + port);

			// have another thread handle this socket, so the server
			// can continue to handle new users
			while (true) {
				try {
					Socket socket = serverSocket.accept();
					String time = dateFormat.format(new Date());
					System.out.println(socket.getRemoteSocketAddress().toString() + " connected at " + time);
					CeasarWorker worker = new CeasarWorker(socket);
					worker.start(); 
				} catch (Exception e) {
					System.out.println(e);
				}
			}

		} catch (Exception e) {
			System.out.println(e);
		}
	}

}
