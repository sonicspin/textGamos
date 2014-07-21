#include <iostream>
#include <string>
        std::string translator(short toTranslate){
        switch (toTranslate)
        {
        case 0:
                return "north";
                break;
        case 1:
                return "east";
                break;
        case 2:
                return "south";
                break;
        case 3:
                return "west";
                break;
        default:
                return 0;
                break;
        }
}
/*
       /size = size of the object
           /weight = weight of the object
           /name = name of the object
        */
class object{
        public:
        unsigned short size;
        unsigned short weight;
        std::string name;
        std::string description;
        unsigned short object_id;
        unsigned short is_compatible_with;
        int uses;
        int max_uses;
        std::string usecheck(){
         if (uses > max_uses)
         {
     return "well-preserved";
         }else if(uses == max_uses){
         return 0;
         }else if(max_uses / 2 < uses && uses< max_uses){
         return "used";
         }else if(uses == max_uses / 2)
         {
                 return "half of";
         }else{
         return "very used";
         }
        }
        };
object itemNone;
struct bodypart{
bool is_limb;
std::string name;
std::string description;
std::string setname;
int score;
// whichset = actual set
// whatset = last set
int set;
bool is_shown;
};
struct wall{
        object items[5];
    unsigned short connects_to;
        };
/*
        /a room
        /walls = duh
        /room_id = for connecting
        */
class room{
        public:
        wall walls[4];
        unsigned short room_id;
        std::string name;
        std::string description;
        void clear(int toclear){
                for(int i = 0; i < 5; i++){
        walls[toclear].items[i] = itemNone;
        }
        }
        };
class player_class{
        public:
    unsigned short max_weight;
        /* /1 = head
           /2 = torso
           /3 = arms
           /4 = hands
           /5 = legs
           /6 = feet
           /7 = tail
           /8 = fur/hair
        */
        bodypart body[8];
        unsigned short room_in;
        unsigned short max_size;
        short player_orient;
        object items[10];
        /* /movement
           /modulo, sum, check
        */
        void move(short mov){
        player_orient = player_orient + mov;
        player_orient = player_orient % 4;
        if(player_orient < 0 ){
        player_orient = 3;
        }
        }
        /*endmovement*/
        /*looks stuff and gives properties*/
        void inspect(room tocheck){
        std::cout << "you are in "<< tocheck.name << std::endl;
        std::cout << "you are pointing "<<translator(player_orient)<<std::endl;
        if(tocheck.walls[player_orient].connects_to != 0){
        std::cout << "There is a door here" << std::endl;
        }
        std::cout << "the objects in this wall are:" <<std::endl;
        for (int i = 0; i < 5; i++)
        {
                if(tocheck.walls[player_orient].items[i].object_id != 1){
                std::cout << i+1 << ". " << tocheck.walls[player_orient].items[i].name<< std::endl;
        }
        }
        }
        void take(room takey, int took){
                int numby = 0;
                bool tho = true;
                int weightsum = 0;
                for (int i = 0; i < 10; i++)
                {
                        weightsum = weightsum + items[i].weight;
                }
                weightsum = weightsum + takey.walls[player_orient].items[took].weight;
                if (weightsum < max_weight){
                while (numby < 10 && tho)
                {
                        if (items[numby].object_id != 1)
                        {
                                numby++;
                        }else if (items[numby].object_id == 1)
                        {
                                items[numby] = takey.walls[player_orient].items[took];
                                std::cout << "you took " << takey.walls[player_orient].items[took].name<< std::endl;
                                takey.walls[player_orient].items[took] = itemNone;
                                tho = !tho;
                        }else{
                        std::cout << "you can't carry anything else!";
                        tho = !tho;
                        }
                }
                }else{
                std::cout << "too heavy!!" << std::endl;
                }
        }
        void inspect_inv(bool debug){
        std::cout << "you have" << std::endl;
        bool have_object = false;
                for (int i = 0; i < 10;i++)
        {
                if(items[i].object_id != 1){
                std::cout << i+1 << ". " << items[i].name<< std::endl;
                if(debug){
                std::cout << items[i].object_id << std::endl;
                }
                have_object = true;
        }
        }
                if(have_object == false){
                std::cout << "nothing" << std::endl;
                }
        }
        //player
        };
/*
        /a wall of a room
        /items = every wall can store 5 items
        /position = orientation
        / 0,1,2,3 = north, east, south, west
        /connects to =
        */
int main(){
        std::cout << ">>a & d to rotate, i to inspect, t <number> to take objects,o to inspect room" << std::endl;
        std::cout << ">>e to enter doors, m to check inventory, q <number> to check an item in your" << std::endl <<" inventory " << std::endl;
        player_class player;
    object candle,bed,nightTable,catFruit;
    room theRoom, theHallway;
        bodypart humanEars,humanLegs;
        //candle                     //night table                         // the nothing
    candle.name = "a candle";/**/nightTable.name = "a night table";/**/itemNone.name = "blob of nothing";
                 candle.size = 2;/**/             nightTable.size = 15;/**/                                itemNone.size = 1;
               candle.weight = 5;/**/           nightTable.weight = 75;/**/                              itemNone.weight = 1;
            candle.object_id = 2;/**/         nightTable.object_id = 3;/**/                       itemNone.object_id = 1;
                 candle.max_uses = 3;/**/          nightTable.max_uses = 1;/**/            itemNone.max_uses = 1;
        candle.description ="an orange, beatifully adorned candle";
                nightTable.description ="a white night table with gold streaks";
                itemNone.description ="a big, fat, nothing";
        catFruit.name = "an orange fruit"; bed.name = "a bed";
                        catFruit.size = 5;      bed.size = 90;
                                  catFruit.weight = 3;   bed.weight = 150;
                           catFruit.object_id = 4;  bed.object_id = 5;
        theRoom.room_id = 1;
        theRoom.name = "The Room";
        theRoom.walls[0].connects_to = 0;
        theRoom.walls[0].items[0] = candle;
        theRoom.walls[0].items[1] = nightTable;
        theRoom.walls[0].items[2] = catFruit;
        theRoom.walls[0].items[3] = bed;
        theRoom.walls[0].items[4] = itemNone;
        theRoom.walls[1].connects_to = 2;
        theRoom.clear(1);
        theRoom.clear(2);
        theRoom.clear(3);
        theRoom.description = "this is a room painted red, it also has some objects scattered through";
        struct mansion{
        room all[127];
        }haus;
        haus.all[0] = theRoom;
        /*
        /player_class = for players & player accesories
        /players can hold 10 items
        /but can only hold so much weight
        /and only carry that much size
        */
        player.max_size = 85;
        player.max_weight = 100;
        player.player_orient = 0;
        player.room_in = 0;
        bool bish = true;
        int ai = 0;
        while(ai < 10){
        player.items[ai] = itemNone;
        ai++;
        }
        char input;
        bool sparker = true;
        while(sparker){
        std::cout<<">>You are in " << theRoom.name<< "."<<" Facing ";
        std::cout<<translator(player.player_orient)<<std::endl << ">>";
        std::cin >> input;
        switch (input)
        {
        case 'a':
                player.move(-1);
                break;
        case'd':
                player.move(1);
                break;
        case'i':
                player.inspect(haus.all[player.room_in]);
                break;
        case't':
                int other;
                std::cin >> other;
                other = other - 1;
                player.take(haus.all[player.room_in],other);
                break;
        case'o':
                std::cout << ">>" << haus.all[player.room_in].description << std::endl;
                break;
        case'm':
                player.inspect_inv(true);
                break;
        default:
                break;
        }
        }
        //TODO,make it rain
}