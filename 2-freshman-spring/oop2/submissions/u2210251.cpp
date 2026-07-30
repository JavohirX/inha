#include<iostream>
#include<string>
class Student{
private:
	std::string Student_ID, Student_Name;
	double Maths_Score, English_Score, OOP2_Score;
public:
	void setStudent_ID(std::string sid){
		Student_ID = sid;
	}
	std::string getStudent_ID(){
		return Student_ID;
	}
	void setStudent_Name(std::string studentName){
		Student_Name = studentName;
	}
	std::string getStudent_Name(){
		return Student_Name;
	}
	void setOOP2_Score(double oopScore){
		OOP2_Score = oopScore;
	}
	double getOOP2_Score(){
		return OOP2_Score;
	}
	void setMaths_Score(double mathScore){
		Maths_Score = mathScore;
	}
	double getMaths_Score(){
		return Maths_Score;
	}
	void setEnglish_Score(double engScore){
		English_Score = engScore;
	}
	double getEnglish_Score(){
		return English_Score;
	}
	double getAverage_Score(){
		return (OOP2_Score + Maths_Score + English_Score) / 3;
	}
	double	getTotal_Score(){
		return (OOP2_Score + Maths_Score + English_Score);
	}
};
int main(){
	Student st;
	st.setStudent_ID("U2210251");
	st.setStudent_Name("Javohir");
	st.setOOP2_Score(99.9);
	st.setMaths_Score(99.99);
	st.setEnglish_Score(99.998);
	std::cout << "id: " << st.getStudent_ID() << std::endl;
	std::cout << "name: " << st.getStudent_Name() << std::endl;
	std::cout << "total score: " << st.getTotal_Score() << std::endl;
	std::cout << "average score: " << st.getAverage_Score() << std::endl;
	std::cout << "english score: " << st.getEnglish_Score() << std::endl;
	std::cout << "maths score: " << st.getMaths_Score() << std::endl;
	std::cout << "oop2 score: " << st.getOOP2_Score() << std::endl;

	system("pause");
	return 0;
}