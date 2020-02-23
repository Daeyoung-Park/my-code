/*
 * �а�: ��ǻ�ͼ���Ʈ������к�
 * �й�: 2016059207
 * �̸�: �ڴ뿵
 * 
 * ����1�� ���� �ҽ��ڵ� �ۼ��� �Ϸ��Ͽ����ϴ�
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

	public static void makeOutput(int N, String path) { // �� �Լ� ������ ������ �־��� 3���� �˰����� ����˴ϴ�
		PrintWriter outputStream = null;
		
		String str_N = Integer.toString(N);
		String OsFilePath = path.replaceAll(Pattern.quote("\\"), Matcher.quoteReplacement(File.separator));
		//System.out.println(OsFilePath);
		Dfs d = new Dfs(N); // dfs �˰����Դϴ�
		long beforeTime1 = System.currentTimeMillis();
		d.start(); // �� �Լ��� ȣ���ϸ� ����� �ش��ϴ� ���ڿ��� Dfs Ŭ���� ���� �����˴ϴ�
		long afterTime1 = System.currentTimeMillis();
		
		Bfs b = new Bfs(N); // bfs �˰����Դϴ�
		long beforeTime2 = System.currentTimeMillis();
		b.start(); // �� �Լ��� ȣ���ϸ� ����� �ش��ϴ� ���ڿ��� bfs Ŭ���� ���� �����˴ϴ�
		long afterTime2 = System.currentTimeMillis();
		
		Dfs_ID did = new Dfs_ID(N); // dfid �˰����Դϴ�
		long beforeTime3 = System.currentTimeMillis();
		did.start(); // �� �Լ��� ȣ���ϸ� ����� �ش��ϴ� ���ڿ��� Dfs_id Ŭ���� ���� �����˴ϴ�
		long afterTime3 = System.currentTimeMillis();
		
		try {
			outputStream = new PrintWriter(new FileOutputStream(OsFilePath + "\\result" + str_N + ".txt"));
			
			outputStream.print(">DFS(cnt=");
			outputStream.print(d.cnt_generating_node); outputStream.println(')');
			if(d.findAns) {
			outputStream.println(d.make_result()); // make_result �� resultN.txt�� �� ���ڿ��� ��ȯ���ݴϴ�
			outputStream.print("Time : ");
			outputStream.println( (afterTime1 - beforeTime1) / 1000.0); // �ð��� '��' ������ ��µǵ��� �Ͽ����ϴ�
			outputStream.println();
			}
			else {
				outputStream.println("No solution \n Time : 0.0 \n");
				outputStream.println();
			}
			
			outputStream.print(">BFS(cnt=");
			outputStream.print(b.cnt_generating_node); outputStream.println(')');
			if(d.findAns) {
			outputStream.println(b.make_result()); // make_result �� resultN.txt�� �� ���ڿ��� ��ȯ���ݴϴ�
			outputStream.print("Time : ");
			outputStream.println( (afterTime2 - beforeTime2) / 1000.0); // �ð��� '��' ������ ��µǵ��� �Ͽ����ϴ�
			outputStream.println();
			}
			else {
				outputStream.println("No solution \n Time : 0.0 \n");
				outputStream.println();
			}
			
			outputStream.print(">DFID(cnt=");
			outputStream.print(did.cnt_generating_node); outputStream.println(')');
			if(did.findAns) {
			outputStream.println(did.make_result()); // make_result �� resultN.txt�� �� ���ڿ��� ��ȯ���ݴϴ�
			outputStream.print("Time : ");
			outputStream.println( (afterTime3 - beforeTime3) / 1000.0); // �ð��� '��' ������ ��µǵ��� �Ͽ����ϴ�
			outputStream.println();
			}
			else {
				outputStream.println("No solution \n Time : 0.0 \n");
			}
			
		}
		catch (FileNotFoundException e) {
			System.out.println("Problem making file.");
			System.exit(0);
		}
		
		outputStream.close();
	}
}
