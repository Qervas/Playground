import java.text.CollationElementIterator;

import java.util.*;

public class HuffmanTree {
	public static boolean DEBUG_INFO = false;
	public static class Node implements Comparable<Node>{
		Character _data;
		int _weight;
		Node left;
		Node right;
		public Node(){/*空节点构造*/}
		public Node(Character data, int weight){
			this._data = data;
			this._weight = weight;
		}
		@Override
		public int compareTo(Node o){
			return o._weight-this._weight;
		}
		@Override
		public String toString() {
			return "{ " + _data + " >>> " + _weight + "}\n";
	}

	}

	// =================================================================
	public static List<Node> toList(String text){
		Map<Character,Integer> countMap = new HashMap<Character,Integer>();//建立Map对象，用于返回
		char x;//用于遍历临时存储
		for(int i= 0; i < text.length(); i++){
			x = text.charAt(i);
			if(!countMap.containsKey(x)){//如果不包含当前字符
				countMap.put(x,1);//则在map对象中加一个，每个字符初次遍历的时候都没有
			}
			else{
				countMap.put(x,countMap.get(x) + 1);//如果有的话就+1
			}
		}
		if(DEBUG_INFO == true){System.out.println(countMap);}
		//将Map转换为list
		List<Node> countList = new ArrayList<Node>();
		for(Map.Entry<Character, Integer> entry : countMap.entrySet()){
			countList.add(new Node(entry.getKey(), entry.getValue()));
			if(DEBUG_INFO == true){System.out.println("Key = " + entry.getKey() + ", Value = " + entry.getValue()); }
		}
		
		return countList;
	}
	public static Node toGroot(List<Node> target){
		List<Node> groot = new ArrayList<Node>(target);
		
		// Collections.sort(groot);
		while(groot.size() > 1){
			// MyComparator mc = new MyComparator();
			Collections.sort(groot);
			Node left = groot.get(groot.size() - 1);
			Node right = groot.get(groot.size() - 2);
			Node parent = new Node('*', left._weight + right._weight);
			parent.left = left;
			parent.right = right;
			groot.remove(groot.size()-1);//extract-min
			groot.remove(groot.size()-1);//extract-min
			groot.add(parent);
		}
		System.out.println(groot);
		// return null;
		return groot.get(0);
	}
	


	public static void inOrderTraverse(Node node) {
       Queue queue = new ArrayDeque<Node>();
        List<Node> list = new ArrayList<Node>();
        if(node != null) {
            queue.offer(node);
        }
          while(!queue.isEmpty()){  
                //将该队列的队尾元素加入到list中  
                list.add((Node) queue.peek());  
                Node p = (Node) queue.poll();  

                //如果左子节点不为null，将它加入到队列  
                if(p.left != null){  
                    queue.offer(p.left);  
                }  

                //如果右子节点不为null，将它加入到队列  
                if(p.right != null){  
                    queue.offer(p.right);  
                }  
            }        
			for(int i = 0; i < list.size(); i++) {
				System.out.println("data:"+list.get(i)._data + " weight:"+list.get(i)._weight);
			}
            return ;  
		}
	public static void main(String[] args){
		System.out.println();
		String data = "In computer science and information theory, "
				+ "a Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. "
				+ "The process of finding and/or using such a code proceeds by means of Huffman coding, "
				+ "an algorithm developed by David A. Huffman while he was a Ph.D. student at MIT, and published in the 1952 paper "
				+ "\"A Method for the Construction of Minimum-Redundancy Codes\".[1] "
				+ "The output from Huffman's algorithm can be viewed as a variable-length code table for encoding a source symbol "
				+ "(such as a character in a file). The algorithm derives this table from the estimated probability or frequency of occurrence"
				+ " (weight) for each possible value of the source symbol. As in other entropy encoding methods, more common symbols are generally "
				+ "represented using fewer bits than less common symbols. Huffman's method can be efficiently implemented, "
				+ "finding a code in linear time to the number of input weights if these weights are sorted.[2] However, "
				+ "although optimal among methods encoding symbols separately, Huffman coding is not always optimal among all compression methods.";
		List<Node> chars = HuffmanTree.toList(data);
		Node receiver = HuffmanTree.toGroot(chars);
		// HuffmanTree.inOrderTraverse(receiver);
		
		
		
	}
}

