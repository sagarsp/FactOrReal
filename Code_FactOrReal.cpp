#include <stdio.h>
#include <stdlib.h>
#define		MAX_LENGTH	3000				// Defining the maximum length of given number

int main()
{
	int givenNumber [MAX_LENGTH] = {4,7,9,0,0,1,6,0,0,-1};		// Given Number with ending value =-1
	int updatedNumber [MAX_LENGTH] ={};				// This will be the updating number every time we divide by 2,3,4,...
	int divisingNumber [MAX_LENGTH] ={};				// This number will be divided by 2,3,4... including reminder
	int instantReminderForInteger [MAX_LENGTH] = {};		// This array shows the Reminder of each digit, while deviding by 2,3,4...
	int flagFectorial = 1;					// Initlizing flag with an assumption, that given number is fectorical of any integer number
	int fectOfResultantNumber = 1;				// Result : The givenNumber is the fectorial of this number
	int i = 0;							// Initlizing i for using in finding the total number of digits in number
	

	/* Open the file to read the number */
	FILE* fileOfNumber;
	char charFromFile;
	int totalLengthOfNumber = 0;
	fileOfNumber = fopen("number.txt","r");
	charFromFile = fgetc (fileOfNumber);
	while(charFromFile != EOF)
	{
		if(charFromFile >=48 && charFromFile <=57)
			totalLengthOfNumber++;
		charFromFile = fgetc(fileOfNumber);
	}		
	fseek(fileOfNumber,0,SEEK_SET);
	
	/* Read the number into givenNumberFromFile */
	int *givenNumberFromFile;
	givenNumberFromFile = (int*)malloc(totalLengthOfNumber*sizeof(int));
	charFromFile = fgetc (fileOfNumber);
	while(charFromFile != EOF)
	{
		if(charFromFile >=48 && charFromFile <=57)
		{
			*givenNumberFromFile = charFromFile - 48;
			printf("%c\n",charFromFile);		
			givenNumber[i] = *givenNumberFromFile;
			givenNumberFromFile++;
			i++;
		}
		charFromFile = fgetc(fileOfNumber);
	}		
	givenNumber[i+1] = -1;

	printf("=====================================\nSize of given number = %d\n=====================================",totalLengthOfNumber);
	/*Find the number of digits in given number*/
	/*
	for (i=0;givenNumber[i] != -1; i++);
		int numberOfDigits = i;
	*/
	int numberOfDigits = totalLengthOfNumber;
	int updatedNumberOfDigits = totalLengthOfNumber;		// Initilize the number of digits in updated number same as given number because, initially we have updated number same as given number
	
	/*The loop for doing division by 2,3,4,... and checking whether the given number is fectorial of any integer number*/
	for(int j=2; 	; j++)					// The loop will always start with 2 and go till infinite number
	{	
		int k;
		for(k=0; k<updatedNumberOfDigits; k++)		// k will go till the LSB of given number or updated number (Initially both are same as j =2. But for j>2, updted number will be the new number when we devide by j (2,3,..).
		{
			if(j==2)				// Logic for j =2
			{
				
				if(k!=0)			// If the given bit is not MSB
				{
					divisingNumber[k] = givenNumber[k] + (10*(divisingNumber[k-1]%j));
					instantReminderForInteger[k] = divisingNumber[k]%j;		// Finding the instant Reminder
													// Instant Reminder will be used to find whether the number is fectorial or not by applying some conditions.
				}
				else				// If the given bit is MSB
				{
					divisingNumber[k] = givenNumber[k];
					instantReminderForInteger[k] = givenNumber[k]%j;
				}
			}
			else					// Some other logic for j = 3,4,5,... The need for keeping this as different than of j =2, is making initial division with given number, which will result into updated number. And then, all other division by updated number.
			{
				
				if(k!=0)			// If the given bit is not MSB
				{
					divisingNumber[k] = updatedNumber[k] + (10*(divisingNumber[k-1]%j));
					instantReminderForInteger[k] = divisingNumber[k]%j;
				}
				else				// If the given bit is MSB
				{
					divisingNumber[k] = updatedNumber[k];
					instantReminderForInteger[k] = updatedNumber[k]%j;
				}
			}
			updatedNumber[k] = divisingNumber[k] / j;	// Updated number is divising number divided by j
			//printf("%d %d ",updatedNumber[k], instantReminderForInteger[k]);
		}
		if(k==updatedNumberOfDigits)		// If k = updatedNumberOfDigits, put -1 at the end of updated numbers string.
			updatedNumber[k] = -1;
		for (i = 0; updatedNumber[i]!= -1; i++);	// Loop to find the number of digits in updated number.This will remain same as digits of given number.
		updatedNumberOfDigits = i;			// When the above loop will end, it will set the value of i to the number of digits of updated number.
		//printf("\t\tDividing by %d ",j);
		
		int checker = 0;				// Checker is the variable used for looping into all the digits are 0 till LSB.
		while(updatedNumber[checker++]==0);		// Check how many contineous digits are zeros from LSB.
		//printf("Checker of %d = %d \n",j,checker-1);
		if(checker==updatedNumberOfDigits &&  updatedNumber[updatedNumberOfDigits-1]==1)	// If checker is total number of digits - 1, meaning we have all the zeros from MSB to second last number. Also, if last digit is 1, that mean the updatedNumber is 0000..001 = 1. Meaning the given number is fectorial of j and dividing by j! resulted in 1.
		{
			fectOfResultantNumber = j;		// Assign the value of j to fectOfResultantNumber. This will tell us given number is the fectorial of which number.
			break;					// Break the for loop as no more permutation is required.
		}
		if(instantReminderForInteger[k-1] != 0)		// If j is increasing from 2,3,4,... and in between in any expression for division, if last digit of reminder is non zero, meaning the given number is not divisable by j. Hence, it is not fectorial of any number.
		{	
			flagFectorial = 0;			// Set the flag of fectorial to 0. So, we can check this flag with 0 and say that given number is not fectorial.
			break;					// If given number is not a fectorial of any number, come out of loop by break.
		}
		
	}
	if(flagFectorial == 1)					// If fectFectorial is 1, that mean the given number is fectorial of integer number
	{
		printf("\nGiven number is Fectorial of %d\n",fectOfResultantNumber);		// Print that number with message.
	}
	else							// If fectFectorial is not 1, that mean the given number is not a fectorial.
	{
		printf("\nGiven numberis not a Fectorial of any integer number\n");		// Print the message.
	}
	
	return 0;
}
