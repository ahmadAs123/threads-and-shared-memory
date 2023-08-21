threads and shared memory polinoms
‏Authored by Ahmad Abu Sbeih
322786757

‏==Description==
‏The program is loop , this programm read a polinom from the user and a value  and then check if this polinom is a legal and then make number of threads according to how many x's is in the polinom and every thread Calculates x with the value and then the main will sum evrey value that the threeads Calculates and print it on the screen  ,the second proggram do the same thing but insted of save in argument we saved in shared meomry that we make it in the first of the loop and we use fork instead of threads and every fork we make forks according to the nmber of the x's in the polinom  (son) calculate a x with the value 

Program DATABASE
evey polinom we write it into the programm , will be checked if is illegal polinom also check if the user writw done then we finish the programm ,the progrram will calculate the polinom according t the value and then print the result on the screen 
‏Functions
‏ functions in the two  programms  are  the main function and f and function1  and  function2 and only_num and check_spaces , the f its a function that  calcualte the polinom with the value that the user write ,  the function and  function1  and  function2  all of them only call the function f and add the result into total ,total1,total2 , the only_num is function that put in total3 the number that the user write in case that there is no x's in the polinom only number    

‏==Program Files==
‏ex4a.c: this file  contains the main programm and all the functions.
‏ex4b.c: this file  contains the main programm and all the functions.

‏==How to compile?==
 
for ex4a.c :     ‏compile: gcc ex4a.c -o ex4a -lpthread
‏run: ./ex4a

for ex4b.c  :  ‏compile: gcc ex4b.c -o ex4b
‏run: ./ex4b

‏==Input==
‏a legal polinom and value or the word (done)

‏==Output:== 

‏int ( the result of the polinom )

string(if we put illegal polinom  there will be a message that tell us that this polinom is not true )
