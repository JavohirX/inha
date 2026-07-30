#include <linux/module.h>    // Included for all kernel modules
#include <linux/kernel.h>    // Included for KERN_INFO
#include <linux/init.h>      // Included for __init and __exit macros

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Xonboboyev_Abdulxafizxon");
MODULE_DESCRIPTION("TEAM Information module");

// Forward declaration of the functions
void team_info(const char *fullName, const char *ID, const char *group_no, int team_no, const char *add, const char *ph_num, const char *email, int cgpa_x100, const char *term_title);
void plan(const char *fullName, const char *dream);

static int __init q3_init(void)
{
    printk(KERN_INFO "Loading TEAM Information module...\n\n");
    team_info("Abdulxafizxon Xonboboyev", "U2210253", "004", 5, "Tashkent, Sagban 30 dead-end", "+9987885003", "a.xonboboyev@mail.inha.uz", 3475, "Inha Online quiz"); // CGPA multiplied by 1000
    team_info("Javohirbek Xatamov", "U2210251", "004", 5 , "Tashkent, Labzak, 70A", "+998902075639", "khatamov37@gmail.com", 3970 , "DOCTORS RESERVATION SYSTEM FOR PATIENTS");
    team_info("Akmaljon Sodikov", "U2210214", "004", 5, "Tashkent, Yunusabad, Islamabad 65", "+998900941289", "akmal.sodikov04@gmail.com", 3720, "DOCTORS RESERVATION SYSTEM FOR PATIENTS ");
    team_info("Samandar Sabitov", "U2210197", "004", 5, "Tashkent, 4- Tuzel/5", "+998998890457", "samandarsabitov1@gmail.com", 1850, "DOCTORS RESERVATION SYSTEM FOR PATIENTS");
    team_info("Davlatbek Kobiljonov", "U2210118", "001", 5, "Tashkent, Labzak, 70A", "+998906003940", "kobiljonovdavlatbek@gmail.com", 3700, "DOCTORS RESERVATION SYSTEM FOR PATIENTS");
    team_info("Temur Eshboyev", "U2210068", "002", 5, "Tashkent, Labzak, 70A", "+998905155548", "eshboyevtemur0@gmail.com", 2750, "DOCTORS RESERVATION SYSTEM FOR PATIENTS");
    return 0;    // Return 0 indicates the module loaded successfully
}

static void __exit q3_cleanup(void)
{
    plan("Abdulxafizxon Xonboboyev", "After graduation, my goal is to become a skilled Backend Java Developer. I am passionate about building efficient, scalable, and secure backend systems that power modern applications. My aspiration is to work with innovative technologies and continuously improve my expertise in Java and backend development");
    plan("Akmaljon Sodikov", "After graduation, I want to become a proficient software engineer, working in a dynamic environment where I can apply my technical skills and continue to learn. My immediate goal is to join a company that values innovation and provides opportunities for growth, where I can contribute to developing impactful software solutions that solve real-world problems.\nMy long-term goal in life is to master software development across various domains, and eventually lead a team or even start my own tech company. I want to create software that not only enhances user experiences but also makes a meaningful difference in people’s lives, whether through efficiency, accessibility, or by addressing specific needs in areas like healthcare, education, or sustainability.");
    plan("Javohirbek Xatamov", "After graduation, I’m excited to dive into the tech industry. With my computer science degree, I have options in software development, data science, and cybersecurity. I’m eager to apply what I’ve learned, tackle real-world challenges, and keep growing my skills, whether at a big tech company or an innovative startup.");
    plan("Davlatbek Kobiljonov", "To become a great IT specialist, I will attend some intensive course to improve in one or more directions in IT, such as Data Science, Cybersecurity, AI. And then apply for a job in Uzbekistan, and improve the development of technologies in our country.");
    plan("Samandar Sabitov", "After graduation, My plan is to go abroad and continue education in second profession and try to be specialist in two professions which will be related to each other. And also I have a goals to become full-stack developer and make a invention in technologies which will be useful for people.");
    plan("Temur Eshboyev", "After graduation, I want to change my major and never do this kinda fatal erro.\n My long-term goal is to live a life where there is no word \"programming\" and \"software engineering\"");
    printk(KERN_INFO "Cleaning up module...\n");
}

module_init(q3_init);
module_exit(q3_cleanup);

// Function definition for team_info
void team_info(const char *fullName, const char *ID, const char *group_no, int team_no, const char *add, const char *ph_num, const char *email, int cgpa_x100, const char *term_title)
{
    printk(KERN_INFO "Full Name: %s\n", fullName);
    printk(KERN_INFO "ID: %s\n", ID);
    printk(KERN_INFO "Level: Junior\n");
    printk(KERN_INFO "Group No.: %s\n", group_no);
    printk(KERN_INFO "Team No.: %d\n", team_no);
    printk(KERN_INFO "Home Address: %s\n", add);
    printk(KERN_INFO "Phone No.: %s\n", ph_num);
    printk(KERN_INFO "Email address: %s\n", email);
    printk(KERN_INFO "CGPA Grade up to Sophomore level: %d.%03d\n", cgpa_x100 / 1000, cgpa_x100 % 1000);  // Display CGPA as decimal
    printk(KERN_INFO "Term Project Title: %s\n", term_title);
    printk(KERN_INFO "\n");
}

// Function definition for plan
void plan(const char *fullName, const char *dream)
{
    printk(KERN_INFO "Full Name: %s\n", fullName);
    printk(KERN_INFO "Future Plan: %s\n", dream);
    printk(KERN_INFO "\n");
}


