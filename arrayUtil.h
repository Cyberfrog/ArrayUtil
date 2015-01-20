typedef struct arrayUtil ArrayUtil;
typedef char * byte;
typedef int (MatchFunc)(void* hint, void* item);
struct arrayUtil{
	void *base;
	int typeSize;
	int length;
};

int areEqual(ArrayUtil a, ArrayUtil b);
ArrayUtil create(int typeSize, int length);
ArrayUtil resize(ArrayUtil util, int length); 
int findIndex(ArrayUtil util, void* element);
void dispose(ArrayUtil util);
void* findFirst(ArrayUtil util, MatchFunc* match, void* hint);
void* findLast(ArrayUtil util, MatchFunc* match, void* hint);
int count(ArrayUtil util, MatchFunc* match, void* hint);
int filter(ArrayUtil util, MatchFunc* match, void* hint, void** destination, int maxItems );
