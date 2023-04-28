#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_board(int board[][4]) {
    for(int n=0;n<4;n++){
        for(int m=0;m<4;m++){
            printf("\t%d",board[n][m]);
        }
        printf("\r\n");
    }
}

void appear(int board[][4]){
    int x=rand()%4; 
    int y=rand()%4;
    while(board[x][y]!=0){
        x=rand()%4; y=rand()%4;
    }
    if(rand()%10==0){
        board[x][y]=4;
    }else{
        board[x][y]=2;
    }
}

void sort(int c,int board[][4]){
    for(int n=0;n<4;n++){
        for(int r=0;r<4;r++){
            for(int m=0;m<3;m++){
                if(c=='k'){
                    if(board[n][m]!=0&&board[n][m+1]==0){
                        board[n][m+1]=board[n][m];
                        board[n][m]=0;
                    }
                }else if(c=='m'){
                    if(board[m][n]!=0&&board[m+1][n]==0){
                        board[m+1][n]=board[m][n];
                        board[m][n]=0;
                    }
                }else if(c=='j'){
                    if(board[n][m]==0&&board[n][m+1]!=0){
                        board[n][m]=board[n][m+1];
                        board[n][m+1]=0;
                    }
                }else if(c=='i'){
                    if(board[m][n]==0&&board[m+1][n]!=0){
                        board[m][n]=board[m+1][n];
                        board[m+1][n]=0;
                    }
                }
            }   
        }
    }
}


void calliculate(int c,int board[][4]){
    for(int n=0;n<4;n++){
        if(c=='k'){
            if(board[n][3]==board[n][2]){
                board[n][3]*=2;
                board[n][2]=0;
                if(board[n][1]==board[n][0]){
                    board[n][1]*=2;
                    board[n][0]=0;
                }
            }else if(board[n][2]==board[n][1]){
                board[n][2]*=2;
                board[n][1]=0;
            }else if(board[n][1]==board[n][0]){
                board[n][1]*=2;
                board[n][0]=0;
            }
        }else if(c=='m'){
            if(board[3][n]==board[2][n]){
                board[3][n]*=2;
                board[2][n]=0;
                if(board[1][n]==board[0][n]){
                    board[1][n]*=2;
                    board[0][n]=0;
                }
            }else if(board[2][n]==board[1][n]){
                board[2][n]*=2;
                board[1][n]=0;
            }else if(board[1][n]==board[0][n]){
                board[1][n]*=2;
                board[0][n]=0;
            }
        }else if(c=='j'){
            if(board[n][0]==board[n][1]){
                board[n][0]*=2;
                board[n][1]=0;
                if(board[n][2]==board[n][3]){
                    board[n][2]*=2;
                    board[n][3]=0;
                }
            }else if(board[n][1]==board[n][2]){
                board[n][1]*=2;
                board[n][2]=0;
            }else if(board[n][2]==board[n][3]){
                board[n][2]*=2;
                board[n][3]=0;
            }
        }else if(c=='i'){
            if(board[0][n]==board[1][n]){
                board[0][n]*=2;
                board[1][n]=0;
                if(board[2][n]==board[3][n]){
                    board[2][n]*=2;
                    board[3][n]=0;
                }
            }else if(board[1][n]==board[2][n]){
                board[1][n]*=2;
                board[2][n]=0;
            }else if(board[2][n]==board[3][n]){
                board[2][n]*=2;
                board[3][n]=0;
            }
        }
    }
}


int main (int argc, char *argv[]){
    srand((unsigned)time(NULL));
    int x=0;
    int y=0;
    int board[4][4]={
        {0,0,0,0}, 
        {0,0,0,0}, 
        {0,0,0,0}, 
        {0,0,0,0}
    };
    printf("Press any key to conitnue\n");
    int c;
    
    appear(board);
    appear(board);
    
    system("/bin/stty raw onlcr");  // enterを押さなくてもキー入力を受け付けるようになる

    system("clear");
    printf("Press '.' to close\r\n");
    print_board(board);
    printf("right:k  up:i left:j  down:m\r\n");

    while((c = getchar()) != '.'){

        sort(c,board);
        calliculate(c,board);
        sort(c,board);
        int count=0;
        for(int n=0;n<4;n++){
            for(int m=0;m<4;m++){
                if(board[n][m]==0){
                    count++;
                }
                if(board[n][m]==2048){
                    count-=20;
                }
            }
        }
        if(count<0){
            printf("GAME CLEAR!\r\n");
            break;
        }else if(count<2){
            printf("GAME OVER...\r\n");
            break;
        }

        appear(board);

        system("clear");
        printf("Press '.' to close\r\n");
        print_board(board);
        
        printf("right:k  up:i left:j  down:m\r\nYou pressed '%c'\r\n", c);
    }

    system("/bin/stty cooked");  // 後始末

    return 0;
}