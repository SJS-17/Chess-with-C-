#include <iostream>

#ifndef C
#define C
namespace chesser {


class Player;
class King;
class Queen;
class Bishop;
class Knight;
class Rook;
class Pawn;

class Board {
private:
  std::string grid[8][8];
  Player* white;
  Player* black;
public:
    Board();
    void display(char color);
    std::string piece_here(int r, int c) const;  //Returns string of piece and returns "\0" if no piece
    bool move_checker(char c, int ir, int ic, int dr, int dc) const;
    bool knight_move_checker(char c, int ir, int ic, int dr, int dc) const;
    bool pawn_move_checker(char c, int ir, int ic, int dr, int dc) const;
    void move_piece(char c, int i_r, int i_c, int d_r, int d_c);
    int row_returner(char c, std::string piece);
    int column_returner(char c, std::string piece);
    void play();
    void eliminate_inside_Player(); //Maybe delete function
    ~Board();
};

class King {
private:
    char color;
    std::string name;
    bool alive;
    Board* B;
public:
    //Constructor
    King(char c, std::string _name, Board* _B) : color(c), name(_name), B(_B), alive(true) {};
    
    //Accessor
    bool alive_or_not() const {return alive;}
    std::string return_name() const {return name;}
    
    //Mutator
    void die() {alive=false;}
    bool move(int ir, int ic, int dr, int dc);
};

class Queen {
private:
    char color;
    std::string name;
    bool alive;
    Board* B;
public:
    //Constructor
    Queen(char c, std::string _name, Board* _B) : color(c), name(_name), B(_B), alive(true) {};
    
    //Accessor
    std::string return_name() const {return name;}
    
    //Mutator
    //   void die();
    bool move(int ir, int ic, int dr, int dc);
    //   bool b_move(char direction, int steps);
};

class Bishop {
private:
    char color;
    std::string name;
    bool alive;
    Board* B;
public:
    //Constructor
    Bishop(char c, std::string _name, Board* _B) : color(c), name(_name), B(_B), alive(true) {};
    
    //Accessor
    std::string return_name() const {return name;}
    
    //Mutator
    //    void die();
    bool move(int ir, int ic, int dr, int dc);
    //   bool b_move(char direction, int steps);
};

class Knight {
private:
    char color;
    std::string name;
    bool alive;
    Board* B;
public:
    //Constructor
    Knight(char c, std::string _name, Board* _B) : color(c), name(_name), B(_B), alive(true) {};
    
    //Accessor
    std::string return_name() const {return name;}
    
    //Mutator
    void die() {alive=false;};
    bool move(int ir, int ic, int dr, int dc);
    //   bool b_move(char direction);
};

class Rook {
private:
    char color;
    std::string name;
    bool alive;
    Board* B;
public:
    //Constructor
    Rook(char c, std::string _name, Board* _B) : color(c), name(_name), B(_B), alive(true) {};
    
    //Accessor
    std::string return_name() const {return name;}
    
    //Mutator
    //   void die();
    bool move(int ir, int ic, int dr, int dc);
    //    bool b_move(char direction, int steps);
};

class Pawn {
private:
    char color;
    std::string name;
    bool alive;
    Board* B;
public:
    //Constructor
    Pawn(char c, std::string _name, Board* _B) : color(c), name(_name), B(_B), alive(true) {};
    
    //Accessor
    std::string return_name() const {return name;}
    
    //Mutator
    //  void die();
    bool move(char c, int ir, int ic, int dr, int dc);
    //    bool w_kill(char direction);
    //    bool b_forward(char direction);
    //    bool b_kill(char direction);
};

class Player {
private:
    char color;
    Board* Bd;
    King* K;
    Queen* Q;
    Bishop* B1;
    Bishop* B2;
    Knight* L1;
    Knight* L2;
    Rook* R1;
    Rook* R2;
    Pawn* P[8];
    
public:
    //Constructor
    Player(char c, Board* _B);
    
    //Accessor
    bool king_alive() const {return (K->alive_or_not());}
    King* king() const {return K;}
    Queen* queen() const {return Q;}
    Bishop* bishop1() const {return B1;}
    Bishop* bishop2() const {return B2;}
    Knight* knight1() const {return L1;}
    Knight* knight2() const {return L2;}
    Rook* rook1() const {return R1;}
    Rook* rook2() const {return R2;}
    Pawn* pawn(char c) const;
    
    //Other stuff
    void eliminate(); 
};
int absolute_value(int i) {
    std::cout << "namespace chesser absolute_value called" << std::endl;
    if (i<0) {
        i*=-1;
        return i;
    }
    else {
        return i;
    }
}
}

int larger_value(int i, int j);
int absolute_value (int i);

#endif
