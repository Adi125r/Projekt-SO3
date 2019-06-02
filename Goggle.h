#include<string>
class Goggle
{

public:

	int id;
	std::mutex mutex;
    bool have = false;
	
};
