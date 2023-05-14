#include <stdio.h>
#include <string.h>
#include <malloc.h>

//데이터와 다음 노드를 가르키는 포인터를 담고 있는 노드 구조체 생성.
typedef struct NODE {

	char szData[64];

	struct NODE* next;

} NODE;

//연결 리스트를 관리할 포인터 생성.
NODE* g_pHead = NULL;

/*
연결 리스트 전체 데이터 출력
(출력 결과 : [현재 노드의 주소] 데이터, next[현재 노드가 가르키고 있는 다음 노드의 주소]
g_pHead->next는 다음 노드의 주소를 가지고 있다.
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
char 데이터를 입력 받아서 새로운 pNode를 생성하고 성공 or 실패 (1 or 0) 반환.
메모리 초기화
strcpy_s 복사 될 메모리의 크기를 적어줌으로서 메모리가 넘치는 버그 방지.
*/
int InsertNewNode(char* pszData) {
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE)); 
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData); 

	/*
	pNode값이 추가 될 위치 선정.
	pNode->next(New Node)가 기존 NODE의 주소를 가리키게 하고, g_pHead는 pNode(New Node)를 가르키게 하면 된다. 순서를 바꾸게 되면 Data 유실.
	*/
	if (g_pHead == NULL)
		g_pHead = pNode;
	else {
		pNode->next = g_pHead;
		g_pHead = pNode;
	}

	return 1;
}

//리스트 삭제 함수
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
	//List 테스트를 위한 코드
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
* 출력 결과가 다음과 같이 거꾸로 보이는 이유는,
* 기존 노드의 앞에 새 노드를 추가 하기 때문이다.
[0000021F623C5340] Test01, next[0000000000000000]

[0000021F623C35D0] Test02, next[0000021F623C5340]
[0000021F623C5340] Test01, next[0000000000000000]

[0000021F623CCF50] Test03, next[0000021F623C35D0]
[0000021F623C35D0] Test02, next[0000021F623C5340]
[0000021F623C5340] Test01, next[0000000000000000]
*/