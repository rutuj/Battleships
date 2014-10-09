#include <simplecpp>
const int side = 40; //length of side
const int base = 65536; //base of modulus
const int o1 = 0, o2 = 600; //origins of left and right grids respectively 
const int red[] = {255,0,0,255}; //Value of red intensity in 4 ships respectively
const int green[] = {0,255,0,255};//Value of green intensity in 4 ships respectively
const int blue[] = {0,0,255,0}; //Value of blue intensity in 4 ships respectively
const int textBoxX = 500 ,textBoxY = 500; //Coordinates of text box


void Grid(Rectangle &r) // Function to create the grid
{
   int ctr = 0;
   for(int i=1;i<=10;i++)
   {
    for(int j=0;j<10;j++)
   {
       r.moveTo((side/2 + (ctr*side) ),(side/2 + (j*side) ));
       r.imprint();
       r.move(o2,0);
       r.imprint();
    }
    ctr++;
    }
}

void color(double x1,double x2,double y1,double y2,int redval,int blueval,int greenval) //Function for colouring the ships. 
{
	if(y2 - y1 == 0)
{
	if(x1 > x2)
		{
		x1 = x1 + x2;
		x2= x1 - x2;
		x1= x1 - x2;
		}
	Rectangle rColor(x1*side + side/2,y1*side + side/2,side,side);
	rColor.setFill(true);
	rColor.setColor(COLOR(redval,greenval,blueval));
	repeat(int(1 + x2 - x1))
{
	rColor.imprint();
	rColor.move(side,0);
}
}
else			
{
	if(y1 > y2)
	{	y1 = y1 + y2;
		y2 = y1 - y2;
		y1 = y1 - y2;
	}
	Rectangle rColor(x1*side + side/2,y1*side + side/2,side,side);
	rColor.setFill(true);
	rColor.setColor(COLOR(redval,greenval,blueval));
	repeat(int(1 + y2 - y1))
	{
		rColor.imprint();
		rColor.imprint();
		rColor.move(0,side);
}
	}
}

int xCoord(int clickVal) // Converts x coordinate of click to respective position in grid eg: 42 = 1, 348 = 8
	{return((clickVal/base)/side);}

int yCoord(int clickVal) // Converts y coordinate of click to respective position in grid
	{return((clickVal%base)/side);}

bool checkVal(int x,int y,int o) // Checks whether or not click lies in grid
{
	o/=side;
	if( (x >= o) && (x <= o + 9) && (y >= 0) && (y <= 9))
		return true;
	else
		return false;
}

void setup(int choice)            //Function for setting up the ships for selection
{
	if(choice==1)                 
	{
		color(10.5,10.5,8,9,255,0,0);
		color(11.5,11.5,7,9,0,255,0);
		color(12.5,12.5,6,9,0,0,255);
		color(13.5,13.5,5,9,255,255,0);
	}
	else
	{
		color(10.5,10.5,8,9,0,0,0);
		color(11.5,11.5,7,9,0,0,0);
		color(12.5,12.5,6,9,0,0,0);
		color(13.5,13.5,5,9,0,0,0);
	}
}

int shipType(int ship)          //Returns the type of ship according to size
{
	int x = ship/base, y = ship % base;
	if(x >= 420 && x <=460 && y <= 400 && y >= 320)
		return 0;
	else
	if(x >= 460 && x <=500 && y <= 400 && y >= 280)
		return 1;
	else
	if(x >= 500 && x <=540 && y <= 400 && y >= 240)
		return 2;
	else
	if(x >= 540 && x <=580 && y <= 400 && y >= 200)
		return 3;
	else
		return 10;
}

bool checkOverlap(int x1[],int x2[],int y1[],int y2[],int val[],int ch) //Checks whether ship to be placed overlaps or not and also that 1x1 ships are disallowed
{
int ctr;
for(int i = 0;i<4;i++)
{
    ctr=0;
	if(val[i]!=0)
	{
		if(x1[ch] - x2[ch] == 0)
		{
			if(y2[ch] > y1[ch])
			{
				repeat(y2[ch]-y1[ch]+1)
				{
					if( ((x1[ch] >= x1[i] && x1[ch] <= x2[i]) || (x1[ch] >= x2[i] && x1[ch] <= x1[i])) && ((y1[ch]+ctr >= y1[i] && y1[ch]+ctr <= y2[i]) || (y1[ch]+ctr >= y2[i] && y1[ch]+ctr<= y1[i])) )
					return false;
					else
					ctr++;					
			    }
			}	
			else
			if(y1[ch] > y2[ch])
			{
				repeat(y1[ch]-y2[ch]+1)
				{
					if( ((x1[ch] >= x1[i] && x1[ch] <= x2[i]) || (x1[ch] >= x2[i] && x1[ch] <= x1[i])) && ((y2[ch]+ctr >= y1[i] && y2[ch]+ctr <= y2[i]) || (y2[ch]+ctr >= y2[i] && y2[ch]+ctr<= y1[i])) )
					return false;
					else
					ctr++;					
			    }
			}	
			else
            return false;			
		}
		else
		if(y1[ch] - y2[ch] == 0)
		{
			if(x2[ch] > x1[ch])
			{
				repeat(x2[ch]-x1[ch]+1)
				{
					if( ((x1[ch]+ctr >= x1[i] && x1[ch]+ctr <= x2[i]) || (x1[ch]+ctr >= x2[i] && x1[ch]+ctr <= x1[i])) && ((y1[ch] >= y1[i] && y1[ch] <= y2[i]) || (y1[ch] >= y2[i] && y1[ch]<= y1[i])) )
					return false;
					else
					ctr++;
				}
			}
			else
			if(x1[ch] > x2[ch])
			{
				repeat(x1[ch]-x2[ch]+1)
				{
					if( ((x2[ch]+ctr >= x1[i] && x2[ch]+ctr <= x2[i]) || (x2[ch]+ctr >= x2[i] && x2[ch]+ctr <= x1[i])) && ((y1[ch] >= y1[i] && y1[ch] <= y2[i]) || (y1[ch] >= y2[i] && y1[ch]<= y1[i])) )
			        return false;
					else
					ctr++;
				}
			}
			else
			return false;
		}
	}
}
return true;
}
		
			
				

void create(int x1[], int y1[], int x2[],int y2[],int o) // Setting up ship positions
{

	Text t(textBoxX,textBoxY,"");
	setup(1);
	int ch,val[4],i=0,clickVal1,clickVal2,ship;
	repeat(4)
		{val[i]=0;
		i++;}

choice : t.reset(textBoxX,textBoxY,"Click on ship to be placed. If none present click anywhere on canvas");
	ship = getClick();
	if(shipType(ship) < 4) // Returns 0,1,2,3 according to ship placed else return 10
{
	t.reset(textBoxX,textBoxY,"Now click on initial grid position of selected ship");
	ch = shipType(ship);
	if(val[ch]==0) // no ship placed
{
	clickVal1 = getClick();
	t.reset(textBoxX,textBoxY,"1st clicked received .Waiting for 2nd one...");
	clickVal2 = getClick();
	x1[ch] = xCoord(clickVal1);
	x2[ch] = xCoord(clickVal2);
	y1[ch] = yCoord(clickVal1);
	y2[ch] = yCoord(clickVal2);
	if( (checkVal(x1[ch],y1[ch],o)==true) && (checkVal(x2[ch],y2[ch],o)==true) )
	{
		if ((x2[ch]-x1[ch]==ch+1 || x1[ch]-x2[ch]==ch+1 || x2[ch]-x1[ch]==0) && (y2[ch]-y1[ch]==ch+1 || y1[ch]-y2[ch]==ch+1 || y2[ch]-y1[ch]==0) )
		{
			if(checkOverlap(x1,x2,y1,y2,val,ch) == true)
			{
			color(x1[ch],x2[ch],y1[ch],y2[ch],red[ch],green[ch],blue[ch]);
			val[ch]++;
			color(10.5+ch,10.5+ch,8-ch,9,255,255,255);
			t.reset(textBoxX,textBoxY,"BINGO! Spot on"); 
			wait(1);
			goto choice;
			}
			else
			{
			t.reset(textBoxX,textBoxY,"Invalid selection. Either ship placed is of disallowed 1x1 size or it overlaps with prexisting ship"); 
			wait(2);
			goto choice;
			}
		}	
		else
		{
		t.reset(textBoxX,textBoxY,"Invalid selection. Required positioning not according to ship size"); 
		wait(1);
		goto choice;
		}
	}
	else
	{
		t.reset(textBoxX,textBoxY,"Invalid selection. Clicks should lie in grid"); 
		wait(1);
		goto choice;
	}
}
	else
	if(val[0]==0 || val[1]==0 || val[2]==0 || val[3]==0)
	{
		t.reset(textBoxX,textBoxY,"No ships of type remaining. Try others"); 
		wait(1);
		goto choice;
	}
	else
	{
		t.reset(textBoxX,textBoxY,"All ships are done with. Ending ship enter procedure"); 
		wait(1);
		goto exit;
	}
}
else
{
	if(val[0]==1 && val[1]==1 && val[2]==1 && val[3]==1)
	{
		t.reset(textBoxX,textBoxY,"All ships are done with. Ending ship enter procedure"); 
		wait(1);
		goto exit;
	}
	else
	{
		t.reset(textBoxX,textBoxY,"Invalid choice. Click again");
		wait(1);
		goto choice;
	}
}
	exit: t.reset(textBoxX,textBoxY,"");
}

void hide(Rectangle &r,int o) // Hides ships after input from canvas
{
	int ctr = 0;
	for(int i=1;i<=10;i++)
	{
		for(int j=0;j<10;j++)
			{
				r.moveTo((side/2 + (ctr*side) ) + o,(side/2 + (j*side) ));
				r.setFill(true);
				r.setColor(COLOR("white"));
				r.imprint();
				r.setFill(false);
				r.setColor(COLOR("black"));
				r.imprint();
			}
		ctr++;
	}
}

void drawCross(int x,int y) //Draws crosses on grid for missed chances
{
	Line l(x*side,y*side,(x + 1)*side,(y + 1)*side);
	l.setColor(COLOR(255,0,0));
	l.imprint();
	l.reset(x*side,(y + 1)*side,(x + 1)*side,y*side);
	l.setColor(COLOR(255,0,0));
	l.imprint();
}


main_program
{
	initCanvas("BATTLESHIPS",1000,600); 
	
	Rectangle r(textBoxX,textBoxY,600,40);
	r.imprint();
	r.reset(side/2,side/2,side,side);
	Text t(textBoxX,textBoxY,"WELCOME");
	int i,clickVal,x,y,countA = 14,countB = 14;

	int x11[4],x12[4],y11[4],y12[4],x21[4],x22[4],y21[4],y22[4];
	for(i = 0;i<4;i++)
		{
			x11[i]=0; x12[i]=0; x21[i]=0;  x22[i]=0;
			y11[i]=0; y12[i]=0; y21[i]=0;  y22[i]=0;
		}
 
	Grid(r);
	t.hide();
	create(x11,y11,x12,y12,o1);
	hide(r,o1);
	create(x21,y21,x22,y22,o2);	 
	hide(r,o2);
	 
	while(true)
		{
			//Player 1's turn
			retryA : t.reset(textBoxX,textBoxY,"Player 1's turn. Click on suspicious location");
			clickVal = getClick();
			x = xCoord(clickVal);
			y = yCoord(clickVal);
			if(checkVal(x,y,o2) == true)
				{
					for(i = 0;i < 4;i++)
						{
							if( ((x >= x21[i] && x <= x22[i]) || (x >= x22[i] && x <= x21[i])) && ((y >= y21[i] && y <= y22[i]) || (y >= y22[i] && y <= y21[i])) )
								{
									color(x,x,y,y,0,0,0);
									countA--;
									if(countA == 0 && countB > 1)
										{
											t.reset(textBoxX,textBoxY,"Player 2 wins. Congrats!");
											wait(1.5);
											goto end;
										}
									else
										goto endA;
								}
						}
					t.reset(textBoxX,textBoxY,"Oops! Your shot missed!");
					drawCross(x,y);
				endA : wait(1.5);
				}
			else
				{
					t.reset(textBoxX,textBoxY,"Invalid click, it should be on your enemy's grid. Try again");
					wait(1.5);
					goto retryA;
				}

				// Player 2's turn
		retryB : t.reset(textBoxX,textBoxY,"Player 2's turn. Click on suspicious location");
		clickVal = getClick();
		x = xCoord(clickVal);
		y = yCoord(clickVal);
		if(checkVal(x,y,o1) == true)
			{
				for(i = 0;i < 4;i++)
					{
						if( ((x >= x11[i] && x <= x12[i]) || (x >= x12[i] && x <= x11[i])) && ((y >= y11[i] && y <= y12[i]) || (y >= y12[i] && y <= y11[i])) )
							{
								color(x,x,y,y,0,0,0);
								countB--;
								if(countB == 0 && countA > 0)
									{
										t.reset(textBoxX,textBoxY,"Player 2 wins. Congrats!");
										for(int i=0;i<255;i++)
										t.setColor(COLOR(i,i,i));
										
										wait(1.5);
										goto end;
									}
								else
								if(countB == 0 && countA == 0)
									{
										t.reset(textBoxX,textBoxY,"The game is a draw");
										wait(1.5);
										goto end;
									}
								else
								goto endB;
							}
					}
				t.reset(textBoxX,textBoxY,"Oops! Your shot missed!");
				drawCross(x,y);
		 endB : wait(1.5);
			}
		else
			{
				t.reset(textBoxX,textBoxY,"Invalid click, it should be on your enemy's grid. Try again");
				wait(1.5);
				goto retryB;
			}
	}
	
	end : for(i=0;i<4;i++)
	{
		color(x11[i],x12[i],y11[i],y12[i],red[i],green[i],blue[i]);
		color(x21[i],x22[i],y21[i],y22[i],red[i],green[i],blue[i]);
	}
	t.reset(textBoxX,textBoxY,"Game ends, thank you");
	wait(5);
	cout<<"\n";
}