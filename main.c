//Totalistic Cellular Automaton

/*-------------------------------------------
Program 1: Totalistic Cellular Automaton (Programming in C: A Total Cell-ebration!)
	A simple version of a totalistic cellular automaton. Its a collection of cells on a world. Where each cell
    contains a value representing its status (inactive, at-risk or active). Its uses a rule to for its evolution
    process, having to check the current cells and the cells to its right and left to see its new status in the
    new generation.
Course: CS 211, Fall 2025, UIC
Author: Evelyn Roa
------------------------------------------- */


#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    int localSum; // total sum of local cells, [left] + [me] + [right]: possible values are 0-6
    int status;   // this cell's current status: 0, 1, or 2
    int count;    // running accumulated count of this cell's active status for all generations
} cell;

// convert an integer rule (0-2186) to its base-3 representation, 
// stored in reverse order, as an array of 7 status values, i.e. valArray[7] 
//   ex: rule = 777  -> [0121001], since 777  = 1*3^1 + 2*3^2 + 1*3^3 + 1*3^6   
//   ex: rule = 177  -> [0210200], since 177  = 2*3^1 + 1*3^2 + 2*3^4
//   ex: rule = 2040 -> [0210122], since 2040 = 2*3^1 + 1*3^2 + 1*3^4 + 2*3^5 + 2*3^6
//return true if input rule is valid (0-2186)
//return false if input rule is invalid
bool setValArray(int valArray[7], int rule) {

    //TODO: Task 1 - write the setValArray() function

    // if statement to check the input is a valid rule
    if(rule < 0 || rule > 2186) {
        return false;
    }
    
    // for loop to obtain the tenary representation
    for (int i = 0; i < 7; i++) {
        valArray[i] = rule % 3;
        rule /= 3;
    }

    return true;
}

// used to print the tenary value in the correct order
void printValArray(const int rule, const int valArray[7]) {
    printf("The value array for rule #%d is ", rule);

    for (int i = 6; i >= 0; i--) {
        printf("%d", valArray[i]);
    }

    printf("\n");
}

// update the localSum subitem for each cell in the world array based on the
// current statuses for the nearby [left, me, right] cells
// note: world is periodic/cyclic, with front-to-back and back-to-front wrapping 
void setSums(cell world[WORLD_SIZE]) {

    //TODO: Task 4 - write the setSums() function
    
    // if statements to make sure we dont try to access past the array size

    for(int i = 0; i < WORLD_SIZE; i++) {
        int right, left;
        if (i == 0) {
            left = world[WORLD_SIZE - 1].status;
            right = world[i + 1].status;
        }
        else if(i == WORLD_SIZE - 1) {
            left = world[i - 1].status;
            right = world[0].status;
        }
        else {
            left = world[i - 1].status;
            right = world[i + 1].status;
        }

        world[i].localSum = left + right + world[i].status;
    }

    return;
}

// function for task 5c
// initializes the world depening on user inputs
// updates count
void initializeWorld(int initialCell, cell world[WORLD_SIZE]) {
    // everything but the center cell is set to 0
    // need to get the middle cell to initialize
    // initialize count
    int mid = WORLD_SIZE / 2;

    for (int i = 0; i < WORLD_SIZE; i++) {
        if (i == mid) {
            world[i].status = initialCell;
            

            if(initialCell == 1) {
                printf("%c", '-');
            }
            else {
                printf("%c", '+');
            }
        }
        else {
            world[i].status = 0;
            printf("%c", ' ');
        }
        
        world[i].count = world[i].status;
    }

    return;
}

// function to get the sum of that generations count and easily print it
void printCount(cell world[WORLD_SIZE]) {
    int c = 0;
    for (int i = 0; i < WORLD_SIZE; i++) {
        c += world[i].count;
    }

    printf(" %d \n", c);

    return;
}

// gets the total count of status
int getCount(cell world[WORLD_SIZE]) {
    int c = 0;
    for (int i = 0; i < WORLD_SIZE; i++) {
        c += world[i].status;
    }

    return c;
}

// Evolve the world to the next generation by updating each cell's status value 
// using its localSum subitem (assumed to be updated outside of this function), where
// ruleValArray[7] stores the status values for the 7 possible local sums, in reverse order, 
// e.g. if local sum = 4, the new status value can be found at index 4 of the ruleValArray[].
// This function must also update the count subitems for all cells in world[] 
// with the new generation status values.
// This function returns the total sum of all status values in world[] after the evolution step.
int evolveWorld(cell world[WORLD_SIZE], int ruleValArray[7]) {

    //TODO: Task 6 - write the evolveWorld() function
    int temp;
    for (int i = 0; i < WORLD_SIZE; i++) {
        // get local sum
        temp = world[i].localSum;
        world[i].status = ruleValArray[temp];

        // update count
        world[i].count += world[i].status;
    }

    // update local sums
    setSums(world);    

    return getCount(world);
}


int main() {
    cell world[WORLD_SIZE];

    printf("Welcome to the Totalistic Cellular Automaton!\n");

    
    
    //TODO: Task 2 - read in a valid rule#, allowing repeated attempts if necessary,
    //      generate the rule's 7-trit (i.e. 7 base-3 digits) status value array,  
    //      print the status value array in correct ternary (i.e. base-3) number order
    int rule;
    int valArray[7];
    bool valid = false;
    do {
        printf("Enter the rule # (0-2186): ");
        scanf("%d", &rule);
        valid = setValArray(valArray, rule);
    } while(!valid);

    printValArray(rule, valArray);
    


    printf("The evolution of all possible states are as follows:\n");
    printf("Local Sum:   6       5       4       3       2       1       0      \n");
    printf("States:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    \n");
    printf("                   |+-+|   |+ +|   |+ -|   |- -|   | - |            \n");
    printf("                   |-++|   | ++|   |-+ |   | --|   |  -|            \n");
    printf("                           |+--|   | +-|   |+  |                    \n");
    printf("                           |-+-|   |- +|   | + |                    \n");
    printf("                           |--+|   | -+|   |  +|                    \n");
    printf("                                   |---|                            \n");
    printf("New Status: ");      
    //TODO: Task 3 - use the rule status value array to report the evolution 
    //      step for all possible cell neighbor states [left, me, right].
    //      Follow the format, including whitespaces, of the sample output EXACTLY.

    // loop through the valArray backwards and checks the value of each element to determine the cells status
    for(int i = 6; i >= 0; i--) {
        if (valArray[i] == 0) {
            printf("|%c|     ", ' ');
        }
        else if (valArray[i] == 1) {
            printf("|%c|     ", '-');
        }
        else {
            printf("|%c|     ", '+');
        }
    }
    
    printf("\n");


        
    //TODO: Task 5a - read in the total number of generation evolution steps
    //      from the user, allowing repeated attempts for invalid values.
    //      Follow the format, including whitespaces, of the sample output EXACTLY.

    int gen;
    do {
        printf("Enter the number of generations (1-49): "); 
        scanf("%d", &gen);
    } while (gen < 1 || gen > 49);
    
    
    //TODO: Task 5b - read in the initial status value for the middle cell, 
    //      allowing repeated attempts for invalid values. 
    //      Follow the format, including whitespaces, of the sample output EXACTLY.

    int initialCell;
    do {
        printf("\nEnter the value (1 or 2) for the initial active cell: ");
        scanf("%d", &initialCell);
    } while (initialCell < 1 || initialCell > 2);

    printf("\nInitializing world & evolving...\n");
    //TODO: Task 5c - initialize the world with the ONLY non-zero cell in the 
    //      exact middle of the world, whose status value is set using the 
    //      scanned-in value from the user above. Make sure to also set the 
    //      localSum subitem for each cell of the initial world.
    //      Follow the format, including whitespaces, of the sample output EXACTLY.

    initializeWorld(initialCell, world);
    setSums(world);
    printCount(world);

    //TODO: Task 7 - evolve the world the user-specified number of generations,
    //      printing the world after each evolution step, where each cell prints as
    //      '+', '-', or ' ' (whitespace) for status value of 2, 1, or 0, respectively.
    //      After the world display, also print out the total sum of all status values.
    //      Follow the format, including whitespaces, of the sample output EXACTLY.
    //
    //      Ex: world = [00000000000000000020101212111001210011121210102000000000000000000]
    //          display->                  + - -+-+---  -+-  ---+-+- - +                   28 <-display
    //
    //      At the end of ALL evolution steps, print a line under the last generation. 
    //      Ex: world = [02211210000121122111001121121001210012112110011122112100001211220]
    //          display-> ++--+-    -+--++---  --+--+-  -+-  -+--+--  ---++--+-    -+--++  64 <-display
    //          display->_________________________________________________________________<-display

    gen--; // one generation counts as the initialized world.

    while(gen  != 0) {
        // evolve
        int totalCount = evolveWorld(world, valArray);

        // print result before evolving again

        for (int i = 0; i < WORLD_SIZE; i++) {
            if (world[i].status == 0) {
                printf(" ");
            }
            else if (world[i].status == 1) {
                printf("-");
            }
            else {
                printf("+");
            }
        }

        printf(" %d \n", totalCount); // print total sum of statuses for that generation, then evolve again
         gen--;
    }

    printf("_________________________________________________________________\n");

    //TODO: Task 8 - after the line under the last generation, 
    //      print the total sum for each cell throughout all evolution steps vertically.
    //      The cell total sums should be printed as two digit numbers across two lines.
    //      Single-digit total sums should be represented as a whitespace on the top line, 
    //      and the single-digit on the lower line. 
    //      For total sums of zero, print both digits as whitespaces.
    //      Follow the format, including whitespaces, of the sample output EXACTLY.
    //
    //      Ex: consider a world after many evolution steps with the following final generation:
    //          display-> ++--+-    -+--++---  --+--+-  -+-  -+--+--  ---++--+-    -+--++  64 <-display
    //          display->_________________________________________________________________<-display   
    //          display->            11111111122121222233233222212122111111111            <-display 
    //          display-> 243666698963456647182091851471191174158190281746654369896666342 <-display 
    //                   ^ ^                             ^
    //      note: the first cell was ALWAYS 0, so its total sum is zero, and prints as two whitespaces
    //            the third cell has a total sum of 4, so it prints as a whitespace above the digit 4
    //            the middle cell has a total sum of 29, so it prints the digit 2 above the digit 9

    // for loop for digits greater than 9
    for (int i = 0; i < WORLD_SIZE; i++) {
        int total = world[i].count;

        if (total == 0) {
            printf(" ");
        }
        else if (total < 10) {
            printf(" ");
        }
        else {
            printf("%d", total / 10);
        }
    }
    
    printf("\n");

    // for loop for the ones place
    for (int i = 0; i < WORLD_SIZE; i++) {
        int total = world[i].count;

        if (total == 0) {
            printf(" ");
        }
        else {
            printf("%d", total % 10);
        }
    }

    printf("\n"); // make sure to end your program with a newline

    return 0;
}
