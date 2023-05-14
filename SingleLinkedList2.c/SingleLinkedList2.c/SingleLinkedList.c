#include <stdio.h>
#include <string.h>
#include <malloc.h>

//�����Ϳ� ���� ��带 ����Ű�� �����͸� ��� �ִ� ��� ����ü ����.
typedef struct NODE {

	char szData[64];

	struct NODE* next;

} NODE;

//���� ����Ʈ�� ������ ������ ����.
NODE* g_pHead = NULL;

/*
���� ����Ʈ ��ü ������ ���
(��� ��� : [���� ����� �ּ�] ������, next[���� ��尡 ����Ű�� �ִ� ���� ����� �ּ�]
g_pHead->next�� ���� ����� �ּҸ� ������ �ִ�.
*/
void PrintList(void) {
	NODE* pHead = g_pHead;
	while (pHead != NULL) {
		printf("[%p] %s, next[%p]\n",
			pHead, pHead->szData, pHead->next); 
		pHead = pHead->next;
	}
	putchar('\n');
}

/*
char �����͸� �Է� �޾Ƽ� ���ο� pNode�� �����ϰ� ���� or ���� (1 or 0) ��ȯ.
�޸� �ʱ�ȭ
strcpy_s ���� �� �޸��� ũ�⸦ ���������μ� �޸𸮰� ��ġ�� ���� ����.
*/
int InsertNewNode(char* pszData) {
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE)); 
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData); 

	/*
	pNode���� �߰� �� ��ġ ����.
	pNode->next(New Node)�� ���� NODE�� �ּҸ� ����Ű�� �ϰ�, g_pHead�� pNode(New Node)�� ����Ű�� �ϸ� �ȴ�. ������ �ٲٰ� �Ǹ� Data ����.
	*/
	if (g_pHead == NULL)
		g_pHead = pNode;
	else {
		pNode->next = g_pHead;
		g_pHead = pNode;
	}

	return 1;
}

//����Ʈ ���� �Լ�
void ReleaseList() {
	NODE* pTmp = g_pHead;
	while (pTmp != NULL) {
		NODE* pDelete = pTmp;
		pTmp = pTmp->next;

		printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
		free(pDelete);
	}
}

int main() {
	//List �׽�Ʈ�� ���� �ڵ�
	InsertNewNode("Test01");
	PrintList();

	InsertNewNode("Test02");
	PrintList();

	InsertNewNode("Test03");
	PrintList();

	ReleaseList(); 
	return 0;
}

/*
* ��� ����� ������ ���� �Ųٷ� ���̴� ������,
* ���� ����� �տ� �� ��带 �߰� �ϱ� �����̴�.
[0000021F623C5340] Test01, next[0000000000000000]

[0000021F623C35D0] Test02, next[0000021F623C5340]
[0000021F623C5340] Test01, next[0000000000000000]

[0000021F623CCF50] Test03, next[0000021F623C35D0]
[0000021F623C35D0] Test02, next[0000021F623C5340]
[0000021F623C5340] Test01, next[0000000000000000]
*/