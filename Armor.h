#include<string>
#include <semaphore.h>
class Armor
{
	
public:

    int id;
	std::mutex mutex;
    bool have = false;
};
