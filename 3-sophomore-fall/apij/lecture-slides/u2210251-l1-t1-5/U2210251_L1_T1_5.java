public class Main{
	static int factorial(int num){
		int factorial;
		if(num == 1){
			return num;
		}
		return num*factorial(num-1);
	}
	static int valueRaiser(int a, int b){
		int temp = 1;
		for(int i = 0; i < b; i++){
			temp *=a;
		}
		return temp;
	}
	public static void main(String[] args){
		//first program
		int a = 7;
		boolean isPrime = true;
		for(int i = 2 ; i <= a/2 ; i++){
			if(a%i == 0){
				isPrime = false;
			}
		}
		if(isPrime == true){
			System.out.println( a + " is prime");
		}
		else {
			System.out.println(a + "is not prime");
		}
		//second program
		int[] array1 = {1,2,3};
		int leastOne = array1[0];
		for(int i =0; i< array1.length; i++){
				if(array1[i] < leastOne){
					leastOne = array1[i];
				}
		}
		System.out.println("Least one: " + leastOne);
		//third program
		int givenNumber = 5;
		if(givenNumber%2 == 0){
			System.out.println(givenNumber + " is even");
		}
		else{
			System.out.println(givenNumber + " is odd");
		}
		// fourth program
		int numForFactorial;
		numForFactorial = factorial(5);
		System.out.println("factorial of " + numForFactorial + " is: " + numForFactorial);
		//fifth program
		int firstNum = 3;
		int secondNum = 3;
		System.out.println(firstNum + " in the power of " + secondNum + " is " + valueRaiser(3, 3));
}
}