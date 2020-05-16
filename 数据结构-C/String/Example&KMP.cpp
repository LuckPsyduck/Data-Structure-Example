#include"String3.h"
void main()
{
	int i, *p;
	SString s1, s2;
	StrAssign(s1, "aaabaaaab");
	printf("主串为: ");
	
	StrPrint(s1);
	StrAssign(s2, "aaaab");

	printf("子串为: ");
	StrPrint(s2);
	p = (int *)malloc((Strlength(s2) + 1) * sizeof(int));
	get_next(s2, p);
	printf("子串的next数组为");
	for (i = 1; i <= Strlength(s2); i++)
		printf("%2d", *(p + i));
	printf("\n");
	i = Index_KMP(s1, s2, 1, p);
	if (i)
		printf("主串和子串在第%d个字符处首次匹配\n", i);
	else
		printf("主串和子串匹配不成功!");

	get_nextval(s2, p);
	printf("主串的nextval数组为");
	for (i = 1; i <= Strlength(s2); i++)
		printf("%2d", *(p + i));
	printf("\n");
	printf("主串和子串在%d个字符串首次匹配\n", Index_KMP(s1, s2, 1, p));
}