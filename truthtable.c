#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef enum {AND, OR, NAND, NOR, XOR, NOT, PASS, DECODER, MULTIPLEXER} type;

typedef struct {
    type gateName; 
    int* inputVariables;
    int* outputVariables;
    int* selectorVariables;
    char myGate[17];
    int inputNumber;
    int outputNumber;
    int selectingNumber;
    int decodingNumber;
} gate;

// This prints out the contents of int* Variables.
void printIntPointer (int* intPointer, int length) {
    for (int i=0; i<length; i++) {
        printf("%d | ", intPointer[i]);
    }
    printf("\n");
}

// This prints out the contents of uniqueVariables.
void printUniqueVariables (char** uniqueVariables, int totalUniqueVariables) {
    for (int i=0; i<totalUniqueVariables; i++) { printf("%s | ", uniqueVariables[i]);}
    printf("\n");
}



// This function takes input1, input2, and outputs output1 for xorGate with a truthTable.
void xorLogicGate ( int* truthTable, int input1, int input2, int output1) {
    if (truthTable[input1] != truthTable[input2]) {
        truthTable[output1] = 1;
    }
    else {
        truthTable[output1] = 0;
    }
}

// This function takes input1 and outputs output1 for notGate with a truthTable.
void notLogicGate ( int* truthTable,int input1, int output1) {
    if (truthTable[input1] == 0) {truthTable[output1] = 1;}
    else {truthTable[output1] = 0;}
}

// This function takes input1 and outputs1 for passGate with a truthTable. 
void passLogicGate (int* truthTable,int input1, int output1 ) {
    truthTable[output1] = truthTable[input1];
}

void DECODERgate(int *values, int *iindex, int *oindex,int n) {
    int s = 0;
    int i;
    for (i = 0; i < pow(2, n); i++) {
        values[oindex[i]] = 0;
    }
    for (i = 0; i < n; i++) {
        s += values[iindex[i]] * pow(2, n - i - 1);
    }
    values[oindex[s]] = 1;
}

// This function takes in pointers to inputs, outputs, and selectors to create the multiplexer. 
void MUX (int* inputsPointer, int* outputsPointer, int* selectorsPointer, int* truthTable, int selectNumber) {
    int jumpToInputNumber = 0;
    for (int i=0; i < selectNumber; i++) {
        if (truthTable[selectorsPointer[i]] == 1) {
            jumpToInputNumber += pow(2, selectNumber-i-1);
            //printf("JumpToInputNumber: %d\n", jumpToInputNumber);
        }
    }
    //printf("Final JumpToInputNumber: %d", jumpToInputNumber);
    truthTable[outputsPointer[0]] = truthTable[inputsPointer[jumpToInputNumber]];
}

void buildCircuit(int * truthTable, int gateType, int combinationCircuitoutputVariables,int combinationCircuitinputVariables0,int combinationCircuitinputVariables1, int *combinationCircuitinputVariablesNO, int *selector, int number){
  switch(gateType) { //Only this line my line
            case 0: //AND Gate
                     truthTable[combinationCircuitoutputVariables] = truthTable[combinationCircuitinputVariables0] && truthTable[combinationCircuitinputVariables1];
                break;
            case 1: //OR Gate
                     truthTable[combinationCircuitoutputVariables] = truthTable[combinationCircuitinputVariables0] || truthTable[combinationCircuitinputVariables1]; 
                break;
            case 2:
                    if (truthTable[combinationCircuitinputVariables0] == 1 && truthTable[combinationCircuitinputVariables1] == 1) {truthTable[combinationCircuitoutputVariables] = 0;}
                        else {truthTable[combinationCircuitoutputVariables]=1;}
                break;
            case 3:
                 if (truthTable[combinationCircuitinputVariables0] == 0 && truthTable[combinationCircuitinputVariables1] == 0) {truthTable[combinationCircuitoutputVariables] = 1;}
                    else {truthTable[combinationCircuitoutputVariables]=0;}
                break;
            case 4:
              //  xorLogicGate(truthTable,combinationCircuitinputVariables0, combinationCircuitinputVariables1, combinationCircuitoutputVariables);
                break;
            case 5:
               // notLogicGate(truthTable,combinationCircuitinputVariables0, combinationCircuitoutputVariables);
                break;
            case 6:
                truthTable[ combinationCircuitoutputVariables] = truthTable[ combinationCircuitinputVariables0];
                break;
            case 7:
              //  DECODERgate(truthTable,combinationCircuitinputVariablesNO,combinationCircuitoutputVariables, number);
                break;
            case 8:
               // multiplexerLogicGate(combinationCircuitinputVariablesNO, combinationCircuitoutputVariables, selector, truthTable, number);
                break;
            }
}

void initialize_variables(gate combinationCircuit[], int numLogicGates){
        
        combinationCircuit[numLogicGates].decodingNumber = 0;
        combinationCircuit[numLogicGates].selectingNumber = 0;
        combinationCircuit[numLogicGates].inputVariables = NULL;
        combinationCircuit[numLogicGates].outputVariables = NULL;
        combinationCircuit[numLogicGates].selectorVariables = NULL;
}

int main (int argc, char* argv[]) {

 
  if (argc - 1 != 1) {
        printf("Invalid number of arguments\n");
        return EXIT_FAILURE;
    }

    //get file, return if invalid path
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }

    // Main variables. 
    char** uniqueV = NULL; 
    int tUnuqiueV = 2;

    // Scanning variables. 
    int numInputs; 
    int numOutputs; 
    char directiveName[20];

    // Reads in the input and dynamically allocates space. 
    fscanf(file, "%s %d", directiveName, &numInputs);
    tUnuqiueV += numInputs;
    uniqueV = malloc (sizeof(char*) * tUnuqiueV);
    
    // Accounts for the case when the inputs are 0/1.
    uniqueV[0] = "0"; uniqueV[1] = "1"; 

    // Stores the input variables inside of uniqueVariables.
    for (int i=2; i<tUnuqiueV; i++) {
        uniqueV[i] = malloc(sizeof(char) * 20);
        fscanf(file, "%s", uniqueV[i]);
    }

    // Reads in the output and dynamically reallocates space. 
    fscanf(file, "%s %d", directiveName, &numOutputs);
    tUnuqiueV += numOutputs; 
    uniqueV = realloc(uniqueV, sizeof(char*) * tUnuqiueV);

    // Stores the output variables inside of uniqueVariables. 
    for (int i=2+numInputs; i<tUnuqiueV; i++) {
        uniqueV[i] = malloc(sizeof(char) * 20);
        fscanf(file, "%s", uniqueV[i]);
    }

    // Creates a truthTable for printing out the row of each TruthTable.
    int* truthTable = calloc(tUnuqiueV, sizeof(int));
    truthTable[1] = 1;
    int numRows = pow(2, numInputs); int rowIterator = 0;

    // Relevant variables for combinationCircuit.
    int nLG = 0; gate* combinationCircuit;

    // This will build the combinationCircuit.
    while (!feof(file)){
        // This allocates/reallocates space for the combinationCircuit.

                
        int numDirectiveInputs = 2; 
        int numDirectiveOutputs = 1;
        char charReader[20];
    if(numDirectiveInputs>1){
        if (nLG == 0) {
            combinationCircuit = malloc(sizeof(gate));
          initialize_variables(combinationCircuit, nLG);
        }
        else {
            combinationCircuit = realloc(combinationCircuit, sizeof(gate) * (nLG+1));
            initialize_variables(combinationCircuit, nLG);
        }  
    }   else return EXIT_FAILURE;
       
        // Sets up parameters of the particular logic gate that we are using.

        // Reads in the directive name from the file.
        fscanf(file, "%s", charReader);
        //Alien Code is here
    if (strcmp(charReader, "AND")==0 || strcmp(charReader, "OR")==0 || 
		strcmp(charReader, "XOR")==0 || strcmp(charReader, "NOR")==0 || 
		strcmp (charReader, "NAND") ==0) {

        		if (strcmp(charReader, "AND")==0) {
						combinationCircuit[nLG].gateName = 0;
					} else if (strcmp(charReader, "OR")==0) {
						combinationCircuit[nLG].gateName = 1;
					} else if (strcmp(charReader, "XOR")==0) {
					    combinationCircuit[nLG].gateName = 4;
					}else if (strcmp(charReader, "NAND")==0) {
					    combinationCircuit[nLG].gateName = 2;
					}else {
					    combinationCircuit[nLG].gateName = 3;
					}
     }

     else if((strcmp("NOT", charReader) == 0)||(strcmp("PASS", charReader) == 0)) { 
         numDirectiveInputs = 1;

        if (strcmp("NOT", charReader) == 0) {
            combinationCircuit[nLG].gateName = 5;
        }
        if (strcmp("PASS", charReader) == 0) {
            combinationCircuit[nLG].gateName = 6;
        }
     }

    else{
        if (strcmp("DECODER", charReader) == 0) {
            combinationCircuit[nLG].gateName = 7;
            fscanf(file, "%d", &numDirectiveInputs);
            combinationCircuit[nLG].decodingNumber = numDirectiveInputs;
            numDirectiveOutputs = pow(2, numDirectiveInputs);
        }
        if (strcmp("MULTIPLEXER", charReader) == 0) {
            combinationCircuit[nLG].gateName = 8;
            fscanf(file, "%d", &numDirectiveInputs);
            combinationCircuit[nLG].selectingNumber = numDirectiveInputs;
            numDirectiveInputs = pow(2, numDirectiveInputs);
        }
  } 

        // Updates fields for the struct.
        combinationCircuit[nLG].inputNumber = numDirectiveInputs;
        combinationCircuit[nLG].outputNumber = numDirectiveOutputs;

        // Dynamically allocate space for numInputDirectives, numOutputDirectives, numSelectorVariables.
        combinationCircuit[nLG].inputVariables = calloc(numDirectiveInputs,sizeof(int));
        combinationCircuit[nLG].outputVariables = calloc(numDirectiveOutputs,sizeof(int));
        combinationCircuit[nLG].selectorVariables = calloc(combinationCircuit[nLG].selectingNumber,sizeof(int));
        combinationCircuit->myGate[1] = numDirectiveInputs;

        // Store the directiveInputs in combinationCircuit[gateNum] struct.
        for (int i=0; i < numDirectiveInputs; i++) {
            fscanf(file, "%s ", charReader);
            int switchNum = 0;
            for (int j=0; j<tUnuqiueV; j++) {
                if (strcmp(uniqueV[j], charReader) == 0) {
                    combinationCircuit[nLG].inputVariables[i] = j;
                    switchNum = 1;
                    break;  
                }
            }

            // Reallocate space for temporary variables if it is necessary.
            if (switchNum == 0 && switchNum == 0) {
                tUnuqiueV++;
                truthTable = realloc(truthTable, sizeof(int) * tUnuqiueV);
                truthTable[tUnuqiueV-1] = 0;
                uniqueV = realloc(uniqueV, sizeof(char*) * tUnuqiueV);
                uniqueV[tUnuqiueV-1] = malloc(sizeof(char) * 20);
                strcpy(uniqueV[tUnuqiueV-1], charReader);
                combinationCircuit[nLG].inputVariables[i] = tUnuqiueV-1;
            }
        }

        // Store the selectorVariables in combinationCircuit[gateNum] struct.
        for (int i=0; i < combinationCircuit[nLG].selectingNumber; i++) {
            fscanf(file, "%s ", charReader);
            for (int j=0; j<tUnuqiueV; j++) {
                if (strcmp(uniqueV[j], charReader) == 0) {
                    combinationCircuit[nLG].selectorVariables[i] = j;
                    break;  
                }
            }
        }

        // Store the directiveOutputs in combinationCircuit[gateNum] struct. 
        for (int i=0; i < numDirectiveOutputs; i++) {
            fscanf(file, "%s ", charReader);
            int switchNum = 0;
            for (int j=0; j<tUnuqiueV; j++) {
                if (strcmp(uniqueV[j], charReader) == 0) {
                    combinationCircuit[nLG].outputVariables[i] = j;
                    switchNum = 1;
                    break;  
                }
            }
        
            // Reallocate space for temporary variables if it is necessary.
            if (switchNum == 0 && switchNum==0) {
                tUnuqiueV++;
                truthTable = realloc(truthTable, sizeof(int) * tUnuqiueV);
                truthTable[tUnuqiueV-1] = 0;
                uniqueV = realloc(uniqueV, sizeof(char*) * tUnuqiueV);
                uniqueV[tUnuqiueV-1] = malloc(sizeof(char) * 20);
                strcpy(uniqueV[tUnuqiueV-1], charReader);
                combinationCircuit[nLG].outputVariables[i] = tUnuqiueV-1;
            }
        }
        nLG++;
    }

    // This prints the inputs/outputs for the truthTable.
    while (rowIterator < numRows) {      

        for (int i=0; i < nLG; i++) {
           switch(combinationCircuit[i].gateName) { //Only this line my line
            case 0: //AND Gate
                     truthTable[combinationCircuit[i].outputVariables[0]] = truthTable[combinationCircuit[i].inputVariables[0]] && truthTable[combinationCircuit[i].inputVariables[1]];
                break;
            case 1: //OR Gate
                     truthTable[combinationCircuit[i].outputVariables[0]] = truthTable[combinationCircuit[i].inputVariables[0]] || truthTable[combinationCircuit[i].inputVariables[1]]; 
                break;
            case 2: //NAND 
                    if (truthTable[combinationCircuit[i].inputVariables[0]] == 1 && truthTable[combinationCircuit[i].inputVariables[1]] == 1) {truthTable[combinationCircuit[i].outputVariables[0]] = 0;}
                        else {truthTable[combinationCircuit[i].outputVariables[0]]=1;}
                break;
            case 3: //NOR
                 if (truthTable[combinationCircuit[i].inputVariables[0]] == 0 && truthTable[combinationCircuit[i].inputVariables[1]] == 0) {truthTable[combinationCircuit[i].outputVariables[0]] = 1;}
                    else {truthTable[combinationCircuit[i].outputVariables[0]]=0;}
                break;
            case 4:
                xorLogicGate(truthTable,combinationCircuit[i].inputVariables[0], combinationCircuit[i].inputVariables[1], combinationCircuit[i].outputVariables[0]);
                break;
            case 5:
                notLogicGate(truthTable,combinationCircuit[i].inputVariables[0], combinationCircuit[i].outputVariables[0] );
                break;
            case 6:
                truthTable[ combinationCircuit[i].outputVariables[0] ] = truthTable[ combinationCircuit[i].inputVariables[0]];
                break;
            case 7:
                DECODERgate(truthTable,combinationCircuit[i].inputVariables,combinationCircuit[i].outputVariables, combinationCircuit[i].decodingNumber);
                break;
            case 8:
                MUX(combinationCircuit[i].inputVariables, combinationCircuit[i].outputVariables, combinationCircuit[i].selectorVariables, truthTable, combinationCircuit[i].selectingNumber);
                break;
            }
            
        }

        // This prints  truthTable.

        for (int i=2; i<numInputs+2; i++) {printf("%d ", truthTable[i]);}
        printf("| ");   

          for (int i=0; i<numOutputs; i++) {
        if (i < (numOutputs-1)) {printf("%d ", truthTable[numInputs+2+i]);}
        else {printf("%d", truthTable[numInputs+2+i]);}
         }
        printf("\n");
  
            for (int i=numInputs+1; i >= 0; i--) {
               truthTable[i] = !truthTable[i];
                if (truthTable[i] == 1) {break;}
                }  
        rowIterator++; 
    }

    // Deallocates dynamically allocated space. 
    for (int i=0; i<nLG; i++) {
        free(combinationCircuit[i].inputVariables);
        free(combinationCircuit[i].outputVariables);
        free(combinationCircuit[i].selectorVariables);
    }

    for (int i=2; i<(tUnuqiueV); i++) {
        free(uniqueV[i]);
    }

    free(combinationCircuit);
    free(uniqueV);
    free(truthTable);

    return EXIT_SUCCESS; 
}