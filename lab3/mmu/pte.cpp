#ifndef PTE
#define PTE 
using namespace std;

struct pte
{
	unsigned int present:1;
	unsigned int modified:1;
	unsigned int referenced:1;
	unsigned int pagedout:1;
	unsigned int pageFrameNum:6;
};

#endif