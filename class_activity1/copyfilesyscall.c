#include <fcntl.h>      // for open()
#include <unistd.h>     // for read(), write(), close()
#include <stdio.h>      // for perror()
#include <stdlib.h>     // for exit()

int main() {
    int source, dest;
    char buffer[1024];
    ssize_t bytesRead;

    // Open source file (result.txt) for reading
    source = open("result.txt", O_RDONLY);
    if (source < 0) {
        perror("Error opening result.txt");
        exit(1);
    }

    // Open destination file (copyresult.txt) for writing (create if not exist)
    dest = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Error opening/creating copyresult.txt");
        close(source);
        exit(1);
    }

    // Copy content
    while ((bytesRead = read(source, buffer, sizeof(buffer))) > 0) {
        if (write(dest, buffer, bytesRead) != bytesRead) {
            perror("Error writing to copyresult.txt");
            close(source);
            close(dest);
            exit(1);
        }
    }

    if (bytesRead < 0) {
        perror("Error reading result.txt");
    }

    close(source);
    close(dest);

    return 0;
}

