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
		Scanner in = new Scanner(System.in);
		BigInt a,b,result;
		String aInt, bInt,sign;
		while(true){
			aInt = in.nextLine();
			bInt = in.nextLine();
			a = new BigInteger(aInt);
			b = new BigInteger(bInt);
		    sign = in.nextLine();
			if(sign.charAt(0) == '+'){
				result = a.add(b);
			}
			else if(sign.charAt(0) == '-'){
				result = a.sub(b);
			}
			else{continue;}
			System.out.println(result);
		}
	}
}
