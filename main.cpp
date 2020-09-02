#include <iostream>
#include <stdlib.h>
#include <vector>

struct Point{
    int x;
    int y;
};

enum class Color {White, Black};
class Chessman;

class IChessman {
    public:
        virtual void move(Point p) = 0;
        virtual void setPosition(Point pos) = 0;
        virtual Point getPosition() const = 0;
        virtual void setColor(Color color) = 0;
        virtual Color getColor() const = 0;
        virtual void kill() = 0;
    friend Chessman;
    private:
       Point pos;
       Color color;
       bool live;
};


class Chessman: public IChessman {
    public:
    Chessman(Color color, Point pos){
            printf("figure init %d %d ",pos.x, pos.y );
        setPosition(pos);
        setColor(color);
    }
        void kill(){
         printf("chessman is dead ");
         live = false;
    }
    Point getPosition() const{
              return this->pos;
    }

    Color getColor() const{
              return this->color;
    }

    void setPosition(Point pos){
        this->pos = pos;
    }

    void setColor(Color color){
        this->color = color;
    }

};



class CPawn: public Chessman{
    public:
       CPawn(Color color, Point pos): Chessman(color, pos){
                std::cout<<"Constructor Pawn "<<std::endl;
       }

       void move(Point p){
                printf("pawn  %d %d \n", p.x, p.y);
       }



};


class CHorse: public Chessman{
    public:
       CHorse(Color color, Point pos): Chessman(color, pos){
                std::cout<<"Constructor Horse "<<std::endl;
       }

       void move(Point p){
                printf("Hourse move  %d %d \n", p.x, p.y);
       }
};



class CKing: public Chessman{
    public:
       CKing(Color color, Point pos): Chessman(color, pos){
                std::cout<<"Constructor king"<<std::endl;
       }

       void move(Point p){
                printf("move king  %d %d \n", p.x, p.y);
       }
};


// Фабрики объектов
class FactoryChessman
{
    public:
         virtual Chessman* createChessman(Color clr, Point p) = 0;
         virtual ~FactoryChessman() {}
};




class CPawnFactory: public FactoryChessman
{
  public:
    Chessman* createChessman(Color clr, Point p) {
      return new CPawn(clr, p);
    }
};

class CKingFactory: public FactoryChessman
{
  public:
    Chessman* createChessman(Color clr, Point p) {
      return new CKing(clr, p);
    }
};

class CHorseFactory: public FactoryChessman
{
  public:
    Chessman* createChessman(Color clr, Point p) {
      return new CHorse(clr, p);
    }
};




int main(int argc, char* argv[]){

    std::vector<Chessman*> player_1;
    CHorseFactory* Fhorse = new CHorseFactory();
    CKingFactory*  FKing = new CKingFactory();
    CPawnFactory*  FPawn = new CPawnFactory();
    Point p;
    p.x = 0;
    p.y = 0;
    for (int i = 0; i < 10; i++){
        player_1.push_back(FPawn->createChessman(Color::Black, p));
    }

    for (int i = 0; i < 2; i++){
        player_1.push_back(Fhorse->createChessman(Color::Black, p));
    }
    p.x = 1;
    p.y = 1;
    for (int i = 0; i < 10; i++){
        player_1.at(i)->move(p);
    }



}

