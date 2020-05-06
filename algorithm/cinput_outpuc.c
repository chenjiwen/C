#ifdef __cplusplus
extern "C"
{
	void char_input_out();
	void word_count();
}
#endif // __cplusplus

#include<stdio.h>

void char_input_out()
{
	int c, prev = 0;
	int ns = 0, nt = 0, nl = 0;

	while ((c = getchar()) != EOF)
	{
		if (c == '\t') {
			++nt;
			putchar('\\');
			putchar('t');
			prev = '\t';
			continue;
		}
		else if (c == ' ') {
			if (prev == c) {
				continue;
			}
			++ns;
			putchar(c);
		}
		else if (c == '\n') {
			++nl;
			putchar(c);
		}	
		else if (c == '\b')
		{
			putchar('\\');
			putchar('b');
		}
		else if (c == '\\')
		{
			putchar('\\');
			putchar('\\');
		}
		else {
			putchar(c);
		}

		prev = c;
	}

	printf("space count:%d\n", ns);
	printf("table count:%d\n", nt);
	printf("line count:%d\n", nl);
}

int word_count(){
	int nw = 0;
	int c, prev = -1;

	while (c = getchar())
	{
		if (c == '\n' || c == ' ' || c == '\t' || c == EOF) {
			if ((prev <= 'Z' && prev >= 'A') || ((prev <= 'z') && prev >= 'a')) {
				nw++;
				putchar('\n');
			}


			if (c == EOF)
				break;
		}
		else {
			putchar(c);
		}
		prev = c;
	}

	return nw;
}