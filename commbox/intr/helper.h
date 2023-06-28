#include <stdio.h>
#ifndef HELPER_H
#define HELPER_H

char *keywords_arr[] = {
	"commbox", "const", "var", "integer", "boolean", "address", "begin", "if", "then", 
	"fi", "for", "in", "do", "od", "activate", "with", "timeout", "send", "to", "recv",
        "from", "end", "true", "false", NULL	
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
	"|", ",", ";", ":=", ">>>", NULL
};


#endif
