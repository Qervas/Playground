/**
 * 
 */
//package cn.edu.bistu.cs;

/**
 * @author
 *
 */
import java.util.LinkedList;
public  interface BigInt {
	
	public enum Sign {
		POSITIVE, NEGATIVE;
	};
	/**
	 * 高精度整数加法，将整数bInt与当前整数相加，
	 * 并将结果作为一个新的BitInt类型整数返回，
	 * 方法不改变bInt整数以及当前整数的值
	 * @param bInt
	 * @return
	 */
	public BigInt add(BigInt bInt);
	
	/**
	 * 高精度整数减法，当前整数减去bInt，
	 * 并将结果作为一个新的BitInt类型整数返回
	 * 方法不改变bInt整数以及当前整数的值
	 * @param bInt
	 * @return
	 */
	public BigInt sub(BigInt bInt);

	/**
	 * 高精度整数加法，将长整形变量bLong与当前整数相加，
	 * 并将结果作为一个新的BitInt类型整数返回，
	 * 方法不改变bLong以及当前整数的值
	 * @param bLong
	 * @return
	 */
	public BigInt add(long bLong);
	
	/**
	 * 高精度整数减法，当前整数减去bLong，
	 * 并将结果作为一个新的BitInt类型整数返回
	 * 方法不改变bLong以及当前整数的值
	 * @param bLong
	 * @return
	 */
	public BigInt sub(long bLong);
	
	/**
	 * 高精度整数加法，将整形变量bInt与当前整数相加，
	 * 并将结果作为一个新的BitInt类型整数返回，
	 * 方法不改变bInt以及当前整数的值
	 * @param bInt
	 * @return
	 */
	public BigInt add(int bInt);
	
	/**
	 * 高精度整数减法，当前整数减去bInt，
	 * 并将结果作为一个新的BitInt类型整数返回
	 * 方法不改变bInt以及当前整数的值
	 * @param bInt
	 * @return
	 */
	public BigInt sub(int bInt);
	
	
	public boolean isPositive();
	
	public Sign getSign();
	
	public void setSign(Sign sign);
	
	public Byte[] getValue();

	public void setBit(int bit);//设定位数

	public int getBit();
	
	@Override
	/**
	 * 覆盖Object对象的toString方法，将超长整数值输出
	 * @return
	 */
	String toString();

	public void foo(String input);//用来调用调试
	public LinkedList<Byte> sameSign(Byte[] longerArray,Byte[] shorterArray);
	public LinkedList<Byte> difSign(Byte[] longerArray,Byte[] shorterArray);
	
}
