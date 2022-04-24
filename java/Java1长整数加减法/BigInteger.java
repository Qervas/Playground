import java.util.LinkedList;
/*=======Function Overview==================Brief Instruction===============
*String toString()				||override the default toString()method
*BigInter()						||empty parameter constructor
*BigInteger(String)				||tranfer a String to a LinkedList and set how many of its digits
*BigInteger(Long)				||use Long-->String and call the former constructor
*BigInt sameSign(Byte[], Byte[])||same sign addition and subtraction
*BigInt difSign(Byte[], Byte[]) ||different sign addition and subtraction
*BigInt add(BigInt)				||addition
*BigInt sub(BigInt)				||subtraction
*BigInt add(long)				||addition
*BigInt sub(long)				||subtraction
*BigInt add(int)				||addition
*BigInt sub(int)				||subtraction
*boolean isPositive()	s		||whether the number is positive
*Sign getSign()					||get the sign(+ or -) of the number
*void setSign(Sign)				||a sign assignment method
*Byte[] getValue()				||get the value of the number as a byte-array
*int getBit();					||get the number of digits
*void setLinkList(LinkedList<Byte> list)  ||a LinkedList assignment method 
*byte compareGetBiggerAbs(Byte[], Byte[]) ||compare two number and distinguish the one has larger absolute value
*toPrintValue()					||averse the order of digits before toString() method 
*
*/
public class BigInteger implements BigInt {
	@Override
	public String toString() {//override the toString() method when the system print method calling BigInt 
		boolean Question2 = true, checkZero = true; //"Question2" is for printing with comma(,); "checkZero" is for checking whether the value is zero or not 
		String str = ""; //initial a string to return to the system print method
		for(int i = 0; i < this.getValue().length; i++){
			if(this.toPrintValue()[i] != 0){checkZero = false;}//if all digits are 0, it should print as "0", not "0,000" kind.
			if(Question2 && i%3 == 0){str += ',';}//for Question:"Print with the comma every 3 digits"
				str += this.toPrintValue()[i];    //add the digit to the output string(call the toString() method in background)
		}
		if(checkZero == true){str = "0";}		  //all digits are "0"
		if(str.charAt(0) == ','){str = str.substring(1);}//since the method of comma divide may have one comma at the front of the string
		return str;	
	}
	//================constructors============================
	BigInteger(){} //to instantiate an object with default values
	public BigInteger(String integer) {
		//divide the sign from the string and set the sign
		if(integer.charAt(0) == '+'){setSign(Sign.POSITIVE);integer = integer.substring(1);}
		else if(integer.charAt(0) == '-'){setSign(Sign.NEGATIVE);integer = integer.substring(1);}
		else if('0' <= integer.charAt(0) && integer.charAt(0) <= '9'){setSign(Sign.POSITIVE);}//input number without sign also treats as a positive one
		
		//put each character into the list backwards
        for(int i = integer.length() - 1; i >=0; i--){
			if(integer.charAt(i) == ','){continue;}//skip commas
            numbers.add(((byte)(integer.charAt(i) - '0')));
        }
		setBit(numbers.size());//set the number of the digits. It's useful when comparing the value
	}
	public BigInteger(Long integer) {
		this(Long.toString(integer));
	}
	//=============member variables======================
	public LinkedList<Byte> numbers = new LinkedList<Byte>();//store each digit of the input number
	Sign sign; //Pos-1, Neg-0 
	int bit;//count how many digits
	
	//============member functions========================
	@Override
	public LinkedList<Byte> sameSign(Byte[] largerArray, Byte[] smallerArray) {
		//Every time add by bit, the carry from last addition(lastCarry), possible carry on next digit(nextCarry) and the temporary sum for the two single digits(tempSum), the final digit remaining on the position(single) 
        byte lastCarry = 0, nextCarry = 0, tempSum = 0, single = 0;
		LinkedList<Byte> answer = new LinkedList<Byte>();
		//2 situation: different and same length for the two arrays 
		int longerLength = (largerArray.length > smallerArray.length ? largerArray.length : smallerArray.length);//get the longer length of the arrays
		int shorterLength = (largerArray.length < smallerArray.length ? largerArray.length : smallerArray.length);//get the shorter length of the arrays
		//Start to compute
		for(int i = 0; i < longerLength; i++){
                if(i < shorterLength){//in this condition,add corresponding for each digit 
                    tempSum = (byte)(largerArray[i] + smallerArray[i]); //temporary sum on each digit
                    nextCarry = (byte) (tempSum/10);					//the carry for the next digit 
                    single = (byte) (tempSum%10);						
                    if(lastCarry + single >= 10){ //sum(of carry from last round and current single digit number) has new carry
                        tempSum = (byte) (lastCarry + single); 			//update the temporary sum value
                        single = (byte) (tempSum%10);					//update the single digit value
                        nextCarry = (byte) (nextCarry + tempSum/10);	//update the next carry value
                    }
                    else {//(single) + (lastCarry) < 10
                        single = (byte) (single + lastCarry);			//update the single digit value
                    }
					//prepare for the next round
                    lastCarry = nextCarry;								//the nextCarry(this round) will be the lastCarry(next round)
                    answer.add(single);									//add the final version of single digit value to the "answer" LinkedList
                    single = 0;											//reset the value
                    nextCarry = 0;										//reset the value
                }
                else{//two arrays have different length
                    answer.add((byte) (largerArray[i] + lastCarry));	//there's might be one carry need to process
                    lastCarry = 0;										//reset the last round carry value
                }
		}
		if(shorterLength == longerLength && lastCarry != 0){answer.add(lastCarry);}//for this special condition, one digit should be added and the number gets +1 number of digits
		return answer;
	}
	@Override
	public LinkedList<Byte> difSign(Byte[] largerArray, Byte[] smallerArray){

        byte lastCarry = 0, nextCarry = 0, tempSum = 0, single = 0;
		LinkedList<Byte> answer = new LinkedList<Byte>();
		int longerLength = (largerArray.length > smallerArray.length ? largerArray.length : smallerArray.length);
		int shorterLength = (largerArray.length < smallerArray.length ? largerArray.length : smallerArray.length);	
		for(int i = 0; i < longerLength; i++){//Start to compute
			if(i < shorterLength){
				tempSum = (byte)(largerArray[i] - smallerArray[i]);//subtraction
				if(tempSum  + lastCarry< 0){
					nextCarry = -1;								   //the carry is negative now
					single = (byte) (10 + tempSum + lastCarry);	   //ensure the single digit value is positive
				}
				else{
					single = (byte) (tempSum + lastCarry);		   //(single) is non-negative 
				}
				//update values
				lastCarry = nextCarry;
				answer.add(single);	
				nextCarry = 0;
				single = 0;			
			}
			else if(shorterLength == longerLength && lastCarry != 0){answer.add((byte)(largerArray[i] + lastCarry));}
			else{
				if(largerArray[i] + lastCarry != 0){
					if(largerArray[i] + lastCarry < 0){
						answer.add((byte) (largerArray[i] + lastCarry + 10));
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
		byte flag = compareGetBiggerAbs(this.getValue(), bInt.getValue());		//get which number is bigger(or they're eqaul)
		Byte[] largerArray = ( flag == -1 ? this.getValue() : bInt.getValue()); //get the value from the larger array
		Byte[] smallerArray = ( flag == -1 ? bInt.getValue() : this.getValue());//get the value from the smaller array
		BigInt answer = new BigInteger();										//instantiate an object with default value
		if(this.getSign() == bInt.getSign()){									//same sign addition
			answer.setLinkList(sameSign(largerArray,smallerArray));				//get the output from addition and put into "answer" 
		}
		else if(this.getSign() != bInt.getSign()){								//different sign subtraction
			if(flag == 0){answer.add(0);}										//when their absolute values are equal, the answer is zero
			answer.setLinkList(difSign(largerArray,smallerArray));				//get the output from addition and put into "answer"
		}
		return answer;															//return the "answer" LinkedList
	}
	@Override
	public BigInt sub(BigInt bInt) {//it's dual to the add()
		byte flag = compareGetBiggerAbs(this.getValue(), bInt.getValue());
		Byte[] largerArray = ( flag == -1 ? this.getValue() : bInt.getValue()); 
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
	public BigInt add(long bLong) {//Type conversion: long --> String
		BigInt other = new BigInteger(Long.toString(bLong));
		return this.add(other);
	}

	@Override
	public BigInt sub(long bLong) {//Type conversion: long --> String
		BigInt other = new BigInteger(Long.toString(bLong));
		return this.sub(other);
	}

	@Override
	public BigInt add(int bInt) {//Type conversion: int --> String
		BigInt other = new BigInteger(Integer.toString(bInt));
		return this.add(other);
	}

	@Override
	public BigInt sub(int bInt) {//Type conversion: int --> String
		BigInt other = new BigInteger(Integer.toString(bInt));
		return this.sub(other);
	}

	@Override
	public boolean isPositive() {//whether the number is positive
		if(getSign() == Sign.POSITIVE){
			return true;
		}
		return false;
	}

	@Override
	public Sign getSign() {//get the sign
		return this.sign;
	}

	@Override
	public void setSign(Sign sign) {//set the sign
		this.sign = sign;
	}

	@Override
	public Byte[] getValue() {	//get the value as a Byte[] array without operate on the member variable directly
		Byte[] value = new Byte[numbers.size()];
		for(int x = 0; x < numbers.size(); x++){
			value[x] = numbers.get(x);
		}
		return value;
	}

	@Override
	public Byte[] toPrintValue(){	//inverse the order(the original is from low to high as the index from 0 to n) 
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
	public int getBit() { //getter for number of digits
		return bit;
	}
	
	@Override
	public byte compareGetBiggerAbs(Byte[] A, Byte[] B) {//return value >> -1--> A's bigger; 1--> B's bigger; 0--> equal
		//easy for those who have different number of digits
		if(A.length != B.length){
			return (byte) (A.length > B.length ? -1 : 1); //the longer, the bigger
		}
		else{
			//From high position to low position, the one, which first digit more than the other, is big.
			for(int i = A.length-1; i > 0; i--){
				if(A[i] > B[i]){return -1;}
				else if(A[i] < B[i]){return 1;}
			}
		}
		return 0;
	}
	@Override
	public void setLinkList(LinkedList<Byte> list) {//A LinkedList assignment method
		this.numbers = list;
	}

}
