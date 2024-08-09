#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <variant>
using namespace std;

#define small_ship_length 2
#define big_ship_length 3

struct Coordinates {
    int x;
    int y;
};

struct Ship {
    int ship_type; // 0 = small, 1 = big
    int direction; // 0 = down, 1 = right
    int ship_id;
    Coordinates *coordinates[];
};

struct Game_field {
    int field_size;
    int small_ship_amount;
    int big_ship_amount;

    Ship *ships;
};


void print_coordinates(Coordinates *coordinates) {
    cout << "(" << coordinates->x << "|" << coordinates->y << ")";
}

string cli_get_coordinates_string() {
    string coordinates_string;

    cout << ">>     ";
    getline(cin, coordinates_string);
    if (cin.eof() == 1) {
        exit(0);
    } else if (coordinates_string.find(",") == string::npos) {
        throw invalid_argument("No comma supplied");
    }
    return coordinates_string;
}

void cli_get_coordinates_int(string coordinates_string, int *x, int *y) {
    int comma_position = coordinates_string.find(",");
    try {
        *x = stoi(coordinates_string.substr(0, comma_position));
        *y = stoi(coordinates_string.substr(comma_position+1, coordinates_string.length()));
    } catch (invalid_argument e) {
        throw invalid_argument("Can't convert coordinates to ints");
    }
}

bool validate_coordinates(Coordinates *coordinates, int game_field_size) {
    if (coordinates->x < 0 || coordinates->y < 0) {
        return false;
    } else if (coordinates->x >= game_field_size || coordinates->y >= game_field_size) {
        return false;
    }
    return true;
}

Coordinates* cli_get_coordinates(int game_field_size) {
    Coordinates *coordinates = new Coordinates;
    int x, y;
    
    cout << "[I]    Ship coordinates:" << endl;
    while (true) {
        try {
            string coordinates_string = cli_get_coordinates_string();
            cli_get_coordinates_int(coordinates_string, &x, &y);
            coordinates->x = x;
            coordinates->y = y;
            if (validate_coordinates(coordinates, game_field_size)) {
                break;
            }
            cout << "[E]    Invalid coordinates: Outside of playing field" << endl;
        } catch (invalid_argument e) {
            cout << "[E]    Invalid input, coordinate format: 'x, y'" << endl;
        }
    }

    return coordinates;
}

int get_ship_orientation() {
    string orientation_string;
    int orientation, down_flag, right_flag;

    cout << "[I]    Ship orientation:" << endl;
    while (true) {
        try {
            cout << ">>     ";
            getline(cin, orientation_string);
            if (cin.eof()) {
                exit(0);
            }
            down_flag = orientation_string.find("d") == string::npos;
            right_flag = orientation_string.find("r") == string::npos;
            if ((down_flag && right_flag) || (!down_flag && !right_flag)) {
                throw invalid_argument("Invalid direction entered");
            }
            return down_flag ? 0 : 1;
        } catch (invalid_argument e) {
            cout << "[E]    Invalid orientation: d = down, r = right";
        }
    }
}

Coordinates* get_orienation_coordinates(Coordinates *base_coordinates, int orientation, int ship_type) {
    int ship_length = ship_type == 0 ? small_ship_length : big_ship_length;
    int *xy_coordinate = orientation == 0 ? &base_coordinates->x : &base_coordinates->y;
    Coordinates **coordinates = new Coordinates*[ship_length];

    coordinates[0] = base_coordinates;
    for (int i = 1; i < ship_length; i++) {
        
    }
}

void set_ship_coordinates(Ship *ship, Game_field *game_field) {
    while (true) {
        Coordinates *coordinates = cli_get_coordinates(game_field->field_size);
        int orientation = get_ship_orientation();
        return;
    }
}


// Ship type: 0 = small, 1 = big
void set_ships(Game_field *game_field, int ship_type) {
    string ship_type_string = ship_type == 0 ? "small" : "big";
    int ship_amount = ship_type == 0 ? game_field->small_ship_amount : game_field->big_ship_amount;
    Ship *ships = new Ship[ship_amount];
    
    cout << "[I]    Setting " << ship_type_string << " ships:\n";
    for (int i = 1; i <= ship_amount; i++) {
        cout << "[I]    Setting ship nr. " << i << endl;
        ships[i-1].ship_type = ship_type;
        set_ship_coordinates(&ships[i-1], game_field);        
    }
}

Game_field* make_game_field(int field_size, int small_ship_amount, int big_ship_amount) {
    Game_field* game_field = new Game_field;
    game_field->field_size = field_size;
    game_field->small_ship_amount = small_ship_amount;
    game_field->big_ship_amount = big_ship_amount;

    set_ships(game_field, 0);
    set_ships(game_field, 1);


    return game_field;
}

int main() {

    make_game_field(8, 2, 3);
    return 1;
}