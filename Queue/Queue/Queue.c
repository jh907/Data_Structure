#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE {
	char szData[64];

	struct NODE* next;

} NODE;
//���� ���
NODE g_pHead = { 0 };

void PrintList() {
	NODE* pTmp = g_pHead.next;
	while (pTmp != 0) {
		printf("[%p] %s, next[%p]\n",
			pTmp, pTmp->szData, pTmp->next);
		pTmp = pTmp->next;
	}
	printf("\n");
}

//���� ��� �� ��� �߰� �Լ�.
int InsertAtHead(char* pszData) {
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	if (g_pHead.next == 0) {
		g_pHead.next = pNode;
	}
	else {
		pNode->next = g_pHead.next;
		g_pHead.next = pNode;
	}
	return 1;
}

//���� ��� �� ��� �߰� �Լ�.
int InsertAtTail(char* pszData) {
	NODE* pTmp = &g_pHead;
	while (pTmp->next != 0) {
		pTmp = pTmp->next;
	}

	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	pTmp->next = pNode;

	return 1;
}

//��� ���� �Լ�.

//��ü ��� ���� �Լ�.
void ReleaseNode() {
	printf("\nReleaseList()\n");
	NODE* pTmp = g_pHead.next;
	while (pTmp != 0) {
		NODE* pDelete = pTmp;
		pTmp = pTmp->next;

		printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
		free(pDelete);
	}
	//�������� ������尡 �ΰ��� ������ ���� ������ �� ����.
	g_pHead.next = 0;
	printf("\n\n");
}

NODE* FindData(char* pszData) {
	NODE* pTmp = g_pHead.next;
	NODE* pPrev = &g_pHead;

	while (pTmp != 0) {
		if (strcmp(pTmp->szData, pszData) == 0) {
			return pPrev;
		}
		pTmp = pTmp->next;
		pPrev = pPrev->next;
	}
	return 0;
}

int DeleteData(char* pszData) {
	NODE* pPrev = FindData(pszData);
	if (pPrev != 0) {
		NODE* pDelete = pPrev->next;
		pPrev->next = pDelete->next;

		printf("DeleteDate() [%p] %s\n", pDelete, pDelete->szData);
		free(pDelete);
		return 1;
	}

	return 0;
}

void PushData(char* pszData) {
	InsertAtHead(pszData);
}

int PopData(NODE* pPopNode) {

	NODE* sp = g_pHead.next;
	if (g_pHead.next == 0) {
		return 0;
	}

	memcpy(pPopNode, sp, sizeof(NODE));

	g_pHead.next = sp->next;
	free(sp);

	return 1;
}

int EnQueue(char* pszData) {
	return InsertAtTail(pszData);
}

int Dequeue(NODE* pPopNode) {
	return PopData(pPopNode);
}

int main() {

	//Queue �׽�Ʈ�� ���� �ڵ�
	EnQueue("Test01");
	EnQueue("Test02");
	EnQueue("Test03");

	PrintList();

	NODE node = { 0 };
	Dequeue(&node);
	printf("Dequeue: %s\n", node.szData);
	PrintList();

	Dequeue(&node);
	printf("Dequeue: %s\n", node.szData);
	PrintList();

	Dequeue(&node);
	printf("Dequeue: %s\n", node.szData);
	PrintList();

	if (Dequeue(&node) == 0) {
		puts("Empty");
	}

	ReleaseNode();

	return 0;
}