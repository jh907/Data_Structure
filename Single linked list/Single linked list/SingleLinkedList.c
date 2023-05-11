#include <stdio.h>

typedef struct NODE {
	
	int nData;

	struct NODE* next;

} NODE;


int main() {

	NODE list[5] = { 0 };

	list[0].next = &list[1];
	list[1].next = &list[2];
	list[2].next = &list[3];
	list[3].next = &list[4];
	list[4].next = 0;

	list[0].nData = 100;
	list[1].nData = 200;
	list[2].nData = 300;
	list[3].nData = 400;
	list[4].nData = 500;

	for (int i = 0; i < 5; i++)
		printf("list[%d] : %d\n", i, list[i].nData);

	NODE* pTmp = &list[0];
	while (pTmp != 0) {
		printf("%p : %p\n", pTmp, pTmp->next);
		pTmp = pTmp->next;
	}

	return 0;
}


