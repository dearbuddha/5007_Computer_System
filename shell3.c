#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define rmax 4
#define smax 80
#define MMAX 16

// registers
int r[rmax];

int i;

// memory
int m[MMAX];

// cmd input string
char cmd_input[smax];

// cmd portion of input (1st word)
char cmd[smax];

// argument portion of input (2nd word)
char arg[smax];
int iarg;                     // integer version of argument

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

void printMemoryLocations(int memo) {
    // prints value of m[memo] in correct display mode
    printf("[%s] ", display_mode);

    if (strcmp(display_mode, "DEC") == 0) {
        printf("m[%d]: ", memo);
        printf("%d\n", m[memo]);
    } else if (strcmp(display_mode, "HEX") == 0) {
        printf("m[0x%x]: ", memo);
        printf("0x%x\n", m[memo]);
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
    i = 0;

    while ((string[i] != '\0') && (i < smax)) {
    if (string[i] >= 'a' && string[i] <= 'z') {
      string[i] = string[i] - 32;
    }
    i++;
    }
}


void clearAllRegisters(){
    for (i=0; i<rmax; i++) {
    r[i] = 0;
    }
}

void clearAllMemoryLocations(){
    for (i=0; i<MMAX; i++){
        m[i] = 0;
    }
}


// ============= MAIN PROGRAM ==============

int main () {
    // initialize registers to 0
    clearAllRegisters();

    //initialize memories to 0
    clearAllMemoryLocations();

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
            // no argument found, substitute empty string
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

        } else if (strcmp(cmd, "DIV") == 0) {
            // integer divides r[1]/r[0], puts answer into r[0]
            // moves r[2]->r[1]
            // moves r[3]->r[2]
            // moves 0->r[3]
            if(r[0] == 0){
                printf("Error: denominator is zero");
            } else{
                r[0] = r[1] / r[0];
                r[1] = r[2];
                r[2] = r[3];
                r[3] = 0;
            }

        } else if (strcmp(cmd, "REM") == 0) {
            // computes remainder of r[1]%r[0], puts answer into r[0]
            // moves r[2]->r[1]
            // moves r[3]->r[2]
            // moves 0->r[3]
            if(r[0] == 0){
                printf("Error: denominator is zero");
            } else{
                r[0] = r[1] % r[0];
                r[1] = r[2];
                r[2] = r[3];
                r[3] = 0;
            }

        } else if (strcmp(cmd, "INC") == 0) {
            // adds one to r[0], puts answer into r[0] - other registers are unchanged
            r[0] += 1;

        } else if (strcmp(cmd, "DEC") == 0) {
            // subtracts one from r[0], puts answer into r[0] - other registers are unchanged
            r[0] -= 1;

        } else if (strcmp(cmd, "NEG") == 0) {
            // multiplies r[0] by -1, puts answer into r[0] - other registers are unchanged
            r[0] = -r[0];

        } else if (strcmp(cmd, "HELP") == 0) {
            // list all commands
            printf("Commands:\n");
            printf("EXIT (or QUIT): terminate program\n");
            printf("NOP: no effect\n");
            printf("ECHO arg: print content of first word of arg\n");
            printf("MODE arg: change input/output display of numbers - either DEC or HEX\n");
            printf("HELP: list valid commands\n");
            printf("\n");
            printf("LOADI arg: load integer 'arg' into register 0, scroll registers up\n");
            printf("LOADM arg: load contents of memory location m[arg] into register 0, scroll registers up\n");
            printf("STORM arg: move contents of register 0 into memory location m[arg], scroll registers down\n");
            printf("CLRRS: clear all registers\n");
            printf("CLRMS: clear all memories\n");
            printf("\n");
            printf("ADD: add contents of register r0 to r1 store into r0, scroll registers down\n");
            printf("SUB: subtract contents of register r0 from r1 store into r0, scroll registers down\n");
            printf("MUL: multiply contents of register r0 by r1 store into r0, scroll registers down\n");
            printf("DIV: integer divide contents of register r1 by r0 store into r0, scroll registers down\n");
            printf("REM: integer remainder of register r1 dividd by r0 store into r0, scroll registers down\n");
            printf("\n");
            printf("PRTRS: print content of all registers\n");
            printf("PRTMS: print content of all memories\n");
            printf("\n");
            printf("INC: adds one to r[0], puts answer into r[0] - other registers are unchanged\n");
            printf("DEC: subtracts one from r[0], puts answer into r[0] - other registers are unchanged\n");
            printf("NEG: multiplies r[0] by -1, puts answer into r[0] - other registers are unchanged\n");
            printf("FSTOR fn: “fn” is the name of a file in the current working directory; Open file fn, write out values of registers and memory – one per line in decimal format, close fn\n");
            printf("FLOAD fn: “fn” is the name of a file in the current working directory; Open file fn, read in values of registers and memory – one per line in decimal format, close fn\n");




        } else if (strcmp(cmd, "MODE") == 0) {
            stringUpper(arg);
            if (strcmp(arg, "DEC") == 0) {
                strcpy(display_mode, "DEC");
            } else if (strcmp(arg, "HEX") == 0) {
                strcpy(display_mode, "HEX");
            } else {
                printf(">> Unknown Display Mode |%s|\n", arg);
            }
        } else if(strcmp(cmd, "CLRMS") == 0) {
            //clear all memory locations
            clearAllMemoryLocations();
        } else if (strcmp(cmd, "PRTMS") == 0) {
            // print out the value of all the memory locations
            printf("--------------------\n");
            for (i = MMAX - 1; i >= 0; i--) {
                printMemoryLocations(i);
            }
            printf("--------------------\n");
        } else if (strcmp(cmd, "LOADM") == 0) {
            // copy m[arg] to r[0], scroll other registers up (only valid for 0 <= arg <= 15)
            iarg = readIntFromString(arg);

            if ((0 <= iarg) && (iarg < MMAX)) {
                // push the other registers up
                for (i=rmax-1; i>0; i--) {
                    r[i] = r[i-1];
                }
                // load m[arg] into r[0]
                r[0] = m[iarg];

            } else {
                printf("Error: invalid memory location\n");
            }
        } else if (strcmp(cmd, "STORM") == 0) {
            // store r[0] into memory m[arg]
            // convert arg to integer - make sure it is valid
            iarg = readIntFromString(arg);
            if ((0 <= iarg) && (iarg < MMAX)) {
                // store r[0] into m[arg]
                m[iarg] = r[0];
                // scroll the other registers down
                for (i=0; i<=rmax-2; i++){
                    r[i] = r[i+1];
                }
                r[rmax-1] = 0;
            } else {
                printf("Error: invalid memory location\n");
            }
        } else if (strcmp(cmd, "FSTOR") == 0) {
            // Open file fn, write out values of registers and memory – one per line in decimal format, close fn
            FILE *fp;
            fp = fopen(arg, "w");
            if(fp == NULL){
                printf("Error: file opening error");
                exit(1);
            }
            for(i = 0; i < rmax; i++){
                fprintf(fp, "%d\n", r[i]);
            }
            for(i = 0; i < MMAX; i++){
                fprintf(fp, "%d\n", m[i]);
            }
            fclose(fp);

        } else if (strcmp(cmd, "FLOAD") == 0) {
            // Open file fn, read in values of registers and memory – one per line in decimal format, close fn
            int input;
            FILE *fp;

            fp = fopen(arg, "r");

            if(fp == NULL){
                printf("Error: file opening error\n");
                exit(1);
            }

            if(feof(fp) == 0){
                for(i = 0; i < rmax; i++){
                    fscanf(fp, "%d", &input);
                    r[i] = input;
                }

                for(i = 0; i < MMAX; i++){
                    fscanf(fp, "%d", &input);
                    m[i] = input;
                }
            }

            fclose(fp);
        }
        else {
            // Error on Input
            printf(">> Unknown Command |%s|%s|\n", cmd, arg);
        }
    }
    printf("\nEnd Program.\n\n");
    return (0);
}
