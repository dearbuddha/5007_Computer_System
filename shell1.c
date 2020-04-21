#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define rmax 4
#define smax 80

// registers
int r[rmax];

int i;

// cmd input string
char cmd_input[smax];

// cmd portion of input (1st word)
char cmd[smax];

// argument portion of input (2nd word)
char arg[smax];
int iarg;                     // interger version of argument

// number words found in input
int wordsFound;

// display mode 
char display_mode[4] = "DEC"; // same as {'D','E','C','\0'}

bool done = false;


void printRegister(int reg) {
  // prints value of r[reg] in correct display mode
  printf("[%s] ", display_mode);
  printf("r[%d]: ", reg);
  
  if (strcmp(display_mode, "DEC") == 0) {
      printf("%d\n", r[reg]);
  } else if (strcmp(display_mode, "HEX") == 0) {
      printf("%#x\n",r[reg]);
  } else {
      printf("INVALID MODE\n");
  }
}


int readIntFromString(char* source){
  // reads value of integer from source string in correct display mode
  int intsFound;
  int result;

  if (strcmp(display_mode, "DEC") == 0) {
      intsFound = sscanf(source, "%d", &result);
      if (intsFound != 1) {
          printf("INVALID NUMBER - used 0 instead\n");
          result = 0;
      }
  } else if (strcmp(display_mode, "HEX") == 0) {
      intsFound = sscanf(source, "0x%x", &result);
      if (intsFound != 1) {
          printf("INVALID NUMBER - used 0 instead\n");
          result = 0;
      }
  } else {
    printf("INVALID MODE - used 0 instead\n");
    result = 0;
  }
  
  return(result);
}


void stringUpper(char string[]){
  // upper case the argument string
  int i = 0;

  while ((string[i] != '\0') && (i < smax)) {
    if (string[i] >= 'a' && string[i] <= 'z') {
      string[i] = string[i] - 32;
    }
    i++;
  }
}


void clearAllRegisters(){
  int i;
  for (i=0; i<rmax; i++) {
    r[i] = 0;
  }
}


// ============= MAIN PROGRAM ==============

int main () {
    // initialize registers to 0
    clearAllRegisters();

    printf("\nWelcome to the command shell.\n");

    while (!done) {
        // GET INPUT
        // show current status and value of r[0]

        printRegister(0);

        //prompt for input and read input string
        printf("> ");
        fgets(cmd_input, smax, stdin);

        // break the input string into cmd arg and junk
        wordsFound = sscanf(cmd_input, "%s %s %*s", cmd, arg);

        // uppercase cmd to standard format
        stringUpper(cmd);

        // handle error inputs
        if (wordsFound <= 0) {
            // no command found, substitute NOP
            strcpy(cmd, "NOP");
        } else if (wordsFound <= 1) {
            // no argument found, substute empty string
            strcpy(arg, "");
        }

        // PROCESS INPUT
        if ((strcmp(cmd, "EXIT") == 0) || (strcmp(cmd, "QUIT") == 0)) {
            // exit from shell
            printf("EXIT encountered.\n");
            done = true;

        } else if (strcmp(cmd, "NOP") == 0) {
            // do nothing
            printf("NOP\n");

        } else if (strcmp(cmd, "LOADI") == 0) {
            // load (immediate) arg into r[0]
            // convert arg to integer - make sure it is valid

            iarg = readIntFromString(arg);

            // push the other registers up
            for (i = rmax - 1; i > 0; i--) {
                r[i] = r[i - 1];
            }

            // load arg into r[0]
            r[0] = iarg;

        } else if (strcmp(cmd, "PRTRS") == 0) {
            // print out the value of all the registers

            printf("--------------------\n");

            for (i = rmax - 1; i >= 0; i--) {
                printRegister(i);
            }

            printf("--------------------\n");

        } else if (strcmp(cmd, "ECHO") == 0) {
            // echo arg
            printf("%s\n", arg);

        } else if (strcmp(cmd, "CLRRS") == 0) {
            // clear all registers
            clearAllRegisters();

        } else if (strcmp(cmd, "ADD") == 0) {
            // adds r[0]+r[1], puts answer into r[0]
            // moves 0->r[3]
            // moves r[3]->r[2]
            // moves r[2]->r[1]

            r[0] = r[0] + r[1];

            for (i = 1; i <= rmax - 2; i++) {
                r[i] = r[i + 1];
            }

            r[rmax - 1] = 0;


        } else if (strcmp(cmd, "SUB") == 0) {
            // subtracts r[1]-r[0], puts answer into r[0]
            // moves r[2]->r[1]
            // moves r[3]->r[2]
            // moves 0->r[3]

            r[0] = r[1] - r[0];
            r[1] = r[2];
            r[2] = r[3];
            r[3] = 0;

        } else if (strcmp(cmd, "MUL") == 0) {
            // multiplies r[1]*r[0], puts answer into r[0]
            // moves r[2]->r[1]
            // moves r[3]->r[2]
            // moves 0->r[3]

            r[0] = r[1] * r[0];
            r[1] = r[2];
            r[2] = r[3];
            r[3] = 0;

        } else if (strcmp(cmd, "HELP") == 0) {
            // list all commands
            printf("Commands:\n");
            printf("NOP: no effect\n");
            printf("EXIT (or QUIT): terminate program\n");
            printf("LOADI arg: load integer 'arg' into register 0, scroll registers up\n");
            printf("PRTRS: print content of all registers\n");
            printf("ECHO arg: print content of first word of arg\n");
            printf("CLRRS: clear all registers\n");
            printf("ADD: add contents of register r0 to r1 store into r0, scroll registers down\n");
            printf("HELP: list valid commands\n");


        } else if (strcmp(cmd, "MODE") == 0) {
            stringUpper(arg);
            if (strcmp(arg, "DEC") == 0) {
                strcpy(display_mode, "DEC");
            } else if (strcmp(arg, "HEX") == 0) {
                strcpy(display_mode, "HEX");
            } else {
                printf(">> Unknown Display Mode |%s|\n", arg);
            }
        }else {
            // Error on Input
            printf(">> Unknown Command |%s|%s|\n", cmd, arg);
        }
    }
    printf("\nEnd Program.\n\n");
    return (0);
}
