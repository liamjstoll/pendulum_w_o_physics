#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <math.h>

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH =800;


using namespace std;

#define PI 3.14159265

enum Color { RED, BLUE, GREEN, ORANGE, CYAN, YELLOW, MAGENTA, AMBER };


class Controller
{
public:
    Controller();
    ~Controller();

    void DrawPixel(Color color, int x, int y);
    void DrawLine(Color color,
     int x1, int y1, int x2, int y2);
    void InitializeGraphics();
    void ClearScreen();
    void UpdateScreen();
    void DrawCircle(const int h, const int k, const int radius, const Color color);
    bool HasUserQuit();

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    void SetRendererColor(const Color color);
};

//---------------------------------------------------------------------------
int main(int argc, char * args[])
{
    Controller controller;
    int keyPressed = -1;
    double val = PI / 180;

    double x1 = SCREEN_WIDTH/2;
    double y1 = SCREEN_HEIGHT/2;


    int x2=1;
    int y2=0;

    int counter =0;

    int arr[SCREEN_WIDTH][SCREEN_HEIGHT]={0};


// in the loop, increment the y2 and x2 values that are drawn by sin and cos of y1 and x1
    while (!controller.HasUserQuit())
    {
        counter++;
        x2=counter+1;
        y2=counter;


        controller.ClearScreen();

        for(int i =0;i< SCREEN_WIDTH;i++)
        {
            for(int j=0;j<SCREEN_HEIGHT;j++)
            {
                if(arr[i][j]!=0)
                {
                    controller.DrawPixel(MAGENTA,i,j);
                }
            }
        }
      
      
        // The lengths of the lines, their speeds, and rotation directions are hard-coded.     
        // Could change those to accept input...
        controller.DrawLine(BLUE,(int)x1,(int)y1,(int)x1+cos(x2*val)*200,(int)y1-sin(y2*val)*200);

        double x3=(int)x1+cos(x2*val)*200;
        double y3=(int)y1-sin(y2*val)*200;


        controller.DrawLine(RED,(int)x3,(int)y3,(int)x3+cos(x2*val)*100,(int)y3+sin(y2*val)*100);

        double x4=(int)x3+cos(x2*val)*100;
        double y4=(int)y3+sin(y2*val)*100;
        controller.DrawLine(GREEN,(int)x4,(int)y4,(int)x4+cos(x2*val*2)*50,(int)y4-sin(y2*val*2)*50);
        
        double x5=(int)x4+cos(x2*val*2)*50;
        double y5=(int)y4-sin(y2*val*2)*50;
        

        controller.DrawLine(YELLOW,x5,(int)y5,(int)x5+cos(x2*val*2)*25,(int)y5+sin(y2*val*2)*25);
        
        double x6=(int)x5+cos(x2*val*2)*25;
        double y6=(int)y5+sin(y2*val*2)*25;

        arr[(int)x6][(int)y6]=1;

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {


			if(e.type==SDL_KEYDOWN && e.key.keysym.sym!=keyPressed)
			{
				keyPressed=e.key.keysym.sym;
            
            }
        }
        switch(keyPressed)
        {
            case SDLK_q:
                controller.~Controller();
                break;
        }
        usleep(3000);

        controller.UpdateScreen();
    }
       // usleep(30000);



    return 0;
}
//--------------------------------------------------------------------------------
Controller::Controller()
{
	_renderer = nullptr;
	_window = nullptr;
	InitializeGraphics();
}

Controller::~Controller()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_renderer = nullptr;
	_window = nullptr;
	SDL_Quit();
}

void Controller::DrawPixel(Color color, int x, int y)
{
    SetRendererColor(color);
    SDL_RenderDrawPoint(_renderer,x,y);
}

void Controller::DrawLine(Color color, int x1, int y1, int x2, int y2)
{
    SetRendererColor(color);
    SDL_RenderDrawLine(_renderer,x1,y1,x2,y2);
}

// initilizes SDL things. Checks for errors
void Controller::InitializeGraphics()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cerr << "Init Error \n " << SDL_GetError() << endl;
		return;
	}
	_window = SDL_CreateWindow("Pendulum (No Physics)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600,1600, SDL_WINDOW_SHOWN);
	if (_window == nullptr)
	{
		cerr << "Window Error \n " << SDL_GetError() << endl;
		return;
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr)
	{
		cerr << "Renderer Error \n " << SDL_GetError() << endl;
		return;
	}

}

void Controller::SetRendererColor(const Color color)
{
    switch (color)
    {
        case RED:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF);
            break;
        case BLUE:
            SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0xFF, 0xFF);
            break;
        case AMBER:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xBF, 0xF0, 0xFF);
            break;
        case GREEN:
            SDL_SetRenderDrawColor(_renderer, 0x00, 0xFF, 0x00, 0xFF);
            break;
        case CYAN:
            SDL_SetRenderDrawColor(_renderer, 0x00, 0xFF, 0xFF, 0xFF);
            break;
        case MAGENTA:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0xFF, 0xFF);
            break;
        case ORANGE:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xA5, 0x00, 0xFF);
            break;
        case YELLOW:
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0x00, 0xFF);
            break;
    }
}
void Controller::ClearScreen()
{
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(_renderer);
}

void Controller::UpdateScreen()
{
	SDL_RenderPresent(_renderer);
}
void Controller::DrawCircle(const int h, const int k, const int radius, const Color color)
{
   const int diameter = (radius * 2);

   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);
   SetRendererColor(color);
   while (x >= y)
   {
      SDL_RenderDrawPoint(_renderer, h + x, k - y);
      SDL_RenderDrawPoint(_renderer, h + x, k + y);
      SDL_RenderDrawPoint(_renderer, h - x, k - y);
      SDL_RenderDrawPoint(_renderer, h - x, k + y);
      SDL_RenderDrawPoint(_renderer, h + y, k - x);
      SDL_RenderDrawPoint(_renderer, h + y, k + x);
      SDL_RenderDrawPoint(_renderer, h - y, k - x);
      SDL_RenderDrawPoint(_renderer, h - y, k + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

bool Controller::HasUserQuit()
{
    //just return false for now, change later
	return false;
}
