/*
**Author: Janak Agrawal 
**Date created: 1 Oct. 2015 
**Date Last modified: 18 Jan. 2020 
**License: MIT 
**C++ version: C++ 14
**Description: A very basic UI to play 2 player checkers.
*/

#include<simplecpp>
#include"head.h"

\\Function to initialize the checkers board.
\\Creates a 8x8 board of class rectangle. Sets the pieces on the board by setting the values in rectangle to 1 and then prints the board.
void board()
{
	Rectangle r[8][8];
	
	\\reset the position of the puck in the graphical board to be printed.
	for(int j=0;j<8;j++)
	{
		for(int i=0;i<8;i++)
		{
			r[i][j].reset(100*(i+1),100*(j+1),100,100);
		}
	}
	
	\\fill all the positions on a new checker board.
	for(int j=0;j<8;j=j+2){
		r[j][0].setFill(1);
		r[j][2].setFill(1);
		r[j][4].setFill(1);
		r[j][6].setFill(1);
	}
	for(int j=1;j<8;j=j+2){
		r[j][1].setFill(1);
		r[j][3].setFill(1);
		r[j][5].setFill(1);
		r[j][7].setFill(1);
	}	
	
	\\print the board by printing each cell.
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			r[i][j].imprint();
		}
	}
}

\\A struct to store the positions of all the player's pucks using an array of the struct Circle.
\\
\\Attributes:
\\	c: an array of Circle to keep track of a player's 12 pucks
struct player
{	
	Circle c[12];

	\\A constructor to set the color of the player based on if the value of n is 0 or 1.
	\\Args:
	\\	n: int used to identify the color of player
	player(int n)
	{
		\\If n is 1 set the color of this player to gray or else black.
		if(n)
		{
			for(int i=0;i<8;i=i+2)
			{
				c[i/2].reset(100*(i+1),100,30);
				c[i/2].setColor(COLOR(220,220,220));
				c[i/2].setFill(1);
				c[i/2+4].reset(100*(i+2),200,30);
				c[i/2+4].setColor(COLOR(220,220,220));
				c[i/2+4].setFill(1);
				c[i/2+8].reset(100*(i+1),300,30);
				c[i/2+8].setColor(COLOR(220,220,220));
				c[i/2+8].setFill(1);
			}
		}else
		{
			for(int i=0;i<8;i=i+2)
			{
				c[i/2].reset(100*(i+2),600,30);
				c[i/2].setColor(COLOR(70,70,70));
				c[i/2].setFill(1);
				c[i/2+4].reset(100*(i+1),700,30);
				c[i/2+4].setColor(COLOR(70,70,70));
				c[i/2+4].setFill(1);
				c[i/2+8].reset(100*(i+2),800,30);
				c[i/2+8].setColor(COLOR(70,70,70));
				c[i/2+8].setFill(1);
			}
		}
	}
	
	\\Check if the player has a pawn at the position (x,y)
	\\Args:
	\\	x: int of x position on board
	\\	y: int of y position on board
	\\Returns:
	\\	pawn number if it exists at x,y otherwise 12
	int checkpawn(int x, int y)
	{
		int i;
		
		\\iterate over all of players pawn and compare their coordinates.
		for(i=0;i<12;i++)
		{
			if(100*x==c[i].getX()&&100*y==c[i].getY())break;
		}
		
		return i;
	}
	
	\\check if a pawn can be moved to the position (x,y).
	\\Args:
	\\	b: the pawn number
	\\	x: the new x position
	\\	y: the new y position
	\\	a: the board as an int array
	\\	com: the competitor player struct
	\\Returns:
	\\	1 if valid move in adjacent cell
	\\	2 if jumping over pawn
	\\	0 if invalid
	int validmove(int b, int x, int y, int* a,const player &com)
	{
		\\check if the there is pawn between the current and new position
		if(a[x-1][y-1])==-1){cout<<"Cannot move on white";return 0;}
		\\check if pawn exists at new position
		else if(a[x-1][y-1]==1||a[x-1][y-1]==2){cout<<"Cannot move on pawn";return 0;}
		else
		{
			int x1=c[b].getX(),y1=c[b].getY(),i;
			\\check if moving to adjacent cell
			if(y*100==y1+100&&(x*100==x1-100||x*100==x1+100))
			{
				a[x1/100-1][y1/100-1]=0;a[x-1][y-1]=1;
				c[b].moveTo(x*100,y*100);
				return 1;
			}
			\\check if jumping over pawn to left
			else if(y*100==y1+200&&x*100==x1-200)
			{
				if(a[x][y-2]==2)
				{
					a[x1/100-1][y1/100-1]=0;a[x-1][y-1]=1;a[x][y-2]=0;c[b].moveTo(x*100,y*100);
					for(i=0;i<12;i++)
					{
						if(x*100==com.c[i].getX()&&(y-2)*100==com.c[i].getY())com.c[i].moveTo(10000,10000);
					}
					return 2;
				}
			}
			\\check if jumping over pawn to right	
			else if(y*100==y1+200&&x*100==x1+200)
			{
				if(a[x-2][y-2]==2)
				{
					a[x1/100-1][y1/100-1]=0;a[x-1][y-1]=1;a[x-2][y-2]=0;c[b].moveTo(x*100,y*100);
					for(i=0;i<12;i++)
					{
						if(x*100==com.c[i].getX()&&(y-2)*100==com.c[i].getY())com.c[i].moveTo(10000,10000);
					}
						return 2;
				}
			else return 0;
		}
	}
};

\\convert from pixel value to index of cell on board
\\Args:
\\	n:value of pixel
\\Returns:
\\	index of cell on board
int get_index(int n){
	if(n<50||n>850)return 0;
	else return (n+50)/100;
}

int main()
{
	\\initialize players and board
	int x,y,z,x1,y1,z1,c;
	int a[8][8]={{1,-1,1,-1,1,-1,1,-1},
	{-1,1,-1,1,-1,1,-1,1},{1,-1,1,-1,1,-1,1,-1},{-1,0,-1,0,-1,0,-1,0},
	{0,-1,0,-1,0,-1,0,-1},{-1,2,-1,2,-1,2,-1,2},{2,-1,2,-1,2,-1,2,-1},{-1,2,-1,2,-1,2,-1,2}
	};
	
	bool chanceofuser=true;
	initCanvas("board",1000,1000);
	board();
	player com(0),user(1);
	
	\\while loop to run the game
	while(1)
	{
		\\check if its first players chance
		if(chanceofuser)
		{
			\\get coordinates of the user click on pawn
			z=getClick();
			x=z/65536;
			y=z%65536;
			x=get_index(x);
			
			\\check if x coordinate of click was valid
			if(!x)
			{
				cout<<"Invalid click; Click inside the board"<<endl;
				continue;
			}
			
			\\check if y coordinate of click was valid
			y=get_index(y);
			if(!y)
			{
				cout<<"Invalid click; Click inside the board"<<endl;
				continue;
			}
			
			\\check if click was on users pawn
			c=user.checkpawn(x,y);
			if(c==12)
			{
				cout<<"Invalid click; Click on your pawn"<<endl;continue;
			}
			
			\\while loop to move the selected pawn
			while(1)
			{
				\\get coordinates of players click to move the pawn
				z1=getClick();
				x1=z1/65536;
				y1=z1%65536;
				x1=get_index(x1);
				if(!x1)
				{
					cout<<"Invalid click; Click inside the board"<<endl;
					continue;
				}
				y1=get_index(y1);
				if(!y1)
				{
					cout<<"Invalid click; Click inside the board"<<endl;
					continue;
				}
				
				\\check if the move was valid
				if(!user.validmove(c,x1,y1,a)){cout<<"Select move again"<<endl;continue;}
				else if(user.validmove(c,x1,y1,a)==2){cout<<"Opponent killed; move again"<<endl;continue;}
			
				break;
			}
		}		
	}
	getClick();
}
