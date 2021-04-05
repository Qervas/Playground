import java.text.CollationElementIterator;
import java.util.*;
public class HuffmanTree {
	public static boolean DEBUG_INFO = false;
	public static class Node implements Comparable<Node>{
		Character _data = '\0';
		int _weight = 0;
		Node left = null;
		Node right = null;
		public Node(){}//默认空构造函数
		public Node(Character data, int weight){//含参构造
			this._data = data;
			this._weight = weight;
		}
		@Override
		public int compareTo(Node o){
			return o._weight-this._weight;
		}
		@Override
		public String toString() {
			return "{ " + _data + " >>> " + _weight + "}";
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
			Node parent = new Node((char)0, left._weight + right._weight);//set "*" as the data of each parent node
			parent.left = left;
			parent.right = right;
			groot.remove(groot.size()-1);//extract-min
			groot.remove(groot.size()-1);//extract-min
			groot.add(parent);
		}
		// System.out.println(groot);
		return groot.get(0);
	}
	// =========================Coding part=======================================
	public static String[] dic = new String[256]; //ASCII Dictionary for coding characters
	public static ArrayList<Character> memorandum = new ArrayList<Character>();//备忘录用来记录遍历过程
	public static int i = 0; 
	public static void DFS(Node root){
		// System.out.println("memorandum: " + memorandum + " i: " + (++i));
		if(root._data != (char)0){dic[(int)root._data] = memorandum.toString(); return ;} //叶子节点,把备忘录内容写入编码字典,倒着存
		if(root.left != null){
			memorandum.add('0');
			DFS(root.left);
			memorandum.remove((memorandum.size()-1)); 
		}
		if(root.right != null){
			memorandum.add('1');
			DFS(root.right);
			memorandum.remove(memorandum.size()-1);
		}
	}
	public static void checkDic(){
		int i = 0;
		for(int x = 0; x < dic.length ; x++){
			if(dic[x] !=  null){
				i++;
			System.out.printf("%c:  %s \n",x, dic[x]);
			}
		}
		System.out.println("编码组数 = " + i);
	}
	public static ArrayList<String> encode(String data){
		ArrayList<String> code = new ArrayList<>();
		for(int i = 0; i < data.length(); i++){
			
			code.add(dic[(int)data.charAt(i)]);
		}
		String display = new String();
		for(String x : code){
			display += x;
		}
		// System.out.println(code);

		// System.out.println(display);

		return code;
	}
	public static String decode(ArrayList<String> code, Node root){
		String data = new String();
		Node retriveNode = new Node();
		int i;
		retriveNode = root;
		// System.out.println(code);
		for(int j = 0; j < code.size(); j++){
			retriveNode = root;
			for(i = 0; i < code.get(j).length(); i++){
				if(code.get(j).charAt(i) == '0'){
					retriveNode = retriveNode.left;
				}
				if(code.get(j).charAt(i) == '1'){
					retriveNode = retriveNode.right;
				}
			}
			data += retriveNode._data;
		}
		System.out.println(data);
		return data;
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
		HuffmanTree.DFS(receiver);
		// HuffmanTree.checkDic();
		HuffmanTree.decode(HuffmanTree.encode(data), receiver);
		
		
	}
}

