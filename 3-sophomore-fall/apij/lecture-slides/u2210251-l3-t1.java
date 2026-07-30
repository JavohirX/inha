import java.util.Scanner;
public class InheritanceDemo {
    public static void main(String[] args) throws InterruptedException
    {
        Scanner input = new Scanner(System.in);
        System.out.println("Enter the student name");
        String studentName = input.nextLine();
        System.out.println("Enter the student ID");
        int studentId = input.nextInt();
        System.out.println("Enter the english score");
        double english = input.nextDouble();
        System.out.println("Enter the maths score");
        double maths = input.nextDouble();
        Student st = new Student(studentName, studentId, english, maths);
        System.out.println("----------------------------------------------");
        System.out.println("Total score of this person(english and math) is " + st.totalScore());
        System.out.println("Is he SOCIE or SOL? \nEnter 1 for SOCIE \n2 for SOL");
        int userInput = input.nextInt();
        if(userInput == 1){
            System.out.println("Enter his oop1 score");
            int oopScore = input.nextInt();
            System.out.println("Enter his Introduction to IT score");
            int ititScore = input.nextInt();
            socieStudent socSt = new socieStudent(studentName, studentId, english, maths, oopScore, ititScore);
            System.out.println("This SOCIE student's total score(english, math, oop1 and Intro2it) is: " + socSt.totalScore());
        }
        else{
            System.out.println("Enter his Computer Programming score");
            int compProgramming = input.nextInt();
            System.out.println("Enter his Introduction to Economics score");
            int ite = input.nextInt();
            solStudent solSt = new solStudent(studentName, studentId, english, maths, compProgramming, ite);
            System.out.println("This SOL student's total score(english, math, compProgramming and Intro2Eco) is: " + solSt.totalScore());
        }
    }
}
class Student{
    private String studentName;
    private int studentID;
    private double english;
    private double maths;
    public Student(){}
    public Student(String sn, int sid,  double eng, double m){
        studentName = sn;
        studentID = sid;
        english = eng;
        maths = m;
    }
    public String getStudentName() {
        return studentName;
    }

    public void setStudentID(int studentID) {
        this.studentID = studentID;
    }

    public void setEnglish(double english) {
        this.english = english;
    }

    public void setMaths(double maths) {
        this.maths = maths;
    }

    public void setStudentName(String studentName) {
        this.studentName = studentName;
    }

    public double getEnglish() {
        return english;
    }

    public double getMaths() {
        return maths;
    }

    public int getStudentID() {
        return studentID;
    }
    public double totalScore(){
        return (english + maths);
    }

}
class solStudent extends Student{
    private double compProgramming;
    private double intro2Eco;
    public solStudent(){}
    public solStudent(String sn, int sid,  double eng, double m, double cp, double ite){
        super(sn, sid, eng, m);
        compProgramming = cp;
        intro2Eco = ite;
    }

    public double getCompProgramming() {
        return compProgramming;
    }

    public double getIntro2Eco() {
        return intro2Eco;
    }

    public void setCompProgramming(double compProgramming) {
        this.compProgramming = compProgramming;
    }

    public void setIntro2Eco(double intro2Eco) {
        this.intro2Eco = intro2Eco;
    }
    public double totalScore(){
        return (super.getEnglish() + super.getMaths() + compProgramming + intro2Eco );
    }

}
class socieStudent extends Student{
    private double oop1;
    private double intro2It;
    public socieStudent(){}
    public socieStudent(String sn, int sid,  double eng, double m, double oop1, double iti){
        super( sn,  sid,   eng, m);
        this.oop1 = oop1;
        intro2It = iti;
    }

    public double getOop1() {
        return oop1;
    }

    public double getIntro2It() {
        return intro2It;
    }

    public void setOop1(double oop1) {
        this.oop1 = oop1;
    }

    public void setIntro2It(double intro2It) {
        this.intro2It = intro2It;
    }
    public double totalScore(){
        return (super.getEnglish() + super.getMaths() + oop1 + intro2It );
    }
}