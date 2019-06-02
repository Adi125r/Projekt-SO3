#include <atomic>
#include <chrono>
#include <mutex>
#include <random>
#include <thread>
#include <vector>
#include "Armor.h"
#include "Goggle.h"
#include "Helmet.h"
#include "Shoes.h"
#include "Bpoint1.h"
#include "Bpoint2.h"
#include "Bpoint3.h"
#include "Bpoint4.h"
#include "semaphore.h"
sem_t mutex;
class PlayerProblem {
public:
    std::array<Armor, 1> armors;
    std::array<Goggle, 1> goggles;
    std::array<Helmet, 1> helmets;
    std::array<Shoes, 1> shoes;
    std::array<Bpoint1, 1> bpoint1;
    std::array<Bpoint2, 1> bpoint2;
    std::array<Bpoint3, 1> bpoint3;
    std::array<Bpoint4, 1> bpoint4;
    PlayerProblem();
    std::atomic<bool> ready{false};
};

PlayerProblem::PlayerProblem() {}

class Player {
public:
    int id;
    PlayerProblem &table;
    Armor &armor;
    Goggle &goggle;
    Helmet &helmet;
    Shoes &shoes;
    Bpoint1 &bpoint1;
    Bpoint2 &bpoint2;
    Bpoint3 &bpoint3;
    Bpoint4 &bpoint4;
    bool haveArmor = false;
    bool haveGoggle = false;
    bool haveHelmet = false;
    bool haveShoes = false;
    bool zgoda = false;
    bool point1 = false;
    bool point2 = false;
    bool point3 = false;
    bool point4 = false;
    int po2 =0;
    int po3 =0;
    int po4 =0;
    std::thread t;
    std::mt19937 rng{std::random_device{}()};
    int state = -1;
    int progress = 0;
    int color = 1;
    int i =0;
    std::mutex mtx;
    
    bool exit = false;
    Player(int _id, PlayerProblem &table_ref, Armor &a, Goggle &g, Helmet &h, Shoes &s, Bpoint1 &bp1, Bpoint2 &bp2, Bpoint3 &bp3, Bpoint4 &bp4) : id(_id), table(table_ref), armor(a), goggle(g), helmet(h), shoes(s),bpoint1(bp1),bpoint2(bp2),bpoint3(bp3),bpoint4(bp4), t(&Player::live, this) {
sem_init(&bpoint1.sem1, 0, 2);
sem_init(&bpoint2.sem2, 0, 2);
sem_init(&bpoint3.sem3, 0, 2);
sem_init(&bpoint4.sem4, 0, 2);
}
    void live();
    void p1();
    void p2();
    void p3();
    void p4();
    void breakpoint1();
    void breakpoint2();
    void breakpoint3();
    void breakpoint4();

};
void Player::live() {

    while (!table.ready) {
        std::this_thread::yield();
    }

    while (!exit) {
std::this_thread::sleep_for(std::chrono::seconds(2));
        if(haveArmor == false){
       p1();
        i=1;
       state = 0;} 
        if(haveGoggle == false && i==1){
       p2();
       state = 0;}
         if(haveHelmet == false && i==1) {
       p3();
       state = 0; }
         if(haveShoes == false && i==1){
       p4();
        i=0;
       state = 5; }
std::this_thread::sleep_for(std::chrono::seconds(1));
       if(zgoda== true && point3 == false){
        breakpoint1();
        state =10;}
       if(zgoda== true && point1 == true && point3 == false) {
        breakpoint2();
        state =10;}
       if(zgoda== true && point2 == true && point3 == false) {
        breakpoint3();
        state = 10;}
if(zgoda== true && point3 == true && point4 == false) {
        breakpoint4();
        state =9;
        std::this_thread::sleep_for(std::chrono::seconds(1));    }
    }
    return;
}
void Player::p1() {
    
    armor.mutex.lock();
    
    state = 1;
    
    int part = std::uniform_int_distribution<int>(15, 25)(rng);
    
    for (auto i = 1; i <= part; i++) {

        double p = (double)i / (double)part;
        progress = std::round(p * 100);;
        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        if (exit) {
            armor.mutex.unlock();
            return;
        }
    }
   haveArmor = true; 
   armor.mutex.unlock();
}
void Player::p2() {
    goggle.mutex.lock();
   
    state = 2;
    
    int part = std::uniform_int_distribution<int>(15, 25)(rng);
    
    for (auto i = 1; i <= part; i++) {

        double p = (double)i / (double)part;
        progress = std::round(p * 100);;
        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        if (exit) {
            goggle.mutex.unlock();
            return;
        }
    }
haveGoggle = true;
goggle.mutex.unlock();
}
void Player::p3() {
    
    helmet.mutex.lock();

    state = 3;
    
    int part = std::uniform_int_distribution<int>(15, 25)(rng);
    
    for (auto i = 1; i <= part; i++) {

        double p = (double)i / (double)part;
        progress = std::round(p * 100);;
        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        if (exit) {
            helmet.mutex.unlock();
            return;
        }
    }
haveHelmet = true;
helmet.mutex.unlock();
}
void Player::p4() {
    
    shoes.mutex.lock();
    
    
    
    state = 4;
    
    int part = std::uniform_int_distribution<int>(15, 25)(rng);
    
    for (auto i = 1; i <= part; i++) {

        double p = (double)i / (double)part;
        progress = std::round(p * 100);;
        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        if (exit) {
            shoes.mutex.unlock();
            return;
        }
    }
haveShoes =true;
shoes.mutex.unlock();
}
void Player::breakpoint1() {
state=6;
 int part = rand() % 20 + 10;
  color = 2 ;  
    for (auto i = 1; i <= part; i++) {

        double p = (double)i / (double)part;
        progress = std::round(p * 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        if (exit) {
            
            return;
        }
    }
point1= true;
}
void Player::breakpoint2() {
sem_wait(&bpoint2.sem2);
state=7;
 int part = rand() % 20 + 10;
 color = 3;   
    for (auto i = 1; i <= part; i++) {

        double p = (double)i / (double)part;
        progress = std::round(p * 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        if (exit) {
            sem_post(&mutex);
            return;
        }
    }
point2= true;
sem_post(&bpoint2.sem2);
}
void Player::breakpoint3() {
sem_wait(&bpoint3.sem3);
state=8;
 int part = rand() % 20 + 10;
 color = 4 ;  
    for (auto i = 1; i <= part; i++) {

        double p = (double)i / (double)part;
        progress = std::round(p * 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        if (exit) {
            sem_post(&mutex);
            return;
        }
    }
point3= true;
sem_post(&bpoint3.sem3);
color = 5 ;
}
void Player::breakpoint4() {
sem_wait(&bpoint4.sem4);
state=11;
 int part = rand() % 20 + 10;
 color = 4 ;  
    for (auto i = 1; i <= part; i++) {

        double p = (double)i / (double)part;
        progress = std::round(p * 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        if (exit) {
            sem_post(&mutex);
            return;
        }
    }
point4= true;
sem_post(&bpoint4.sem4);
color = 5 ;
}

