/*
 * scopeFunction.c
 *
 *  Created on: Mar 29, 2017
 *      Author: Jonathan
 */

#include <stdio.h>

#define MAXLINE 1000

int convertToDecimal(char originalNumberInput[],int originalBase);
int convertCharToDecimal(char c);
int getLine(char line[], int maxLength);
void convertFromDecimal(int numberInDecimal, int targetBase, char result[]);


int main(void)
{
	printf("Please enter the number's base:\n");
	fflush(stdout);
	char originalBaseInput[MAXLINE];
	getLine(originalBaseInput, MAXLINE);
	int originalBase;
	sscanf(originalBaseInput, "%d", &originalBase);
	// I am assuming the program receives an integer..
	if (originalBase < 2 || originalBase > 16)
	{
		printf("Invalid input base\n");
		return -1;
	}


	printf("Please enter the desired base:\n");
	fflush(stdout);
	char targetBaseInput[MAXLINE];
	getLine(targetBaseInput, MAXLINE);
	int targetBase;
	sscanf(targetBaseInput, "%d", &targetBase);
	// I am assuming the program receives an integer..
	if (targetBase < 2 || targetBase > 16)
	{
		printf("Invalid input base\n");
		return -1;
	}

	printf("Please enter a number in base %d:\n", originalBase);
	fflush(stdout);
	char originalNumberInput[MAXLINE];
	getLine(originalNumberInput, MAXLINE);

	int numberInDecimal = convertToDecimal(originalNumberInput, originalBase);
	if (numberInDecimal < 0)
		return -1;

//	printf("%s converted to decimal is: %d\n", originalNumberInput, numberInDecimal);

	char convertedToTargetBase[MAXLINE];
	convertFromDecimal(numberInDecimal,targetBase,convertedToTargetBase);

	printf("The result is : %s\n", convertedToTargetBase);





	return 0;
}


int getLine(char line[], int maxLength)
{
	int c,i;

	for (i=0; i<maxLength-1 && (c=getchar())!=EOF && c!='\n'; ++i)
	{
		line[i] = c;
	}
	line[i] = '\0';

	return i;
}


int convertToDecimal(char originalNumberInput[],int originalBase) // using horners method
{
	int i, convertedC, result =0;
	char c;
	for(i=0; (c=originalNumberInput[i])!= '\0'; i++)
	{
		result *= originalBase;

		convertedC = convertCharToDecimal(c);
		if(convertedC < 0 || convertedC >= originalBase)
		{
			printf("Invalid number!\n");
			return -1;
		} else
		{
			result += convertedC;
		}


	}



	return result;
}


int convertCharToDecimal(char c)
{
 if(c >= 48 && c <= 57)
 {
	 return c - 48;
 }
 else if (c >= 65 && c <= 70) // ABCDEF
 {
	 return c - 65 + 10;
 } else if(c >= 97 && c<=102) // abcdef
 {
	 return c - 97 + 10;
 }

 return -1;

}


void convertFromDecimal(int numberInDecimal, int targetBase, char result[])
{
	int remainder = 0,i;
	char c;
	for(i = 0; numberInDecimal != 0; i++)
	{
		remainder = numberInDecimal % targetBase;
		if (remainder > 9)
			c = 97 + (remainder %10);
		else
			c = 48 + remainder;

		result[i] = c;
		numberInDecimal /= targetBase;
	}
	result[i] = '\0';
	i--;

	for (int j = 0; j <= i/2; j++ )
	{
		c = result[i - j];
		result[i-j] = result[j];
		result[j] = c;
	}
}
