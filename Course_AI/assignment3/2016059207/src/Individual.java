
// �� ��ü�� �ǹ��մϴ�

public class Individual {
	public int fitness; // ��ü�� fitness �����Դϴ�
	int[] curState = null; // ��ü�� state(board �� �ǹ�)�Դϴ� => �ε����� row�̰� �� �ε��� �ȿ� �ִ� ���� column�� �ǹ��մϴ�
	public Individual(int N) {
		fitness =0;
		curState = new int[N];
	}
}
