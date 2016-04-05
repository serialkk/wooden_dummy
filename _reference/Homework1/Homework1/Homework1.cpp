#include <cstdio>
#include <cstdlib>
#include <cstring>


char* StringToAttach(char* str1, char* str2)
{
	int iDestSize = strlen(str1);
	int iSrcSize = strlen(str2);
	char *pStrReturn = (char*)malloc(iDestSize + iSrcSize + 1);

	strcpy(pStrReturn, str1);
	pStrReturn += iDestSize;

	strcpy(pStrReturn, str2);
	pStrReturn -= iDestSize;
	return pStrReturn;
}

char* new_strtok(char* str1, char* str2);

char* new_strlwr(char* str1);

int new_strcmp(char* str1, char* str2);


void main()
{
	char *str1, str2[10];
	str1 = (char*)malloc(sizeof(char) * 100);

	/*
	printf("\========= ���ڿ� ����      ===========\n");
	*/
	strcpy(str1, "KGCA game academy -17-");
	strncpy(str2, "KGCA Game Academy", 4);
	str2[4] = 0;

	printf("\========= ���ڿ� ����/�� ===========\n");
	printf("str1 Length: %u\n", strlen(str1));
	printf("str2 Length: %u\n", strlen(str2));
	printf("str1 Length: %d\n", new_strcmp(str1, str2));
	printf("str1 Length: %d\n", new_strcmp(str2, str1));

	
	printf("\========= ���ڿ� ��ȯ      ===========\n");
	printf("str1 Small Letter: %s\n", new_strlwr(str1));
	printf("str1 Default: %s\n", str1);



	printf("\========= ���ڿ� �и�      ===========\n");
	char * pch;
	printf("Splitting string \"%s\" into tokens:\n", str1);
	pch = new_strtok(str1, " ,.-");
	//pch = new_strtok(str1, "-");
	while (pch != NULL)
	{
		printf("%s\n", pch);
		pch = new_strtok(NULL, " ,.-");
	}

	free(str1);
}




//���ڿ����� ��ū�� ã�Ƴ���.
char *new_strtok(char *src, char *sep)
{
	static char *next = NULL;
	static int next_len;
	static int next_count;

	char *start = NULL;

	int i;

	if (src) {
		next = src;
		next_len = strlen(next);
		next_count = 0;
	}

	start = next;

	while (*next) {
		for (i = 0; i < strlen(sep); i++) {
			if (*next == *(sep + i)) {
				if (next == start) {
					start++;
					continue;
				}
				*next = 0;
				next++;
				next_count++;
				return start;
			}
		}
		next++;
		next_count++;
	}

	if (next_len == next_count++) return start;
	return NULL;
}

//�빮�ڸ� �ҹ��ڷ� �����Ѵ�.
char* new_strlwr(char* str1)
{
	char *strtemp;
	strtemp = (char*)malloc(sizeof(char)*strlen(str1));
	strcpy(strtemp, str1);
	int i = 0;


	for (i = 0; i < strlen(strtemp); i++)
	{
		if(*(strtemp +i) >= 65 && *(strtemp+i) <=90)
		  *(strtemp + i) += 32;
	}
	return strtemp;
}

//�� ���� ���ڿ��� ��� ���Ѵ�
int new_strcmp(char* str1, char* str2)
{
	int i = 0, j = 0, result = 0;

	while (*(str1 + i) != '\0')
	{
		//printf("str1 i: %d, str2 j: %d\n", *(str1 + i), *(str2 + j));
		if (str1[i++] != str2[j++])
			break;
	}

	result = (*(str1 + i) - *(str2 + j));

	if (result > 0)
		return 1;
	else if (result < 0)
		return -1;
	else
		return 0;

}