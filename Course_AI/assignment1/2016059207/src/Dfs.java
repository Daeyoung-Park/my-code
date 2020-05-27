/*
 * dfs �˰����� �����ϴ� Ŭ�����Դϴ�
 */


import  java.util.Arrays;
import java.util.ArrayList;

public class Dfs {
	static int n = 0; // n-queens���� n�� �ǹ��մϴ�
	static ArrayList<Integer> answer = null; // ���������� ���´�� �� col���� queen�� ��ġ�� row��ġ�� ǰ�� �ְ� �� �����Դϴ�
	static int[] rootnode = null; // search tree�� root�̰� initial state�� �ش��մϴ�
	static TreeNode<int[]> root = null; // �ٷ� ������ ���� state�� ������ Node�Դϴ�
	static boolean findAns = false; // dfs�� �����ϴ� ù solution�� ã���� dfs�� recursive call�� ���߰� �ϱ� ���� ����մϴ�
	static int cnt_generating_node = 0; // generated�Ǵ� ��带 counting�ϱ� ���� ����մϴ�
	
	public Dfs(int N) { // �����ڸ� ���� �ʿ��� �������� �ʱ�ȭ�Ͽ����ϴ�
		n = N;
		answer = new ArrayList<>(n+1); 
		for(int i=0; i<n+1; i++) {
			answer.add(0);
		}
		rootnode = new int[N+1];
		Arrays.fill(rootnode, 0);
		root = new TreeNode<int[]>(rootnode);
	}
	
	public void start() { // �־��� ������ ���� ã�� ���� MainClass���� ȣ���ؾ� �� �Լ��Դϴ� 
		
		dfs(0,root); // ù ���ڴ� row�� �ǹ��մϴ�. row�� �ϳ��� �������� ���� �켱 Ž���� �ϵ��� �����Ͽ����ϴ�
		
		int sum = 0; // solution�� ���� ��츦 üũ�ϱ� ���� �����Դϴ�
		for(int i: answer) {
			sum += i;
		}
		if(sum == 0) {
			//System.out.println("no solution");
			return;
		}
		/*
		 * for(int i : answer) {
			System.out.print(i);
			System.out.print(" ");
		}
		System.out.println();
		 */
		
	}
	
	public String make_result() { // ����� resultN.txt�� ���� ���� ������ �Լ��Դϴ�. dfs ���� �� ��� �� ���� ��ȯ���ִ� �Լ��Դϴ�.
		String str = "Location : ";
		for(int i : answer) {
			String s = Integer.toString(i);
			str += (s + " ");
		}
		str += '\n';
		return str;
	}
	
	public void dfs(int row , TreeNode<int[]> node) { // ���� dfs �˰��� �ش��ϴ� �Լ��Դϴ�. recursive version���� �����Ͽ����ϴ�.
		if (findAns == true) {
			return;
		}
		else {
			if (row == n && isGoalPath(node)) { // ���� state�� ���̶�� ���� ã�Ҵٴ� ǥ�ø� �ϰ� answer ������ ���� �����ϴ�
				findAns = true;
				
				for(int i=0; i<n; i++) {
					//System.out.println(node.data[i+1]);
					answer.set(node.data[i+1],i);
				}
				answer.remove(0);
				return;
			}
			else if ( row == n && !isGoalPath(node) ) { // ��� queen�� �� ��ġ�Ͽ��µ� ���� �ƴ϶�� backtracking�Ͽ� �ٸ� branch�� �̵��մϴ�.
				return;
			}
			else { // expanding�� �ϴ� �κ��Դϴ�
				for (int i = 1; i <= n; i++) {
					int[] childData = new int[n+1];
					System.arraycopy(node.data, 0, childData, 0, node.data.length); // �ڽĳ��: 1) �ϴ� �θ��� state�� deep copy�� ��,
					TreeNode<int[]> childNode = node.addChild(childData); // �� state ������ �� ��忡 ���Խ�Ű�� �θ�� �����մϴ�.
					childNode.data[row+1] = i; // 2) ���� row�� queen�� ��ġ�ϴ� action ���� ���Խ�ŵ�ϴ�.
					
					cnt_generating_node++; // generated�Ǵ� ������ ������ ���ϴ�.
					//System.out.println(Arrays.toString(childNode.data));
					dfs(row + 1, childNode); // ���� �ڽ��� �θ���� �ΰ� recursive�ϰ� Ž���մϴ�.
				}
			}
	    
		}
	}
	
	public boolean isGoalPath(TreeNode<int[]> node) { // ���ڷ� �־��� ��尡 goal state���� Ȯ���ϴ� �Լ��Դϴ�
	    // node.data�� index�� row �̰� �� ĭ�� ���� ���� col�Դϴ�. 
	    // ex) col[1] = 1 => 1�� 1��, col[2] = 3 => 2�� 3��
		int[] col = node.data;
	    
		for(int c = 2; c<n+1; c++) {
	    for (int i = 1; i < c; i++) {
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