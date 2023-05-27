#include<windows.h>
#include <graphics.h>
#include <stdio.h>

typedef struct snake {
	int body[100][2];
	int lenght;
	int direction;
} snake;

typedef struct fruit {
	int x, y;
}fruit;

typedef struct state {
	snake *snake;
	fruit *fruit;
	int highscore;
}state;




void run(state *state, int tile);
void render(state *state, int tile);
void move(state *state, int tile);
void spawnfruit(state *state);
void save(state *state);
void load(state *state);

main () {
	int tile = 20;
	int i, j, k;
	
	state state;
	snake snake;
	fruit fruit;
	state.highscore = 0;
				
				snake.lenght = 2;
				snake.direction = 1;
				snake.body[0][0] = 5;
				snake.body[0][1] = 2;
				snake.body[1][0] = 6;
				snake.body[1][1] = 2;
				
				
	state.snake = &snake;
	state.fruit = &fruit;
	spawnfruit(&state);
 	initwindow(500, 500);
 	
 	load(&state);
 
 	run(&state, tile);

	getch();
} 

void load(state *state) {
	FILE *fp;
	
	fp = fopen("./score.ini", "rb+");
	fread((void*)&state->highscore, sizeof(state->highscore), 1, fp);
	fclose(fp);
}

void save(state *state) {
	
		FILE *fp;
		
		fp = fopen("./score.ini", "wb+");
		fwrite((void*)&state->highscore, sizeof(state->highscore), 1, fp);
		fclose(fp);
}

void spawnfruit(state *state) {
	fruit *fruit = state->fruit;
	
	fruit->x = rand() % 20;
	fruit->y = rand() % 20;
}

void move(state *state,int tile) {
	int i;
	snake *snake = state->snake;
	fruit *fruit = state->fruit;
	int lenght = snake->lenght;
	
	for(i = lenght; i > 0; i--) {
		int aux = i - 1;

		snake->body[i][0] = snake->body[aux][0];
		snake->body[i][1] = snake->body[aux][1];
	}
	
	
	if(GetAsyncKeyState(VK_UP)) {
		snake->direction = 0;
	}else if(GetAsyncKeyState(VK_RIGHT)) {
		snake->direction = 1;
	}else if(GetAsyncKeyState(VK_DOWN)) {
		snake->direction = 2;
	}else if(GetAsyncKeyState(VK_LEFT)) {
		snake->direction = 3;
	}
	
	if(snake->direction == 0) {
		snake->body[0][0] = snake->body[0][0];
		snake->body[0][1] = snake->body[0][1] - 1;
	}else if(snake->direction == 1) {
		snake->body[0][0] = snake->body[0][0] + 1;
		snake->body[0][1] = snake->body[0][1];
	}else if(snake->direction == 2) {
		snake->body[0][0] = snake->body[0][0];
		snake->body[0][1] = snake->body[0][1] + 1;
	}else if(snake->direction == 3) {
		snake->body[0][0] = snake->body[0][0] - 1;
		snake->body[0][1] = snake->body[0][1];
	}
	
	if(snake->body[0][1] < 0) {
		snake->body[0][1] = 25;
	}else if(snake->body[0][0] > 25) {
		snake->body[0][0] = 0;
	}else if(snake->body[0][1] > 25) {
		snake->body[0][1] = 0;
	}else if(snake->body[0][0] < 0) {
		snake->body[0][0] = 25;
	}
	
	
	
	if(snake->body[0][0] == fruit->x && snake->body[0][1] == fruit->y) {
		snake->lenght++;
		snake->body[lenght][0] = snake->body[lenght-1][0];
		snake->body[lenght][1] = snake->body[lenght-1][1];
		
		spawnfruit(state);
	}
	
	for(i = 1; i < lenght; i++) {
		if(snake->body[0][0] == snake->body[i][0]  &&  snake->body[0][1] == snake->body[i][1]) {
			save(state);
			closegraph();
			break;
		}
	}
	
}

void run(state *state,int  tile) {
	render(state, tile);
	move(state, tile);
	snake *snake = state->snake;
	
	if(snake->lenght > state->highscore) {
		state->highscore = snake->lenght;
		
	}
	
	
	delay(300);
	run(state, tile);
}


void render(state *state, int tile) {
	int i, j, k;
	snake *snake = state->snake;
	fruit *fruit = state->fruit;
	
	setfillstyle(SOLID_FILL, 0);
	bar(0, 0, 500, 500);
	
	
	settextstyle(3, 0, 5);
	char buffer[10];
	itoa(state->highscore, buffer, 10);
	outtextxy ( 220, 10, buffer);
	
	
	
	setfillstyle(SOLID_FILL, 2);
	 for(i =0; i < snake->lenght; i++) {

		 	int bodytileX = snake->body[i][0] ;
		 	int bodytileY = snake->body[i][1] ;
		 	
		 	bar(bodytileX * tile, bodytileY * tile, (bodytileX * tile) + tile, (bodytileY * tile)+ tile);
	}
	
	setfillstyle(SOLID_FILL, 4);
	bar((fruit->x * tile), fruit->y * tile, (fruit->x * tile) + tile, (fruit->y * tile)+ tile);
	
	
	
		
}

