//---------------------STACKS FUNCTIONS
//STACK* createStack()
//NODE* createNode(void* dataPtr)
//int isEmpty(STACK* stackPtr)
//void pushStack(STACK* stackPtr, void* dataPtr)
//void* popStack(STACK* stackPtr)
//void destroyStack(STACK* stackPtr)

typedef struct nodeStruct{
    void* dataPtr;
    struct nodeStruct* link;
} NODE;

typedef struct stackStruct{
    int count;
    NODE* top;
} STACK;

STACK* createStack(){
    STACK* stackPtr;
    stackPtr = (STACK*) malloc(sizeof(STACK));
    stackPtr->count = 0;
    stackPtr->top = NULL;
    return stackPtr;
}

int isEmpty(STACK* stackPtr){
    if (stackPtr->count <= 0){
        return 1;
    } else {
        return -1;
    }
}

NODE* createNode(void* dataPtr){
    NODE* node;
    node = (NODE*) malloc(sizeof(NODE));
    node->link = NULL;
    node->dataPtr = dataPtr;
    return node;
}

void pushStack(STACK* stackPtr, void* dataPtr){
    NODE* newNode;
    newNode = createNode(dataPtr);
    newNode->link = stackPtr->top;
    stackPtr->top = newNode;
    stackPtr->count++;
}

void* popStack(STACK* stackPtr){
    NODE* popedNode;
    void* dataPtr;

    if (isEmpty(stackPtr) != 1){
        popedNode = stackPtr->top;
        dataPtr = popedNode->dataPtr;
        stackPtr->top = popedNode->link;
        stackPtr->count--;
        free(popedNode);
        return dataPtr;
    } else {
        return NULL;
    }
}

void destroyStack(STACK* stackPtr){
    NODE* node;
    while(stackPtr->top){
        node = stackPtr->top;
        stackPtr->top = node->link;
        free(node->dataPtr);
        free(node);
    }
    free(stackPtr);
}
