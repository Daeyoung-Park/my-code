
/*
 * queen�� ��ġ�� ������ ��, ���� action�� ���� ������ �ݿ��� state�� ������ Ʈ�� �ڷᱸ���Դϴ�.
 * search tree�� �� Node(state�� ����)�� �ش� �ڷᱸ���� �̷�����ϴ�
 */

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;

public class TreeNode<T> implements Iterable<TreeNode<T>>{
    public T data; // ���� queen���� ��ġ�� ǥ���� state�Դϴ�. T�� int[]�� ���εǰ� index�� row �̰� �� ĭ�� ���� ���� col�Դϴ�. 
    public TreeNode<T> parent;
    public List<TreeNode<T>> children;
    
    public int depth; // �� ����� depth ������ �ǹ��մϴ�(���� ���, root�� 0, root�� �ڽĵ��� 1). BfsŬ�������� ����մϴ�.
 
    public TreeNode(T data) {
        this.data = data;
        this.children = new LinkedList<TreeNode<T>>();
        this.depth = 0;
    }
 
    public TreeNode<T> addChild(T child) { // �� �ڽĵ��� ������ �����Ű�� ���� ������ �Լ��Դϴ�
        TreeNode<T> childNode = new TreeNode<T>(child);
        childNode.parent = this;
        this.children.add(childNode);
        return childNode;
    }
 
    public Iterator<TreeNode<T>> iterator() {
        // TODO Auto-generated method stub
        return null;
    }
}	