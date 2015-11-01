package edu.hm.cs.network1.sheet2.task2;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Benjamin Königsberg.
 */
public class CatProxy {

    private static final int LISTENING_PORT = 8082;

    private static final String CAT_URL = "<img src=\"https://upload.wikimedia.org/wikipedia/commons/thumb/2/22/Turkish_Van_Cat.jpg/819px-Turkish_Van_Cat.jpg\"";


    public static void main(String[] args) throws Exception {
        String host = args.length > 0 ? args[0] : "mmix.cs.hm.edu";

        while (true) {
            try (ServerSocket serverSocket = new ServerSocket(LISTENING_PORT);
                 Socket socket = serverSocket.accept();
                 InputStreamReader inputStreamReader = new InputStreamReader(socket.getInputStream());
                 BufferedReader bufferedReader = new BufferedReader(inputStreamReader);

                 OutputStream outputStream = socket.getOutputStream();
                 OutputStreamWriter outputStreamWriter = new OutputStreamWriter(outputStream);
                 PrintWriter printWriter = new PrintWriter(outputStreamWriter)) {

                String requestLine = bufferedReader.readLine();

                List<String> request = new ArrayList<>();
                while (requestLine != null
                        && !"".equals(requestLine)) {
                    request.add(requestLine);
                    requestLine = bufferedReader.readLine();
                }
                System.out.println("Inital Request: " +request);

                List<String> modifiedRequest = modifyHeader(request);

                List<String> response = sendRequestAndGetResponse(modifiedRequest, host);


                for (String responseLine : response) {
                    responseLine = responseLine.replaceAll("you", "you, admirer of cats and all things feline :-)");

                    if (responseLine.trim().contains("img src=")) {
                        printWriter.println(responseLine.replaceAll("<img[^>]+src=\"([^\">]+)\"", CAT_URL));
                    } else {
                        printWriter.println(responseLine);
                    }
                    printWriter.flush();
                }
            }
        }
    }


    private static List<String> sendRequestAndGetResponse(List<String> request, String host) throws IOException {
        List<String> response = new ArrayList<>();

        try (Socket socket = new Socket(host, 80);
             OutputStream outputStream = socket.getOutputStream();
             OutputStreamWriter outputStreamWriter = new OutputStreamWriter(outputStream);
             PrintWriter printWriter = new PrintWriter(outputStreamWriter);

             InputStream inputStream = socket.getInputStream();
             InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
             BufferedReader bufferedReader = new BufferedReader(inputStreamReader)) {

            for (String line : request) {
                printWriter.println(line);
            }
            // empty line to make correct HTTP request.
            printWriter.println();
            printWriter.flush();

            String readLine = bufferedReader.readLine();

            while (readLine != null) {
                response.add(readLine);
                readLine = bufferedReader.readLine();
            }
        }

        return response;
    }

    private static List<String> modifyHeader(List<String> header) {
        List<String> modifiedHeader = new ArrayList<>();

        for (String line : header) {
            if (line.startsWith("GET")) {
                String[] wordsInLine = line.split(" ");
                modifiedHeader.add("GET / " + wordsInLine[2]);

                String host = wordsInLine[1].substring(1);
                modifiedHeader.add("Host: " + host);

            } else if (line.startsWith("Host:")
                    || line.startsWith("Accept-Encoding:")) {
                // ignore on purpose, set in GET case
            } else {
                modifiedHeader.add(line);
            }
        }


        return modifiedHeader;
    }
}
