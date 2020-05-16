#include"String.h"
void main()
{
	int i;
	char c, *p = "God bye!", *q = "God luck!";
	HString t, s, r;

	InitString(t);
	InitString(s);
	InitString(r);

	StrAssign(t, p);
	printf("串t为：");
	StrPrint(t);

	printf("串长为%d,串空否?%d(1 空 0 否)\n", StrLength(t), StrEmpty(t));
	StrAssign(s, q);
	printf("串s为：");
	StrPrint(s);
	i = StrCompare(s, t);
	if (i < 0)
		c = '<';
	else if (i == 0)
		c = '=';
	else
		c = '>';
	printf("串s %c 串t\n", c);
	Concat(r, t,s);
	printf("串t连接串s产生的串r为：\n");
	StrPrint(r);
}