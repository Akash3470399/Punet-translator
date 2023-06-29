#include <stdio.h>
#include <string.h>

#include "../intr/tokenizer.h"
#include "../intr/helper.h"

int err = 0;


void check_is_valid_id()
{
	char str[32];
	enum token tok = next();
	if(tok == -1)
	{
		// cur_tok is from tokenizer file which store the current token string
		strcpy(str, cur_tok); 
		err |= !is_valid_id(str);
	}
	else
		err |= 1;
}

void check_is_same(enum token exp_tok)
{
	enum token inp_tok = next();
	err |= (exp_tok == inp_tok);
}

void check_commbox()
{
	check_is_same(COMMBOX);
	check_is_valid_id();
	check_is_same(SEMICOLON);
}

int main()
{
	tokenizer_config();
	check_commbox();
	printf("err :%d\n", err);
	return 0;
}
