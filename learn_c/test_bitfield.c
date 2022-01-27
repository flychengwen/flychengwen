#include <stdio.h>
#include <string.h>

/************************************************
 sizeof(struct st_aaa) = 4  sizeof(struct st_bbb) = 4

 sizeof(struct st_ccc) = 4   .a=5 .b=4 .c=3
 ccc:  .a=-1 .b=-2 .c=-3
 ddd:  .a=15 .b=14 .c=13
 *************************************************/

int main()
{
	struct st_aaa{
		int a:1;
		int b:1;
		int c:1;
	};

	struct st_bbb{
		int a:1,
		    b:1,
		    c:1;
	};
	
	printf("sizeof(struct st_aaa) = %ld  sizeof(struct st_bbb) = %ld\n",
			sizeof(struct st_aaa),   sizeof(struct st_bbb));

	struct st_ccc{
		int a:4,
		    b:4;
		int c:4;
	}ccc;

	ccc.a = 5;
	ccc.b = 4;
	ccc.c = 3;
	printf("\nsizeof(struct st_ccc) = %ld   .a=%d .b=%d .c=%d\n",
			sizeof(struct st_ccc),  ccc.a, ccc.b, ccc.c);

	memset(&ccc, 0, sizeof(ccc));
	ccc.a=15;
	ccc.b=14;
	ccc.c=13;
	printf("ccc:  .a=%d .b=%d .c=%d\n", ccc.a, ccc.b, ccc.c);


	struct st_ddd{
		unsigned int a:4,
		             b:4;
		unsigned int c:4;
	}ddd;
	ddd.a=15;
	ddd.b=14;
	ddd.c=13;
	printf("ddd:  .a=%d .b=%d .c=%d\n", ddd.a, ddd.b, ddd.c);
	return 0;
}
