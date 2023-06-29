#include <stdio.h>

// check if ch is a valid alphabate
int is_alpha(char ch)
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

// check if ch is valid numeric digit
int is_digit(char ch)
{
	return (ch >= '0' && ch <= '9');
}


// check if str is valid identifier
int is_valid_id(char *str)
{
	int result = 1, i = 0;
	if(str[i] == '_' || is_alpha(str[i]))
	{
		i += 1;
		while((result == 1) && (str[i] != '\0'))
		{
			result = (is_alpha(str[i]) || is_digit(str[i]) || str[i] == '_');  
			i += 1;
		}
	}
	else result = 0;
	return result;
}
// return 1 if ch is a space char else 0
int is_space(char ch)
{
        return (ch == ' ' || ch == '\n' || ch == '\t');
}

// check if ch is present in charSeq char array.
// charSeq is char array & at the end it have '\0' char
int is_present(char ch, char charSeq[])
{
        int i = 0, result = 0;
        while(charSeq[i] != '\0' && (result == 0))
        {
                if(ch == charSeq[i])
                       result = 1;
                i += 1;
        }
        return result;
}
