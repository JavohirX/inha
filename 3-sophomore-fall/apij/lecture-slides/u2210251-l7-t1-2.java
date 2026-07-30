import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class ConsoleChatApp {
    private static final int PORT = 9999;
    private static List<Socket> clients = new ArrayList<>();
    private static List<PrintWriter> writers = new ArrayList<>();

    public static void main(String[] args) {
        // Start the server
        new Thread(() -> startServer()).start();


        // Start client 1
        new Thread(() -> startClient("Client 1")).start();

        // Start client 2
        new Thread(() -> startClient("Client 2")).start();
    }

    private static void startServer() {
        try {
            ServerSocket serverSocket = new ServerSocket(PORT);
            System.out.println("Server started. Waiting for clients...");

            while (true) {
                Socket clientSocket = serverSocket.accept();
                clients.add(clientSocket);
                System.out.println("Client connected: " + clientSocket);

                // Create a new thread to handle the client
                Thread clientHandler = new Thread(() -> handleClient(clientSocket));
                clientHandler.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter writer = new PrintWriter(clientSocket.getOutputStream(), true);
            writers.add(writer);

            // Receive and broadcast messages
            while (true) {
                String clientMessage = reader.readLine();
                if (clientMessage == null) {
                    break; // Connection closed by client
                }

                System.out.println("Received from " + clientSocket + ": " + clientMessage);

                // Broadcast the message to all clients
                for (PrintWriter clientWriter : writers) {
                    clientWriter.println(clientMessage);
                }
            }

            // Remove the disconnected client
            clients.remove(clientSocket);
            writers.remove(writer);
            System.out.println("Client disconnected: " + clientSocket);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void startClient(String clientName) {
        try {
            Socket socket = new Socket("localhost", PORT);
            System.out.println(clientName + " connected to server.");

            // Send messages to the server
            BufferedReader consoleReader = new BufferedReader(new InputStreamReader(System.in));
            PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);

            while (true) {
                String message = consoleReader.readLine();
                writer.println(clientName + ": " + message);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
