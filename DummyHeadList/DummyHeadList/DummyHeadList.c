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
	printf("\nReleaseList\n");
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

int FindData(char* pszData) {
	NODE* pTmp = g_pHead.next;

	while (pTmp->next != 0) {
		if (strcmp(pTmp->szData, pszData) == 0) {
			printf("FindData(): [%p] %s\n", pTmp, pTmp->szData);
			return 1;
		}
		pTmp = pTmp->next;
	}
	return 0;
}

int DeleteData(char* pszData) {
	NODE* pTmp = g_pHead.next;
	NODE* pPrev = &g_pHead;
	while (pTmp != 0) {
		if (strcmp(pTmp->szData, pszData) == 0) {
			printf("DeleteData(): [%p] %s\n", pTmp, pTmp->szData);
			pPrev->next = pTmp->next;
			free(pTmp);
			return 1;
		}
		pTmp = pTmp->next;
		pPrev = pPrev->next;
	}
	return 0;
}

int main() {
	//��� �ٷ� �� �߰�
	InsertAtHead("Test01");
	PrintList();

	InsertAtHead("Test02");
	PrintList();

	InsertAtHead("Test03");
	PrintList();

	ReleaseNode();

	//�� �κп��� �߰�.
	InsertAtTail("Test01");
	PrintList();

	InsertAtTail("Test02");
	PrintList();

	InsertAtTail("Test03");
	PrintList();

	//������ ã��
	FindData("Test01");

	//������ ã�Ƽ� ����
	DeleteData("Test01");
	PrintList();


	return 0;
}