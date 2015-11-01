package edu.hm.cs.network1.sheet1.task2;import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.String;import java.lang.System;import java.util.Scanner;

/**
 * Initiert einen TestServer
 *
 * @author B. Königsberg und P. Masch.
 */
public class TestServer2 {


    /**
     * The entry point of application.
     *
     * @param args the input arguments
     * @throws IOException the io exception
     */
    public static void main(String[] args) throws IOException {

        try (Scanner sc = new Scanner(System.in);
             FileWriter fileWriter = new FileWriter("test.txt");
             PrintWriter printWriter = new PrintWriter(fileWriter)) {

            System.out.println("Printing the file passed in:");
            while (sc.hasNextLine()) {
                printWriter.println(sc.nextLine());
                printWriter.flush();
            }
        }
    }
}
