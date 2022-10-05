//aaa lang executer v1
//made with love by the infamous dinguskhan0
#include <stdio.h>

//change this if you somehow managed to hit the memory limit and need more
#define MEMORY_SIZE 32767

int main(int argc, char* argv[]) {
    //file reading
    if (argc < 2) {
        printf("a?! runtime requires one argument specifying path\n");
        return -1;
    }

    FILE* input = fopen(argv[1], "r");
    
    if (input == NULL) {
        perror("argv[1]");
    }

    int filesize;

    fseek(input,0,SEEK_END);
    filesize = ftell(input);

    fseek(input,0,SEEK_SET);

    char data[filesize];

    for (int i = 0; i < filesize; i++) {
        data[i] = fgetc(input);
    }

    int last = 0;

    char memory[MEMORY_SIZE] = {0};
    int mindex;
    int flag = 0; //used to skip commands
    //flag 1 = skip until reach ?!
    //flag -1 = go back until reach a!

    //interpreter
    for (int i = 1; i < filesize; i++) {
        if (!(data[i] == 'A' || data[i] == '?' || data[i] == '!')) {
            if (data[i-1] == 'A' || data[i-1] == '?' || data[i-1] == '!') last = i - 1;
            continue;
        };
        if (!(data[i-1] == 'A' || data[i-1] == '?' || data[i-1] == '!')) {
            data[i-1] = data[last];
        };
        // last = i;
        char command[] = {data[i-1], data[i]}; 

        if (i == 0) {
            printf("ERROR: program counter out of bounds [min 1, attempted 0]\n");
            return -1;
        }

        //command parsing

        int code = 0;
        switch (command[0])
        {
        case 'A':
            code += 1;
            break;
        case '?':
            code += 2;
            break;
        case '!':
            code += 3;
            break;
        default:
            break;
        }

        switch (command[1])
        {
        case 'A':
            code += 10;
            break;
        case '?':
            code += 20;
            break;
        case '!':
            code += 30;
            break;
        default:
            break;
        }

        // printf("code %d\n",code);

        // flag = 0;

        //execution
        if (flag != 0) {
            //flag instructions
            if (flag == -1) {
                i -= 2;
                if (code == 31) {
                    flag = 0;
                }
                continue;
            };
            if (flag == 1) {
                if (code == 32) {
                    flag = 0;
                }
            }
            continue;
        }
        switch (code)
        {
        case 11: //AA
            putchar(memory[mindex]);
            break;
        case 12: //?A
            memory[mindex]--;
            break;
        case 13: //!A
            memory[mindex]++;
            break;
        case 21: //A?
            if (mindex > 0) mindex--;
            break;
        case 22: //??
            memory[mindex] = getchar();
            break;
        case 23: //!?
            if (mindex < MEMORY_SIZE) mindex++;
            break;
        case 31: //A!
            if (memory[mindex] == 0) flag = 1;
            break;
        case 32: //?!
            if (memory[mindex] != 0) flag = -1;
            break;
        case 33: //!!
            if (memory[mindex] != 0) flag = 1;
            break;
        default:
            break;
        }
        if (flag == -1) i -= 1;
        if (i >= filesize) {
            printf("ERROR: program counter out of bounds [max %d, attempted %d]\n", filesize, i);
            return -1;
        }
        if (i == 0) {
            printf("ERROR: program counter out of bounds [min 1, attempted 0]\n");
            return -1;
        }
    }
    printf("\nprocess exited mem[%d] = %d\n",mindex,memory[mindex]);
    return 0;
}
