/*
 * �а�: ��ǻ�ͼ���Ʈ������к�
 * �й�: 2016059207
 * �̸�: �ڴ뿵
 * 
 * ����2�� ���� �ҽ��ڵ� �ۼ��� �Ϸ��Ͽ����ϴ�
 */


import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.nio.file.Paths;
import java.io.FileNotFoundException;
import java.io.File;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MainClass {
	
	public static void main(String[] args) {
		int N = Integer.parseInt(args[0]);
		String path = args[1];
		
		makeOutput(N,path); // resultN.txt�� ����� ���� �Լ��Դϴ�
		//System.out.println(N);
		//System.out.println(path);
	}

	public static void makeOutput(int N, String path) { // �� �Լ� ������ ������ �־��� �˰����� ����˴ϴ�
		PrintWriter outputStream = null;
		
		String str_N = Integer.toString(N);
		String OsFilePath = path.replaceAll(Pattern.quote("\\"), Matcher.quoteReplacement(File.separator));
		//System.out.println(OsFilePath);
		
		Hill_climbing hill = new Hill_climbing(N); // Hill climbing �˰����Դϴ�
		long beforeTime = System.currentTimeMillis();
		hill.start(); // �� �Լ��� ȣ���ϸ� ����� �ش��ϴ� ���ڿ��� Hill_climbing Ŭ���� ���� �����˴ϴ�
		long afterTime = System.currentTimeMillis();
		
		try {
			outputStream = new PrintWriter(new FileOutputStream(OsFilePath + "\\result" + str_N + ".txt"));
			
			outputStream.print(">Hill Climbing(cnt=");
			outputStream.print(hill.cnt_restart); outputStream.println(')');
			if(hill.findAns) {
			outputStream.println(hill.make_result()); // make_result�Լ��� resultN.txt�� �� ���ڿ��� ��ȯ���ݴϴ�
			outputStream.print("Total Elapsed Time : ");
			outputStream.println( (afterTime - beforeTime) / 1000.0); // �ð��� '��' ������ ��µǵ��� �Ͽ����ϴ�
			outputStream.println();
			}
			else {
				outputStream.println("No solution \n Time : 0.0 \n");
				outputStream.println();
			}
			
			
		}
		catch (FileNotFoundException e) {
			System.out.println("Problem making file.");
			System.exit(0);
		}
		
		outputStream.close();
	}
}
