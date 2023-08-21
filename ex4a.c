#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <pthread.h>
 //322786757
int count_pluse;
int j;
int total1 = 0;
int total2 = 0;
int total3 = 0;
int ind;
pthread_t th1, th2, th3;
pthread_t thread1;
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
int counter;
int number;
int val;
int n;
int spaces_count = 0;
int ror = 0;
int fl;
void * function (void * );
void * function1(void * );
void * function2(void * );
void * only_num(void * );

int check_spaces(char str[]) {
  while (str[ror] != '\0') { // check if there is spaces befor or after , and + and * , also I wrote the code  that make sure if the polinom dosent have also spaces only one space after the (,) must be according to the question
    if (str[ror] == '+' || str[ror] == '*' || str[ror] == '^') {
      if (str[ror + 1] == ' ' || str[ror + 1] == '\n' || str[ror + 1] == '\0' || str[ror - 1] == ' ' || str[ror + 1] == ',') {
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

    int i = 0;
    int y;
    int k;
    int count = 0;
    int count1 = 0;
    count_pluse = 0;
    i = 0;
    fflush(stdin);
    printf(" enter  polinom with number :\n");
    fgets(str, 512, stdin); //
    str[strlen(str) - 1] = '\0';

    if (strcmp(str, "done") == 0) { // check if the input was done then finish the programm

      count_pluse = 0;
      count1 = 0;
      count = 0;
      total = 0;
      break;

    } else if (check_spaces(str) == 1) { // check if there spaces in polinom
      printf("please enter right polinom!!, try again\n");
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
      //  printf("%d\n",count);

      i = 0;
      while (str[i] != '\0') { // count how many + operation in the polinom
        if (str[i] == '+')
          count_pluse++;
        i++;
      }

      if (count == 0) { // there is only number then print it
        pthread_t th1;
        int status;
        status = pthread_create( & th1, NULL, only_num, NULL);
        if (status != 0) {
          fputs(" create  was failed!!", stderr);
          exit(EXIT_FAILURE);
        }

        pthread_join(th1, NULL);
        printf("the result is %d\n", total3);
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

        int status;
        status = pthread_create( & thread1, NULL, function, NULL);
        if (status != 0) {
          fputs(" create was failed!!", stderr);
          exit(EXIT_FAILURE);
        }

        pthread_join(thread1, NULL);

        if (count_pluse == 1)
          total += atoi(last_num);
        printf("the result is %d\n", total);

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

        int status, status1;
        status = pthread_create( & th1, NULL, function, NULL);
        if (status != 0) {
          fputs(" create was failed!!", stderr);
          exit(EXIT_FAILURE);
        }
        status1 = pthread_create( & th2, NULL, function1, NULL);
        if (status1 != 0) {
          fputs(" create was failed!!", stderr);
          exit(EXIT_FAILURE);
        }

        pthread_join(th1, NULL);
        pthread_join(th2, NULL);
        total += total1;
        if (count_pluse == 2)
          total += atoi(last_num);
        printf("the result is %d\n", total);

      } else {
        if (count_pluse == 3) {
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

          int ind = j + 1;
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

        int status, status1, status2;
        status = pthread_create( & th1, NULL, function, NULL);
        if (status != 0) {
          fputs(" create was failed!!", stderr);
          exit(EXIT_FAILURE);
        }
        status1 = pthread_create( & th2, NULL, function1, NULL);
        if (status1 != 0) {
          fputs(" create was failed!!", stderr);
          exit(EXIT_FAILURE);
        }
        status2 = pthread_create( & th3, NULL, function2, NULL);
        if (status2 != 0) {
          fputs(" create was failed!!", stderr);
          exit(EXIT_FAILURE);
        }

        pthread_join(th1, NULL);
        pthread_join(th2, NULL);
        pthread_join(th3, NULL);
        total += total1;
        total += total2;
        if (count_pluse == 3)
          total += atoi(last_num);
        printf("the result is %d\n", total);

      }

    }
    count_pluse = 0;
    count1 = 0;
    count = 0;
    ror = 0;
    total = 0;
    total1 = 0;
    total2 = 0;
    total3 = 0;
  }

}

void * function (void * a) {

  total += f(x1, str2);

  return NULL;
}
void * function1(void * a) {

  total1 += f(x2, str2);

  return NULL;
}
void * function2(void * a) {

  total2 += f(x3, str2);

  return NULL;
}
void * only_num(void * a) {

  total3 += strtol(str1, NULL, 10);
  return NULL;
}