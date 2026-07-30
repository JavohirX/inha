readme for link time interpositioning
gcc -Wall -DLINKTIME -c mymalloc_link.c
gcc -Wall -c main.c
gcc -Wall -Wl,--wrap=malloc -Wl,--wrap=free -o main main.o mymalloc_link.o
./main