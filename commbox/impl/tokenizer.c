#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "../intr/tokenizer.h"
#include "../intr/helper.h"



int tokenizeing_fd = -2;
char *cur_tok;

// function return corresponding enum value of a tokne string
// return -1 if string is not valid keyword.
enum token str_to_enum(char *tok_str)
{
	int i = 0, j = 0, token_id = -1;
	char **str_arrs[] = {
		keywords_arr, types_arr, paren_arr, cmp_ops_arr, logical_ops_arr, spcl_ops, NULL
	};

	while(token_id == -1 && (str_arrs[i] != NULL))
	{
		j = 0; 
		while(token_id == -1 && (str_arrs[i][j] != NULL))
		{
			if(strcmp(tok_str, str_arrs[i][j]) == 0)
				token_id = (100 * i) + j;
			j += 1;
		}
		i += 1;
	}
	if(token_id == -1 && (is_number(tok_str) == 1)) token_id = NUMERIC;
	else if(token_id == -1 && (is_valid_id(tok_str) == 1)) token_id = ID; 
	return token_id;
}

// function read content from file & saperate it as token string
// & return token (enum) value 
// also store the token sting in cur_tok
enum token next()
{

	char delimiters1[] = {
		';', ',', '[', ']', '(', ')', '\0'
	};

	char delimeters2[] = {
		'=', '>', '<', ':', '\0'
	};

	char ch;
	int found = 0, len = 0, tok_type1 = -1, tok_type2 = -1, token_id = -1;

	while(found == 0 && (read(tokenizeing_fd, &ch, 1) != 0))
	{
		if(len > 0 && is_space(ch))
			found = 1;
		else if(is_present(ch, delimiters1))
		{
			tok_type1 = 1;
			found = 1;
		}
		else if(is_present(ch, delimeters2))
			tok_type1 = 2;
		else if(!is_space(ch)) 
			tok_type1 = 3;
	
		if(!is_space(ch) && (tok_type2 == -1 || (tok_type1 == tok_type2)))
			cur_tok[len++] = ch;
		else if(len > 0)
		{
			found = 1;
			lseek(tokenizeing_fd, -1, SEEK_CUR);
		}
		
		tok_type2 = tok_type1;
	}
	
	if(len > 0)
	{
		cur_tok[len] = '\0'; 
		token_id = str_to_enum(cur_tok);	
	}
	else cur_tok = NULL;

	return token_id;
}

void go_back()
{
	lseek(tokenizeing_fd, -1*strlen(cur_tok), SEEK_CUR);
}

// hadels file to tokenize
void tokenizer_config()
{
	char tok_filename[128];

	printf("Enter file name :");
	scanf("%s", tok_filename);

	if((tokenizeing_fd = open(tok_filename, O_RDONLY)) == -1)
		printf("Invalid filename!!!\n");
	else
		cur_tok = (char *)malloc(sizeof(char) * 32);
}

// print tokens read from file
// print as (tok_enum_value tok_string)
//
void print_tokens()
{
	int pos = 0;
	if(tokenizeing_fd == -2)
		tokenizer_config();	
	else
		pos = lseek(tokenizeing_fd, 0, SEEK_SET);
	
	enum token tok = next();
	while(cur_tok != NULL)
	{
		printf("%d\t%s\n", tok, cur_tok);
		tok = next();
	}
	lseek(tokenizeing_fd, pos, SEEK_SET);
}

