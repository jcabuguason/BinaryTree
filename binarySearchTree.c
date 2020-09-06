#include <stdio.h>
#include <stdlib.h>

//Create node objects for tree
typedef struct Node{
	int key;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
}node;


//declare methods
node* treeMinimum(node*current);
node* treeMaximum(node*current);
node* treeSuccessor(node* current);
node* treePredecessor(node* current);
node* treeSearch(node* current,int key);
void insertNode(node*z);
void deleteNode(node*z);										
node* createNode(int key);

//declare variables -- check what static means again
node* root = NULL;

int main(){
	
	int choice = 0;
	int keyForSearch = 0;
	int insertedKey;
	node* current;
	int running = 1;

	printf("Welcome to Binary Tree Application\n\n");
	
	while(running != 0){

		//reset loop 
		current = NULL;

		printf("\nWhat would you like to do?\n"
			"1. Create binary tree\n"
			"2. Find Maximum\n"
			"3. Find Minimum\n"
			"4. Find Successor\n"
			"5. Find Predecessor\n"
			"6. Delete Node\n"
			"7.Exit\n");

		printf(".. Enter an integer input:\n");

		scanf("%d",&choice);

		switch(choice){
			case 1:
				printf("Enter desired key(s) for binary tree. Exit with input = -1\n");
				scanf("%d",&insertedKey);
				while(insertedKey != -1){
					printf("insertedKey: %d \n",insertedKey);
					insertNode(createNode(insertedKey));
					scanf("%d",&insertedKey);
				}
				break;
			case 2:
				printf("Maximum of binary tree: %d\n", treeMaximum(root)->key);
				break;
			case 3:
				printf("Minimum of binary tree: %d\n", treeMinimum(root)->key);
				break;
			case 4: 
				printf("What node key would you like to find the succesor for?\n");
				scanf("%d",&keyForSearch);
				current = treeSearch(root,keyForSearch);
				if(current == NULL){
					printf("Search for node with key = %d not found!\n",keyForSearch);
				}
				else{
					printf("Successor of node with key = %d is node with key = %d\n",keyForSearch,treeSuccessor(current)->key );
				}
				break;
			case 5:
				printf("What node key would you like to find the predecessor for?\n");
				scanf("%d",&keyForSearch);
				current = treeSearch(root,keyForSearch);
				if(current == NULL){
					printf("ERROR: Search for node with key = %d not found!\n",keyForSearch);
				}
				else{
					printf("Predecessor of node with key = %d is node with key = %d\n",keyForSearch,treePredecessor(current)->key );
				}
				break;
			case 6:
				printf("Enter key of node you would like to delete:\n");
				scanf("%d",&keyForSearch);
				current = treeSearch(root,keyForSearch);
				if(current!= NULL){
					deleteNode(current);
					printf("Node with key = %d deleted successfully!",keyForSearch);
				}
				else
					printf("ERROR: Node with key = %d not found!\n",keyForSearch);
				break;
			case 7:
				running = 0;
				break;
		}	
	}

}



//finds minimum using binary tree property
node* treeMinimum(node* current){
	while(current->left != NULL){
		current = current-> left;
	}
	return current;
}

//find maximum using binary tree property
node* treeMaximum(node* current){
	while(current->right != NULL){
		current = current -> right;
	}
	return current; 
}

node* treeSuccessor(node* current){
	node* temp;

	if(current->right != NULL)
		return treeMinimum(current-> right);
	
	temp = current-> parent;
	
	while(temp != NULL && current == temp -> right){
		current = temp;
		temp = temp-> parent;
	}

	return temp;
}

//returns tree predecessor of passed node
node* treePredecessor(node* current){
	node* temp;

	if(current -> left != NULL)
		return treeMaximum(current->left);

	temp = current -> parent;
	while(temp != NULL && current == temp-> left){
		current = temp;
		temp = temp-> parent;
	}
	return temp;
}

//search tree and return node with value of var key
node* treeSearch(node* current,int key){	
	//if no binary tree
	if(current == NULL|| key == current->key){
		return current;
	}

	//recursively search top to bottom of binary tree
	if(key < current->key){
		return treeSearch(current->left,key);
	}else{
		return treeSearch(current->right,key);
	}
}


//insert node into given binary tree	
void insertNode(node* z){
	node *y = NULL;
	node *x = root;//node1

	while(x != NULL){
		y = x;
		if(z->key < x->key){
			x = x-> left;
		}
		else{
			x = x ->right;
		}
	}

	z->parent = y;

	if(y == NULL){
		root = z;
	}
	else if(z->key < y->key){
		y->left = z;
	}
	else{
		y->right = z;
	}

}


void deleteNode(node* nodeToDelete){
	node* x = NULL;
	node* y = NULL;
	
	if(nodeToDelete->left == NULL || nodeToDelete->right == NULL)
		y = nodeToDelete;
	else
		y = treeSuccessor(nodeToDelete);

	if(y->left != NULL)
		x = y->left;
	else
		x = y->right;

	if(x!= NULL)
		x->parent = y->parent;
	
	if(y->parent == NULL)
		root = x;
	else if(y == y->parent->left)
		y->parent->left = x;
	else 
		y->parent->right = x;

	if(y != nodeToDelete)
		nodeToDelete->key = y->key;

}

//create binary tree node
node* createNode(int key){
	node* newNode = (node*)malloc(sizeof(node));

	if(newNode == NULL){
		printf("Memory not allocated.\n");
		return 0;
	}

	newNode -> key =  key;
	newNode -> left = NULL;
	newNode -> right = NULL;
	newNode -> parent = NULL;
	return newNode;
}
