import java.util.Scanner;
public class U2210251_L2_T1_3{
    public static void main(String[] args) {

        Scanner scoreScanner = new Scanner(System.in);
        System.out.println("Enter the scrore: ");
        int score = scoreScanner.nextInt();

        Grader GraderObj = new Grader();

        System.out.println(GraderObj.grader(score));

        Scanner numberScanner = new Scanner(System.in);
        System.out.println("Enter the number1: ");
        String number1 = numberScanner.nextLine();
        System.out.println("Enter the number1: ");
        String number2 = numberScanner.nextLine();

        HugeInteger HugeIntegerObj1 = new HugeInteger();
        HugeInteger HugeIntegerObj2 = new HugeInteger();
        HugeInteger sumRes = new HugeInteger();

        int[] numberArray1 =  HugeIntegerObj1.parse(number1);
        int[] numberArray2 =  HugeIntegerObj2.parse(number2);

        for(int i =0; i < numberArray1.length; i++){
            System.out.print(numberArray1[i]);
        }
        for(int i =0; i < numberArray2.length; i++){
            System.out.print(numberArray2[i]);
        }
        System.out.println("\n sum");
        int[] AddTwoHugeIntegers = sumRes.add(numberArray1, numberArray2);

        for(int i =0; i < AddTwoHugeIntegers.length; i++){
            System.out.print(AddTwoHugeIntegers[i]);
        }

        System.out.println("\n sub");
        int[] SubTwoHugeIntegers = sumRes.substract(numberArray1, numberArray2);

        for(int i =0; i < SubTwoHugeIntegers.length; i++){
            System.out.print(SubTwoHugeIntegers[i]);
        }


        System.out.println("\n date");


        System.out.println("Input the date: ");
        int date = numberScanner.nextInt();
        System.out.println("Input the month: ");
        int month = numberScanner.nextInt();
        System.out.println("Input the year: ");
        int year = numberScanner.nextInt();

        Date Calendar = new Date(year, month, date);

        Calendar.display(("integer"));
        Calendar.display(("string"));
        Calendar.display(("days"));

    }
}

class Grader {
    String grade;


    public Grader (){

    }
    String letterGrader(){
        return grade;
    }

    String grader (int score){
        if(score >= 90){
            return "A+";
        }
        if(score >= 85){
            return "A";
        }
        if(score >= 80){
            return "B+";
        }
        if(score >= 75){
            return "B";
        }
        if(score >= 65){
            return "C+";
        }
        if(score >= 60){
            return "C";
        }
        if(score >= 55){
            return "D+";
        }
        if(score >= 50){
            return "D";
        }
        return "F";
    }
}


class HugeInteger {
    int[] numberArray = new int[40];
    int[] parse(String number){
        for(int i = number.length() - 1, j = 39; i >= 0 ; i--, j--){
            numberArray[j] = number.charAt(i) - 48;
        }
        return numberArray;
    }
    String toString(String number){
        return number;
    }
    int[] add(int[] num1, int[] num2){
        int[] res = new int[40];
        int rem = 0;
        for(int i = num1.length - 1; i >= 0; i--){
            res[i] = num1[i] + num2[i] + rem;
            rem = 0;
            while(res[i] >= 10){
                res[i] -= 10;
                rem += 1;
            }
        }
        return res;
    }
    int[] substract (int[] num1, int[] num2){
        int[] res = new int[40];
        int rem = 0;
        for(int i = num1.length - 1; i >= 0; i--){
            if(num1[i] - num2[i] < 0){
                num1[i - 1] -= 1;
                num1[i] += 10;
            }
            res[i] =  num1[i] - num2[i];
        }
        return res;
    }
    static boolean isEqualTo(int[] num1, int[] num2){
        for(int i = 0; i <= num1.length - 1; i ++){
            if(num2[i] != num1[i]){
                return false;
            }
        }
        return true;
    }

    static boolean isNotEqualTo(int[] num1, int[] num2){
        for(int i = 0; i <= num1.length - 1; i ++){
            if(num2[i] != num1[i]){
                return true;
            }
        }
        return false;
    }

    static boolean isGraterThan(int[] num1, int[] num2){
        for(int i = 0; i <= num1.length - 1; i ++) {
            if (num1[i] > 0 || num2[i] > 0) {
                if (num2[i] > num1[i]) {
                    return false;
                }
            }
        }
        return true;
    }

    static boolean isLessThan(int[] num1, int[] num2){
        for(int i = 0; i <= num1.length - 1; i ++) {
            if (num1[i] > 0 || num2[i] > 0) {
                if (num2[i] > num1[i]) {
                    return true;
                }
            }
        }
        return false;
    }

    static boolean isGreaterThanOrEqualTo(int[] num1, int[] num2){
        for(int i = 0; i <= num1.length - 1; i ++) {
            if (num1[i] > 0 || num2[i] > 0) {
                if (num2[i] > num1[i]) {
                    return false;
                }
            }
        }
        return true;
    }

    static boolean isLessThanOrEqualTo(int[] num1, int[] num2){
        for(int i = 0; i <= num1.length - 1; i ++) {
            if (num1[i] > 0 || num2[i] > 0) {
                if (num2[i] > num1[i]) {
                    return true;
                }
            }
        }
        return false;
    }

}


class Date{
    int year = 2023;
    int month = 9;
    int date = 17;
    Date(int Y, int M, int D){
        year = Y;
        month = M;
        date = D;
    }

    void display(String type){
        if(type == "integer"){
            System.out.println(month + "/" + date + "/" + year);
        }else if(type == "string"){
            String monthString = "Month";
            if(month == 1){
                monthString = "January";
            } else if (month == 2) {
                monthString = "February";
            }
            else if (month == 3) {
                monthString = "March";
            }
            else if (month == 4) {
                monthString = "April";
            }
            else if (month == 5) {
                monthString = "May";
            }
            else if (month == 6) {
                monthString = "June";
            }
            else if (month == 7) {
                monthString = "July";
            }
            else if (month == 8) {
                monthString = "August";
            }
            else if (month == 9) {
                monthString = "September";
            }
            else if (month == 10) {
                monthString = "October";
            }
            else if (month == 11) {
                monthString = "November";
            }
            else if (month == 12) {
                monthString = "December";
            }
            System.out.println(monthString + " " + date + "," + year);
        } else if (type == "days") {
            int days = 0;

            days = (month - 1)  * 30 + date;

            System.out.println(days + " " + year);
        }
    }

}
