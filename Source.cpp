
#include <iostream>
#include <stdio.h>

using namespace std;

struct ListNode
{
	char op = '\0';
	int number = 0;
	int priority = 0;
	bool nonTrivial = false;
	ListNode* next = nullptr;		
	ListNode* prev = nullptr;		
};

void addNode(ListNode*& head, ListNode*& tail, int num, char oper)
{
	ListNode* newNode = new ListNode;
	
	newNode->number = num;
	newNode->op = oper;

	if (head == nullptr) 
	{
		head = newNode;
		tail = newNode; 
	}
	else 
	{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode; 
	}
}

void addPriority(ListNode*& node, char oper)		
{
	int op = node->op;

	if (op == '+' || op == '-')
	{
		node->priority = 1;
	}
	else if (op == '*' || op == '/')
	{
		node->priority = 2;
	}
	else if (op == '!' || op == '@' || op == '#' || op == '$')
	{
		node->priority = 3;
	}
	else if (op == '(')
	{
		node->priority = 4;
	}
}

void nodeToNull(ListNode*& node)
{
	node->prev = nullptr;
	node->next = nullptr;
	node->number = 0;
	node->op = '\0';
	node->priority = 0;
	node = nullptr;
}

void deleteLastNode(ListNode*& head, ListNode*& tail)		
{
	ListNode* current = head;

	if (current == nullptr) 
	{
		return; 
	}

	if (current->next == nullptr) 
	{
		nodeToNull(current);
		current = nullptr;
		head = nullptr;
		tail = nullptr;
		return;
	}

	while (current->next != tail)
	{
		current = current->next;
	}

	 tail = nullptr;
	current->next->op = '\0';
	current->next->number = 0;
	current->next->priority = 0;
	current->next = nullptr;
	
	tail = current;
}

void deleteNode(ListNode*& head, ListNode*& tail, ListNode* nodeToDelete)
{
	if (nodeToDelete == nullptr || head == nullptr)
	{
		return; 
	}

	if (nodeToDelete == head)
	{
		if (head->next != nullptr)
		{
			head = head->next; 
			head->prev = nullptr; 
		}
		else
		{
			head = nullptr;
			tail = nullptr;
		}
		nodeToDelete = nullptr; 
	}
	else if (nodeToDelete == tail)
	{
		tail = tail->prev; 
		tail->next = nullptr; 
		nodeToDelete = nullptr; 
	}
	else
	{
		nodeToDelete->prev->next = nodeToDelete->next; 
		nodeToDelete->next->prev = nodeToDelete->prev; 
		nodeToDelete = nullptr; 
	}
}

void checkPrevPriority(ListNode*& stackHead, ListNode*& stackTail, ListNode*& outputHead, ListNode*& outputTail, bool& deleted)
{
	if (stackTail->prev != nullptr && outputTail->prev != nullptr)
	{
		if (stackTail->prev->priority >= stackTail->priority)
		{
			if (stackTail->prev->op != '(')
			{
				addNode(outputHead, outputTail, NULL, stackTail->prev->op);
				ListNode* prevNode = stackTail->prev->prev;

				deleteNode(stackHead, stackTail, stackTail->prev);
				deleted = true;
				stackTail->prev = prevNode;
			}
		}
	}
}

void addNum(ListNode*& cntNode, ListNode*& stackTail)
{ 
	bool weAreDone = false;
	ListNode* current = stackTail;

	while (weAreDone != true)
	{
		if (cntNode->op == current->op )	
		{
			current->number = cntNode->number;
			weAreDone = true;
		}
		current = current->prev;
	}
}

int CharToInt(char* string, int end) 
{
	int p = 1;
	int res = 0;

	for (int i = end; i > 0; i--) 
	{
		res += (int(string[i - 1]) - 48) * p;
		p *= 10;
	}
	return res;
}

void printOperators(char op, int num)
{
	if (op == '!')
	{
		cout << 'N' << ' ';
	}
	else if (op == '@')
	{
		cout << "IF" << ' ';
	}
	else if (op == '#')
	{
		cout << "MAX"<< num << ' ';
	}
	else if (op == '$')
	{
		cout << "MIN"<< num << ' ';
	}
	else
	{
		cout << op << ' ';
	}
}

void checkIfNegationIsLast(ListNode*& stackHead, ListNode*& stackTail, ListNode*& outputHead, ListNode*& outputTail)	
{
	ListNode* curr = stackTail;				

	if (curr != nullptr && curr->op == '!')
	{
		addNode(outputHead, outputTail, NULL, stackTail->op);
		deleteLastNode(stackHead, stackTail);
	}
	
}

void deleteList(ListNode*& head, ListNode*& tail)
{
	ListNode *current = tail, *temp = nullptr;
	while (current != nullptr)
	{
		temp = current->prev;
		deleteLastNode(head, tail);
		current = temp;
	}
}

void alterOutput(ListNode*& head, ListNode*& tail, bool& error)
{
	int max = 0, min = -1, ifRes = 0, res = 0, numArgs = 0;
	ListNode* curr = tail->prev->prev;
	numArgs = tail->number;
	bool notDeleted = false;

	if (tail->op == '#')							//MAX
	{
		for (int i = 1; i < numArgs; i++)
		{
			if (curr->next != nullptr)
			{
				if (curr->number > max)
				{
					max = curr->number;
					
				}
			}
			curr = curr->prev;
		}
		deleteNode(head, tail, tail);

		curr = tail;
		while (curr->prev != nullptr )
		{
			if (numArgs > 0)
			{
				if (curr->number != max)
				{
					deleteNode(head, tail, curr);
				}
				
			}
			else 
			{
				return;
			}
			curr = curr->prev;
			numArgs--;
		}
	}
	else if (tail->op == '$')							//MIN
	{	
		min = tail->prev->number;
		for (int i = 1; i < numArgs; i++)
		{
			if (curr->next != nullptr)
			{
				if (curr->number < min)
				{
					min = curr->number;
				}
			}
			curr = curr->prev;
		}
		
		deleteLastNode(head, tail);

		curr = tail;
		while (curr != nullptr)
		{
			if (numArgs > 0)
			{
				if (curr->number != min)
				{
					deleteNode(head, tail, curr);
				}
			}
			else
			{
				return;
			}
			curr = curr->prev;
			numArgs--;
		}
	}
	else if (tail->op == '!')									// N
	{
		tail->prev->number = tail->prev->number * (-1);
		deleteLastNode(head, tail);
	}
	else if (tail->op == '@')									//IF
	{
		if (tail->prev->prev->prev->number > 0)
		{
			ifRes = tail->prev->prev->number;	
		}
		else
		{
			ifRes = tail->prev->number;		
		}
		deleteLastNode(head, tail);

		curr = tail;
		for (int i = 0; i < 3; i++)
		{
			if (curr != nullptr)
			{
				if (curr->number != ifRes)
				{
					deleteNode(head, tail, curr);
				}
				else
				{
					if (notDeleted)
					{
						deleteNode(head, tail, curr);
					}
					notDeleted = true;
				}
			}
			curr = curr->prev;
		}
	}
	else if (tail->op == '+')
	{
		deleteLastNode(head, tail);		
		res = tail->number + tail->prev->number;
		deleteLastNode(head, tail);		
		deleteLastNode(head, tail);		
		addNode(head, tail, res, NULL);
	}
	else if (tail->op == '-')
	{
		deleteLastNode(head, tail);		
		res = tail->prev->number - tail->number;
		deleteLastNode(head, tail);		
		deleteLastNode(head, tail);		
		addNode(head, tail, res, NULL);
	}
	else if (tail->op == '*')
	{
		deleteLastNode(head, tail);
		res = tail->prev->number * tail->number;
		deleteLastNode(head, tail);
		deleteLastNode(head, tail);
		addNode(head, tail, res, NULL);
	}
	else if (tail->op == '/')
	{
		deleteLastNode(head, tail);
		if (tail->number != 0)
		{
			res = tail->prev->number / tail->number;
			deleteLastNode(head, tail);
			deleteLastNode(head, tail);
			addNode(head, tail, res, NULL);
		}
		else
		{
			deleteList(head, tail);
			cout << "ERROR";
			error = true;
		}
	}

}

int main()
{

	/*	N -- !
	*   IF -- @
	*   MAX -- #
	*   MIN -- $
	*/  

	ListNode* stackHead = nullptr, *stackTail = nullptr;
	ListNode* outputHead = nullptr, *outputTail = nullptr;
	ListNode* countingHead = nullptr, * countingTail = nullptr;
	
	ListNode* current = nullptr, *curr1 = nullptr,  *temp = nullptr, *traverse = nullptr;
	char lineFragment[10];
	int n;
	bool number = false, operation = false, basicOperation = false, operLastInStack = false, minMaxLast = false, operCounting = false, /*parOpened = false*/ comma = false, deletedFromStack = false, error = false, lastChunkCounted = false;
																
	char c, operToChar, charOp;
	int end = 0, opBetween = 0, parOpened = 0;		

	cin >> n;

	for (int i = 0; i < n; i++) 
	{
		cout << endl;
		c = getchar();

		while (c != '.') 
		{
			if (c >= 48 && c <= 57)								// numbers
			{
				lineFragment[end] = c;
				end++;
				number = true;
			}
			else if (c >= 65 && c <= 90)						//alfabet
			{
				lineFragment[end] = c;
				end++;
				operation = true;
			}
			else if (c == 40)									// (
			{
				addNode(stackHead, stackTail, NULL, c);
				addPriority(stackTail, c);
				parOpened++;
			}
			else if (c == 41)									//)
			{	
				if (minMaxLast && countingTail != nullptr)		
				{
					countingTail->number++;
					addNum(countingTail, stackTail);
					deleteLastNode(countingHead, countingTail);
				}
				

				curr1 = stackTail;

				while (curr1 != nullptr && curr1->op != '(')		
				{
					temp = curr1->prev;
					addNode(outputHead, outputTail, stackTail->number, stackTail->op);
					deleteLastNode(stackHead, stackTail);
					curr1 = temp;
					if (opBetween > 0)				
					{
						opBetween--;
					}
				}
				deleteLastNode(stackHead, stackTail);		//deleting (
				if (stackTail != nullptr &&  stackTail->nonTrivial == true &&  stackTail->op != '(')	//tu wystarczy 2 warunek?			
				{
					addNode(outputHead, outputTail, stackTail->number, stackTail->op);		
					deleteLastNode(stackHead, stackTail);	
				}
				checkIfNegationIsLast(stackHead, stackTail, outputHead, outputTail);
				
				parOpened--;		
				if (parOpened == 0)
				{
					opBetween = 0;
				}
			}								
			else if (c >= 42 && c < 44 || c > 44 && c <= 47)		//operators
			{
				charOp = c;
				basicOperation = true;
			}
			else if (c == 44)										// ,		
			{
				if (opBetween > 0)		
				{
					if (stackTail != nullptr && stackTail->op != '(')
					{
						current = stackTail;
						for (int i = 0; i < opBetween; i++)
						{
							addNode(outputHead, outputTail, current->number, current->op);
							deleteLastNode(stackHead, stackTail);
							current = current->prev;
						}
						opBetween = 0;
					}
				}
				
				if (countingHead != nullptr )
				{
					countingTail->number++;
				}
				lastChunkCounted = false;
				comma = true;
			}
			else if (c == ' ')
			{
				if (operation)		
				{
					if (end == 1)						//N
					{
						operToChar = '!';
					}
					else if (end == 2)					// IF
					{
						operToChar = '@';
						operLastInStack = true;							
						
					}
					else if (end == 3)
					{
						if (lineFragment[2] == 'X')
						{
							operToChar = '#';			// MAX
						}
						else
						{
							operToChar = '$';			// MIN
						}
					}
					addNode(stackHead, stackTail, NULL, operToChar);
					addPriority(stackTail, operToChar);
					stackTail->nonTrivial = true;
					
					if (operToChar!='!')
					{
						addNode(countingHead, countingTail, NULL, operToChar);		
						minMaxLast = true;
						operLastInStack = true;		
					}
					operation = false;
				}
				else if (basicOperation)
				{
					deletedFromStack = false;
					addNode(stackHead, stackTail, NULL, charOp);
					addPriority(stackTail, charOp);
					checkPrevPriority(stackHead, stackTail, outputHead, outputTail, deletedFromStack);
					
					if (parOpened>0 || comma)			
					{
						opBetween++;
					}

					if (deletedFromStack)		
					{
						opBetween--;
						checkPrevPriority(stackHead, stackTail, outputHead, outputTail, deletedFromStack);
					}
					basicOperation = false;
					operLastInStack = false;
				}
				else if (number)
				{
					addNode(outputHead, outputTail, CharToInt(lineFragment, end), NULL);	
					checkIfNegationIsLast(stackHead, stackTail, outputHead, outputTail);
					number = false;
				}

				for (int i = 0; i < end; i++)
				{
					lineFragment[i] = 0;
				}
				
				end = 0;
			}
			c = getchar();		
		}

		current = stackTail;					
		while (current != nullptr)
		{
			temp = current->prev;
			
			addNode(outputHead, outputTail, current->number, current->op);
			deleteLastNode(stackHead, stackTail); 
			current = temp;
		}

		current = outputHead;					
		while (current != nullptr)
		{
			if (current->op == NULL)
			{
				cout << current->number << " ";
			}
			else if (current->op != NULL)
			{
				printOperators(current->op, current->number);
			}
			current = current->next;
		}
		cout << endl;

		ListNode *nextOutputHead = nullptr, *nextOutputTail = nullptr, *lastOper = nullptr;				
		lastOper = outputHead;
		traverse = outputHead;
		while (traverse != nullptr && error == false)
		{
			while (traverse->op == '\0')
			{
				addNode(nextOutputHead, nextOutputTail, traverse->number, NULL);		
				traverse = traverse->next;
			} 
			addNode(nextOutputHead, nextOutputTail, traverse->number, traverse->op);
			lastOper = traverse;

			current = nextOutputTail;
			while (current != nullptr)				
			{
				if (current->op == NULL)
				{
					cout << current->number << " ";
				}
				else if (current->op != NULL)
				{
					printOperators(current->op, current->number);
				}
				current = current->prev;
			}
			cout << endl;

			alterOutput(nextOutputHead, nextOutputTail, error);
			traverse = lastOper->next;

		}
		error = false;
		
		current = nextOutputHead;
		while (current != nullptr)
		{
			cout << current->number;
			current = current->next;
		}

		deleteList(outputHead, outputTail);
	}

	return 0;
}
