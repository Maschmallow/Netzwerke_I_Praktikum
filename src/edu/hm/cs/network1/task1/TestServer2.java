package edu.hm.cs.network1.task1;import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.String;import java.lang.System;import java.util.Scanner;

/**
 * Created by Benjamin Königsberg.
 */
public class TestServer2 {


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
