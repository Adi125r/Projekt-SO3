#include<string>
class Shoes
{
	
public:

	int id;
	std::mutex mutex;
	bool have = false;
};
