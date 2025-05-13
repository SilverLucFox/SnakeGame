
//#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <GL/glut.h>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>
#include <windows.h>
#include <thread>
#include <time.h>
using namespace std;
const int maxsize = 6;// change 20
GLfloat vertexX;
int timeG = 0;
GLfloat vertexY;
bool on = true;
string leader[10];
string lnames[10];
int llevels[10];
int lstar[10];
int lpoints[10];
int ltime[10];
string ones[] = { "One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten" };
string teens[] = { "eleven","twelve","thirteen","fourteen","fifteen", "sixteen","seventeen","eighteen","nineteen" };
string tens[] = { "twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety" };
string hints[] = { "Not all snakes lay eggs.","Snakes don't have eyelids ","Snakes smell with their tongues.",
"Snakes are shy, secretive animals" ,"snakes are dichromatic"," snakes are active at night ","Snakes are deaf to all airborne sounds" };
int level = 0;
bool updat = false;
float levels[10][3] = {
    {1.0f,1.0f,1.0f} ,//lvl 1
    {.678431f,0.917647f,.917647f},//lvl 2
    {.309804f,0.184314f,.309804f},//lvl 3
    {.5f,1.0f,0.0f},//lvl 4
    {1.0f,0.5f,0.0f},//lvl 5
    {0.0f,.5f,0.0f},//lvl 6
    {1.0f,0.0f,0.0f},//lvl 7
    {1.0f,0.0f,0.0f},//lvl 8
    {1.0f,0.0f,0.0f},//lvl 9
    {0.8f,0.498039f,0.196078f} };//lvl 10
int foodjump = 10000;
bool popupfun = false;
int index = -1;
int stars = 0;
float boxlen = -.68;
bool gameEnded = true;
int points = 0;
int highp = 0;
string message;
int windowN;
int popuptextcol;
GLfloat red = 1.0f;
bool gamestarted = false;
GLfloat green = 0.0f;
GLfloat blue = 0.0f;
string username = "";
int speed = 100;
int SKey = GLUT_KEY_RIGHT;
float mouseX;
float mouseY;
class snake
{
public:
    GLfloat centerPosX1 = 0.0f;
    GLfloat centerPosY1 = 0.0f;
    void up() {
        centerPosY1 += 0.03f;
        if (centerPosY1 > 1.0f)centerPosY1 = -1.0f;
    }
    void down() {
        centerPosY1 -= 0.03f;
        if (centerPosY1 < -1.0f)centerPosY1 = 1.0f;
    }
    void left() {
        centerPosX1 -= 0.03f;
        if (centerPosX1 < -1.0f)centerPosX1 = 1.0f;
    }
    void right() {
        centerPosX1 += 0.03f;
        if (centerPosX1 > 1.0f)centerPosX1 = -1.0f;
    }
};

class obj {
public:
    GLfloat cpX;
    GLfloat ccpY;
};
class pp {
public:int star;
      int level;
      int points;
      int time;
      string name;
};
class rock {
public:
    float posX;
    float posY;
};
rock rocks[100];
int setrok = 0;
int rockadder = 1;
int nofRocks = 0;
thread autowalk;
thread moving;
thread timeee;
struct stack {
    snake arr[maxsize];
    obj food;
    int ctr = -1;
}a;

bool comparePP(const pp& a, const pp& b) {
    if (a.star != b.star) {
        return a.star > b.star;
    }
    if (a.level != b.level) {
        return a.level > b.level;
    }
    if (a.points != b.points) {
        return a.points > b.points;        
    }
    return a.time < b.time;
}

void makeRec(float x, float y, float h, float w, int color) {
    int r = color / 100;
    int g = (color / 10) % 10;
    int b = color % 10;
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x, y);
    glVertex2f(x, y - h);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y - h);
    glVertex2f(x + w, y - h);
    glVertex2f(x, y - h);
    glEnd();
}


void WWWLeader() {
    pp p[11];

    p[10].level = level;
    p[10].points = highp;
    p[10].name = username;
    p[10].star = stars;
    p[10].time = timeG;
    for (int i = 0; i < 10; i++) {
        p[i].star = lstar[i];
        p[i].level = llevels[i];
        p[i].points = lpoints[i];
        p[i].time = ltime[i];
        p[i].name = lnames[i];
    }

    ////// work hoooooooooon/// leader sort 
    sort(p, p + 11, comparePP);

    for (int i = 0; i < 11; i++)
        cout << "" + p[i].name + " " + to_string(p[i].star) + " " + to_string(p[i].level) + " " + to_string(p[i].points) + " " + to_string(p[i].time) + '\n';

    ofstream MyFile("leader.txt");
    for (int i = 0; i < 10; i++)
        MyFile << "" + p[i].name + " " + to_string(p[i].star) + " " + to_string(p[i].level) + " " + to_string(p[i].points) + " " + to_string(p[i].time) + '\n';
    MyFile.close();
    cout << "leaderbored been updated";
}
void readingLeader() {

    string myText;
    ifstream MyReadFile("leader.txt");
    int i = 0;
    cout << "reading txt file . . . ";
    while (getline(MyReadFile, myText)) {
        leader[i] = myText; i++;
    }
    MyReadFile.close();
    cout << " \ntxt file  been read successfully. . . ";
    cout << "\n printing....";
    for (int j = 0; j < 10; j++)cout << "\n" << leader[j] << endl;
    cout << "splitting . . ." << endl;
    for (int i = 0; i < 10; i++) {
        string temp = leader[i].substr(0, leader[i].find_first_of(" "));

        lnames[i] = temp;
        leader[i] = leader[i].substr(leader[i].find_first_of(" ") + 1, leader[i].length());
        cout << setw(10) << temp;

        temp = leader[i].substr(0, leader[i].find_first_of(" "));
        lstar[i] = stoi(temp);
        leader[i] = leader[i].substr(leader[i].find_first_of(" ") + 1, leader[i].length());
        cout << setw(10) << temp;


        temp = leader[i].substr(0, leader[i].find_first_of(" "));
        llevels[i] = stoi(temp);
        leader[i] = leader[i].substr(leader[i].find_first_of(" ") + 1, leader[i].length());
        cout << setw(10) << temp;


        temp = leader[i].substr(0, leader[i].find_first_of(" "));
        lpoints[i] = stoi(temp);
        leader[i] = leader[i].substr(leader[i].find_first_of(" ") + 1, leader[i].length());
        cout << setw(10) << temp;

        temp = leader[i].substr(0, leader[i].length());
        cout << setw(10) << temp;

        ltime[i] = stoi(temp);
        cout << endl;
    }


}

void WWord(string s, float X, float Y, int color) {
    glutPostRedisplay();
    int r = color / 100;
    int g = (color / 10) % 10;
    int b = color % 10;
    glColor3f(r, g, b);
    glRasterPos3f(X, Y, 0);
    for (int i = 0; i < s.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }


}
void distime() {
    int m = timeG / 60;
    int s = timeG % 60;
    WWord(m < 10 ? "0" + to_string(m) : to_string(m), -.9, .9, 111);
    WWord(": " + (s < 10 ? "0" + to_string(s) : to_string(s)), -.8, .9, 111);
}
void mouseMoveOnPop(int button, int stat, int mouseX, int mouseY)
{
    if (stat == 0)glutDestroyWindow(windowN);
}
void displaypop() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    WWord(message, -.8, 0, popuptextcol);
    glRasterPos3f(-0.40, 0.65, 0);
    glPopMatrix();
    glFlush();
}
void popup() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(450, 100);
    glutInitWindowPosition(450, 300);
    glutCreateWindow("");
    glutDisplayFunc(displaypop);
    glutSetCursor(GLUT_CURSOR_INFO);
    glutMouseFunc(mouseMoveOnPop);
    glutMainLoop();

}
void move() {
    if (a.ctr != maxsize) {
        a.food.ccpY = ((rand() % 200) - 100) / 100.0f;
        a.food.cpX = ((rand() % 200) - 100) / 100.0f;
    }
}
void spawnR() {
    if (nofRocks < rockadder &&nofRocks<100) {
        rocks[nofRocks].posX = ((rand() % 200) - 100) / 100.0f;
        rocks[nofRocks].posY = ((rand() % 200) - 100) / 100.0f;
        nofRocks++;
    }
    if (setrok <= rockadder) {
        rocks[setrok].posX = ((rand() % 200) - 100) / 100.0f;
        rocks[setrok].posY = ((rand() % 200) - 100) / 100.0f;
        setrok++;
    }
    else
        setrok = 0;
}
void timeT0Move() {
    while (true) {
        Sleep(foodjump);
        if (rockadder < 50)
            rockadder++;
        move();
    }
}
void push() {
    a.ctr++;

    snake b;
    a.arr[a.ctr] = b;
    a.arr[a.ctr].centerPosX1 = a.arr[0].centerPosX1;
    a.arr[a.ctr].centerPosY1 = a.arr[0].centerPosY1;
}
void timer() {
    while (true) {
        if (foodjump > 10000)foodjump -= points;
        spawnR();
        timeG++;
        Sleep(1000);
        cout << "{(speed : " << speed << " )} pos:x[ " << a.arr[0].centerPosX1 << "] pos:Y:[" << a.arr[0].centerPosY1 << "]" << "food { " << a.food.ccpY << " : " << a.food.cpX << " }" << " {foodjt :" << foodjump << " } points:" << points << "length:" << a.ctr << endl;
    }
}
void draw_circle(float cx, float cy, float radius, int segments, float r, float g, float b) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(cx, cy, 0.0f);
    glColor3f(r, g, b);
    static const int circle_points = 100;
    static const float angle = 2.0f * 3.1416f / circle_points;
    glBegin(GL_POLYGON);
    double angle1 = 0.0;
    glVertex2d(radius * cos(0.0), radius * sin(0.0));
    int i;
    for (i = 0; i < circle_points; i++)
    {
        glVertex2d(radius * cos(angle1), radius * sin(angle1));
        angle1 += angle;
    }
    glEnd();
    glPopMatrix();
}
void hit() {
    if (updat) {
            WWWLeader();
            readingLeader();
            updat = false;
    }
            
}
void update() {
    float x, y;
    for (int i = 0; i < rockadder; i++) {
        if (a.arr[0].centerPosX1 > (rocks[i].posX - .03) &&
            a.arr[0].centerPosX1 < (rocks[i].posX + .03) &&
            a.arr[0].centerPosY1>(rocks[i].posY - .03) &&
            a.arr[0].centerPosY1 < (rocks[i].posY + .03)) {
            cout << "hit..." << endl;  gameEnded = false; hit();
            break;

        }
    }
    if (a.arr[0].centerPosX1 > (a.food.cpX - .03) &&
        a.arr[0].centerPosX1 < (a.food.cpX + .03) &&
        a.arr[0].centerPosY1>(a.food.ccpY - .03) &&
        a.arr[0].centerPosY1 < (a.food.ccpY + .03)) {
        push(); move(); points++;

    }
    if (a.ctr == 0 && points > 0) {
        push();
        if (level > 9) {
            level = 0;
            stars++;
        }
        red = levels[level][0];
        green = levels[level][1];
        blue = levels[level][2];
        points++;
        level++;
    }
    if (points > highp)highp = points;
    for (int i = a.ctr; i > 0; i--) {
        x = a.arr[i - 1].centerPosX1;
        y = a.arr[i - 1].centerPosY1;
        a.arr[i].centerPosX1 = x;
        a.arr[i].centerPosY1 = y;
    }
}
void walk()
{
    switch (SKey) {
    case GLUT_KEY_UP:
        update();
        a.arr[0].up();
        break;
    case GLUT_KEY_DOWN:
        update();
        a.arr[0].down();
        break;
    case GLUT_KEY_LEFT:
        update();
        a.arr[0].left();
        break;
    case GLUT_KEY_RIGHT:
        update();
        a.arr[0].right();
        break;
    }

}
void step() {
    while (true) {
        Sleep(speed);
        walk();

    }
}

void specialKeys(int key, int x, int y) {
    if ((key == GLUT_KEY_UP && SKey != GLUT_KEY_DOWN) ||
        (key == GLUT_KEY_DOWN && SKey != GLUT_KEY_UP) ||
        (key == GLUT_KEY_LEFT && SKey != GLUT_KEY_RIGHT) ||
        (key == GLUT_KEY_RIGHT && SKey != GLUT_KEY_LEFT))
    {
        switch (key) {
        case GLUT_KEY_UP:
            SKey = GLUT_KEY_UP;
            break;
        case GLUT_KEY_DOWN:
            SKey = GLUT_KEY_DOWN;
            break;
        case GLUT_KEY_LEFT:
            SKey = GLUT_KEY_LEFT;
            break;
        case GLUT_KEY_RIGHT:
            SKey = GLUT_KEY_RIGHT;
            break;
        }
    }


}
void display() {

    if (gameEnded) {

        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
        distime();
        for (int i = 0; i < a.ctr; i++)
            draw_circle(a.arr[i].centerPosX1, a.arr[i].centerPosY1, 0.03, 100, red, green, blue);
        for (int i = 0; i < nofRocks; i++)
            draw_circle(rocks[i].posX, rocks[i].posY, 0.03, 100, 0.7, 0, 0.7);
        WWord("score : " + to_string(points), .55, .9, 010);
        draw_circle(a.food.cpX, a.food.ccpY, 0.03, 100, 0, 0, 1);

        glPopMatrix();
        glFlush();
    }
    else {
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
        WWord("GAME OVER !!", -.3,.5, 100);

        WWord("RESTART", -.5, 0, 10);
        WWord("EXIT", .3, 0, 1);

        makeRec(-.55, .13, .19,  .54, 101);
        makeRec(.25, .13, .19, .34, 110);

        glPopMatrix();
        glFlush();
    }
}

void keyess(unsigned char key, int x, int y) {
    switch (key)
    {
    case ' ':
        //joint();
        break;
    case 'a':
        SKey = GLUT_KEY_LEFT;
        break;
    case 'w':
        SKey = GLUT_KEY_UP;
        break;
    case 'd':
        SKey = GLUT_KEY_RIGHT;
        break;
    case 's':
        SKey = GLUT_KEY_DOWN;
        break;
    }
}
void mouseMovee(int b, int c, int x, int y) {
    if (!gameEnded && c==1) {
        if (x > 113 && x < 245 && y > 219 && y < 265) {
            cout << "restarting. . . . \n\n\n";
            updat = true;
            highp = 0;
            nofRocks = 0;
            setrok = 0;
            rockadder = 1;
            level = 0;
            points = 0;
            stars = 0;
            timeG = 0;
            a.ctr = 4;
            red = 1.0f;
            green = 0.0f;
            blue = 0.0f;
            for(int i=0;i<3;i++){
            a.arr[i].centerPosX1 = 0;
            a.arr[i].centerPosY1 = 0;
                }
            gameEnded = true;

        }
        if (x > 313 && x <396 && y > 220 && y<265) {
            cout << "exiting . . . . . bye!! \n\n\n";
            exit(0);
        }
    }
}

void gameDis() {
    srand(time(0));
    move();
    for (int i = 0; i < 5; i++)
        push();
    thread moving(timeT0Move);
    thread timeee(timer);
    thread autowalk(step);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(390, 150);
    glutCreateWindow("snake");
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseMovee);
    glutKeyboardFunc(keyess);
    glutMainLoop();
    autowalk.join();
    timeee.join();
    moving.join();
}


void specialKeysInsertName(unsigned char key, int x, int y) {
    float z = 0;
    cout << "key:" << key << "boxlenght: " << boxlen << endl;
    if (username.length() != 0 || key != '\b') {
        username += key;
        if (key == '\b') {
            username = username.substr(0, username.length() - 2);
            boxlen = boxlen - .02f;
        }
        else
            boxlen += 0.02f;
    }
}
void wleader() {

    WWord("Name", .48, .55, 111);
    WWord("Star", .60, .55, 111);
    WWord("Level", .68, .55, 111);
    WWord("Points", .78, .55, 111);
    WWord("Time", .89, .55, 111);
    float vicky = 0.45;
    for (int i = 0; i < 10; i++) {
        WWord(lnames[i], .48, vicky, 111);
        WWord(to_string(lstar[i]), .60, vicky, 111);
        WWord(ones[llevels[i]], .68, vicky, 111);
        WWord(to_string(lpoints[i]), .79, vicky, 111);
        WWord((ltime[i] / 60 < 10 ? "0" + to_string(ltime[i] / 60) : to_string(ltime[i] / 60)) + ":" + (ltime[i] % 60 < 10 ? "0" + to_string(ltime[i] % 60) : to_string(ltime[i] % 60)), .89, vicky, 111);
        vicky -= 0.1;
    }
}
void mouseDraw(int x, int y) {
    float x1 = x / (float)1265;
    float y1 = y / (float)650;
    WWord("s", x1, y1, 101);

}

void mainDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glutSetCursor(GLUT_CURSOR_NONE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    makeRec(0.45, .85, 1.7, 0.55, 100);//leaderboard
    makeRec(-.99, .85, 1.7, 0.55, 10);//leaderboard
    wleader();
    makeRec(-0.85, 0.12, 0.18, 0.17, 1);//start
    makeRec(-0.84, -0.28, 0.18, 0.17, 10);//exit
    makeRec(-.4, .95, 0.18, 0.17, 101);//star
    WWord(to_string(stars), -0.325, .84, 111);
    makeRec(.25, .95, 0.18, 0.17, 101);//level
    WWord(ones[level], 0.28, .84, 111);
    makeRec(boxlen, .55, .07, 0, 111);
    WWord("Name:", -0.8, .5, 111);
    WWord(username, -.68, .5, 110);
    glColor3f(255, 165, 0);
    makeRec(-0.17, 0.9, 0.15, 0.35, 111);
    WWord("Crazy Snake !", -.1, .8, 111);
    WWord(gamestarted ? to_string(highp) : "Start", -.8, 0, 111);
    WWord("Leaderboard", .65, .7, 111);
    WWord("Exit", -0.79, -0.4, 111);
    glLoadIdentity();
    //glutPassiveMotionFunc(mouseDraw);
    glutKeyboardFunc(specialKeysInsertName);
    glEnd();
    glFlush();
}




void mouseMove(int button, int stat, int mouseX, int mouseY)
{
    srand(time(0));
    cout << button << "," << stat << " poss:" << mouseX << ", " << mouseY << endl;
    if (mouseX >= 157 && mouseX <= 333 && mouseY >= 93 && mouseY <= 138 && stat == 1) {
        popuptextcol = rand() % 100;
        message = hints[rand() % 7];
        popuptextcol = 100;
        windowN = 2;
        popup();
    }
    if (mouseX >= 95 && mouseX <= 200 && mouseY >= 244 && mouseY <= 388 && stat == 1) {
        cout << "starting . . . " << endl;
        if (username.length() != 0) {
            gamestarted = true;
           
            updat = true;
            windowN = 2;
            points = 0;
            gameDis();

        }
        else {
            popuptextcol = 100;
            message = "pls enter your name !";
            windowN = 2;
            popup();
        }

    }
    if (mouseX >= 102 && mouseX <= 207 && mouseY >= 416 && mouseY <= 471 && stat == 1) {
        cout << "byeeeeee . . . " << endl;
        on = false;
        PostQuitMessage(0);
    }


}

int main(int argc, char** argv) {
    readingLeader();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1265, 650);
    //glutFullScreen(); trying to fullscrean 
    glutInitWindowPosition(0, 0);
    glutCreateWindow("main");
    glutDisplayFunc(mainDisplay);
    glutMouseFunc(mouseMove);
    glutMainLoop();


    return 0;
}