#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE {

	char szData[64];

	struct NODE* prev;
	struct NODE* next;

} NODE;

NODE* g_pHead;
NODE* g_pTail;
int g_nSize;


//ÃÊ±âÈ­
void InitList(void) {
	g_pHead = (NODE*)malloc(sizeof(NODE));
	g_pTail = (NODE*)malloc(sizeof(NODE));

	g_nSize = 0;
	memset(g_pHead, 0, sizeof(NODE));
	memset(g_pTail, 0, sizeof(NODE));

	strcpy_s(g_pHead->szData, sizeof(g_pHead->szData), "DUMMY HEAD");
	strcpy_s(g_pTail->szData, sizeof(g_pTail->szData), "DUMMY TAIL");

	g_pHead->next = g_pTail;
	g_pTail->prev = g_pHead;
}

void ReleaseList(void) {
	NODE* pTmp = g_pHead;

	while (pTmp != NULL) {
		NODE* pDelete = pTmp;
		pTmp = pTmp->next;

		printf("free(%p)\n", pDelete);
		free(pDelete);
	}

	g_pHead = NULL;
	g_pTail = NULL;
	g_nSize = 0;
	puts("ReleaseList()");
}

void PrintList(void) {
	int i = 0;
	printf("PrintList(): g_nSize: %d, g_pHead [%p], g_pTail [%p]\n", g_nSize, g_pHead, g_pTail);
	NODE* pTmp = g_pHead;
	while (pTmp != NULL) {
		if (pTmp == g_pHead || pTmp == g_pTail) {
			printf("[%p] %p, %s [%p]\n", pTmp->prev, pTmp, pTmp->szData, pTmp->next);
		}
		else {
			printf("Index:%d [%p] %p, %s [%p]\n", i, pTmp->prev, pTmp, pTmp->szData, pTmp->next);
			++i;
		}
		pTmp = pTmp->next;
	}
	printf("\n");
}

int InsertAtHead(const char* pszData) {
	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	memset(pNewNode, 0, sizeof(NODE));
	strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);

	pNewNode->next = g_pHead->next;
	pNewNode->prev = g_pHead;

	g_pHead->next = pNewNode;
	pNewNode->next->prev = pNewNode;

	g_nSize++;
	return g_nSize;
}

int InsertAtTail(const char* pszData) {
	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	memset(pNewNode, 0, sizeof(NODE));
	strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);

	pNewNode->next = g_pTail;
	pNewNode->prev = g_pTail->prev;

	g_pTail->prev = pNewNode;
	pNewNode->prev->next = pNewNode;

	g_nSize++;
	return g_nSize;
}

NODE* FindNode(const char* pszData) {
	NODE* pTmp = g_pHead->next;
	while (pTmp != g_pTail) {
		if (strcmp(pTmp->szData, pszData) == 0) {
			return pTmp;
		}
		pTmp = pTmp->next;
	}
	return NULL;
}

int DeleteNode(const char* pszData) {

	NODE* pNode = FindNode(pszData);

	pNode->prev->next = pNode->next;
	pNode->next->prev = pNode->prev;

	free(pNode);
	g_nSize--;
	printf("DeleteNode(): [%p]\n", pNode);
	return 0;
}

int GetSize(void) {
	return g_nSize;
}

int GetLength(void) {


	return GetSize();
}

int IsEmpty(void) {


	return GetSize();
}

void InsertBefore(NODE* pDstNode, const char* pszData) {
	NODE* pPrev = pDstNode->prev;

	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	memset(pNewNode, 0, sizeof(NODE));
	strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);

	pNewNode->prev = pDstNode->prev;
	pNewNode->next = pDstNode;

	pDstNode->prev = pNewNode;
	pPrev->next = pNewNode;

	g_nSize++;
}

int InsertAt(int idx, const char* pszData) {
	int i = 0;
	NODE* pTmp = g_pHead->next;
	while (pTmp != g_pTail) {
		if (i == idx) {
			InsertBefore(pTmp, pszData);
			return i;
		}
		pTmp = pTmp->next;
		++i;
	}
	InsertAtTail(pszData);
	return i;
}

NODE* GetAt(int idx) {
	int i = 0;
	NODE* pTmp = g_pHead->next;
	while (pTmp != g_pTail) {
		if (i == idx) {
			return pTmp;
		}
		pTmp = pTmp->next;
		++i;
	}

	return NULL;
}


int main() {

	InitList();

	InsertAtTail("Test01");
	InsertAtTail("Test02");
	InsertAtTail("Test03");

	InsertAt(0, "Test At 00");
	PrintList();

	InsertAt(2, "Test At 02");
	PrintList();

	InsertAt(4, "Test At 04");
	PrintList();

	InsertAt(10, "Test At 10");
	PrintList();

	NODE* pNode = GetAt(0);
	if (pNode)
		printf("GetAt(%d): %s\n", 0, pNode->szData);
	else
		printf("GetAt(%d): %s\n", 0, "Not Found");

	pNode = GetAt(3);
	if (pNode)
		printf("GetAt(%d): %s\n", 3, pNode->szData);
	else
		printf("GetAt(%d): %s\n", 3, "Not Found");

	pNode = GetAt(6);
	if (pNode)
		printf("GetAt(%d): %s\n", 6, pNode->szData);
	else
		printf("GetAt(%d): %s\n", 6, "Not Found");

	pNode = GetAt(7);
	if (pNode)
		printf("GetAt(%d): %s\n", 7, pNode->szData);
	else
		printf("GetAt(%d): %s\n", 7, "Not Found");

	DeleteNode("Test01");
	DeleteNode("Test02");
	DeleteNode("Test03");

	PrintList();
	ReleaseList();

	return 0;
}