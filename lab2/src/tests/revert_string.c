#include "revert_string.h"

void RevertString(char *str) {
	if (!str || *str == '\0') return;
	char* iter = str;
	while (*(++iter) != '\0');
	--iter;	
	for (; str < iter; ++str, --iter) {
		char tmp;
		tmp = *iter;
		*iter = *str;
		*str = tmp;
	}
}