/**
 * 
 */
//package cn.edu.bistu.cs;
import java.util.Scanner;

/**
 * @author 
 *
 */
public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		System.out.println("\nWelcome!");
		BigInt aInt = new BigInteger("111,111,111,000,000,000");
		BigInt bInt = new BigInteger(111111000L);
		BigInt result = bInt.add(aInt.add(new BigInteger("111")));
		System.out.println(result);
	}
}
