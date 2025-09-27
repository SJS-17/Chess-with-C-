#include <iostream>
#include "chess.hpp"

namespace chesser {
//BOARD GAME

Board::Board() {
    white=new Player('W', this);
    black=new Player('B', this);
    std::string w_pawn="WP ";
    std::string b_pawn="BP ";
    for (int i=0; i<8; i++) {
        char w_temp='8'-i;
        w_pawn[2]=w_temp;
        grid[1][i]=w_pawn;
        char b_temp='0'+i+1;
        b_pawn[2]=b_temp;
        grid[6][i]=b_pawn;
    }
    // Initializing the Grid
    std::string w_bishop="WB1";
    std::string b_bishop="BB1";
    
    std::string w_knight="WL1";
    std::string b_knight="BL1";
    
    std::string w_rook="WR1";
    std::string b_rook="BR1";
    for (int i=0; i<4; i++) {
        switch (i) {
            case 0:
                grid[0][i]=w_rook;
                w_rook[2]='2';
                grid[0][7-i]=w_rook;
                grid[7][i]=b_rook;
                b_rook[2]='2';
                grid[7][7-i]=b_rook;
                break;
            case 1:
                grid[0][i]=w_knight;
                w_knight[2]='2';
                grid[0][7-i]=w_knight;
                grid[7][i]=b_knight;
                b_knight[2]='2';
                grid[7][7-i]=b_knight;
                break;
            case 2:
                grid[0][i]=w_bishop;
                w_bishop[2]='2';
                grid[0][7-i]=w_bishop;
                grid[7][i]=b_bishop;
                b_bishop[2]='2';
                grid[7][7-i]=b_bishop;
                break;
            case 3:
                grid[0][i]=(white->king())->return_name();
                grid[0][7-i]=(white->queen())->return_name();
                grid[7][i]=(black->king())->return_name();
                grid[7][7-i]=(black->queen())->return_name();
                break;
        }
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (grid[i][j]=="") {
                grid[i][j]="___";
            }
        }
    }
}

Board::~Board() {
    white->eliminate();
    black->eliminate();
    delete white;
    delete black;
}

std::string Board::piece_here(int r, int c) const{
    return grid[r][c];
}

void Board::display(char color) {
    std::cout << std::endl;
    for (int i=1; i<=42;i++) {
        std::cout << "_";
    }
    std::cout << std::endl;
    std::cout << "  |  1";
    for (int i=2; i<=8; i++) {
        char n='0'+i;
        std::cout << "    " << n;
    }
    std::cout << std::endl << "__|_";
    for (int i=5; i<=42;i++) {
        std::cout << "_";
    }
    std::cout << std::endl << "  |" << std::endl;
    if (color=='B') {
        for (int i=0; i<8; i++) {
            char n='1'+i;
            std::cout << n << " | ";
            for (int j=0; j<8; j++) {
                std::cout << grid[i][j];
                if (j<7) {
                    std::cout << "  ";
                }
            }
            if (i<7) {
                std::cout << std::endl << "  | " << std::endl;
            }
            else {
                std::cout << std::endl << "__|";
            }
        }
    }
    
    if (color=='W') {
        for (int i=7; i>=0; i--) {
            char n='8'-i;
            std::cout << n << " | ";
            for (int j=7; j>=0; j--) {
                std::cout << grid[i][j];
                if (j>0) {
                    std::cout << "  ";
                }
            }
            if (i>0) {
                std::cout << std::endl << "  | " << std::endl;
            }
            else {
                std::cout << std::endl << "__|";
            }
        }
    }
    for (int i=4; i<=42;i++) {
        std::cout << "_";
    }
    std::cout << std::endl;
}

bool Board::move_checker(char c, int ir, int ic, int dr, int dc) const{ //This checks whether or not there are pieces in the way of the movement, but checking how the piece moves is up to the functions of the individual piece;
    int fr=ir+dr;
    int fc=ic+dc;
    if ((grid[fr][fc])[0]==c) {
        return false;
    }
    if (fr>7 || fc>7 || fr<0 || fc<0) {
        return false;
    }
    while (true) {
        if (ir!=fr) {
            if (dr<0) {
                ir--;
            }
            else {
                ir++;
            }
        }
        if (ic!=fc) {
            if (dc<0) {
                ic--;
            }
            else {
                ic++;
            }
        }
        if (ir==fr && ic==fc) {
            break;
        }
        if (grid[ir][ic]!="___") {
            return false;
        }
    }
    
    return true;
}

bool Board::knight_move_checker(char c, int ir, int ic, int dr, int dc) const{
    int fr=ir+dr;
    int fc=ic+dc;
    if (fr>7 || fc>7) {
        return false;
    }
    if (fr<0 || fc<0) {
        return false;
    }
    if ((grid[fr][fc][0])==c) {
        return false;
    }
    
    return true;
}
bool Board::pawn_move_checker(char c, int ir, int ic, int dr, int dc) const{
    int fr=ir+dr;
    int fc=ic+dc;
    int adr=absolute_value(dr);
    int adc=absolute_value(dc);
    if (fr>7 || fc>7) {
        return false;
    }
    if (fr<0 || fc<0) {
        return false;
    }
    if (adr>0 && adc>0 && grid[fr][fc]!="___") {
        return true;
    }
    if (adr>0 && adc>0 && grid[fr][fc]=="___") {
        return false;
    }
    if (grid[fr][fc]!="___") {
        return false;
    }
    else {
        return true;
    }
}

void Board::move_piece(char c, int i_r, int i_c, int f_r, int f_c) {
    std::string temp=grid[f_r][f_c];
    if (temp[1]=='K') {
        if (temp[0]=='W') {
            (white->king())->die();
        }
        if (temp[0]=='B') {
            (black->king())->die();
        }
    }
    grid[f_r][f_c]=grid[i_r][i_c];
    grid[i_r][i_c]="___";
}

int Board::row_returner(char c, std::string piece) {
    if ((piece[0]=='W' && c!='W') || (piece[0]=='B' && c!='B')) {
        return -1;
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (grid[i][j]==piece) {
                return i;
            }
        }
    }
    return -1;
}

int Board::column_returner(char c, std::string piece) {
    if ((piece[0]=='W' && c!='W') || (piece[0]=='B' && c!='B')) {
        return -1;
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (grid[i][j]==piece) {
                return j;
            }
        }
    }
    return -1;
}

void Board::play() {
    std::cout << "Welcome to the game of Chess." << std::endl;
    std::cout << "In order to move pieces in the game, start by inputting the coordinate of the piece you want to move. Then, once prompted, input the coordinate where you wish to move the piece. Each piece is labeled in the following format: (color)(piece type)(piece number)" << std::endl;
    std::cout << "For example, the black king piece would be labeled as BK0 while one of the white pawns will be labeled as WP2" << std::endl;
    std::cout << "Coordinates are chosen in the form of row,column" << std::endl;
    std::cout << "The top left coordinate is 1,1 while the bottom right coordinate would be 8,8" << std::endl;
    std::cout << "Now, Let's begin with white side starting: " << std::endl;
    int counter=1;
    while (white->king_alive() && black->king_alive()) {
        std::cout << std::endl;
        if (counter%2==1) {
            display('W');
            std::cout << std::endl << "White's turn" << std::endl;
        }
        if (counter%2==0) {
            display('B');
            std::cout << std::endl << "Black's turn" << std::endl;
            
        }
        std::string piece("1,1");
        std::string move("1,1");
        int i_r,i_c,f_r,f_c,d_r,d_c;
        std::string name;
        while (true) {
            std::cout<<std::endl;
            std::cout << "Please enter the name of the piece that you want to move: ";
            std::cin >> piece;
            char color;
            if (counter%2==1) {
                color='W';
            }
            else {
                color='B';
            }
            while (row_returner(color, piece)==-1) {
                std::cout << "Please enter a valid piece: ";
                std::cin >> piece;
            }
            i_r=(*this).row_returner(color, piece);
            i_c=this->column_returner(color, piece);
            std::cout << "Enter the coordinate where you would like to move it: ";
            std::cin >> move;
            while (((move[0]-'0')>8) || (move[1]!=',') || ((move[2]-'0')>8) || move.length()!=3) {
                std::cout << "Please enter a valid input: ";
                std::cin >> move;
            }
            if (counter%2==0) {
                f_r=move[0]-'0'-1;
                f_c=move[2]-'0'-1;
                d_r=f_r-i_r;
                d_c=f_c-i_c;
            }
            else {
                f_r=9-(move[0]-'0')-1;
                f_c=9-(move[2]-'0')-1;
                d_r=f_r-i_r;
                d_c=f_c-i_c;
            }
            name=grid[i_r][i_c];
            //            std::cout << "Piece: " << name << std::endl;
            //            std::cout << "d_r=" << d_r << std::endl;
            //            std::cout << "d_c=" << d_c << std::endl;
            switch (name[1]) {
                case 'K':
                    if (counter%2==1) {
                        if ((white->king())->move(i_r,i_c,d_r,d_c)) {
                            move_piece('W',i_r,i_c,f_r,f_c);
                        }
                        else {
                            std::cout << "Please enter a valid input: ";
                            continue;
                        }
                    }
                    if (counter%2==0) {
                        if ((black->king())->move(i_r,i_c,d_r,d_c)) {
                            move_piece('B',i_r,i_c,f_r,f_c);
                        }
                        else {
                            std::cout << "Please enter a valid input: ";
                            continue;
                        }
                    }
                    break;
                case 'Q':
                    if (counter%2==1) {
                        if ((white->queen())->move(i_r,i_c,d_r,d_c)) {
                            move_piece('W',i_r,i_c,f_r,f_c);
                        }
                        else {
                            std::cout << "Please enter a valid input: ";
                            continue;
                        }
                    }
                    if (counter%2==0) {
                        if ((black->queen())->move(i_r,i_c,d_r,d_c)) {
                            move_piece('B',i_r,i_c,f_r,f_c);
                        }
                        else {
                            std::cout << "Please enter a valid input: ";
                            continue;
                        }
                    }
                    break;
                case 'B':
                    if (counter%2==1) {
                        switch (name[2]) {
                            case '1':
                                if ((white->bishop1())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('W',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                            case '2':
                                if ((white->bishop2())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('W',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                        }
                    }
                    if (counter%2==0) {
                        switch (name[2]) {
                            case '1':
                                if ((black->bishop1())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('B',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                            case '2':
                                if ((black->bishop2())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('B',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                        }
                    }
                    break;
                case 'L':
                    if (counter%2==1) {
                        switch (name[2]) {
                            case '1':
                                if ((white->knight1())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('W',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                            case '2':
                                if ((white->knight2())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('W',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                        }
                    }
                    if (counter%2==0) {
                        switch (name[2]) {
                            case '1':
                                if ((black->knight1())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('B',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                            case '2':
                                if ((black->knight2())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('B',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                        }
                    }
                    break;
                case 'R':
                    if (counter%2==1) {
                        switch (name[2]) {
                            case '1':
                                if ((white->rook1())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('W',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                            case '2':
                                if ((white->rook2())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('W',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                        }
                    }
                    if (counter%2==0) {
                        switch (name[2]) {
                            case '1':
                                if ((black->rook1())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('B',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                            case '2':
                                if ((black->rook2())->move(i_r, i_c, d_r, d_c)) {
                                    move_piece('B',i_r,i_c,f_r,f_c);
                                }
                                else {
                                    std::cout << "Please enter a valid input: ";
                                    continue;
                                }
                                break;
                        }
                    }
                    break;
                case 'P':
                    if (counter%2==1) {
                        if ((white->pawn(name[2]))->move('W', i_r, i_c, d_r, d_c)) {
                            move_piece('W', i_r, i_c, f_r, f_c);
                        }
                        else {
                            std::cout << "Please enter a valid input: ";
                            continue;
                        }
                        if (f_r==7) {
                            std::cout << "Enter the piece you would like to convert your pawn to: ";
                            std::string npawn="WQ0";
                            do {
                                if (npawn[0]!='W') {
                                    std::cout << "Please enter a valid piece: ";
                                }
                                std::cin >> npawn;
                                
                            } while (npawn[0]!='W');
                            grid[f_r][f_c]=npawn;
                        }
                    }
                    if (counter%2==0) {
                        if ((black->pawn(name[2]))->move('B', i_r, i_c, d_r, d_c)) {
                            move_piece('B', i_r, i_c, f_r, f_c);
                        }
                        else {
                            std::cout << "Please enter a valid input: ";
                            continue;
                        }
                        if (f_r==0) {
                            std::cout << "Enter the piece you would like to convert your pawn to: ";
                            std::string npawn="BQ0";
                            do {
                                if (npawn[0]!='B') {
                                    std::cout << "Please enter a valid piece: ";
                                }
                                std::cin >> npawn;
                                
                            } while (npawn[0]!='B');
                            grid[f_r][f_c]=npawn;
                        }
                    }
                    break;
            }
            break;
        }
        counter++;
    }
    if (white->king_alive()==false) {
        std::cout << std::endl << "Black side wins!" << std::endl;
    }
    if (black->king_alive()==false) {
        std::cout << std::endl << "White side wins!" << std::endl;
    }
    std::cout << std::endl;
}




//PLAYER
Player::Player(char c, Board* Board) {
    color=c;
    Bd=Board;
    std::string name=" ";
    name[0]=c;
    K=new King(c, name+"K0", Board);
    Q=new Queen(c, name+"Q0", Board);
    B1=new Bishop(c, name+"B1", Board);
    B2=new Bishop(c, name+"B2", Board);
    L1=new Knight(c, name+"L1", Board);
    L2=new Knight(c, name+"L2", Board);
    R1=new Rook(c, name+"R1", Board);
    R2=new Rook(c, name+"R1", Board);
    for (int i=0; i<8; i++) {
        std::string temp="0";
        temp[0]=i+'0';
        P[i]=new Pawn(c, name+"P"+temp, Board);
    }
}


void Player::eliminate() {
    delete K;
    delete Q;
    delete B1;
    delete B2;
    delete L1;
    delete L2;
    delete R1;
    delete R2;
    for (int i=0; i<8; i++) {
        delete P[i];
    }
    std::cout << "Player hopefully deleted" << std::endl;
}

Pawn* Player::pawn(char c) const {
    switch (c) {
        case '1':
            return P[0];
        case '2':
            return P[1];
        case '3':
            return P[2];
        case '4':
            return P[3];
        case '5':
            return P[4];
        case '6':
            return P[5];
        case '7':
            return P[6];
        case '8':
            return P[7];
        default:
            return nullptr;
    }
}

//King
bool King::move(int ir, int ic, int dr, int dc) {
    int adr=absolute_value(dr);
    int adc=absolute_value(dc);
    if (adr>1 || adc>1) {
        return false;
    }
    
    if (B->move_checker(color, ir, ic, dr, dc)) {
        return true;
    }
    return false;
}


//Queen
bool Queen::move(int ir, int ic, int dr, int dc) {
    int adr=absolute_value(dr);
    int adc=absolute_value(dc);
    if ((adr!=0 && adc!=0) && (adr!=adc)) {
        return false;
    }
    
    if(B->move_checker(color, ir, ic, dr, dc)) {
        return true;
    }
    else {
        return false;
    }
}

//Bishop
bool Bishop::move(int ir, int ic, int dr, int dc) {
    int adr=absolute_value(dr);
    int adc=absolute_value(dc);
    if (dr==0 || dc==0) {
        return false;
    }
    if (adr!=adc) {
        return false;
    }
    if (!(B->move_checker(color, ir, ic, dr, dc))) {
        return false;
    }
    return true;
}

//Knight
bool Knight::move(int ir, int ic, int dr, int dc) {
    if (dr==0 || dc==0) {
        return false;
    }
    int adr=absolute_value(dr);
    int adc=absolute_value(dc);
    if (adr==1 && adc!=2) {
        return false;
    }
    if (adr==2 && adc!=1) {
        return false;
    }
    if (!(B->knight_move_checker(color, ir, ic, dr, dc))) {
        return false;
    }
    
    return true;
}

//Rook
bool Rook::move(int ir, int ic, int dr, int dc) {
    int adr=absolute_value(dr);
    int adc=absolute_value(dc);
    
    if (adr>0 && adc>0) {
        return false;
    }
    if (!(B->move_checker(color, ir, ic, dr, dc))) {
        return false;
    }
    return true;
}

//Pawn
bool Pawn::move(char c, int ir, int ic, int dr, int dc) {
    int adr=absolute_value(dr);
    int adc=absolute_value(dc);
    if (c=='W' && dr<=0) {
        return false;
    }
    if (c=='B' && dr>=0) {
        return false;
    }
    if (c=='B') {
        if (adr==2 && ir!=6) {
            return false;
        }
        else if (adr==2 && ir==6){
            return B->pawn_move_checker(c, ir, ic, dr, dc);
        }
    }
    else {
        if (adr==2 && ir!=1) {
            return false;
        }
        else if (adr==2 && ir==1){
            return B->pawn_move_checker(c, ir, ic, dr, dc);
        }
    }
    if (adr>1 || adc>1) {
        return false;
    }
    if (!(B->pawn_move_checker(c, ir, ic, dr, dc))) {
        return false;
    }
    
    return true;
}

//Idea for converting string to correct pointer:
//Create a function that returns void* which means that it will end up returning the correct memory address of the chess piece that the player is trying to move. Then, outside of the function use contents of the string to determine what type of object the void pointer is pointing to, then static cast that void* to the correct type and then do whatever operations needed on that static casted pointer.



void output() {std::cout << "Output" << std::endl;}
}

using namespace chesser;

int main() {
    output();
    chesser::Board B;
    B.play();
    B.display('W');
    return 0;
}

int larger_value(int i, int j) {
    if (i<0) {
        i*=-1;
    }
    if (j<0) {
        j*=-1;
    }
    if (i>j) {
        return i;
    }
    else {
        return j;
    }
}

int absolute_value(int i) {
    if (i<0) {
        i*=-1;
        return i;
    }
    else {
        return i;
    }
}
