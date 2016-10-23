// EX6_08.CPP
// A program to implement a calculator

#include <stdio.h>  // For input/output
#include <stdlib.h>	// For the exit() function
#include <ctype.h>  // For the isdigit() function
#include <string.h> // For the strcpy() function
#include <math.h>

void eatspaces(char * str);					// Function to eliminate blanks
double expr(char * str);					// Function evaluating an expression
double term(char * str, int * pindex);	    // Function analyzing a term
double number(char * str, int * pindex);    // Function to recognize a number
char * extract(char * str, int * index);    // Function to extract a substring
double mfunc(char * str, int * pindex);
double mswitch(int t,char * str, int * pindex);
double mlog(char * str, int * pindex);

const int MAX = 80;			// Maximum expression length including '\0'

int main(void)
{
    system("TITLE Wallace'sCalculator");
    system("mode con cols=50 lines=35");
    system("color B0");
	char buffer[MAX];		// Input area for expression to be evaluated
	char c;
	int i;

	printf("Welcome to the calculator adapted by Wallace.\n");
	printf("Enter an expression, or an empty line to quit.\n\n");

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

		printf( "\t= %f\n\n",expr(buffer));		// Output value of expression
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


// Function to get the value of a term
double term(char * str, int * pindex)
{
	double value = 0;					// Somewhere to accumulate the result

	value = number(str, pindex);		// Get the first number in the term

    if(islower(*(str+(*pindex)))||isupper((*(str+(*pindex)))))
        value*=mfunc(str,pindex);

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
	 }
	 return value;						 // We've finished, so return what we've got
}


// Function to recognize a number in a string
double number(char * str, int * pindex)
{
	double value = 0.0;						// Store the resulting value

	char * psubstr;                         // Pointer for substring
	if(*(str + (*pindex)) == '(')           // Start of parentheses
    {
        ++(*pindex);
        psubstr = extract(str, pindex);     // Extract substring in brackets
        value = expr(psubstr);              // Get the value of the substring
        return value;                       // Return substring value
    }

    if(islower(*(str+(*pindex)))||isupper((*(str+(*pindex)))))
        value+=mfunc(str,pindex);

	while(isdigit(*(str+(*pindex))))		// Loop accumulating leading digits
		value=10*value + (*(str+(*pindex)++) - 48);

											// Not a digit when we get to here
    while((*(str+(*pindex))=='^')||(*(str+(*pindex))=='%')||(*(str+(*pindex))=='!'))
    {
        if(*(str+(*pindex))=='!')
            {
                ++(*pindex);
                int t=floor(value),i=1;
                for(;i<t;i++)
                {
                    value*=i;
                }
            }

        if(*(str+(*pindex))=='^')
            {
                ++(*pindex);
                value=powf(value,number(str, pindex));
            }

        if(*(str+(*pindex))=='%')
            {
                ++(*pindex);
                value=(int)value%(int) number(str, pindex);
            }

    }
	if(*(str+(*pindex))!='.')				// so check for decimal point
		return value;						// and if not, return value

	double factor = 1.0;					// Factor for decimal places
 	while(isdigit(*(str+(++(*pindex)))))	// Loop as long as we have digits
	{
		factor *= 0.1;								 // Decrease factor by factor of 10
		value=value + (*(str+(*pindex))-48)*factor;	 // Add decimal place
	}

	return value;										 // On loop exit we are done
}

// Function to extract a substring between parentheses
// (requires string.h)
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
                        printf("Memory allocation failed, program terminated.") ;
                        exit(1);
                    }
                    strcpy(pstr, buffer);   // Copy substring to new memory
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
    exit(1);
}

double mfunc(char * str, int * pindex)
{
    char buffer[MAX];
    char fname[16][5] = {{'s','i','n','h'},{'c','o','s','h'},{'t','a','n','h'},{'a','s','i','n'},{'a','c','o','s'},{'a','t','a','n'},{'s','q','r','t'},{'a','b','s'},{'l','g'},{'l','o','g'},{'l','n'},{'s','i','n'},{'c','o','s'},{'t','a','n'},{'c','e','i','l'},{'f','l','o','o','r'}};
    int mcorres[16]={4,4,4,4,4,4,4,3,2,3,2,3,3,3,4,5};
    int bufindex = *pindex;
    int i=0,j=0,k=0,t;
    while(islower(*(str+(*pindex)))||isupper(*(str+(*pindex))))
    {
         if(isupper(*(str+(*pindex))))
            (*(str+(*pindex)))+=32;
         buffer[(*pindex) - bufindex] = *(str + (*pindex));
         ++(*pindex);
    }
    buffer[(*pindex) - bufindex]='\0';
    for (i = 0; i <= 15; i++)
        {
            for(j=0;j<=mcorres[i]-1;j++)
            {
                if (buffer[j] == fname[i][j])
                    {
                        k++;
                        if(k==mcorres[i])
                            {
                                t=i;
                                return mswitch(t,str,pindex);
                            }
                    }
            }
            k=0;
        }
    printf("Syntax error\n");
    exit(1);
}

double mswitch(int t,char * str, int * pindex)
{
            switch(t)
                {
                    case 0 :return sinh(number(str,pindex));
                    case 1 :return cosh(number(str,pindex));
                    case 2 :return tanh(number(str,pindex));
                    case 3 :return asin(number(str,pindex));
                    case 4 :return acos(number(str,pindex));
                    case 5 :return atan(number(str,pindex));
                    case 6 :return sqrt(number(str,pindex));
                    case 7 :return fabs(number(str,pindex));
                    case 8 :return log10(number(str,pindex));
                    case 9 :return mlog(str,pindex);
                    case 10 :return log(number(str,pindex));
                    case 11 :return sin(number(str,pindex));
                    case 12 :return cos(number(str,pindex));
                    case 13 :return tan(number(str,pindex));
                    case 14 :return ceil(number(str,pindex));
                    case 15 :return floor(number(str,pindex));
                    default:
                        {
                            printf("Syntax error.\n");
                            exit(1);
                        }
                }
}

//The log(a,b) function in mathmatics
double mlog(char * str, int * pindex)
{
    double a,b;
    if(*(str + (*pindex))=='(')
    {
        ++(*pindex);
        a=number(str,pindex);
        if(*(str + (*pindex))==',')
        {
            ++(*pindex);
            b=number(str,pindex);
            if(*(str + (*pindex))==')')
                ++(*pindex);
            else
            {
                printf("Syntax error.\n");
                exit(1);
            }
            return log(b)/log(a);
        }
        else
        {
            printf("Syntax error.\n");
            exit(1);
        }
    }
    else
    {
        printf("Syntax error.\n");
        exit(1);
    }
}

