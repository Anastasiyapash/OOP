#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZEX 700
#define SIZEY 700
typedef struct Coords { 
int x; 
int y; 
} coord; 

class Game { 
public: 
virtual void draw(HDC hDC)=0; 
}; 

class Screen : public Game { 
private: 
  int sizex;
  int sizey;
  int kx;
  int ky;
public: 
  Screen(int x, int y); 
  int getkx();
  int getky();
  virtual void draw(HDC hDC); 
  ~Screen(); 
};

class Apple : public Screen {
	private:
		coord xy;
	public:
		Apple();
		int getx();
		int gety();
		void draw(HDC hdc);
		void generate();
		~Apple();
};

class Snake : public Screen {
	private:
		int len;
		coord * coords;
		int vector;
		int move1;
	public:
		Snake(int xhead, int yhead);
        void move();
        void eat(Apple* app);
        int getHeadx();
        int getHeady();
		void setVector(int vec);
		void draw(HDC hdc); 
		~Snake();
};
