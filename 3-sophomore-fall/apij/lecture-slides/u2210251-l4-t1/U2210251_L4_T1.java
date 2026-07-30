import java.util.Scanner;
public class U2210251_L4_T1 {
    public static void main(String[] args) throws NumberNotFoundException {
        Scanner input = new Scanner(System.in);
        int[] arr = new int[10];
        System.out.println("Select what you want to do: \n1)find the value by index \n2)find the index by value" +
                "\n3)Enter the value for the array element \n4)Enter the value for all elements at once");
        int userInput = input.nextInt();
        switch(userInput){
            case 1:
                System.out.println("Enter the index");
                int index = input.nextInt();
                if(index > 9){ // it's 9 as the elemnts are from 0 to 9
                    throw new ArrayIndexOutOfBoundsException("The index you entered doesn't exist");
                }
                else if(arr[index] == 0){
                    throw new ArrayIndexOutOfBoundsException("You didn't inputted value for this element yet");
                }
                System.out.println("The value of the element with this index is: " + arr[index]);
                break;
            case 2:
                System.out.println("Enter the value");
                int val = input.nextInt();
                boolean isExist = false;
                for(int i = 0; i < arr.length; i++){
                    if(val == arr[i]){
                        System.out.println("The index is this element is: " + i);
                        isExist = true;
                    }
                }
                if(!isExist){
                    throw new NumberNotFoundException("The number you entered doesn't exist");
                }
                break;
            case 3:
                System.out.println("Enter the index of the element you want to input value for");
                index = input.nextInt();
                System.out.println("Enter the value for this element");
                arr[index] = input.nextInt();
                break;
            case 4:
                for(int i = 0; i < arr.length; i++) {
                    System.out.println("Enter the value for the element with index " + (i + 1));
                    arr[i] = input.nextInt();
                }
                break;
        }
    }
}

