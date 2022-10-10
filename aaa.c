//aaa lang executer v1
//made with love by the infamous dinguskhan0
#include <stdio.h>

//change this if you somehow managed to hit the memory limit and need more
#define MEMORY_SIZE 32767

int main(int argc, char* argv[]) {
    int DEBUG = argc > 2 && argv[2][0] == 'd';
    if (DEBUG) printf("[DEBUG MODE]\n");
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

        //execution
        if (DEBUG) printf("executing '%c%c'\n",data[i-1], data[i]);
        switch (code)
        {
        case 11: //AA
            putchar(memory[mindex]);
            break;
        case 12: //?A
            memory[mindex]--;
            if (DEBUG) printf("   mem[%d] = %d\n",mindex,memory[mindex]);
            break;
        case 13: //!A
            memory[mindex]++;
            if (DEBUG) printf("   mem[%d] = %d\n",mindex,memory[mindex]);
            break;
        case 21: //A?
            if (mindex > 0) mindex--;
            if (DEBUG) printf("   mem[%d] = %d\n",mindex,memory[mindex]);
            break;
        case 22: //??
            memory[mindex] = getchar();
            if (DEBUG) printf("   mem[%d] = %d\n",mindex,memory[mindex]);
            break;
        case 23: //!?
            if (mindex < MEMORY_SIZE) mindex++;
            if (DEBUG) printf("   mem[%d] = %d\n",mindex,memory[mindex]);
            break;
        case 31: //A!
            if (memory[mindex] == 0) {
                int level = 1;
                while (1)
                {
                    i++;
                    if (i > filesize) { 
                        printf(" ERROR: attempt to skip past file bounds");
                        return -1;
                    }
                    if (data[i-1] == 'A' && data[i] == '!') {
                        level++;
                    }
                    if (data[i-1] == '?' && data[i] == '!') {
                        level--;
                        if (!level) break;
                    }
                    if (DEBUG) printf("   skipping [f] '%c%c'\n",data[i-1], data[i]);
                }
                i--;
                if (DEBUG) printf(" END SKIP\n");
            } else if (DEBUG) printf("   mem[%d] != 0\n",mindex);
            
            break;
        case 32: //?!
            if (memory[mindex] != 0) {
                int level = 1;
                while (1)
                {
                    i--;
                    if (i < 3) { 
                        printf(" ERROR: attempt to skip past file bounds");
                        return -1;
                    }
                    if (data[i-2] == '?' && data[i-1] == '!') {
                        level++;
                    }
                    if (data[i-2] == 'A' && data[i-1] == '!') {
                        level--;
                        if (!level) {
                            i++;
                            break;
                        };
                    }
                    if (DEBUG) printf("   skipping [r] '%c%c'\n",data[i-1], data[i]);
                }
                i -= 2;
                if (DEBUG) printf(" END SKIP\n");
            } else if (DEBUG) printf("   mem[%d] == 0\n",mindex);
            break;
        case 33: //!!
            if (memory[mindex] > 0) {
                i = memory[mindex];
                if (DEBUG) printf("skipping to %d\n", memory[mindex]);
            } else if (DEBUG) printf("did not skip to %d\n", memory[mindex]);
            break;
        default:
            break;
        }
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
