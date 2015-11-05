#include<simplecpp>
#include"head.h"
void board(){
		Rectangle r[8][8];
		for(int j=0;j<8;j++){
			for(int i=0;i<8;i++){
				r[i][j].reset(100*(i+1),100*(j+1),100,100);
			}
		}
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
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				r[i][j].imprint();
			}
		}
		}

	struct player
	{
		Circle c[12];
		player(int n){
			if(n){
			for(int i=0;i<8;i=i+2){
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
			}
			else{
				for(int i=0;i<8;i=i+2){
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
		int checkpawn(int x, int y)
		{
			int i;
			for(i=0;i<12;i++)
			{
				if(100*x==c[i].getX()&&100*y==c[i].getY())break;
			}
			return i;
		}
		int validmove(int b, int x, int y, int* a,const player &com){
			if(a[x-1][y-1])==-1){cout<<"Cannot move on white";return 0;}
			else if(a[x-1][y-1]==1||a[x-1][y-1]==2){cout<<"Cannot move on pawn";return 0;}
			else{
				int x1=c[b].getX(),y1=c[b].getY(),i;
				if(y*100==y1+100&&(x*100==x1-100||x*100==x1+100)){
					a[x1/100-1][y1/100-1]=0;a[x-1][y-1]=1;
					c[b].moveTo(x*100,y*100);
					return 1;}
				else if(y*100==y1+200&&x*100==x1-200){
					if(a[x][y-2]==2){
						a[x1/100-1][y1/100-1]=0;a[x-1][y-1]=1;a[x][y-2]=0;c[b].moveTo(x*100,y*100);
						for(i=0;i<12;i++){if(x*100==com.c[i].getX()&&(y-2)*100==com.c[i].getY())com.c[i].moveTo(10000,10000);}

						return 2;}
				}
				else if(y*100==y1+200&&x*100==x1+200){
					if(a[x-2][y-2]==2){
						a[x1/100-1][y1/100-1]=0;a[x-1][y-1]=1;a[x-2][y-2]=0;c[b].moveTo(x*100,y*100);
						for(i=0;i<12;i++){if(x*100==com.c[i].getX()&&(y-2)*100==com.c[i].getY())com.c[i].moveTo(10000,10000);}
						return 2;
				}
				else return 0;
			}
		}
		 
	};
	int get_index(int n){
		if(n<50||n>850)return 0;
		else return (n+50)/100;
	}
		

		


int main(){
	int x,y,z,x1,y1,z1,c;
	int a[8][8]={{1,-1,1,-1,1,-1,1,-1},
	{-1,1,-1,1,-1,1,-1,1},{1,-1,1,-1,1,-1,1,-1},{-1,0,-1,0,-1,0,-1,0},
	{0,-1,0,-1,0,-1,0,-1},{-1,2,-1,2,-1,2,-1,2},{2,-1,2,-1,2,-1,2,-1},{-1,2,-1,2,-1,2,-1,2}
	};
	
	bool chanceofuser=true;
	initCanvas("board",1000,1000);
	board();
	player com(0),user(1);
	while(1){
		if(chanceofuser){
		z=getClick();
		x=z/65536;
		y=z%65536;
		x=get_index(x);
		if(!x){
			cout<<"Invalid click; Click inside the board"<<endl;
			continue;}
		y=get_index(y);
		if(!y){
			cout<<"Invalid click; Click inside the board"<<endl;
			continue;}
			c=user.checkpawn(x,y);
		if(c==12){
			cout<<"Invalid click; Click on your pawn"<<endl;continue;}
			while(1)
			{
			z1=getClick();
		x1=z1/65536;
		y1=z1%65536;
		x1=get_index(x1);
		if(!x1){
			cout<<"Invalid click; Click inside the board"<<endl;
			continue;}
		y1=get_index(y1);
		if(!y1){
			cout<<"Invalid click; Click inside the board"<<endl;
			continue;}
			if(!user.validmove(c,x1,y1,a)){cout<<"Select move again"<<endl;continue;}
			else if(user.validmove(c,x1,y1,a)==2){cout<<"Opponent killed; move again"<<endl;}
			
			break;
			}

	



		}
		

	}
	getClick();
}