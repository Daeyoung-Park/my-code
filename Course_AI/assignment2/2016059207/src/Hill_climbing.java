
/*
 * ������ �־��� Hill climbing �˰����� ������ Ŭ�����Դϴ�
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class Hill_climbing {
	static int n = 0; // n-queens���� n�� �ǹ��մϴ�
	static ArrayList<Integer> answer = null; // ���������� ���´�� �� col���� queen�� ��ġ�� row��ġ�� ǰ�� �ְ� �� �����Դϴ�
	static int[] curState = null; // ���� state�Դϴ�. �� �ε����� row �̰� �� ĭ�� ���� ���� col�� �ǹ��մϴ�
	static int[] Successor = null; // ���� state�� objective function�� ���� ���� successor�Դϴ�
	static int[] localOptimum = null; // Hill climbing �˰����� �ѹ� �� �� ���ϰ� �� local optimum�Դϴ�. �� ���� ���� �ַ������ üũ�Ǿ�� �մϴ�
	static Random random = new Random();
	static boolean findAns = false;
	static int cnt_restart = 0; // �� �� restart�ǰ� ���� �ַ���� ���ϴ��� Ȯ���ϱ� ���� �����Դϴ�
	
	public Hill_climbing(int N) { // ������ �Դϴ�
		n = N;
		answer = new ArrayList<>(n); 
		for(int i=0; i<n; i++) {
			answer.add(0);
		}
		curState = new int[N];
		Successor = new int[N];
		localOptimum = new int[N];
	}
	
	public void restart() { // local optimum�� ������ �ƴҶ� �� �Լ��� ȣ���Ͽ� restart�մϴ�
		for(int i=0; i<n; i++) {
			curState[i] = random.nextInt(n); // ���� ��ġ�� �ٽ� �մϴ�
		}
	}
	
	public String make_result() { // ���� �ַ���� ���ڿ��� ������ִ� �Լ��Դϴ�.
		String str = "Location : ";
		for(int i : answer) {
			String s = Integer.toString(i);
			str += (s + " ");
		}
		str += '\n';
		return str;
	}
	
	public void start() {
		
		for(int i=0; i<n; i++) {
			curState[i] = random.nextInt(n); // initial state �ʱ�ȭ �κ��Դϴ�. ������ ���´�� �����ϰ� ���� �ֽ��ϴ�.
		}
		
		if(n==2 || n==3) { // n�� 2�̰ų� 3�϶��� ������ ���� ������ iteration�� Ƚ���� �����մϴ�(10��)
			for(int i=0; i<10; i++) {
				hillClimbing(1);
				if(isPerfectSolution(localOptimum)) {
					findAns = true;
					for(int j=0; j<n; j++) {
						answer.set(localOptimum[j],j);
					}
					return;
				}
				else {
					restart();
					cnt_restart++;
				}
			}
		}
		else {
			while(true) { // ���� �����ϴ� ������� perfect �ַ���� ã�������� �ݺ��մϴ�
			hillClimbing(1); // �� �Լ��� ��ȯ�Ǹ� localOptimum�� �������µ�
			if(isPerfectSolution(localOptimum)) { // �� localOptimum�� ���� �������� Ȯ���մϴ�
				findAns = true;
				for(int j=0; j<n; j++) {
					answer.set(localOptimum[j],j); // ������ �´ٸ� ���� �������� �䱸�Ѵ�� ����ϱ� ���� �� col�� row���� ������ �մϴ�
				}
				return;
			}
			else {
				restart(); // ������ �ƴϸ� restart�մϴ�
				cnt_restart++;
			}
			}
		}
		
		//System.out.println(Arrays.toString(curState));
	}
	
	public void hillClimbing(int row) { //  Hill climbing �˰����� �����ϴ� �Լ��Դϴ�
		if(row == n) {
			localOptimum = curState;
			return;
		}
		System.arraycopy(curState,0,Successor,0,curState.length);
		Successor[row] = random.nextInt(n); // successor�� ���� state���� row ������ �ش��ϴ� row�� ���� �����ϰ� �ٲߴϴ�(action). ��, �� �࿡ �ִ� ���� ���� ������ �ٸ� ���� �̵���ŵ�ϴ�.
		int val_current = computeTheNumOfAttack(curState,row); // ���� objective �Լ��� ���� ���
		int val_Succesor = computeTheNumOfAttack(Successor,row); // successor�� objective �Լ��� ���� ���
		
		if(val_current<=val_Succesor) { // ���� �� ���� ���̰� ���� �� ������
			hillClimbing(row+1); // ���� �����ؼ� ��� �����մϴ�
		}
		else { // successor�� �� ������ �� state�� current state�� �˴ϴ�
			curState = Successor;
			hillClimbing(row+1);
		}
	}
	
	public int computeTheNumOfAttack(int[] state, int row) { // objective function�̰� output���� ����� ���� ���Դϴ�
		int num_attack = 0; // �� ���� ������ ���� �Ҽ��� �����ϴ� ���Դϴ�
		
		for (int i = 0; i < row; i++) {
	        // ���� ��, ��
	        if (state[i] == state[row]) {
	        	num_attack+=1;
	        }
	        // �밢��
	        if (Math.abs(state[i] - state[row]) == Math.abs(i - row)) {
	        	num_attack+=1;
	        }
	    }
		
		return num_attack; // ���� �����̶�� 0�� ��ȯ�� ���Դϴ�
	}
	
	public boolean isPerfectSolution(int[] state) { // hill climbing���� ���� local optimum�� ���� �������� Ȯ���մϴ�
	    // col[1] = 1�� *��
	    // col[1] = 1 => 1�� 1��, col[2] = 3 => 2�� 3��
		int[] col = state;
	    
		for(int c = 1; c<n; c++) {
	    for (int i = 0; i < c; i++) {
	        // ���� ��, ���� ���� üũ�մϴ�
	        if (col[i] == col[c]) {
	            return false;
	        }
	        // �밢���� ���� üũ�մϴ�
	        if (Math.abs(col[i] - col[c]) == Math.abs(i - c)) {
	            return false;
	        }
	    }
		}
	    return true;
	}
}
