#include"String.h"
void main()
{
	int i, j;
	Status k;
	char s, c[MAX_STR_LEN + 1];
	SString t, s1, s2;
	printf("请输入串s1: ");
	gets_s(c);
	k = StrAssign(s1, c);
	if (!k)
	{
		printf("串长超过MAX_STR_LEN(=%d)\n", MAX_STR_LEN);
		exit(EXIT_FAILURE);
	}
	printf("串长为%d,串空否?%d(1 是 0 否)\n", Strlength(s1), StrEmpty(s1));
	StrCopy(s2, s1);
	printf("赋值s1生成的串为");
	StrPrint(s2);
	printf("请输入串s2: ");
	gets_s(c);
	StrAssign(s2, c);
	i = StrCompare(s1, s2);
	if (i < 0)
		s = '<';
	else
		s = '>';
	printf("串s1 %c串s2\n", s);
	k = Concat(t, s1, s2);
	printf("串s1连接串s2得到的串t为");
	StrPrint(t);
	if (k == false)
		printf("串t有截断\n");
	ClearString(s1);
	printf("清为空串后，串s1为");
	StrPrint(s1);
	printf("串长为%d,空串否？(1 是 0 否)]\n", Strlength(s1), StrEmpty(s1));
}