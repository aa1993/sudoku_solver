#include <curses.h>
#include <stdlib.h> //noetig fuer atexit()

char board[9][9] = {{'.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.'}};

int curx;
int cury;

void quit()
{
  endwin();
}

void render()
{
  clear();

  mvprintw(0, 0, "%c%c%c|%c%c%c|%c%c%c", board[0][0], board[1][0], board[2][0], board[3][0], board[4][0], board[5][0], board[6][0], board[7][0], board[8][0]);
  mvprintw(1, 0, "%c%c%c|%c%c%c|%c%c%c", board[0][1], board[1][1], board[2][1], board[3][1], board[4][1], board[5][1], board[6][1], board[7][1], board[8][1]);
  mvprintw(2, 0, "%c%c%c|%c%c%c|%c%c%c", board[0][2], board[1][2], board[2][2], board[3][2], board[4][2], board[5][2], board[6][2], board[7][2], board[8][2]);
  mvprintw(3, 0, "---+---+---");
  mvprintw(4, 0, "%c%c%c|%c%c%c|%c%c%c", board[0][3], board[1][3], board[2][3], board[3][3], board[4][3], board[5][3], board[6][3], board[7][3], board[8][3]);
  mvprintw(5, 0, "%c%c%c|%c%c%c|%c%c%c", board[0][4], board[1][4], board[2][4], board[3][4], board[4][4], board[5][4], board[6][4], board[7][4], board[8][4]);
  mvprintw(6, 0, "%c%c%c|%c%c%c|%c%c%c", board[0][5], board[1][5], board[2][5], board[3][5], board[4][5], board[5][5], board[6][5], board[7][5], board[8][5]);
  mvprintw(7, 0, "---+---+---");
  mvprintw(8, 0, "%c%c%c|%c%c%c|%c%c%c", board[0][6], board[1][6], board[2][6], board[3][6], board[4][6], board[5][6], board[6][6], board[7][6], board[8][6]);
  mvprintw(9, 0, "%c%c%c|%c%c%c|%c%c%c", board[0][7], board[1][7], board[2][7], board[3][7], board[4][7], board[5][7], board[6][7], board[7][7], board[8][7]);
  mvprintw(10, 0, "%c%c%c|%c%c%c|%c%c%c", board[0][8], board[1][8], board[2][8], board[3][8], board[4][8], board[5][8], board[6][8], board[7][8], board[8][8]);

  mvprintw(12,0, "Navigate with arrow keys and input with numberkeys.");
  mvprintw(13,0, "Delete a field with the '0' or '.' key.");
  mvprintw(14,0, "Solve it with the 'l' key.");

  move(cury+0+(cury/3), curx+0+(curx/3));
  refresh();
}

void next(void){
  cury = (cury + ((curx+1)/9)) % 9;
  curx = (curx +1) %9;
}

int correctspot(int x, int y){
  if(x<0 || x>8){
    mvprintw(15,10, "correctspot: x cant be %d", x);
    getch();
    return 0;
  }
  if(y<0 || y>8){
    mvprintw(15,10, "correctspot: y cant be %d", y);
    getch();
    return 0;
  }

  char c = board[x][y];

  for(int i = 0; i<9 ; i++){
    if(i!=x && c == board[i][y])
      return 0;
  }

  for(int j = 0; j<9 ; j++){
    if(j!=y && c == board[x][j])
      return 0;
  }

  int istart = x/3*3;
  int jstart = y/3*3;
  int iend = istart+3;
  int jend = jstart+3;

  for(int i = istart; i < iend; i++){
    for(int j = jstart; j< jend; j++){
      if(i!=x && j!=y && c==board[i][j])
        return 0;
    }
  }
  return 1;
}

int solve(void){
  int x =0;
  int y =0;
  for(int i = 0;i<9;i++){
    for(int j = 0;j<9;j++){
      if(board[i][j]=='.'){
        x=i;
        y=j;
        i=9;
        j=9;
      }
    }
  }
  if(x==0 && y==0 && board[0][0]!='.')
    return 1;

  for(char c = '1'; c<='9' ; c++){
    board[x][y]=c;
    if(0 == correctspot(x,y)){
      continue;
    }
    if(1== solve()){
      return 1;
    }
  }
  board[x][y]='.';
  return 0;
}

int main(void)
{
  initscr();
  atexit(quit);
  curs_set(1);
  noecho();
  curx=0;
  cury= 0;
  render();

  while(1){
    switch(getch())
      {
      case 'q':
        return(0);
      case '0':
      case '.':
        board[curx][cury]='.';
        next();
        break;
      case '1':
        board[curx][cury]='1';
        next();
        break;
      case '2': 
        board[curx][cury]='2';
        next();
        break;
      case '3':
        board[curx][cury]='3';
        next();
        break;
      case '4':
        board[curx][cury]='4';
        next();
        break;
      case '5':
        board[curx][cury]='5';
        next();
        break;
      case '6':
        board[curx][cury]='6';
        next();
        break;
      case '7':
        board[curx][cury]='7';
        next();
        break;
      case '8':
        board[curx][cury]='8';
        next();
        break;
      case '9':
        board[curx][cury]='9';
        next();
        break;
      case 'l':
        solve();
        break;
      case 27:
        if(getch()==91)
          switch(getch()){
          case 65: //up
            cury = (cury+8)% 9;
            break;
          case 66: //down
            cury = (cury+1)% 9;
            break;
          case 68: //left
            curx = (curx+8)% 9;
            break;
          case 67: //right
            curx = (curx+1)% 9;
            break;
          }
        break;
      }
      /*
    for(int i = 0;i<10;i++){
      c= getch();
      mvprintw(2, i*4+2, "%d", (int)c);
        if(c=='q')
          return 0;
    }
    */
    render();
  }

  getch();
  return(0);
}
