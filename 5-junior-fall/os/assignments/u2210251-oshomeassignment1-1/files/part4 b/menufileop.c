#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILENAME 256
#define MAX_BUFFER 1024

int create_file();
int open_file();
void read_file(int fd);
void write_file(int fd);
void seek_file(int fd);
void delete_file();
void rename_file();
void copy_file();

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice;
    int fd = -1;

    while (1) {
        printf("\nFile Operations Menu:\n");
        printf("1. Create a new file\n");
        printf("2. Open an existing file\n");
        printf("3. Read from file\n");
        printf("4. Write to file\n");
        printf("5. Seek file\n");
        printf("6. Delete file\n");
        printf("7. Rename file\n");
        printf("8. Copy file\n");
        printf("9. Quit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                fd = create_file();
                break;
            case 2:
                fd = open_file();
                break;
            case 3:
                if (fd != -1) read_file(fd);
                else printf("No file is currently open.\n");
                break;
            case 4:
                if (fd != -1) write_file(fd);
                else printf("No file is currently open.\n");
                break;
            case 5:
                if (fd != -1) seek_file(fd);
                else printf("No file is currently open.\n");
                break;
            case 6:
                delete_file();
                break;
            case 7:
                rename_file();
                break;
            case 8:
                copy_file();
                break;
            case 9:
                if (fd != -1) close(fd);
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

int create_file() {
    char filename[MAX_FILENAME];
    printf("Enter filename to create: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline

    int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("Error creating file");
        return -1;
    }

    printf("File created successfully.\n");
    return fd;
}

int open_file() {
    char filename[MAX_FILENAME];
    int mode;
    printf("Enter filename to open: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline

    printf("Enter mode (1: Read only, 2: Write only with Append, 3: Read & Write with Append): ");
    scanf("%d", &mode);
    getchar(); // Consume newline

    int flags;
    switch (mode) {
        case 1:
            flags = O_RDONLY;
            break;
        case 2:
            flags = O_WRONLY | O_APPEND;
            break;
        case 3:
            flags = O_RDWR | O_APPEND;
            break;
        default:
            printf("Invalid mode.\n");
            return -1;
    }

    int fd = open(filename, flags);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    printf("File opened successfully.\n");
    return fd;
}

void read_file(int fd) {
    char buffer[MAX_BUFFER];
    ssize_t bytes_read;
    int num_bytes;

    printf("Enter number of bytes to read : ");
    scanf("%d", &num_bytes);
    getchar(); // Consume newline

    if (num_bytes == 0) {
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
    } else {
        bytes_read = read(fd, buffer, num_bytes);
        if (bytes_read > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
    }

    if (bytes_read == -1) {
        perror("Error reading file");
    }
}

void write_file(int fd) {
    char buffer[MAX_BUFFER];
    ssize_t bytes_written;

    printf("Enter text to write (press Ctrl+D on a new line when finished):\n");

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        bytes_written = write(fd, buffer, strlen(buffer));
        if (bytes_written == -1) {
            perror("Error writing to file");
            return;
        }
    }

    if (feof(stdin)) {
        clearerr(stdin);  // Clear EOF condition
        printf("Text written to file successfully.\n");
    } else {
        perror("Error reading input");
    }
}

void seek_file(int fd) {
    int origin, offset;
    char option;

    printf("Enter origin (0: beginning, 1: current, 2: end): ");
    scanf("%d", &origin);
    printf("Enter offset: ");
    scanf("%d", &offset);
    getchar(); // Consume newline

    if (lseek(fd, offset, origin) == -1) {
        perror("Error seeking file");
        return;
    }

    printf("Seek successful. Do you want to read (r) or write (w)? ");
    scanf("%c", &option);
    getchar(); // Consume newline

    if (option == 'r') {
        read_file(fd);
    } else if (option == 'w') {
        write_file(fd);
        
        // After writing, display the entire file contents from the beginning
        printf("\nDisplaying entire file contents:\n");
        if (lseek(fd, 0, SEEK_SET) == -1) {
            perror("Error seeking to beginning of file");
            return;
        }
        
        char buffer[MAX_BUFFER];
        ssize_t bytes_read;
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        
        if (bytes_read == -1) {
            perror("Error reading file");
        }
        
    } else {
        printf("Invalid option.\n");
    }
}

void delete_file() {
    char filename[MAX_FILENAME];
    char confirm;

    printf("Enter filename to delete: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline

    printf("Are you sure you want to delete %s? (y/n): ", filename);
    scanf("%c", &confirm);
    getchar(); // Consume newline

    if (confirm == 'y' || confirm == 'Y') {
        if (unlink(filename) == -1) {
            perror("Error deleting file");
        } else {
            printf("File deleted successfully.\n");
        }
    } else {
        printf("File deletion cancelled.\n");
    }
}

void rename_file() {
    char old_name[MAX_FILENAME], new_name[MAX_FILENAME];

    printf("Enter old filename: ");
    fgets(old_name, sizeof(old_name), stdin);
    old_name[strcspn(old_name, "\n")] = 0; // Remove newline

    printf("Enter new filename: ");
    fgets(new_name, sizeof(new_name), stdin);
    new_name[strcspn(new_name, "\n")] = 0; // Remove newline

    if (rename(old_name, new_name) == -1) {
        perror("Error renaming file");
    } else {
        printf("File renamed successfully.\n");
    }
}

void copy_file() {
    char src_name[MAX_FILENAME], dest_name[MAX_FILENAME];
    char buffer[MAX_BUFFER];
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written;

    printf("Enter source filename: ");
    fgets(src_name, sizeof(src_name), stdin);
    src_name[strcspn(src_name, "\n")] = 0; // Remove newline

    printf("Enter destination filename: ");
    fgets(dest_name, sizeof(dest_name), stdin);
    dest_name[strcspn(dest_name, "\n")] = 0; // Remove newline

    src_fd = open(src_name, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return;
    }

    dest_fd = open(dest_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (dest_fd == -1) {
        perror("Error creating destination file");
        close(src_fd);
        return;
    }

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            return;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading from source file");
    } else {
        printf("File copied successfully.\n");
    }

    close(src_fd);
    close(dest_fd);
}
