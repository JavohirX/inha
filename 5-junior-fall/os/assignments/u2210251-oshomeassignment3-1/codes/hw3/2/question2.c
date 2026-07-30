#include<linux/module.h> 
#include<linux/init.h> 
#include<linux/kernel.h> 

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Temur Eshboyev");
MODULE_DESCRIPTION("It is question 2 from Part I");

static int __init question2_init(void) 
{
	printk(KERN_INFO "LOADING QUESTION2 MODULE....\n\n\n");
	printk(KERN_INFO "***************\n");
	printk(KERN_INFO "BELOW YOU CAN SEE THE ENTIRE 16 WEEK OPERATING SYSTEM COURSE SYLLABUS:\n\n");
	printk(KERN_INFO "I WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : Overview (Ch 1)\n");
	printk(KERN_INFO "Basic Operating System Concepts, Linux Versus Other Unix-Like Kernels, Hardware Dependency, Linux Versions, An Overview of the Unix Filesystem, An Overview of Unix Kernels\n");
	printk(KERN_INFO "Homework Assignment\n");
	printk(KERN_INFO "Understand the usage of linux commands such as ls, cp, mv, etc., and system calls such as read(), write(), etc. Practise a given list of basic linux commands and system calls\n\n");
	printk(KERN_INFO "II WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : Linux kernel (Ch 1, Appendix A)\n");
	printk(KERN_INFO "An Overview of Unix Kernels, System Startup – BIOS Bootstrapping procedure, Boot Loader, Booting Linux from Hard disk (LILO – LInux LOader), setup and startup functions, Shell Programming\n");
	printk(KERN_INFO "Homework Assignment\n");
	printk(KERN_INFO "- Installation of linux with kernel source.\n");
	printk(KERN_INFO "- Explain the kernel code structure.\n");
	printk(KERN_INFO "- Show the basic techniques to read through the linux kernel\n");
	printk(KERN_INFO " - Writing Shell Scripts\n\n");
	printk(KERN_INFO "III WEEK\n");
	printk(KERN_INFO "Lecture Topic : Memory Addressing (Ch 2)\n");
	printk(KERN_INFO "Memory Addresses- logical, linear, physical addresses, Segmentation in Hardware - Segmentation Registers, Segmentation Descriptors, Global Descriptor table (GDT), Local Descriptor Table(LDT), Segment selector, Segmentation in Linux, Paging in Hardware, Paging in Linux\n");
	printk(KERN_INFO "Home Assignment : Compiling linux (Linux kernel)\n");
	printk(KERN_INFO "- How to compile the Linux kernel source code.\n");
	printk(KERN_INFO "- How to make some modification and recompile the kernel.\n\n");
	printk(KERN_INFO "IV WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : Interrupt concept (Ch 4)\n");
	printk(KERN_INFO "Explain basic interrupt concept, Role of Interrupt Signals, Type of Interrupts, Types of Exceptions, Interrupt and Exception vectors, IRQs, Advanced Programmable interrupt controller(APIC), Multi-APIC System, Interrupt Descriptor Table(IDT), Hardware Handling of Interrupts and Exceptions\n");
	printk(KERN_INFO "Home Assignment\n");
	printk(KERN_INFO "Show a detailed example with keyboard interrupt. Explain kernel interrupt code for keyboard interrupt.\n\n");
	printk(KERN_INFO "V WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : Writing a sample Linux Kernel Module\n");
	printk(KERN_INFO "Utilities to Manipulate Kernel Module, Creating Makefile to compile kernel module, Inserting the sample kernel module, remove the sample kernel module\n");
	printk(KERN_INFO "Interrupt example: Keyboard interrupt (Linux kernel)\n");
	printk(KERN_INFO "Home Assignment\n");
	printk(KERN_INFO "Explain how to change kernel keyboard interrupt handling code to modify keyboard interrupt behavior in Linux.\n\n");
	printk(KERN_INFO "VI WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : Process: basic data structure (Ch 3)\n");
	printk(KERN_INFO "Explain basic concept of process and basic data structure to handle process.\n");
	printk(KERN_INFO "Explain what information the OS should keep in the process control block to manage processes.\n");
	printk(KERN_INFO "Home Assignment\n");
	printk(KERN_INFO "Find process related data structure in the kernel code.\n\n");
	printk(KERN_INFO "VII WEEK\n\n");
	printk(KERN_INFO "MID-TERM EXAM\n\n");
	printk(KERN_INFO "VIII WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : Process: system calls (Ch 3) & Socket Programming\n");
	printk(KERN_INFO "Explain the inner working of process related system calls: fork, exec, exit, wait.\n");
	printk(KERN_INFO "Inter-Process Communication (IPC) - Socket Programming\n");
	printk(KERN_INFO "Home Assignment\n");
	printk(KERN_INFO "- Write example code that uses the system calls fork, exec, exit, wait.\n");
	printk(KERN_INFO "- Read kernel code related to process.\n");
	printk(KERN_INFO "- Socket Programming demonstrating Inter Process Communication\n\n");
	printk(KERN_INFO "IX WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : Inter Process communication- IPC (Ch19)\n");
	printk(KERN_INFO "Basic Mechanisms to allow interprocess communication - Pipes and FIFOs (named pipes), Semaphores, Messages, Shared memory regions, Sockets\n");
	printk(KERN_INFO "System V IPC Resources- IPC Semaphores, IPC Messages, IPC Shared Memory, POSIX Message Queues\n\n");
	printk(KERN_INFO "X WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : File: on-disk file system (Ch 18)\n");
	printk(KERN_INFO "Linux Disk File system based on Inode Structure – Extended File System(Ext), General Characteristics of Extended File System Ex2, Ex3, Data Structures, Ext File System, File Types, directory.\n");
	printk(KERN_INFO "Reading Assignment\n");
	printk(KERN_INFO "- Read kernel code for disk file systems\n\n");
	printk(KERN_INFO "XI WEEK");
	printk(KERN_INFO "Lecture Topic : File: on-disk file system (Ch 18)\n");
	printk(KERN_INFO "Ext Memory Data Structure, Creating Ext File System, Data Blocks Addressing, Journaling File Systems.\n");
	printk(KERN_INFO "Reading Assignment\n");
	printk(KERN_INFO "- Read kernel code for disk file systems\n\n");
	printk(KERN_INFO "XII WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : File: on-memory file system & File system calls (Ch 12, Ch 16)\n");
	printk(KERN_INFO "Virtual File System(VFS), Common File Model, System Calls handled by the VFS, VFS Data Structures, Superblock operations, Inode Objects, Inode operations, File Objects, File Operations, dentry Objects, Files associated with a process, Special File Systems, Mounting and Unmounting a file system, Implementation of VFS System Calls, File Locking- File handling system calls\n");
	printk(KERN_INFO "Reading Assignment\n");
	printk(KERN_INFO "- Read the kernel code and find the related code in the kernel that handles the above tasks including file handling system calls\n\n");
	printk(KERN_INFO "XIII WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : Memory: paging (Ch 8)\n");
	printk(KERN_INFO "Memory Management – Page Frame Management, Page Descriptors, Non-Uniform Memory access, Memory zones, Zoned Page Frame Allocator, Buddy System Algorithm, Zone Allocator, Memory Area Management, Slab Allocator, Non-Contiguous Memory Area Management.\n");
	printk(KERN_INFO "XIV WEEK\n\n");
	printk(KERN_INFO "Lecture Topic : Memory: paging data structure, page fault (Ch 9) and System Calls & Signals (Ch 10 & 11)\n");
	printk(KERN_INFO "Process address Space, Memory Descriptor, Memory regions, Memory Region Data Structures, Memory Region Handling page fault exception, and the related kernel code to handle paging and page fault.\n");
	printk(KERN_INFO "POSIX API vs System Calls, System Call handler and Service Routines, Entering and Exiting a System Call, parameter Passing\n");
	printk(KERN_INFO "Compare signal vs interrupt. Explain various kinds of signal. Actions Performed upon Delivering a Signal, Catching a Signal, System Calls Related to Signal Handling, Related data structure and kernel code to handle signal.\n\n");
	printk(KERN_INFO "XV WEEK\n\n");
	printk(KERN_INFO "FINAL EXAM\n\n");
	printk(KERN_INFO "XVI WEEK\n\n");
	printk(KERN_INFO "- Term Project Presentation & Demo\n");
	printk(KERN_INFO "- Term Project Report Submission\n");
	printk(KERN_INFO "***************\n");
	return 0; 
}

static void __exit question2_cleanup(void) 
{
	printk(KERN_INFO "*********************\n");
	printk(KERN_INFO "BELOW YOU CAN SEE THE ENTIRE TERM PROJECT GUIDELINES:\n\n");
	printk(KERN_INFO "Term Project involves the following main tasks :\n");
	printk(KERN_INFO "Selection of a particular IPC related problem\n");
	printk(KERN_INFO "Project Design & Implementation/Simulation\n");
	printk(KERN_INFO "Preparation of the Project Report\n");
	printk(KERN_INFO "Presentation of the Project work\n\n");
	printk(KERN_INFO "Each Project Team can consist of 4 to 8 members (or more depending on the size of the section) with a maximum of 10 project teams in a section.\n\n");
	printk(KERN_INFO "Project Teams are given time till 3rd week of the semester to select a IPC (Inter-Process Communication) related to real- time problem pertaining to society /social networking (sectors include Banking, Airline/Railways/Bus Transports, Education/University, Hotel/Restaurant, HealthCare, COVID- 19 Contact tracing/Management, Online Education, Traffic Control/Management, Digital Money Transfer/ Digital Asset Management, Social media or any other domain of interest) and carry out the Project work in a team.\n\n");
	printk(KERN_INFO "Each project team is required to develop the software that model the business process according to the System Request. It must be implemented using client – server architecture, all inter process communications should be organized using the popular IPC mechanism - Sockets.\n\n");
	printk(KERN_INFO "The title of the selected Term Project along with abstract, Brief project description, Requirements definition document in the form of a Project Preliminary Document also known as Project Proposal must be submitted by the end of 6th week of the semester.\n\n");
	printk(KERN_INFO "No two Teams can have the same Project. The problem selected must belong to different areas.\n\n");
	printk(KERN_INFO "Project Presentation will be held in the 16th week of the semester (18th to 22nd December 2023)\n\n");
	printk(KERN_INFO "Maximum duration of the presentation will be 45 minutes followed by 15 minutes for question/answer session for each Project team. All members of the team must present a part of the Project carried-out in rotation. The time- division for presentation among the members must be done judiciously so that complete Project work carried out is presented in a Perfect way without missing any detail and after that a live Demo of the Project developed will be given – Demo duration : 30 minutes.\n\n");
	printk(KERN_INFO "The Final Project Report must include the following Sections : Abstract, Introduction, Project Overview, Requirements definition section including Use case diagram, Activity diagrams, Class diagrams, Behavioral diagram, Project Design & Implementation, Simulation Results & Discussions, Conclusion, Future Work, References.\n\n");
	printk(KERN_INFO "The Project Report must be submitted atleast one day before the Presentation or on the day of Presentation before the Presentation.\n\n");
	printk(KERN_INFO "Project Deliverables : Project Report(Soft Copy) with Simulation Results, Source Code developed, Presentation PPTs\n\n");
	printk(KERN_INFO "*********************\n");
	printk(KERN_INFO "\n\n\nCLEANING UP QUESTION2 MODULE....\n");
}

module_init(question2_init);
module_exit(question2_cleanup);

