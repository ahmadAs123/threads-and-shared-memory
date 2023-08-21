#include <stdio.h>
//322786757
#include <string.h>

#include <stdlib.h>

#include <sys/types.h>

#include <sys/ipc.h>

#include <sys/shm.h>

#include <unistd.h>

#include <sys/wait.h>

int * mem;
int sh_id;
int ror = 0;
int count_pluse;
int j;
int ind;
char last_num[512];
int total = 0;
char str[512];
char str1[512];
char x1[512];
char x2[512];
char x3[512];
char str2[512];
int result;
int res;
int spaces_count = 0;
int counter;
int number;
int val;
int n;
int fl;

int check_spaces(char str[]) {
    while (str[ror] != '\0') { // check if there is spaces befor or after , and + and * and ,also i write the code that check if the polinom have spaces ,only one space after the (,) according to the question
        if (str[ror] == '+' || str[ror] == '*' || str[ror] == '^') {
            if (str[ror + 1] == ' ' || str[ror + 1] == '\n' || str[ror + 1] == '\0' || str[ror - 1] == ' ' || str[ror + 1] == ',') {
                shmdt(mem);
                shmctl(sh_id, IPC_RMID, NULL);
                return spaces_count + 1;
            }
        }
        if (str[ror] == ',') {
            if (str[ror - 1] == ' ')
                return spaces_count + 1;
            if (str[ror + 1] != ' ')
                return spaces_count + 1;
            if (str[ror + 2] == ' ')
                return spaces_count + 1;
        }
        ror++;
    }
    return spaces_count;
}
int f(char a[], char b[]) { // function that Doing the arithmetic and substitute the value of the x into the equation
    result = 0;
    res = 0;
    counter = 0;
    number = 0;
    val = 0;

    n = 0;
    int z;

    if (strlen(a) == 1 && a[0] == 'x') { //if the poilinom was only x then return the value
        result = atoi(b);
        return result;
    }

    for (z = 0; z < strlen(a); z++) {
        if (a[z] == '*') { // if us there arithmetic multiplication operation
            number = a[z - 1] - '0';
            z += 2;
            //     int l = z;
            while (z < strlen(a)) { //   if there also with the * a  power in the polinom
                if (a[z] == '^') {
                    counter++;
                    n = a[z + 1] - '0';
                    val = atoi(b);
                    res = val;
                    n = n - 1;
                    while (n > 0) {
                        res *= val;
                        n--;
                    }
                    number *= res;
                    result = number;

                }
                z++;
            }
            if (counter == 0) { // if there is only * operation without ^
                fl = atoi(b);
                number *= fl;
                result = number;
            }

        }

    }
    if (a[1] == '^') { // check if there only ^ operation
        n = a[2] - '0';
        val = atoi(b);
        res = val;
        n = n - 1;
        while (n > 0) {
            res *= val;
            n--;
        }

        result = res;

    }
    return result;
}

int main() {

    while (1) {

        key_t key1;

        if ((key1 = ftok("/tmp", 'f')) == -1) // make key for the chared memory
        {
            perror("ftok was failed while we tried to creat !");
            exit(EXIT_FAILURE);
        }

        sh_id = shmget(key1, 2000, IPC_CREAT | IPC_EXCL | 0600); //creating
        if (sh_id == -1) {
            perror("shmget was failed !");
            exit(EXIT_FAILURE);
        }

        mem = (int * ) shmat(sh_id, NULL, 0); // pointer that point on the space of shared memory that named mem
        if (mem == (int * ) - 1) {
            perror("shmat was failed!!!");
            exit(EXIT_FAILURE);
        }

        int i = 0;
        int y;
        int k;
        int count = 0;
        int count1 = 0;
        count_pluse = 0;
        i = 0;
        printf("enter  polinom with number :\n");
        fgets(str, 512, stdin); //
        str[strlen(str) - 1] = '\0';

        if (strcmp(str, "done") == 0) { // check if the input was done then finish the programm

            count_pluse = 0;
            count1 = 0;
            count = 0;
            total = 0;
            shmdt(mem);
            shmctl(sh_id, IPC_RMID, NULL);
            break;

        } else if (check_spaces(str) == 1) { // check if there spaces in the polinom
            printf("please enter right polinom!!, try again\n");
            shmdt(mem);
            shmctl(sh_id, IPC_RMID, NULL);
        } else {

            while (str[i] != ',') {

                i++;
            }

            strncpy(str1, & str[0], i); // put the polinom in an array called str1
            str1[i] = '\0';
            i++;
            strncpy(str2, & str[i], strlen(str) - i); // put the value that we will put in the polinom in array called str2
            str2[strlen(str) - i] = '\0';
            i = 0;

            while (str[i] != '\0') { // count the x in the polinom to make threads after that
                if (str[i] == 'x')
                    count++;
                i++;
            }

            i = 0;
            while (str[i] != '\0') { // count how many + operation in the polinom
                if (str[i] == '+')
                    count_pluse++;
                i++;
            }

            if (count == 0) { // there is only number then print it
                pid_t c1;
                c1 = fork();
                if (c1 < 0) {
                    perror("fork  was failed!!!");
                    exit(EXIT_FAILURE);
                }

                if (c1 == 0) { //son proggres is beggining
                    mem[0] = atoi(str1);
                    shmdt(mem);
                    exit(0);
                }
                wait(NULL);
                total += mem[0];
                printf("the total is %d\n", total);
                shmdt(mem);
                shmctl(sh_id, IPC_RMID, NULL);
            } else if (count == 1) { // there is only one x in the polinom
                j = 0;
                if (count_pluse == 1) { // ther is x withou + number like x
                    while (str[j] != '+') {
                        count1++;
                        j++;
                    }
                    strncpy(x1, & str[0], count1);
                    x1[count1] = '\0';
                    ind = j + 1;
                    count1 = 0;
                    j++;
                    while (str[j] != ',') {
                        count1++;
                        j++;
                    }
                    strncpy(last_num, & str[ind], count1);
                    last_num[count1] = '\0';
                } else { // there is number like x+3
                    int j = 0;
                    while (str[j] != ',') {
                        count1++;
                        j++;
                    }
                    strncpy(x1, & str[0], count1);
                    x1[count1] = '\0';
                }

                pid_t c1;
                c1 = fork();
                if (c1 < 0) {
                    perror("fork  was failed!!!");
                    exit(EXIT_FAILURE);
                }

                if (c1 == 0) { //son proggres is beggining
                    mem[0] = f(x1, str2);
                    shmdt(mem);
                    exit(0);
                }
                wait(NULL);
                total += mem[0];
                if (count_pluse == 1)
                    total += atoi(last_num);
                printf("the total is %d\n", total);
                shmdt(mem);
                shmctl(sh_id, IPC_RMID, NULL);
            } else if (count == 2) { // there is 2 x in the polinom
                j = 0;
                if (count_pluse == 2) {
                    while (str[j] != '+') {
                        count1++;
                        j++;
                    }
                    strncpy(x1, & str[0], count1);
                    x1[count1] = '\0';
                    j++;
                    count1 = 0;
                    y = j;
                    while (str[j] != '+') {

                        count1++;
                        j++;
                    }
                    strncpy(x2, & str[y], count1);
                    x2[count1] = '\0';

                    ind = j + 1;
                    count1 = 0;
                    j++;
                    while (str[j] != ',') {
                        count1++;
                        j++;
                    }
                    strncpy(last_num, & str[ind], count1);
                    last_num[count1] = '\0';
                } else {
                    j = 0;
                    while (str[j] != '+') {
                        count1++;
                        j++;
                    }
                    strncpy(x1, & str[0], count1);
                    x1[count1] = '\0';
                    j++;
                    count1 = 0;
                    int y = j;
                    while (str[j] != ',') {

                        count1++;
                        j++;
                    }
                    strncpy(x2, & str[y], count1);
                    x2[count1] = '\0';

                }

                pid_t c1, c2; // making forks to do the math
                c1 = fork();
                if (c1 < 0) {
                    perror("fork  was failed!!!");
                    exit(EXIT_FAILURE);
                }
                if (c1 == 0) { //son proggres is beggining
                    mem[0] = f(x1, str2);
                    shmdt(mem);
                    exit(0);
                }
                c2 = fork();
                if (c2 < 0) {
                    perror("fork  was failed!!!");
                    exit(EXIT_FAILURE);
                }
                if (c2 == 0) { //son proggres is beggining
                    mem[1] = f(x2, str2);
                    shmdt(mem);
                    exit(0);
                }
                waitpid(c1, NULL, 0);
                waitpid(c2, NULL, 0);
                total += mem[0]; // add what in the shared memory into total regester
                total += mem[1];
                if (count_pluse == 2)
                    total += atoi(last_num);
                printf("the total is %d\n", total);
                shmdt(mem);
                shmctl(sh_id, IPC_RMID, NULL);
            } else {
                if (count_pluse == 3) { // there is number in the polinom like x^2+x^3+x+1
                    j = 0;
                    while (str[j] != '+') {
                        count1++;
                        j++;
                    }
                    strncpy(x1, & str[0], count1);
                    x1[count1] = '\0';
                    j++;
                    count1 = 0;
                    int y = j;
                    while (str[j] != '+') {
                        count1++;
                        j++;
                    }
                    strncpy(x2, & str[y], count1);
                    x2[count1] = '\0';
                    j++;
                    count1 = 0;
                    k = j;
                    while (str[j] != '+') {
                        count1++;
                        j++;
                    }
                    strncpy(x3, & str[k], count1);
                    x3[count1] = '\0';
                    int ind = j + 1; //make sure that we save the number in array named last_num to add it to total after that
                    count1 = 0;
                    j++;
                    while (str[j] != ',') {
                        count1++;
                        j++;
                    }
                    strncpy(last_num, & str[ind], count1);
                    last_num[count1] = '\0';
                } else { // there is no number only polinom with x's
                    j = 0;
                    while (str[j] != '+') {
                        count1++;
                        j++;
                    }
                    strncpy(x1, & str[0], count1);
                    x1[count1] = '\0';
                    j++;
                    count1 = 0;
                    int y = j;
                    while (str[j] != '+') {
                        count1++;
                        j++;
                    }
                    strncpy(x2, & str[y], count1);
                    x2[count1] = '\0';
                    j++;
                    count1 = 0;
                    int k = j;
                    while (str[j] != ',') {
                        count1++;
                        j++;
                    }
                    strncpy(x3, & str[k], count1);
                    x3[count1] = '\0';

                }

                pid_t c1, c2, c3;
                c1 = fork(); // making 3 forks each fork do specific x that in x1,x2,x3 arrays
                if (c1 < 0) {
                    perror("fork  was failed!!!");
                    exit(EXIT_FAILURE);
                }
                if (c1 == 0) {
                    mem[0] = f(x1, str2);
                    shmdt(mem);
                    exit(0);
                }

                c2 = fork();
                if (c2 < 0) {
                    perror("fork  was failed!!!");
                    exit(EXIT_FAILURE);
                }
                if (c2 == 0) { //son proggres is beggining
                    mem[1] = f(x2, str2);
                    shmdt(mem);
                    exit(0);
                }
                c3 = fork();
                if (c3 < 0) {
                    perror("fork  was failed!!!");
                    exit(EXIT_FAILURE);
                }
                if (c3 == 0) { //son proggres is beggining
                    mem[2] = f(x3, str2);
                    shmdt(mem);
                    exit(0);
                }
                waitpid(c1, NULL, 0);
                waitpid(c2, NULL, 0);
                waitpid(c3, NULL, 0);
                total += mem[0];
                total += mem[1];
                total += mem[2];
                if (count_pluse == 3) //add the number that we saved in array called last_num
                    total += atoi(last_num);
                printf("the total is %d\n", total);
                shmdt(mem); //remove the pointer
                shmctl(sh_id, IPC_RMID, NULL);
            }

        }
        shmdt(mem); //remove the pointer
        shmctl(sh_id, IPC_RMID, NULL);
        count_pluse = 0;
        count1 = 0;
        count = 0;
        total = 0;
        ror = 0;
    }

}