// package cn.edu.bistu.cs;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.HashMap;
/**
 * 哈夫曼树实现
 * @author
 *
 */
public class HuffmanTree {

	/**
	 * 哈夫曼编码
	 */
	private Map<Character, String> code = null;
	
	/**
	 * 生成的huffman树根结点
	 */
	private HTNode tree = null;
		
	/**
	 * 根据初始的结点列表，建立哈夫曼树，
	 * 并生成哈夫曼编码，保存在当前类的code对象中，
	 * 生成的树根结点，被保存在当前类的tree对象中。
	 * 可以反复生成哈夫曼树，每次重新构建树，将更新编码
	 * @param nodes
	 * @return
	 */
	public HTNode buildTree(List<HTNode> nodes){
		return null;
	}
	
	/**
	 * 根据已建立的哈夫曼树根结点，生成对应的字符编码，
	 * 字符编码应为0，1字符串
	 * @param tree
	 * @return
	 */
	public static Map<Character, String> getCode(HTNode tree){
		//TODO
		return null;
	}
	
	/**
	 * 获取已建立的哈夫曼树生成的字符编码，
	 * 字符编码应为0，1字符串
	 * @return
	 */
	public Map<Character, String> getCode(){
		return this.code;
	}
	
	
	/**
	 * 统计字符串中字符出现的频率
	 * @param text
	 * @return
	 */
	public static Map<Character,Integer> computeCharCount(String text){
		Map<Character,Integer> count = new HashMap<Character,Integer>();//建立Map对象，用于返回
		char x;//用于遍历临时存储
		for(int i= 0; i < text.length(); i++){
			x = text.charAt(i);
			if(!count.containsKey(x)){//如果不包含当前字符
				count.put(x,1);//则在map对象中加一个，每个字符初次遍历的时候都没有
			}
			else{
				count.put(x,count.get(x) + 1);//如果有的话就+1
			}
		}
		return count;
	}
	public static void sortCharCount(Map<Character,Integer>){
		//在这里写把Map排序的算法，用于第一次和每一次合成树
		//=====================================================

	}
	
	/**
	 * 使用当前类训练好的huffman编码来对文本进行编码
	 * 
	 * @return
	 */
	public String encode(String text){
		//TODO
		return null;
	}
	
	/**
	 * 使用指定的huffman编码来对文本进行编码
	 * @return
	 */
	public static String encode(String text, Map<Character, String> code){
		//TODO
		return null;
	}

	/**
	 * 使用当前类中训练好的huffman编码，
	 * 对编码后的文本进行解码
	 * @param text
	 * @return
	 */
	public String decode(String text){
		//TODO
		return null;
	}
	
	public HTNode getTree() {
		return tree;
	}

	/**
	 * 使用预先建立好的huffman树，
	 * 对编码后的文本进行解码
	 * @param text
	 * @return
	 */
	public String decode(String text, HTNode tree){
		//TODO
		return null;
	}
	public static void main(String[] args){
		HuffmanTree htree = new HuffmanTree();
		//首先对字符串中的字符出现次数进行统计
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
		Map<Character, Integer> chars = HuffmanTree.computeCharCount(data);
		System.out.println(chars);
		// ArrayList<HTNode> nodes = new ArrayList<>();
		// for(Character c : chars.keySet()){
		// 	HTNode node = new HTNode();
		// 	node.setData(c);
		// 	node.setWeight(chars.get(c));
		// 	node.setLchild(null);
		// 	node.setRchild(null);
		// 	node.setLeaf(true);
		// 	nodes.add(node);
		// }
		// HTNode tree = htree.buildTree(nodes);
		// Map<Character, String> code = HuffmanTree.getCode(tree);
		// for(Character c : code.keySet()){
		// 	System.out.println("字符'"+c+"'的哈夫曼编码："+code.get(c));
		// }
		// String text = "In computer science and information theory";
		// String coded = htree.encode(text);
		// System.out.println("字符串：In computer science and information theory");
		// System.out.println("被编码为："+coded);
		// String oriText = htree.decode(coded);
		// System.out.println("编码："+coded);
		// System.out.println("被解码为："+oriText);
		// System.out.println(oriText.equals(text));
	}
	
	
	
}
