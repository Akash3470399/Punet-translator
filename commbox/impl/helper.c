#include <stdio.h>
#include <string.h>

char *keywords_arr[] = {
	"commbox", "const", "var","begin", "if", "then", "fi", "for", 
	"in", "do", "od", "activate", "with", "timeout", "send", "to", "recv",
        "from", "end", "true", "false", NULL	
};

char *types_arr[] = {
 	"integer", "boolean", "address", NULL 
};

char *paren_arr[] = {
	"(", ")", "[", "]", NULL
};

char *cmp_ops_arr[] = {
	"<", ">", "==", "<=", ">=", NULL
};	

char *logical_ops_arr[] = {
	"and", "or", "not", NULL
};


char *spcl_ops[] = {
	"|", ",", ":", ";", ":=", "=", ">>>", NULL
};


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


int is_number(char *str)
{
	int i = 0, result = 1;
	while(result == 1 && str[i] != '\0')
	{
		if(!is_digit(str[i]))
			result = 0;
		i += 1;
	}
	return result;
}
// check if str is one of keywords.
int is_keyword(char *str)
{
	int i = 0, j = 0,  result = 0;
	char **str_arr[] = {
			keywords_arr, types_arr, logical_ops_arr, NULL
	};

	while(result == 0 && (str_arr[i] != NULL))
	{
		j = 0;
		while(result == 0 && (str_arr[i][j] != NULL))
		{
			if(strcmp(str, str_arr[i][j]) == 0)
				result = 1;
			j += 1;
		}
		i += 1;
	}
	return result;
}

// check if str is valid identifier
int is_valid_id(char *str)
{
	int result = 1, i = 0;
	if(!is_keyword(str) && (str[i] == '_' || is_alpha(str[i])))
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

int is_valid_type(char *str)
{
	int i = 0, result = 0;
	while(result == 0 && (types_arr[i] != NULL))
	{
		if(strcmp(types_arr[i], str) == 0)
			result = 1;
		i += 1;
	}
	return result;
}


