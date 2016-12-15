// EX6_08.CPP
// A program to implement a calculator

#include <stdio.h>  // For input/output
#include <stdlib.h>	// For the exit() function
#include <ctype.h>  // For the isdigit() function
#include <string.h>  // For the strcpy() function
#include<math.h>
#define PI 3.1415926
void eatspaces(char * str);					// Function to eliminate blanks
double expr(char * str);					// Function evaluating an expression
double term(char * str, int * pindex);	    // Function analyzing a term
double number(char * str, int * pindex);    // Function to recognize a number
double log_func(char *str,int *pindex);
char * extract(char * str, int * pindex);    // Function to extract a substring
double jie_cheng(double value);
double func_2(char * str, int * pindex);
const int MAX = 80;			// Maximum expression length including '\0'

int main(void)
{
	char buffer[MAX];		// Input area for expression to be evaluated
	char c;
	int i;

	printf("Welcome to your friendly calculator.\n");
	printf("Enter an expression, or an empty line to quit.\n");

	for(;;)
	{
		i=0;
		scanf("%c",&c); // Read an input line
		while(c!='\n')
        {
            buffer[i++]=c;
            scanf("%c",&c);
		}
		buffer[i]='\0';

		eatspaces(buffer);						// Remove blanks from input

		if(!buffer[0])							// Empty line ends calculator
			 return 0;

		printf( "\t= %f\n\n",expr(buffer));
		                                        // Output value of expression
	}
}


// Function to eliminate blanks from a string
void eatspaces(char * str)
{
	int i=0;				 // 'Copy to' index to string
	int j=0;				 // 'Copy from' index to string

	while((*(str+i) = *(str+j++)) != '\0')	 // Loop while character copied is not \0
		if(*(str+i) != ' ')					 // Increment i as long as
			 i++;							 //	character is not a blank
	return;
}


// Function to evaluate an arithmetic expression
double expr(char * str)
{
	double value = 0;					// Store result here
	int index = 0;						// Keeps track of current character position

	value = term(str, &index);	        // Get first term

	for(;;)								// Infinite loop, all exits inside
	{
		switch(*(str+index++))	        // Choose action based on current character
		{
			 case '\0':					// We're at the end of the string
				return value;			//	so return what we have got

			 case '+':							// + found so add in the
				value += term(str, &index);		//	next term
				break;

			 case '-':							// - found so subtract
				value -= term(str, &index);		//	the next term
				break;

			 default:											 // If we reach here the string
				printf("Arrrgh!*#!! There's an error.\n");
				exit(1);
        }
	 }
}
double func_2(char * str, int * pindex )
{
    double value=0;
    if(*(str+(*pindex))=='s')
      {      (*pindex)++;
            if((*(str+(*pindex)++)=='i')&&(*(str+(*pindex)++)=='n'))
            {value+=sin(number(str,pindex)*PI/180);}
      }
    if(*(str+(*pindex))=='c')
       {    (*pindex)++;
            if((*(str+(*pindex)++)=='o')&&(*(str+(*pindex)++)=='s'))
            {value+=cos(number(str,pindex)*PI/180);}
        }
    if(*(str+(*pindex))=='t')
        {     (*pindex)++;
             if((*(str+(*pindex)++)=='a')&&(*(str+(*pindex)++)=='n'))
             {value+=tan(number(str,pindex)*PI/180);}
        }
    if(*(str+(*pindex))=='a')
      {     (*pindex)++;
            if(*(str+(*pindex))=='s')
            {   (*pindex)++;
               if((*(str+(*pindex)++)=='i')&&(*(str+(*pindex)++)=='n'))
            {   value+=asin(number(str,pindex));}
            }

            if(*(str+(*pindex))=='c')
            {   (*pindex)++;
               if((*(str+(*pindex)++)=='o')&&(*(str+(*pindex)++)=='s'))
            {   value+=acos(number(str,pindex));}
            }

            if(*(str+(*pindex))=='t')
            {   (*pindex)++;
               if((*(str+(*pindex)++)=='a')&&(*(str+(*pindex)++)=='n'))
            {   value+=asin(number(str,pindex));}
            }
      }

    if(*(str+(*pindex))=='l')
        {       (*pindex)++;
                if(*(str+(*pindex))=='n'){
                (*pindex)++;value+=log(number(str,pindex));}

                if(*(str+(*pindex)++)=='o')
                if(*(str+(*pindex)++)=='g')
                {value+=log_func(str,pindex);}
        }

    if(*(str+(*pindex))=='e')
        {       (*pindex)++;
                if(*(str+(*pindex)++)=='^')
                value+=exp(number(str,pindex));
        }
return value;
}

// Function to get the value of a term
double term(char * str, int * pindex)
{
	double value = 0;					// Somewhere to accumulate the result
	value = number(str, pindex);
	if((*(str+(*pindex)))>='a'&&(*(str+(*pindex)))<='z')
        value=func_2(str,pindex);
    // Loop as long as we have a good operator
	while((*(str+(*pindex))=='*')||(*(str+(*pindex))=='/'))
	{

		if(*(str+(*pindex))=='*')					// If it's multiply,
        {
            ++(*pindex);
			 value *= number(str, pindex);			//	multiply by next number
        }

		if(*(str+(*pindex))=='/')					// If it's divide,
        {
            ++(*pindex);
			 value /= number(str, pindex);			//	divide by next number
        }
        			                        //	divide by next number
	 }
	 return value;						 // We've finished, so return what we've got
}


// Function to recognize a number in a string
double number(char * str, int * pindex)
{
	double value = 0.0;						// Store the resulting value
    char * psubstr;                          // Pointer for substringreturn
    if((*(str+(*pindex)))>='a'&&(*(str+(*pindex)))<='z')
        value=func_2(str,pindex);
	if(*(str + (*pindex)) == '(')           // Start of parentheses
    {
        ++(*pindex);
        psubstr = extract(str, pindex);     // Extract substring in brackets
        value = expr(psubstr);
        if(*(str+(*pindex))=='^')          // so check for decimal point
	{
	    (*pindex)++;
	value=pow(value,number(str,pindex));}              // Get the value of the substring
        if(*(str+(*pindex))=='!')          // so check for decimal point
	{
	    (*pindex)++;
	value=jie_cheng(value);}              // Get the value of the substring// Return substring value
    return value;
    }                      // Return substring value

    while(isdigit(*(str+(*pindex))))		// Loop accumulating leading digits
		value=10*value + (*(str+(*pindex)++) - 48);
                                                    // Not a digit when we get to here
	if(*(str+(*pindex))=='^')          // so check for decimal point
	{
	    (*pindex)++;
	value=pow(value,number(str,pindex));
		return value;
	}
	if(*(str+(*pindex))=='!')          // so check for decimal point
	{
	    (*pindex)++;
	value=jie_cheng(value);
		return value;
	}										// and if not, return value
    if(*(str+(*pindex))=='.')
	{
	    double factor = 1.0;					// Factor for decimal places

 	while(isdigit(*(str+(++(*pindex)))))	// Loop as long as we have digits
	{
		factor *= 0.1;								 // Decrease factor by factor of 10
		value=value +(*(str+(*pindex))-48)*factor;	 	 // Add decimal place
	}
	}
	return value;										 // On loop exit we are done
}
double jie_cheng(double value)
{
    double a=1,i=0;
    for(i=1;i<=value;i++)
        a*=i;
    return a;
}
                                                           // Loop accumulating leading digits
double log_func(char *str,int *pindex)
{
    double a=0.0,b=0.0,value=0.0;
    while(isdigit(*(str+(*pindex))))		// Loop accumulating leading digits
		a=10*a + (*(str+(*pindex)++)-48);
    if(*(str+(*pindex))=='(')
        {
          b=number(str, pindex);
          value=log(b)/log(a);
          return value;
        }
   value=log(a);
   return value;
}
char * extract(char * str, int * pindex)
{
    char buffer[MAX];           // Temporary space for substring
    char * pstr = NULL;         // Pointer to new string for return
    int numL = 0;               // Count of left parentheses found
    int bufindex = *pindex;     // Save starting value for index
    do
    {
        buffer[(*pindex) - bufindex] = *(str + (*pindex));
        switch(buffer[(*pindex) - bufindex])
        {
            case ')':
                if(numL == 0)
                {
                    buffer[(*pindex) - bufindex] = '\0';    // Replace ')' with '\0'
                    ++(*pindex);
                    pstr = (char *) malloc((*pindex) - bufindex + 1);
                    if (!pstr)
                    {
                        printf("Memory allocation failed, program terminated.");
                        exit(1);
                    }
                    strcpy(pstr,buffer);   // Copy substring to new memory
                    return pstr;            // Return substring in new memory
                }
                else
                    numL--;     // Reduce count of '(' to be matched
                break;
            case '(':
                    numL++;     // Increase count of '(' to be // matched
                    break;
        }
    } while(*(str + (*pindex)++) != '\0');      // Loop - don't overrun end of string
    printf("Ran off the end of the expression, must be bad input.\n");
    exit(1); }
