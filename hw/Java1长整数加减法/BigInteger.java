//package cn.edu.bistu.cs;
/**
 * @author 
 *
 */
import java.util.LinkedList;


public class BigInteger implements BigInt {

	@Override
	public String toString() {
		boolean Question2 = false;
		String str = "";
		for(int i = 0; i < this.getValue().length; i++){
			if(Question2 && (i-1)%3 == 0){str += ',';}//for Question 3.2
				str += this.toPrintValue()[i];
		}
		return str;
	}
	//================constructors============================
	 BigInteger(){}
	public BigInteger(String integer) {
		if(integer.charAt(0) == '+'){setSign(Sign.POSITIVE);integer = integer.substring(1);}
		else if(integer.charAt(0) == '-'){setSign(Sign.NEGATIVE);integer = integer.substring(1);}
		else if('0' <= integer.charAt(0) && integer.charAt(0) <= '9'){setSign(Sign.POSITIVE);}
		
        for(int i = integer.length() - 1; i >=0; i--){
			if(integer.charAt(i) == ','){continue;}
            numbers.add(((byte)(integer.charAt(i) - '0')));
        }
		setBit(numbers.size());
	}
	
	public BigInteger(Long integer) {
		// System.out.println("afterlife: " + Long.toString(integer));
		this(Long.toString(integer));

	}
	//=============member variables======================
	public LinkedList<Byte> numbers = new LinkedList<Byte>();
	Sign sign; //Pos-1, Neg-0 
	int bit;//count how many digits

	//============member functions========================
	@Override
	public LinkedList<Byte> sameSign(Byte[] largerArray, Byte[] smallerArray) {
		// System.out.println(">>>sameSign()");
        byte lastCarry = 0, nextCarry = 0, tempSum = 0, single = 0;
		LinkedList<Byte> answer = new LinkedList<Byte>();
		int longerLength = (largerArray.length > smallerArray.length ? largerArray.length : smallerArray.length);
		int shorterLength = (largerArray.length < smallerArray.length ? largerArray.length : smallerArray.length);	
		//Start to compute
		for(int i = 0; i < longerLength; i++){
                if(i < shorterLength){//add corresponding each digit 
                    tempSum = (byte)(largerArray[i] + smallerArray[i]);
                    nextCarry = (byte) (tempSum/10);
                    single = (byte) (tempSum%10);
                    if(lastCarry + single >= 10){ //carry from last round
                        tempSum = (byte) (lastCarry + single);
                        single = (byte) (tempSum%10);
                        nextCarry = (byte) (nextCarry + tempSum/10);

                    }
                    else {
                        single = (byte) (single + lastCarry);
                    }
                    lastCarry = nextCarry;
                    answer.add(single);
                    single = 0;
                    nextCarry = 0;
                }
                else{
                    answer.add((byte) (largerArray[i] + lastCarry));
                    lastCarry = 0;
                }
			
		}
		if(shorterLength == longerLength && lastCarry != 0){answer.add(lastCarry);}
		return answer;
	}
	@Override
	public LinkedList<Byte> difSign(Byte[] largerArray, Byte[] smallerArray){

		// System.out.println(">>>difSign()" + smallerArray.length);
        byte lastCarry = 0, nextCarry = 0, tempSum = 0, single = 0;
		LinkedList<Byte> answer = new LinkedList<Byte>();
		int longerLength = (largerArray.length > smallerArray.length ? largerArray.length : smallerArray.length);
		int shorterLength = (largerArray.length < smallerArray.length ? largerArray.length : smallerArray.length);	
		for(int i = 0; i < longerLength; i++){//Start to compute
			if(i < shorterLength){
				tempSum = (byte)(largerArray[i] - smallerArray[i]);
				if(tempSum  + lastCarry< 0){
					nextCarry = -1;
					single = (byte) (10 + tempSum + lastCarry);
				}
				else{
					single = (byte) (tempSum + lastCarry);
				}

				lastCarry = nextCarry;
				answer.add(single);	
				nextCarry = 0;
				single = 0;			
			}
			else if(shorterLength == longerLength && lastCarry != 0){answer.add((byte)(largerArray[i] + lastCarry));}
			else{
				if(largerArray[i] + lastCarry != 0){
					if(largerArray[i] + lastCarry < 0){
						answer.add((byte) (largerArray[i] + lastCarry + 10));//bug fixed
						lastCarry = -1;
					}
					else{
						answer.add((byte) (largerArray[i] + lastCarry));
						lastCarry = 0;
					}
				}
			}
			
		}
		return answer;
	}

	@Override
	public BigInt add(BigInt bInt) {
		// System.out.println(">>>add()");
		byte flag = compareGetBiggerAbs(this.getValue(), bInt.getValue());
		// System.out.println("flag: " + flag);
		Byte[] largerArray = ( flag == -1 ? this.getValue() : bInt.getValue()); //former array is larger
		Byte[] smallerArray = ( flag == -1 ? bInt.getValue() : this.getValue());
		BigInt answer = new BigInteger();
		if(this.getSign() == bInt.getSign()){
			answer.setLinkList(sameSign(largerArray,smallerArray));
		}
		else if(this.getSign() != bInt.getSign()){
			if(flag == 0){ answer.add(0);}
			answer.setLinkList(difSign(largerArray,smallerArray));
		}
		return answer;
	}
	@Override
	public BigInt sub(BigInt bInt) {
		// System.out.println(">>>sub(): this: " + this.numbers + "");
		byte flag = compareGetBiggerAbs(this.getValue(), bInt.getValue());
		Byte[] largerArray = ( flag == -1 ? this.getValue() : bInt.getValue()); //longer array
		Byte[] smallerArray = ( flag == -1 ? bInt.getValue() : this.getValue());
		BigInt answer = new BigInteger();
		if(this.getSign() == bInt.getSign()){
			answer.setLinkList(difSign(largerArray, smallerArray));
		}
		else if(this.getSign() != bInt.getSign()){
			if(flag == 0){return null;}
			answer.setLinkList(sameSign(largerArray,smallerArray));
		}
		return answer;
	}

	@Override
	public BigInt add(long bLong) {
		BigInt other = new BigInteger(Long.toString(bLong));
		return this.add(other);
	}

	@Override
	public BigInt sub(long bLong) {
		BigInt other = new BigInteger(Long.toString(bLong));
		return this.sub(other);
	}

	@Override
	public BigInt add(int bInt) {
		BigInt other = new BigInteger(Integer.toString(bInt));
		return this.add(other);
	}

	@Override
	public BigInt sub(int bInt) {
		BigInt other = new BigInteger(Integer.toString(bInt));
		return this.sub(other);
	}

	@Override
	public boolean isPositive() {
		if(getSign() == Sign.POSITIVE){
			return true;
		}
		return false;
	}

	@Override
	public Sign getSign() {
		return this.sign;
	}

	@Override
	public void setSign(Sign sign) {
		this.sign = sign;
	}

	@Override
	public Byte[] getValue() {
		Byte[] value = new Byte[numbers.size()];
		for(int x = 0; x < numbers.size(); x++){
			value[x] = numbers.get(x);
		}
		return value;
	}

	@Override
	public Byte[] toPrintValue(){
		Byte[] toPrint = new Byte[numbers.size()];
		for (int i = 0; i < numbers.size(); i++){
			toPrint[numbers.size() - i - 1] = numbers.get(i);
		}
		return toPrint;

	}
	@Override
	public void setBit(int bit) { //set how many digits according to the input
		this.bit = bit;
	}

	@Override
	public int getBit() { //getter
		return bit;
	}
	
	@Override
	public byte compareGetBiggerAbs(Byte[] A, Byte[] B) {//-1: A, 1: B, 0: the same
		if(A.length != B.length){
			return (byte) (A.length > B.length ? -1 : 1);
		}
		else{
			for(int i = A.length-1; i > 0; i--){
				if(A[i] > B[i]){return -1;}
				else if(A[i] < B[i]){return 1;}
			}
		}
		return 0;
	}
	@Override
	public void setLinkList(LinkedList<Byte> list) {
		this.numbers = list;
	}

}
