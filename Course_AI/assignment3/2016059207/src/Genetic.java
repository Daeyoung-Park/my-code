/*
 * ���� ������ ���� �˰����Դϴ�
 * 1. population size: 10
 * 2. parent selection method: tournament method => k�� 3���� �ξ����ϴ�
 * 3. crossover rate: 80% => 20%�� �θ� �״�� ī���ϰ� , ������ �ڽĵ鿡 ���ؼ��� one-point ũ�ν������� ����Ͽ����ϴ�
 * 4. mutation rate: 10% => �θ� ���� population 10�� �� 1���� ���ؼ��� �����Ͽ����ϴ�
 * 5. fitness �Լ�: output�� ���ƾ� ������ �������� �ǹ��մϴ� => ����,����,�밢�� ���� Ƚ���� ���Ͽ����ϴ�
 * */


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class Genetic {
	static int n = 0; // n-queens���� n�� �ǹ��մϴ�
	static ArrayList<Integer> answer = null; // ���������� ���´�� �� col���� queen�� ��ġ�� row��ġ�� ǰ�� �ְ� �� �����Դϴ�
	static Individual[] curGeneration = null; // state�� �̿� ���� fitness ���� �����ϴ� ��ü(individual)��� ������ '���� ����'�Դϴ�. state�� �� �ε����� row �̰� �� ĭ�� ���� ���� col�� �ǹ��մϴ�
	static Individual[] nextGeneration = null; // ���� �����Դϴ�. ���⿡ ���� ���뿡�� �״�� ī���� �θ��, ũ�ν������� ���� �ڽĵ�, mutation�� ��ü ���� ���Ե˴ϴ�
	static Random random = new Random();
	static boolean findAns = false;
	static int cnt_generation = 0; // generation�� ������� Ƚ���� ���� ���� �����Դϴ�
	
	public Genetic(int N) {
		n = N;
		answer = new ArrayList<>(n); 
		for(int i=0; i<n; i++) {
			answer.add(0);
		}
		curGeneration = new Individual[10];
		nextGeneration = new Individual[10];
		for(int i=0; i<10; i++) {
			curGeneration[i] = new Individual(n);
			nextGeneration[i] = new Individual(n);
		}
	}
	
	public void start() { // main���� �� �Լ��� ȣ���ؾ� ���� �˰����� ����˴ϴ�
		random_individuals(); // 0��° ���븦 �����ϰ� �����մϴ�
		
		if(n==1) {
			findAns = true;
			for(int j=0; j<n; j++) {
				answer.set(0,1);
			}
			return;
		}
		if(n==2 || n==3) {
			return;
		}
		else {
			while(true) {
				genetic_process(); // ���� ���븦 �����ϱ� ���� ȣ���մϴ�. �� �Լ� ������ parents selection, cross-over, mutation�� �̷�����ϴ�
				cnt_generation++;
				Individual bestIndividual = nextGeneration[0];
				for(int i=1; i<10; i++) {
					if(bestIndividual.fitness > nextGeneration[i].fitness) {
						bestIndividual = nextGeneration[i]; // �� ���뿡���� the fittest ��ü�� ���մϴ�
					}
				}
				
				//System.out.println(Arrays.toString(bestIndividual.curState));
				//System.out.print(" the fittest's score: ");
				//System.out.println(bestIndividual.fitness);
				
				if(bestIndividual.fitness == 0) { // ���� Ž�� ���� ���뿡���� the fittest ��ü�� �����̶�� ���� ǥ���ϰ� �����մϴ�
					findAns = true;
					for(int j=0; j<n; j++) {
						answer.set(bestIndividual.curState[j],j);
					}
					return;
				}
				else { // ���� Ž�� ���� ���뿡���� the fittest ��ü�� ������ �ƴ϶�� �ʿ��� �޸� �Ҵ��� �ٽ� �ϰ� while���� �ٽ� �ݺ��մϴ�
					curGeneration = nextGeneration;
					nextGeneration = new Individual[10];
					for(int i=0; i<10; i++) {
						nextGeneration[i] = new Individual(n);
					}
				}
			}
		}
	}
	
	public void genetic_process() { // �� �Լ� ���� �� ���� ���밡 �ϼ��˴ϴ�
		Individual[] num_k = new Individual[3]; // parent selection���� ����ϴ� �Ķ���� k�� ���� �����Դϴ�
		
		num_k[0] = curGeneration[random.nextInt(10)]; // �� ���� ������ �����ϰ� k���� ��ü�� ���ϴ�
		Individual mother = num_k[0];
		for(int i=1; i<3; i++) {
			num_k[i] = curGeneration[random.nextInt(10)]; // with replacement�� ����մϴ�
			if(num_k[i].fitness < mother.fitness) mother = num_k[i]; // k�� �� ���� fitness�� ��ü�� ���� ����� �״�� ī���ؼ� ���� �θ� �� �Ѹ����� �����մϴ�
		}
		
		num_k[0] = curGeneration[random.nextInt(10)]; // crossover rate�� 20%�� ��ұ� ������ 10�� �� �θ�� 2�� �����Ϸ��� �ش� �ڵ带 �ݺ��Ͽ����ϴ�
		Individual father = num_k[0];
		for(int i=1; i<3; i++) {
			num_k[i] = curGeneration[random.nextInt(10)];
			if(num_k[i].fitness < father.fitness) father = num_k[i];
		}
		
		Individual newChild1 = new Individual(n); // �θ� ��ü�鿡 ���� �޸𸮸� deep copy�Ͽ� ���� ����� ���� �غ� �մϴ� 
		System.arraycopy(mother.curState, 0, newChild1.curState, 0, mother.curState.length);
		newChild1.fitness = mother.fitness;
		Individual newChild2 = new Individual(n);
		System.arraycopy(father.curState, 0, newChild2.curState, 0, father.curState.length);
		newChild2.fitness = father.fitness;
		
		nextGeneration[0] = newChild1; nextGeneration[1] = newChild2; // �θ���� �״�� ���� ����� �����ϴ�
		for(int i=2; i<10; i++) {
			Individual newChild = new Individual(n);
			System.arraycopy(mother.curState, 0, newChild.curState, 0, mother.curState.length); // �ڽ��� ���� ��ü�� �����Ͽ� �����޽��ϴ�(cross-over�� �ٷ� �Ʒ�)
			
			// cross-over �κ��Դϴ�
			int row_father = random.nextInt(n);
			int col_father = father.curState[row_father]; // �ƺ� ��ü�� �� row(�����ϰ� ����)�� ��ġ�� queen�� column ��ġ�� ���� ��, 
			newChild.curState[row_father] = col_father; // �ڽĿ� ���� ������ row�� ��ġ�� queen�� column ��ġ�� ������� �մϴ�. ��, subspace�� ���� replace�� �����մϴ�
			newChild.fitness = fitness(newChild.curState); // state�� �ٲ������ fitness ������ �ùٸ� ���� �������� ������Ʈ�մϴ�
			
			nextGeneration[i] = newChild; // �̷��� cross-over�� ������ �ڽ� ��ü�� ���� ����� �ֽ��ϴ�
		}
		
		// mutation �κ�
		int one_mutation = random.nextInt(10);
		nextGeneration[one_mutation].curState[random.nextInt(n)] = random.nextInt(n); // �� ���뿡�� �����ϰ� �� ��ü�� ���� mutation�� �����մϴ�
		nextGeneration[one_mutation].fitness = fitness(nextGeneration[one_mutation].curState); // mutation�� ���������� fitness ������ ������Ʈ �մϴ�.
	}
	
	public void random_individuals() { //  0��° ���븦 �����ϰ� ����� ���� �Լ��Դϴ�
		for(int i=0; i<10; i++) {
		for(int j=0; j<n; j++) {
			curGeneration[i].curState[j] = random.nextInt(n); // ���� ��ġ�� �����ϰ� �ؼ� ���� ��ü�� ����ϴ�
		}
		int fitV = fitness(curGeneration[i].curState); 
		curGeneration[i].fitness = fitV; // �� ��ü�� fitness ������ ����մϴ�
		}
		
		Individual bestIndividual = curGeneration[0];
		for(int i=1; i<10; i++) {
			if(bestIndividual.fitness > curGeneration[i].fitness) {
				bestIndividual = curGeneration[i]; // 0��° ���뿡���� the fittest ��ü�� ���մϴ�
			}
		}
		
		if(bestIndividual.fitness == 0) { // 0���� ���뿡���� the fittest ��ü�� �����̶�� ���� ǥ���ϰ� �����մϴ�
			findAns = true;
			for(int j=0; j<n; j++) {
				answer.set(bestIndividual.curState[j],j);
			}
			return;
		}
	}
	
	public int fitness(int[] state) { // fitness �Լ��Դϴ�. ���� Ƚ���� �������� output���� Ŀ���ϴ� ��, ����� �۾ƾ� ���� fitness�� �ǹ��մϴ�
	    // col[1] = 1�� *��
	    // col[1] = 1 => 1�� 1��, col[2] = 3 => 2�� 3��
		int[] col = state;
		int num_attack = 0; // �� ���� ������ ���� �Ҽ��� �����ϴ� ���Դϴ�
	    
		for(int c = 1; c<n; c++) {
	    for (int i = 0; i < c; i++) {
	        // ���� ��, ���� ���� üũ�մϴ�
	        if (col[i] == col[c]) {
	        	num_attack+=1;
	        }
	        // �밢���� ���� üũ�մϴ�
	        if (Math.abs(col[i] - col[c]) == Math.abs(i - c)) {
	        	num_attack+=1;
	        }
	    }
		}
		return num_attack; // ���� �����̶�� 0�� ��ȯ�� ���Դϴ�
	}
	
	public String make_result() { // ����� �ش��ϴ� ���ڿ��� ����� �Լ��Դϴ�
		String str = "Location : ";
		for(int i : answer) {
			String s = Integer.toString(i);
			str += (s + " ");
		}
		str += '\n';
		return str;
	}
	
}
