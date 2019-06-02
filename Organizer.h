#include <atomic>
#include <chrono>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

class Organizer{
public: 
Player &plyer;


bool zgoda = false;
Organizer(){}
void live();


};
void Organizer::live() {

    while (!exit) {
      for (auto p : plyers) {
        if(p->haveArmor == true && p->haveGoggle == true && p->haveHelmet == true 
            && p->haveShoes == true){
            p->haveArmor =  false; 
            p->haveGoggle = false;
            p->haveHelmet = false; 
            p->haveShoes =  false;
            zgoda = true;
}
    }
    }
    return;
}
