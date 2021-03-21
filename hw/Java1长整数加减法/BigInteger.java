//package cn.edu.bistu.cs;
/**
 * @author 
 *
 */
import java.util.LinkedList;


public class BigInteger implements BigInt {

    // public LinkedList<Byte> numbers = new LinkedList<Byte>();
	//================constructors============================
	pulbic BigInteger(){}
	public BigInteger(String integer) {
		if(integer.charAt(0) == '+'){setSign(Sign.POSITIVE);integer = integer.substring(1);}
		else if(integer.charAt(0) == '-'){setSign(Sign.NEGATIVE);integer = integer.substring(1);}
		else if('0' <= integer.charAt(0) && integer.charAt(0) <= '9'){setSign(Sign.POSITIVE);}
		
        for(int i = integer.length() - 1; i >=0; i--){
			if(integer.charAt(i) == ','){continue;}
            numbers.add(((byte)(integer.charAt(i) - '0')));
        }
		setBit(numbers.size());
		foo(integer);
	}
	
	public BigInteger(Long integer) {
        this(Long.toString(integer));
	}
	//=============member variables======================
	public LinkedList<Byte> numbers = new LinkedList<Byte>();
	Sign sign; //Pos-1, Neg-0 
	int bit;//count how many digits

	//============member functions========================
	@Override
	public LinkedList<Byte> sameSign(Byte[] largerArray, Byte[] smallerArray) {
		System.out.println(">>>sameSign()");
        byte lastCarry = 0, nextCarry = 0, tempSum = 0, single = 0;
		LinkedList<Byte> answer = new LinkedList<Byte>();
		int longerLength = (largerArray.length > smallerArray.length ? largerArray.length : smallerArray.length);
		int shorterLength = (largerArray.length < smallerArray.length ? largerArray.length : smallerArray.length);	
		//Start to compute
		for(int i = 0; i < longerLength; i++){
			/*
			complete unsigned add(),
			require signed add
			*/
                if(i < shorterLength){//add corresponding each digit 
                    tempSum = (byte)(largerArray[i] + smallerArray[i]);
                    nextCarry = (byte) (tempSum/10);
                    single = (byte) (tempSum%10);
                    if(/*Last*/lastCarry + single >= 10){ //carry from last round
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
		System.out.println("answer: " + answer);
		System.out.println("lastCarry: " + lastCarry + " nextCarry: "  + nextCarry + " single: " + single);
		System.out.println("longerLength: " + longerLength + " shorterLength: " + shorterLength);
		return answer;
	}
	@Override
	public LinkedList<Byte> difSign(Byte[] largerArray, Byte[] smallerArray){

		System.out.println(">>>difSign()" + smallerArray.length);
        byte lastCarry = 0, nextCarry = 0, tempSum = 0, single = 0;
		LinkedList<Byte> answer = new LinkedList<Byte>();
		int longerLength = (largerArray.length > smallerArray.length ? largerArray.length : smallerArray.length);
		int shorterLength = (largerArray.length < smallerArray.length ? largerArray.length : smallerArray.length);	
		//start to compute
		for(int i = 0; i < longerLength; i++){
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
				answer.add((byte) (largerArray[i] + lastCarry));
				lastCarry = 0;
				}
			}
			
		}
		System.out.println("answer: " + answer);
		System.out.println("lastCarry: " + lastCarry + " nextCarry: "  + nextCarry + " single: " + single);
		System.out.println("longerLength: " + longerLength + " shorterLength: " + shorterLength);
		return null;
	}

	@Override
	public BigInt add(BigInt bInt) {
		System.out.println(">>>add()");
		byte flag = compareGetBiggerAbs(this.getValue(), bInt.getValue());
		System.out.println("flag: " + flag);
		Byte[] largerArray = ( flag == -1 ? this.getValue() : bInt.getValue()); //former array is larger
		Byte[] smallerArray = ( flag == -1 ? bInt.getValue() : this.getValue());
		if(this.getSign() == bInt.getSign()){
			difSign(largerArray,smallerArray);
		}
		else if(this.getSign() != bInt.getSign()){
			if(flag == 0){ return null;}
			sameSign(largerArray,smallerArray);
		}
		//Preparation for signed calculation

		return null;
	}
	@Override
	public BigInt sub(BigInt bInt) {
		System.out.println(">>>sub(): this: " + this.numbers + "");
		byte flag = compareGetBiggerAbs(this.getValue(), bInt.getValue());
		Byte[] largerArray = ( flag == -1 ? this.getValue() : bInt.getValue()); //longer array
		Byte[] smallerArray = ( flag == -1 ? bInt.getValue() : this.getValue());
		if(this.getSign() == bInt.getSign()){
			difSign(largerArray, smallerArray);
		}
		else if(this.getSign() != bInt.getSign()){
			if(flag == 0){return null;}
			sameSign(largerArray,smallerArray);
		}
		//the sign of final answer decided by the longerArray
		return null;
	}

	@Override
	public BigInt add(long bLong) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public BigInt sub(long bLong) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public BigInt add(int bInt) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public BigInt sub(int bInt) {
		// TODO Auto-generated method stub
		return null;
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
	public void setBit(int bit) { //set how many digits according to the input
		this.bit = bit;
	}

	@Override
	public int getBit() { //getter
		return bit;
	}
	
	@Override
	public void foo(String input){
		System.out.printf("\n>>>foo(): \ninput: %s, LinkedList:",input);
		System.out.println(numbers);
		System.out.println("Sign(F-neg,T-pos):" + isPositive());
		getValue();
		
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
