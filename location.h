//3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
//  location.h
//  p4-zoo
//
//  Created by Trevor Lee on 11/19/21.
//  Copyright © 2021 Trevor Lee. All rights reserved.
//

#ifndef location_h
#define location_h
#include <limits>
using namespace std;
// b = border area; w = wild animal area; n = normal animal area
struct location{
    int x;
    int y;
    char zone;
    location(int x_input, int y_input):x(x_input), y(y_input){
        if ( (x_input <= 0 && y_input == 0) ||  (x_input == 0 && y_input <= 0)){
            zone = 'b';
        }
        
        else if (x_input < 0 && y_input < 0){
            zone = 'w';
        }
        else {zone = 'n';}
    }
};

struct prim_struct{
    double d;
    int p;
    bool k;
    prim_struct(){
        k = false;
        d = numeric_limits<double>::infinity();
        p = -1;
    }
    
};


#endif /* location_h */
