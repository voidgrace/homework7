/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h); //

/* note: freeList는 싱글포인터를 매개변수로 받음
- initialize와 왜 다른지 이해 할것
- 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h); //

int insertNode(headNode* h, int key); 	//노드삽입
int insertLast(headNode* h, int key);  	//뒤에 노드추가q
int insertFirst(headNode* h, int key); 	//앞에 노드 추가
int deleteNode(headNode* h, int key);  	//특정 노드삭제
int deleteLast(headNode* h);  			//뒤에 노드 삭제
int deleteFirst(headNode* h); 			//앞에 노드 삭제
int invertList(headNode* h); 			//노드 거꾸로나열

void printList(headNode* h);			//리스트 출력



int main()
{
	char command;
	int key;
	headNode* headnode=NULL;//헤드노드를 가리키는 포인터 headnode 선언
	printf("[----- [강은혜] [2022041047] -----]\n");
	do{
		
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);//z
			
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));
	
	
	(*h)->first = NULL;//헤드 노드를 비움
	return 1;
}
/* h와 연결된 listNode 메모리 해제
 * headNode도 해제되어야 함.
 */
int freeList(headNode* h){
	
	listNode* p = h->first;//첫노드 주소를 넘김

	listNode* prev = NULL;//전 노드 포인터 변수 선언

	while(p != NULL) {//오른쪽노드로 옮겨가며 노드 free
		prev = p;	  //prev의 현재노드의 위치를 넣고 p는 다음노드로 옮긴뒤 prev를 해제하는 방식
		p = p->rlink;
		free(prev);
	}
	free(h);//마지막으로 헤드프리
	return 0;
}

/*
리스트 출력
*/
void printList(headNode* h) {

	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {//헤드 노드가 비었을시
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //P에 첫노드 시작주소 할당

	while(p != NULL) {	//노드의 오른쪽으로 이동하며 해당 노드의 키값출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);//노드의 총 갯수 출력
}




/**
 * list끝에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));//추가할 노드 할당
	node->key = key;	//추가할 노드에 키 값 등 초기화
	node->rlink = NULL;	
	node->llink = NULL;

	if (h->first == NULL)//노드가 비어있으면 맨앞에 삽입
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->rlink != NULL) {//노드의 오른쪽 맨끝으로 이동
		n = n->rlink;
	}
	n->rlink = node;//맨끝노드의 오르쪽에 노드 삽입
	node->llink = n;
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //현재노드 포인터
	listNode* trail = NULL; //이전노드 포인터

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;
	free(n);

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//노드 초기화
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)	// 노드가 비었을 시
	{
		h->first = node;	// 헤드다음 노드에 삽입
		return 1;
	}

	node->rlink = h->first;	// 삽입노드의 오른쪽 링크에 원래 첫노드 주소 삽입
	node->llink = NULL;		// 삽입노드의 왼쪽 링크 NULL

	listNode *p = h->first;	// p에 기존 첫노드 주소 대입
	p->llink = node;		// p의 왼쪽에 노드링크
	h->first = node;		// h 삽입노드 연결

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;	// n에 첫번째 노드주소 대입
	h->first = n->rlink;	// 헤드가 두번째 노드를 포인트 

	free(n);//n(첫번째 노드) free

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;	//오른쪽에 있는 노드
	listNode *trail = NULL;	//왼쪽에 있는 노드 
	listNode *middle = NULL;//가운데 노드

	while(n != NULL){
		trail = middle;//노드이동
		middle = n;//middle을 오른쪽으로이동
		n = n->rlink;//n을 오른쪽으로 밀기
		middle->rlink = trail;//middle의 오른쪽에 trali
		middle->llink = n;//middle의 왼쪽에 n
	}

	h->first = middle;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)//헤드가 비었을 시 맨앞에 삽입
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;//node의 오른쪽에 n링크
				node->llink = n->llink;//노드의 왼쪽에 n의 이전노드 링크
				n->llink->rlink = node;//삽입한 링크 왼쪽의 노드 오른쪽 노드에 삽입링크 노드
			}
			return 0;
		}

		n = n->rlink;//다음노드 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;//n의 왼쪽에 있는 노드가 n의 다음노드를 포인트
				n->rlink->llink = n->llink;//n의 오른쪽에 있는 노드가 n의 왼쪽 노드를 포인트
				free(n);
			}
			return 1;
		}

		n = n->rlink;//다음노드 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


