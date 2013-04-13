#include <SMARTGPU.h>
#include <Wire.h>

SMARTGPU lcd;

#define orange 0xFC0F
#define brown 0xBBCA
#define ligBlue 0x96DD

//Title X and Y coordinates
#define titleX1 120
#define titleX2 310
#define titleY1 5
#define titleY2 20

//Back Button X and Y coordinates
#define backX1 10
#define backX2 45
#define backY1 228
#define backY2 239

//Menu 1 X and Y coordinates
#define menu1X1 10
#define menu1X2 70
#define menu1Y1 30
#define menu1Y2 90

//Menu 2 X and Y coordinates
#define menu2X1 100
#define menu2X2 160
#define menu2Y1 30
#define menu2Y2 90

//Menu 3 X and Y coordinates
#define menu3X1 10
#define menu3X2 70
#define menu3Y1 120
#define menu3Y2 180

//enumerates the menus' starting at 0
enum menuList
{
  mainMenus=0
 ,mainMenu1
 ,mainMenu2
 ,mainMenu3
};

menuList currentMenu = mainMenus;

/*
 *An array that stores the history of menus selected.
 *The integer will keep track of what part of the array it's on.
*/
menuList menuHist[5];
int menuHistPoint = -1;


int touch[2];
char icon[3];

void setup()
{
  //These two functions are required for SMARTPUGGU
  lcd.init();
  lcd.start();
  drawMainMenus();
  menuHist[0] = currentMenu;

  Wire.begin(5);
  Serial.begin(9600);
}

void drawTitle()
{
  lcd.string(titleX1,titleY1, titleX2, titleY2, BLUE, FONT5, TRANS,"JARVIS");
}

void drawBackButton()
{
  lcd.string(backX1,backY1,backX2,backY2,BLUE,FONT1,FILL,"Back");
  lcd.drawRectangle(backX1-5,backY1-3,backX2,backY2,RED,UNFILL);
}

void drawMainMenu1()
{
  lcd.drawRectangle(menu1X1,menu1Y1,menu1X2,menu1Y2,orange,FILL);
}

void drawMainMenu2()
{
  lcd.drawRectangle(menu2X1,menu2Y1,menu2X2,menu2Y2,brown,FILL);
}

void drawMainMenu3()
{
  lcd.drawRectangle(menu3X1,menu3Y1,menu3X2,menu3Y2,ligBlue,FILL);
}

void drawMenu1SubMenu1()
{
  lcd.drawRectangle(menu1X1,menu1Y1,menu1X2,menu1Y2,orange,FILL);
}

void drawMenu1SubMenu2()
{
  lcd.drawRectangle(menu2X1,menu2Y1,menu2X2,menu2Y2,orange,FILL);
}

void drawMenu1SubMenu3()
{
  lcd.drawRectangle(menu3X1,menu3Y1,menu3X2,menu3Y2,orange,FILL);
}

void selectMainMenu1()
{
  /*Wire.beginTransmission(4);
  Wire.write("1");
  Wire.endTransmission();*/
  lcd.erase();
  drawTitle();
  
  drawMenu1SubMenu1();
  drawMenu1SubMenu2();
  drawMenu1SubMenu3();
  
  drawBackButton();
  menuHistPoint++;
}

void selectMainMenu2()
{
  lcd.erase();
  drawTitle();
  drawBackButton();
  menuHistPoint++;
  lcd.string(10,50,290,220,YELLOW,FONT7,FILL,"Erase in 2");
  delay(1000);
  lcd.erase();
  drawTitle();
  drawBackButton();
  lcd.string(10,50,290,220,YELLOW,FONT7,FILL,"Erase in 1");
    delay(1000);
  lcd.erase();
  drawTitle();
  drawBackButton();
  lcd.string(10,50,290,220,YELLOW,FONT7,FILL,"GONE!");
}

void selectMainMenu3()
{
  byte x = 0;
  Wire.beginTransmission(4);
  Wire.write(x);
  Wire.endTransmission();
  lcd.erase();
  drawTitle();
  lcd.string(10,50,290,220,YELLOW,FONT7,TRANS,"Menu 3 is this");
  drawBackButton();
  menuHistPoint++;
 
}

void drawMainMenus()
{
  lcd.erase();
  drawTitle();
  drawMainMenu1();
  drawMainMenu2();
  drawMainMenu3();
  menuHistPoint = -1;
}

void menuReset()
{
  drawMainMenus();
}

void loop()
{
  lcd.baudChange(2000000); 
  
  while(1)
  {
    if(lcd.touchScreen(touch))
    {
      //Menu 1 is selected
      if(touch[XCOORD] >=menu1X1 && touch[XCOORD] <=menu1X2)
      {
        if(touch[YCOORD] >= menu1Y1 && touch[YCOORD] <= menu1Y2)
        {
          if(menuHistPoint == -1)
          {
            selectMainMenu1();
          }else
          {
            switch(menuHist[menuHistPoint])
            {
              case mainMenus:
                //menuReset();
                break;
            }
          }
        }
      }
      
      //Menu 2 is selected
      if(touch[XCOORD] >=menu2X1 && touch[XCOORD] <=menu2X2)
      {
        if(touch[YCOORD] >= menu2Y1 && touch[YCOORD] <= menu2Y2)
        {
          if(menuHistPoint == -1)
          {
            selectMainMenu2();
          }else
          {
            switch(menuHist[menuHistPoint])
            {
              case mainMenus:
                //menuReset();
                break;
            }
          }
        }
      }
    
    //Menu 3 is selected
      if(touch[XCOORD] >=menu3X1 && touch[XCOORD] <=menu3X2)
      {
        if(touch[YCOORD] >= menu3Y1 && touch[YCOORD] <= menu3Y2)
        {
          if(menuHistPoint == -1)
          {
            selectMainMenu3();
          }else
          {
            switch(menuHist[menuHistPoint])
            {
              case mainMenus:
                //menuReset();
                break;
            }
          }
        }
      }
      
      if(touch[XCOORD] >= backX1 && touch[XCOORD] <= backX2)
      {
        if(touch[YCOORD] >= backY1 && touch[XCOORD] <= backY2)
        {
          if(menuHistPoint >= 0)
          {
            switch(menuHist[menuHistPoint])
            {
              case mainMenus:
                menuReset();
                break;
            }
          }
        }
      }
    }   
    
    
    //Resets back to the main menu if any icon is pressed
    if(lcd.touchIcon(icon))
    {
      menuReset();
    }
  }
}
