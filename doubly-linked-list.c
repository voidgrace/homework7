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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ���� */
int initialize(headNode** h); //

/* note: freeList�� �̱������͸� �Ű������� ����
- initialize�� �� �ٸ��� ���� �Ұ�
- ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h); //

int insertNode(headNode* h, int key); 	//������
int insertLast(headNode* h, int key);  	//�ڿ� ����߰�q
int insertFirst(headNode* h, int key); 	//�տ� ��� �߰�
int deleteNode(headNode* h, int key);  	//Ư�� ������
int deleteLast(headNode* h);  			//�ڿ� ��� ����
int deleteFirst(headNode* h); 			//�տ� ��� ����
int invertList(headNode* h); 			//��� �Ųٷγ���

void printList(headNode* h);			//����Ʈ ���



int main()
{
	char command;
	int key;
	headNode* headnode=NULL;//����带 ����Ű�� ������ headnode ����
	printf("[----- [������] [2022041047] -----]\n");
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode));
	
	
	(*h)->first = NULL;//��� ��带 ���
	return 1;
}
/* h�� ����� listNode �޸� ����
 * headNode�� �����Ǿ�� ��.
 */
int freeList(headNode* h){
	
	listNode* p = h->first;//ù��� �ּҸ� �ѱ�

	listNode* prev = NULL;//�� ��� ������ ���� ����

	while(p != NULL) {//�����ʳ��� �Űܰ��� ��� free
		prev = p;	  //prev�� �������� ��ġ�� �ְ� p�� �������� �ű�� prev�� �����ϴ� ���
		p = p->rlink;
		free(prev);
	}
	free(h);//���������� �������
	return 0;
}

/*
����Ʈ ���
*/
void printList(headNode* h) {

	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {//��� ��尡 �������
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //P�� ù��� �����ּ� �Ҵ�

	while(p != NULL) {	//����� ���������� �̵��ϸ� �ش� ����� Ű�����
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);//����� �� ���� ���
}




/**
 * list���� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));//�߰��� ��� �Ҵ�
	node->key = key;	//�߰��� ��忡 Ű �� �� �ʱ�ȭ
	node->rlink = NULL;	
	node->llink = NULL;

	if (h->first == NULL)//��尡 ��������� �Ǿտ� ����
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->rlink != NULL) {//����� ������ �ǳ����� �̵�
		n = n->rlink;
	}
	n->rlink = node;//�ǳ������ �����ʿ� ��� ����
	node->llink = n;
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //������ ������
	listNode* trail = NULL; //������� ������

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL;
	free(n);

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//��� �ʱ�ȭ
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)	// ��尡 ����� ��
	{
		h->first = node;	// ������ ��忡 ����
		return 1;
	}

	node->rlink = h->first;	// ���Գ���� ������ ��ũ�� ���� ù��� �ּ� ����
	node->llink = NULL;		// ���Գ���� ���� ��ũ NULL

	listNode *p = h->first;	// p�� ���� ù��� �ּ� ����
	p->llink = node;		// p�� ���ʿ� ��帵ũ
	h->first = node;		// h ���Գ�� ����

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;	// n�� ù��° ����ּ� ����
	h->first = n->rlink;	// ��尡 �ι�° ��带 ����Ʈ 

	free(n);//n(ù��° ���) free

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;	//�����ʿ� �ִ� ���
	listNode *trail = NULL;	//���ʿ� �ִ� ��� 
	listNode *middle = NULL;//��� ���

	while(n != NULL){
		trail = middle;//����̵�
		middle = n;//middle�� �����������̵�
		n = n->rlink;//n�� ���������� �б�
		middle->rlink = trail;//middle�� �����ʿ� trali
		middle->llink = n;//middle�� ���ʿ� n
	}

	h->first = middle;

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)//��尡 ����� �� �Ǿտ� ����
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key >= key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				insertFirst(h, key);
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;//node�� �����ʿ� n��ũ
				node->llink = n->llink;//����� ���ʿ� n�� ������� ��ũ
				n->llink->rlink = node;//������ ��ũ ������ ��� ������ ��忡 ���Ը�ũ ���
			}
			return 0;
		}

		n = n->rlink;//������� �̵�
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
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
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h);
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;//n�� ���ʿ� �ִ� ��尡 n�� ������带 ����Ʈ
				n->rlink->llink = n->llink;//n�� �����ʿ� �ִ� ��尡 n�� ���� ��带 ����Ʈ
				free(n);
			}
			return 1;
		}

		n = n->rlink;//������� �̵�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


