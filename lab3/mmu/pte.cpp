#ifndef PTE_CPP
#define PTE_CPP 

using namespace std;

struct Pte
{
	unsigned int present:1;
	unsigned int modified:1;
	unsigned int referenced:1;
	unsigned int pagedOut:1;
	unsigned int pageFrameNum:6;
};

#endif
