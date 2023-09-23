#include "revert_string.h"

void RevertString(char *str) {
	if (*str == '\0') return;
	char* iter = str;
	// unsigned len = 0;
	while (*(++iter) != '\0');
	--iter;	
	// char* reversedString = malloc(sizeof(char)*++len);
	// iter -= 2;
	// for (str = reversedString + len; str != reversedString;) {
	// 	*str-- = *iter--;
	// }
	while (iter - str > 1) {
		char tmp;
		tmp = *iter;
		*iter = *str;
		*str = tmp;
		++iter; --str;
	}	
}

