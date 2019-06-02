#include <iostream>
#include <map>
#include "ncurses.h"
#include <curses.h>
#include <thread>
#include <vector>

#include "Player.h"


#define PBAR "************************************************"
#define LENGTH 30

std::vector<Player *> players;

class ui {
private:
    int row;
    int col;
    int x;
    int y;
    const int max_len = 50;
    std::mutex m;
    std::map<int, const char *> states = {
            std::pair<int, const char *>(-1, "czeka na swoja kolej"),
            std::pair<int, const char *>(0, "czeka za zasobem"),
            std::pair<int, const char *>(1, "Dostaje zbroje"),
            std::pair<int, const char *>(2, "Dostaje gogle"),
            std::pair<int, const char *>(3, "Dostaje kask"),
            std::pair<int, const char *>(4, "Dostaje buty"),
            std::pair<int, const char *>(5, "Gotowy do startu"),
            std::pair<int, const char *>(6, "Startuja"),
            std::pair<int, const char *>(7, "Point 1 zaliczony"),
            std::pair<int, const char *>(8, "Point 2 zaliczony"),
            std::pair<int, const char *>(11, "Point 3 zaliczony"),
            std::pair<int, const char *>(9, "Finish"),
            std::pair<int, const char *>(10, "czeka za wstepem")};

public:
    ui();
    ~ui();
    void update();
};

ui::ui() {
    initscr();
    noecho();
    raw();
    nodelay(stdscr, TRUE);
    start_color();
    use_default_colors();
    curs_set(0);
    init_pair(5, COLOR_WHITE, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(2, COLOR_CYAN, -1);
    init_pair(1, COLOR_GREEN, -1);
    getmaxyx(stdscr, col, row);
    x = row / 2 - max_len;
    y = col / 2 + 3;
attron( COLOR_PAIR( 3 ) ); //4
        printw( "RedBull Megawat 111 " );
    
}

ui::~ui() {
    endwin();
}

void ui::update() {
WINDOW * win = newwin(14, 26, 2, 1);
WINDOW * win1 = newwin(14,26, 2,28);
int p2u =0;
int p3u =0;
int p4u =0;

    refresh();
    while (true) {
        int key = getch();
        if (key == 27) { //esc
            for (auto tedy : players) {
                tedy->exit = true;
            }
            return;
        }
for (auto tedy : players) {
if (tedy->state == 7){
        p2u++;
    tedy->po2 = p2u;
}
if (tedy->state == 8){
        p3u++;
    tedy->po3 = p3u;
}
if (tedy->state == 11){
        p4u++;
    tedy->po4 = p4u;
}
}
p2u=0;
p3u =0;
p4u =0;
        for (auto tedy : players) {
            int id = tedy->id;
            int state = tedy->state;
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Zbroja 1 : ");
    mvwprintw(win, 2, 1, "Zbroja 2 : ");
    mvwprintw(win, 3, 1, "Zbroja 3 : ");
    mvwprintw(win, 4, 1, "Zbroja 4 : ");
    mvwprintw(win, 5, 1, "Zbroja 5 : ");
    box(win1, 0, 0);
    mvwprintw(win, 7, 1, "Kask 1 : ");
    mvwprintw(win, 8, 1, "Kask 2 : ");
    mvwprintw(win, 9, 1, "Kask 3 : ");
    mvwprintw(win, 10, 1, "Kask 4 : ");
    mvwprintw(win, 11, 1, "Kask 5 : ");
    mvwprintw(win1, 1, 1, "Gogle 1 : ");
    mvwprintw(win1, 2, 1, "Gogle 2 : ");
    mvwprintw(win1, 3, 1, "Gogle 3 : ");
    mvwprintw(win1, 4, 1, "Gogle 4 : ");
    mvwprintw(win1, 5, 1, "Gogle 5 : ");

    mvwprintw(win1, 7, 1, "Buty 1 : ");
    mvwprintw(win1, 8, 1, "Buty 2 : ");
    mvwprintw(win1, 9, 1, "Buty 3 : ");
    mvwprintw(win1, 10, 1, "Buty 4 : ");
    mvwprintw(win1, 11, 1, "Buty 5 : ");
    
    wrefresh(win);
    wrefresh(win1); 
            move(y + id - 2, 0);
            clrtoeol();
            move(y + id - 2, x);
            if (state > 5) {
                 attron(COLOR_PAIR(tedy->color));
                
                 printw("Zawodnik %d %s", id, states[state]);

                 

            } else {
                int progress = tedy->progress;
                int lpad = std::round(progress / 100.0f * LENGTH);
                int rpad = LENGTH - lpad;
                attron(COLOR_PAIR(tedy->color));
                 
                printw("Zawodnik %d %s  %3d%% [%.*s%*s]", id, states[state], progress, lpad, PBAR, rpad, "");}

move(y + id + 4, 60);
clrtoeol();
move(y + id + 4, x);
            if (state == 6) {
                int progress = tedy->progress;
                int pad = std::round(progress / 100.0f * 20);
                int lpad = 20 - lpad;
                attron(COLOR_PAIR(tedy->id));
                 
                printw("Tor %d ", id);
move(y + id + 4, 66 + pad);
printw("#") ;
                

                 

            }else {
attron(COLOR_PAIR(tedy->color));
                 
                printw("Tor %d  ", id);

}
        
move(y + id + 4, 89);
clrtoeol();
move(y + id + 4, x);
attron(COLOR_PAIR(tedy->id));

                
if(tedy->id ==5){
printw("| 1 2");
}
else {
printw("|");
}
 
if (state == 7 && tedy->po2 == 1){
int progress = tedy->progress;
int pad = std::round(progress / 100.0f * 6);

clrtoeol();
mvprintw(25-pad,91,"#");
clrtoeol();
}

if (state == 7 && tedy->po2 == 2){
int progress = tedy->progress;
int pad = std::round(progress / 100.0f * 7);

clrtoeol();
mvprintw(25-pad,93,"#");
clrtoeol();
}
if (state == 11 && tedy->po4 == 1){
int progress = tedy->progress;
int pad = std::round(progress / 100.0f * 6);

clrtoeol();
mvprintw(16+pad,59,"#");
clrtoeol();
}

if (state == 11 && tedy->po4 == 2){
int progress = tedy->progress;
int pad = std::round(progress / 100.0f * 7);

clrtoeol();
mvprintw(16+pad,57,"#");
clrtoeol();
}
mvprintw(18,93," T1");
mvprintw(17,93," T2");
if (state == 8 && tedy->po3 ==2){
int progress = tedy->progress;
int pad3 = std::round(progress / 100.0f * 30);
 mvwprintw(win, id,12," jest ");
mvprintw(18,91-31,"M");
mvprintw(18,91-pad3,"#");
clrtoeol();
mvprintw(16,60,"-----------------------------------");
mvprintw(19,60,"---------------------------");
}
if (state == 8 && tedy->po3 ==1){
int progress = tedy->progress;
int pad4 = std::round(progress / 100.0f * 30);
mvwprintw(win, id,12," jest ");
mvprintw(17,91-31,"M");
mvprintw(17,91-pad4,"#");
clrtoeol();
mvprintw(16,60,"-----------------------------------");
mvprintw(19,60,"---------------------------");
}

    tedy->po2 = 0;
    tedy->po4 = 0;
    tedy->po3 = 0;
mvprintw(21,60,"------------------------------");
mvprintw(27,60,"-----------------------------------");
for (int i=0;i<9;i++){

mvprintw(27-i,94,"|");
}
for (int i=0;i<2;i++){
mvprintw(20-i,90,"|");}

tedy->mtx.lock();
 if (tedy->haveArmor == true){
            attron(COLOR_PAIR(2));
            mvwprintw(win, id,12," jest zajety");
           
}else {
attron(COLOR_PAIR(2));
mvwprintw(win, id,12," jest wolny");
}      
   
if (tedy->haveHelmet == true){
            attron(COLOR_PAIR(2));
            mvwprintw(win, (id + 6),12," jest zajety");
           
}else {
attron(COLOR_PAIR(2));
mvwprintw(win, (id + 6),12," jest wolny");
}      
wrefresh(win);  
if (tedy->haveGoggle == true){
            attron(COLOR_PAIR(2));
            mvwprintw(win1, id,12," jest zajety");
           
}else {
attron(COLOR_PAIR(2));
mvwprintw(win1, id,12," jest wolny");
}     
 if (tedy->haveShoes == true){
            attron(COLOR_PAIR(2));
            mvwprintw(win1, (id+6),12," jest zajety");
           
}else {
attron(COLOR_PAIR(2));
mvwprintw(win1, (id + 6),12," jest wolny");
}      
tedy->mtx.unlock();
wrefresh(win1); 
      
}

}}

class Organizer{
public: 


Organizer(){}
void agreement();
void finish();
int liczba = 0;
int liczba2 = 0;


};
void Organizer::agreement() {

    while (!players[0]->exit) {
      for (auto p : players) {
        p->mtx.lock();
        if(p->haveArmor == true && p->haveGoggle == true && p->haveHelmet == true 
            && p->haveShoes == true){
                
                    liczba++;

      } 
p->mtx.unlock();
}
        if(liczba == 5 ){
            for (auto p : players) {
           p->mtx.lock(); 
            p->zgoda = true;
            liczba= 0;
            p->mtx.unlock();

}
               
        }
        else {
            liczba= 0;
        }
    }
  
}
void Organizer::finish() {

    while (!players[0]->exit) {
      for (auto p : players) {
        p->mtx.lock();
        if(p->point3 == true ){
                
                    liczba2++;

      }
p->mtx.unlock();
 }
        if(liczba2 == 5 ){
            for (auto p : players) {
std::this_thread::sleep_for(std::chrono::seconds(1));
    p->mtx.lock();
            
        p->state = -1;
     p->haveArmor = false;
     p->haveGoggle = false;
     p->haveHelmet = false;
     p->haveShoes = false;
     p->zgoda = false;
     p->point1 = false;
     p->point2 = false;
     p->point3 = false;
     p->color = 1;
    liczba2 =0;
p->mtx.unlock();
     std::this_thread::sleep_for(std::chrono::seconds(1));
            }
               
        }
        else {
            liczba2= 0;
        }
    }
  
}

int main() {
    PlayerProblem table;
    ui u;
    Organizer o;
    
    for (auto i = 0; i < 5; i++) {
        Player *p = new Player(i + 1, table, std::ref(table.armors[0]), std::ref(table.goggles[0]), std::ref(table.helmets[0]), std::ref(table.shoes[0]), std::ref(table.bpoint1[0]), std::ref(table.bpoint2[0]), std::ref(table.bpoint3[0]), std::ref(table.bpoint4[0]));
        players.push_back(p);
    }

    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    table.ready = true;
    std::thread t1(&ui::update, &u);
    std::thread t2(&Organizer::agreement, &o);
    std::thread t3(&Organizer::finish, &o);
    t3.join();
    t1.join();
    t2.join();
    for (auto p : players) {
        p->t.join();
    }
    endwin();
    return 0;
}
