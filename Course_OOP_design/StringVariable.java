package project01_2;


public class StringVariable {

	public static void main(String[] args) {
		// TODO Auto-generated method stub	
		String name = "parkdaeyoung";
		
		String greeting1 = "Hello";
		String greeting2 = "nice to meet you";
		
		String uName = name.toUpperCase();
		
		System.out.println(greeting1 + " " + name + " " + greeting2);
		
		System.out.println("name�� ���� : " + name.length());
		
		System.out.println("name�� uName��  ������ : " + name.equals(uName));
		
		System.out.println("name�� uName�� ��ҹ��ڰ� ������ ������ : " + name.equalsIgnoreCase(uName));
		
		
	}

}
