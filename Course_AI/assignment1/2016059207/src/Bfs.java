/*
 * Bfs �˰����� �����ϴ� Ŭ�����Դϴ�
 * 
 * �� Ŭ���� ������ ���� ������� �Լ����� Dfs Ŭ�������� ���� ������, �Լ���� ������ �̸��� ���� ��, �̵��� ���� �ǹ̸� ���մϴ�
 */

import java.util.ArrayList;
import java.util.Arrays;

import java.util.Queue;
import java.util.LinkedList;

public class Bfs {
	static int n = 0; 
	static ArrayList<Integer> answer = null; 
	static int[] rootnode = null; 
	static TreeNode<int[]> root = null; 
	static boolean findAns = false; 
	Queue<TreeNode<int[]>> q = null; // bfs�� �����ϱ� ���� ����� ť�Դϴ�. ���⿡ �ִ� ������ �ϳ��� ������ goal test�� �ϰ� expanding�մϴ�
	static int cnt_generating_node = 0; 
	
	public Bfs(int N) {
		n = N;
		answer = new ArrayList<>(n+1); 
		for(int i=0; i<n+1; i++) {
			answer.add(0);
		}
		rootnode = new int[N+1];
		Arrays.fill(rootnode, 0);
		root = new TreeNode<int[]>(rootnode);
		q = new LinkedList<TreeNode<int[]>>(); // ť�� �����մϴ�
		cnt_generating_node=0;
	}
	
	public void start() {
		q.offer(root); // ���� queen�� ��ġ���� ���� state�� ť�� �ֽ��ϴ�.
		bfs(root);
	}
	
	public String make_result() {
		String str = "Location : ";
		for(int i : answer) {
			String s = Integer.toString(i);
			str += (s + " ");
		}
		str += '\n';
		return str;
	}
	
	public void bfs(TreeNode<int[]> node) {
		
		while(true) {
			if(q.isEmpty()==true) { // ���� ������ ���µ� ť�� ��� ���� ã�� �������� �ǹ��մϴ�
				//System.out.println("empty");
				break;
			}
			
			TreeNode<int[]> parent = q.poll(); // goal test�� expanding�� ���� ť���� ��带 �����ϴ�
			//System.out.print("parent: ");
			//System.out.println(Arrays.toString(parent.data));
			
			if( parent.depth == n && isGoalPath(parent)) { //goal test�� �մϴ�
				findAns = true;
				for(int k=0; k<n; k++) {
					//System.out.println(parent.data[k+1]);
					answer.set(parent.data[k+1],k); // ù goal state�� ã���� answer ������ ���� �ۼ��ϰ� �����մϴ�
				}
				answer.remove(0);
				return;
			}
			else if (parent.depth !=n) { // ���� ���(parent)�� ������ depth�� �ִ� ����� ���̻� expanded���� �ʵ��� �մϴ�
			for(int j=1; j<n+1; j++) {
				int[] childData = new int[n+1];
				System.arraycopy(parent.data, 0, childData, 0, parent.data.length);
				TreeNode<int[]> childNode = parent.addChild(childData);
				childNode.depth = parent.depth+1; // �ڽ��� �θ��庸�� depth ���� �ϳ� �þ�ϴ�
				childNode.data[childNode.depth] = j;
				
				cnt_generating_node++;
				q.offer(childNode); // ������ �ڽ� ������ ť�� �ֽ��ϴ�
				//System.out.println(Arrays.toString(childNode.data));
			}
			}
		}
	}
	
	public boolean isGoalPath(TreeNode<int[]> node) {
		int[] col = node.data;
	    
		for(int c = 2; c<n+1; c++) {
	    for (int i = 1; i < c; i++) {
	        
	        if (col[i] == col[c]) {
	            return false;
	        }
	        
	        if (Math.abs(col[i] - col[c]) == Math.abs(i - c)) {
	            return false;
	        }
	    }
		}
	    return true;
	}
}