//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll)
{
	/* add your code here */
	if (ll == NULL || ll->head == NULL)	// 
		return;

	ListNode *cur = ll->head; 	// cur는 현재 노드를 저장하는 포인터. 처음에는 head로 초기화함.
	ListNode *prev = NULL;		// cur의 이전 노드를 저장하는 포인터. 처음에는 cur이 head이므로 prev는 NULL로 초기화함.
	ListNode *tail = ll->head;	// tail이 어딘지 저장하는 포인터. 그런데 아직 tail이 어디인지 모르니까 일단 head로 초기화함.
	ListNode *nxt;				// 다음 칸을 저장할 포인터!
	int count = ll->size;		// 리스트의 원래 길이를 저장함. 왜냐구,,? 홀수인 노드들을 뒤로 옮길 때, 리스트 모양이 바뀌게 됨. 근데, 우리는 옮긴 홀수는 안보고, 원래 노드들만 한 번씩 보고싶으.ㅁ
	// 현재 tail 노드 찾기.
	// 
	while (tail->next != NULL) {	// 다음칸이 있니? (다음 칸이 없을 때 까지 반복.)
		tail = tail->next;			// 있으면 tail을 다음 칸으로 이동해. 
	}

	// 원래 길이만큼만 반복해서 볼거임!, 근데, 뒤로 옮긴 홀수는 안 볼거임!
    for (int i = 0; i < count; i++)
    {	
		// cur을 다음칸으로 움직이거나, 뗄수도 있으니깐,, 미리 정보를 저장해두는 것!
		// 만약 지금 7이고, 다음이 4면, 7을 떼내야 하는데, 4의 정보가 사라지면 그 리스트는 실종..하게 됨.
		// 나라는 변수를 통해서 현재 노드의 다음 주소를 기억하고 있겠다. cur너는 사라져도 괜찮아
        nxt = cur->next;

        // 홀수이면 tail로 이동
        if (cur->item % 2 != 0) {
            if (prev == NULL)		// prev가 null이다? cur이 맨 앞 노드라는 뜻.
                ll->head = nxt;	// 맨 앞 노드(cur)를 떼어내면 리스트의 시작점이 바껴야 함.
            else					// cur이 맨 앞 노드가 아닌 경우
                prev->next = nxt;	// prev가 현재 노드(cur)의 앞이고, next가 현재 노드의 뒷칸이니깐..
									// cur을 떼었을 때, prev와 next가 연결되도록 해주는 것!
									
            tail->next = cur;		// tail의 다음 칸이 cur이 되도록 함. 너 맨 뒤로 가버려!
            cur->next = NULL;		// 새로 붙어버린 cur의 다음 칸을 NULL로 만들어서 너는 맨 뒤 노드다! 라고 해주는 것.
            tail = cur;				// tail이 cur이 되도록 함. 왜냐면, cur이 맨 뒤로 갔으니까, 이제 tail은 cur이야~~
            cur = nxt;				// 홀수를 옮겼으니깐.. 이제 아까 기억해둔 다음 칸인 NEXT로 가서 또 검사해라...
        } else {					// 짝수면..
            prev = cur;				// prev는 cur이 되도록 함. 왜냐면, 짝수는 그대로 있으니까, prev도 같이 이동해주는 것!
            cur = nxt;				// cur을 다음 칸으로 이동해. 왜냐면, 짝수는 그대로 있으니까, 다음 칸으로 이동해서 또 검사해라...
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
