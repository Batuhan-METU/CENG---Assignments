#include <stdio.h>

void task1_assembly(void)
{
    int instructionCount; 

    char operationType; 
    char set = 'S', add = 'A', copy = 'C', increment = 'I', decrement = 'D', jump = 'J'; 

    int registers[9] = {0}; /* {0,0,0,0,0,0,0,0,0} */ 
    int instructionID; 
    int number1, number2, number3; 


    char operations[50] = {0};   
    int storeOldValues[100][50] = {0}; 
     /*
     for example
    2 3
    4
    5
    4 5 8              
    */
    

    scanf("%d", &instructionCount); 
    
    for (instructionID = 1; instructionID<=instructionCount; instructionID++)
    {
        scanf(" %c", &operationType); 
        if (operationType == set)  
        {
            scanf(" %d %d", &number1, &number2); 
            registers[number1] = number2; 
            storeOldValues[instructionID][1] = number1;                     
            storeOldValues[instructionID][2] = number2;
            operations[instructionID] = set;                                    
        }
        else if (operationType == add)
        {
            scanf(" %d %d", &number1, &number2); 
            registers[number1] = registers[number1] + registers[number2]; 
            storeOldValues[instructionID][1] = number1; 
            storeOldValues[instructionID][2] = number2; 
            operations[instructionID] = add;   
        }
        else if (operationType == copy)
        {
            scanf(" %d %d", &number1, &number2); 
            registers[number1] = registers[number2]; 
            storeOldValues[instructionID][1] = number1; 
            storeOldValues[instructionID][2] = number2;
            operations[instructionID] = copy;   
        }
        else if (operationType == increment)
        {
            scanf(" %d", &number1); 
            registers[number1] += 1; 
            storeOldValues[instructionID][1] = number1;
            operations[instructionID] = increment;  
        }
        else if (operationType == decrement)
        {
            scanf(" %d", &number1); 
            registers[number1] -= 1; 
            storeOldValues[instructionID][1] = number1;
            operations[instructionID] = decrement;   
        }
        else if (operationType == jump)          
        {
                scanf(" %d %d %d", &number1, &number2, &number3);  
                    
                if (registers[number1] > registers[number2])
                {
                    storeOldValues[instructionID][1] = number1; 
                    storeOldValues[instructionID][2] = number2; 
                    storeOldValues[instructionID][3] = number3; 
                    operations[instructionID] = jump;     
                    while (registers[number1] > registers[number2])
                    {
                        int i; 
                        for (i = number3; i < instructionID; i++) 
                        {
                            if (operations[i] == set)       
                            {
                                int n = storeOldValues[i][1]; 
                                registers[n] = storeOldValues[i][2];  
                            }
                            else if (operations[i] == add)
                            {
                                int n = storeOldValues[i][1]; 
                                int m = storeOldValues[i][2]; 
                                registers[n] = registers[n] + registers[m];     
                            }
                            else if (operations[i] == copy)
                            {
                                int n = storeOldValues[i][1]; 
                                int m = storeOldValues[i][2]; 
                                registers[n] = registers[m]; 
                            }
                            else if (operations[i] == increment)
                            {
                                int n = storeOldValues[i][1]; 
                                registers[n] += 1; 
                            }
                            else if (operations[i] == decrement)
                            {
                                int n = storeOldValues[i][1]; 
                                registers[n] -= 1; 
                            }
                        }
                    }
                } 
                else 
                {
                    storeOldValues[instructionID][1] = number1; 
                    storeOldValues[instructionID][2] = number2; 
                    storeOldValues[instructionID][3] = number3; 
                    operations[instructionID] = jump;     
                }
        }
    }

    printf("R1: %d\n", registers[1]); 
    printf("R2: %d\n", registers[2]); 
    printf("R3: %d\n", registers[3]); 
    printf("R4: %d\n", registers[4]); 
    printf("R5: %d\n", registers[5]); 
    printf("R6: %d\n", registers[6]); 
    printf("R7: %d\n", registers[7]); 
    printf("R8: %d\n", registers[8]);  
}


int findMinPlanes(int index, int length, int width, int planeNumber, int capacities[]) {
    int size = capacities[index]; 
    int minPlanes = 10000;
    int bigArea; 

    int elseCase;
    
    int remainingArea1;
    int remainingArea2;
    int remainingArea3;

    if (length % size == 0 && width % size == 0)  
    {
        return (length * width) / (size * size);
    }

    if (length >= size && width >= size) 
    {
        bigArea = (length / size) * (width / size); 

        remainingArea1 = findMinPlanes(index+1, length-size, width - (width-size), planeNumber, capacities); 
        remainingArea2 = findMinPlanes(index + 1, length-(length-size), width-size, planeNumber, capacities);
        remainingArea3 = findMinPlanes(index + 1, length-size, width-size, planeNumber, capacities); 

        if (bigArea + remainingArea1 + remainingArea2 + remainingArea3 < minPlanes)  
        {
            minPlanes =  bigArea + remainingArea1 + remainingArea2 + remainingArea3;
        }        
    }
    
    elseCase = findMinPlanes(index + 1, length, width, planeNumber, capacities); 
        if (elseCase<minPlanes)
        {
            minPlanes = elseCase;
        }   
        
    return minPlanes;
}
int calculate_planes(int land_length, int land_width, int plane_capacities[], int num_of_planes) 
{
    return findMinPlanes(0, land_length, land_width , num_of_planes, plane_capacities); 
}

void task2_planes(void)
{
    int length; 
    int width; 
    
    int planeNumber; 
    int capacities[6] = 0; /*{0,0,0,0,0,0}*/ 
    int capacity1, capacity2, capacity3, capacity4, capacity5; 

    scanf("%d %d", &length, &width); 

    scanf("%d", &planeNumber);  

    switch (planeNumber)
    {
    case 1:
        scanf("%d", &capacity1); 
        printf("\n"); 
        capacities[0] = capacity1; 
        break;

    case 2:
        scanf("%d", &capacity1); 
        scanf("%d", &capacity2); 

        capacities[0] = capacity1; 
        capacities[1] = capacity2; 
        break;

    case 3:
        scanf("%d", &capacity1); 
        scanf("%d", &capacity2); 
        scanf("%d", &capacity3); 

        capacities[0] = capacity1; 
        capacities[1] = capacity2; 
        capacities[2] = capacity3; 
        break;

    case 4:
        scanf("%d", &capacity1); 
        scanf("%d", &capacity2); 
        scanf("%d", &capacity3); 
        scanf("%d", &capacity4);
 

        capacities[0] = capacity1; 
        capacities[1] = capacity2; 
        capacities[2] = capacity3; 
        capacities[3] = capacity4; 
        break;

        case 5:
        scanf("%d", &capacity1); 
        scanf("%d", &capacity2); 
        scanf("%d", &capacity3); 
        scanf("%d", &capacity4); 
        scanf("%d", &capacity5); 

        capacities[0] = capacity1; 
        capacities[1] = capacity2; 
        capacities[2] = capacity3; 
        capacities[3] = capacity4; 
        capacities[4] = capacity5; 
        break;

    }

    int result = calculate_planes(length, width, capacities, planeNumber); 

    printf("%d planes", result); 
    printf("\n"); 
}