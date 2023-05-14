#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE {
	char szData[64];

	struct NODE* next;

} NODE;
//더미 헤드
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

//더미 헤드 뒤 노드 추가 함수.
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

//더미 헤드 끝 노드 추가 함수.
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

//노드 삭제 함수.

//전체 노드 삭제 함수.
void ReleaseNode() {
	printf("\nReleaseList\n");
	NODE* pTmp = g_pHead.next;
	while (pTmp != 0) {
		NODE* pDelete = pTmp;
		pTmp = pTmp->next;

		printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
		free(pDelete);
	}
	//마지막에 더미헤드가 널값을 가져야 재사용 가능할 것 같다.
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
	//헤드 바로 뒤 추가
	InsertAtHead("Test01");
	PrintList();

	InsertAtHead("Test02");
	PrintList();

	InsertAtHead("Test03");
	PrintList();

	ReleaseNode();

	//끝 부분에서 추가.
	InsertAtTail("Test01");
	PrintList();

	InsertAtTail("Test02");
	PrintList();

	InsertAtTail("Test03");
	PrintList();

	//데이터 찾기
	FindData("Test01");

	//데이터 찾아서 삭제
	DeleteData("Test01");
	PrintList();


	return 0;
}