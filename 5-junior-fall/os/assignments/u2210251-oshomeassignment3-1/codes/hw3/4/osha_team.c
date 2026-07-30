// team_info.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/version.h>

#define BUFFER_SIZE 1024

// **Module Parameters**
static char *student_name = "Javohirbek Xatamov";
module_param(student_name, charp, 0000);
MODULE_PARM_DESC(student_name, "Student Full Name");

static int student_id = 2210251;
module_param(student_id, int, 0000);
MODULE_PARM_DESC(student_id, "Student ID");

static char *level = "Junior";
module_param(level, charp, 0000);
MODULE_PARM_DESC(level, "Level (e.g., Junior)");

static int group_no = 4;
module_param(group_no, int, 0000);
MODULE_PARM_DESC(group_no, "Group Number");

static int team_no = 5;
module_param(team_no, int, 0000);
MODULE_PARM_DESC(team_no, "Team Number");

static char *home_address = "Toshkent, Labzak, 70A";
module_param(home_address, charp, 0000);
MODULE_PARM_DESC(home_address, "Home Address");

static char *phone_no = "+998902075639";
module_param(phone_no, charp, 0000);
MODULE_PARM_DESC(phone_no, "Phone Number");

static char *email_address = "khatamov37@gmail.com";
module_param(email_address, charp, 0000);
MODULE_PARM_DESC(email_address, "Email Address");

static int cgpa = 397; // 3.97
module_param(cgpa, int, 0000);
MODULE_PARM_DESC(cgpa, "CGPA Grade (multiplied by 100)");

static char *project_title = "DOCTORS RESERVATION SYSTEM FOR PATIENTS";
module_param(project_title, charp, 0000);
MODULE_PARM_DESC(project_title, "Term Project Title");

static int project_team_no = 1;
module_param(project_team_no, int, 0000);
MODULE_PARM_DESC(project_team_no, "Term Project Team Number");

static char *filename = "OSHA3TEAM_1";
module_param(filename, charp, 0000);
MODULE_PARM_DESC(filename, "Filename (format: OSHA3TEAM_teamnumber)");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0)
#define USE_KERNEL_RW
#endif

// **Helper Functions**

static void append_to_file(void)
{
    struct file *filep;
    char *buffer;
    ssize_t ret;
    int len;
    int cgpa_int = cgpa / 100;     // Integer part
    int cgpa_frac = cgpa % 100;    // Fractional part

    // **Allocate memory for buffer**
    buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    if (!buffer) {
        pr_err("Team Info Module: Memory allocation failed\n");
        return;
    }

    // **Format the team member information**
    len = snprintf(buffer, BUFFER_SIZE,
                   "----------------------------------------\n"
                   "Student Full Name : %s\n"
                   "Student ID        : %d\n"
                   "Level             : %s\n"
                   "Group No.         : %d\n"
                   "Team No.          : %d\n"
                   "Home Address      : %s\n"
                   "Phone No.         : %s\n"
                   "Email Address     : %s\n"
                   "CGPA              : %d.%02d\n"
                   "Project Title     : %s\n"
                   "Project Team No.  : %d\n"
                   "----------------------------------------\n",
                   student_name, student_id, level, group_no, team_no,
                   home_address, phone_no, email_address,
                   cgpa_int, cgpa_frac,
                   project_title, project_team_no);

    // **Open the file in append mode**
#ifdef USE_KERNEL_RW
    filep = filp_open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (IS_ERR(filep)) {
        pr_err("Team Info Module: Cannot open file %s\n", filename);
        kfree(buffer);
        return;
    }

    // **Write data to file**
    ret = kernel_write(filep, buffer, len, &filep->f_pos);
    if (ret < 0)
        pr_err("Team Info Module: Write failed\n");
    else
        pr_info("Team Info Module: Data appended to %s\n", filename);

    filp_close(filep, NULL);
#else
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);

    filep = filp_open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (IS_ERR(filep)) {
        pr_err("Team Info Module: Cannot open file %s\n", filename);
        set_fs(old_fs);
        kfree(buffer);
        return;
    }

    // **Write data to file**
    ret = vfs_write(filep, buffer, len, &filep->f_pos);
    if (ret < 0)
        pr_err("Team Info Module: Write failed\n");
    else
        pr_info("Team Info Module: Data appended to %s\n", filename);

    filp_close(filep, NULL);
    set_fs(old_fs);
#endif

    kfree(buffer);
}

static void read_and_display_file(void)
{
    struct file *filep;
    char *buffer;
    ssize_t ret;
    loff_t pos = 0;

    // **Allocate memory for buffer**
    buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    if (!buffer) {
        pr_err("Team Info Module: Memory allocation failed\n");
        return;
    }

    // **Open the file in read mode**
#ifdef USE_KERNEL_RW
    filep = filp_open(filename, O_RDONLY, 0);
    if (IS_ERR(filep)) {
        pr_err("Team Info Module: Cannot open file %s\n", filename);
        kfree(buffer);
        return;
    }

    pr_info("Team Info Module: Displaying contents of %s\n", filename);

    while ((ret = kernel_read(filep, buffer, BUFFER_SIZE - 1, &pos)) > 0) {
        buffer[ret] = '\0';
        pr_info("%s", buffer);
    }

    filp_close(filep, NULL);
#else
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);

    filep = filp_open(filename, O_RDONLY, 0);
    if (IS_ERR(filep)) {
        pr_err("Team Info Module: Cannot open file %s\n", filename);
        set_fs(old_fs);
        kfree(buffer);
        return;
    }

    pr_info("Team Info Module: Displaying contents of %s\n", filename);

    while ((ret = vfs_read(filep, buffer, BUFFER_SIZE - 1, &pos)) > 0) {
        buffer[ret] = '\0';
        pr_info("%s", buffer);
    }

    filp_close(filep, NULL);
    set_fs(old_fs);
#endif

    kfree(buffer);
}

// **Module Initialization**
static int __init team_info_init(void)
{
    pr_info("Team Info Module: Initializing\n");
    append_to_file();
    return 0;
}

// **Module Cleanup**
static void __exit team_info_exit(void)
{
    pr_info("Team Info Module: Exiting\n");
    read_and_display_file();
}

module_init(team_info_init);
module_exit(team_info_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Javohirbek Xatamov");
MODULE_DESCRIPTION("Kernel Module for Team Member Information Management");

