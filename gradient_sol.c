#include "gradient.h"

float scan_for_highest(float view[VIEW_SIZE][VIEW_SIZE], int center_x, int center_y, int *highest_x, int *highest_y) {
    float highest_value = -1.0f;
    
    *highest_x = 5;
    *highest_y = 5;
    
    
    generate_view(view, center_y, center_x);
    
    // CHECKS VIEW FOR HIEGHEST POINT
    for (int x = 0; x < 11; x++) {
        for (int y= 0; y < 11; y++) {
            if (view[x][y] > highest_value) {
                highest_value = view[x][y];
                *highest_x = x;
                *highest_y = y;
            }
        }
    }

    return highest_value;
}

int handle_plateau(float view[VIEW_SIZE][VIEW_SIZE],int *current_x, int *current_y,float best_value,int search_dirs[8][2]) {
    int distance, direction;

    //CHECKS UP TO 2 VIEWS FROM POISTION
    for (distance = VIEW_SIZE; distance <= 2 * VIEW_SIZE; distance += VIEW_SIZE) {
        // CHECKS THE VIEWS IN 8 DIRECTIONS
        for (direction = 0; direction < 8; direction++) {

            //GETS THE POISTION OF THE CENTER OF THE VIEW BASED ON THE CURRENT DISTANCE (11 or 22) AND DIRECTION
            int search_x = *current_x + search_dirs[direction][0] * distance;
            int search_y = *current_y + search_dirs[direction][1] * distance;

            //TEMP VARS FOR FUCNTION
            int search_row, search_col;
            // SCANS FOR THE BEST VALUE IN THAT VIEW
            float search_value = scan_for_highest(view,search_x, search_y,&search_row, &search_col);

            //CHEKS IF THE VALUE GOTTEN IN THE PREVIOUS FUNCTION IS THE BEST OF THE PREVIOUSLY LOOKED AT VIEWS
            if (search_value > best_value) {
                *current_x = search_x + (search_col - VIEW_RADIUS);
                *current_y = search_y + (search_row - VIEW_RADIUS);
                return 1;
            }
        }
    }
    // FOUND PEAK
    return 0;
}
path_point find_highest_point() {
    float view[VIEW_SIZE][VIEW_SIZE];

    int current_x = 0;
    int current_y = 0;
    int temp_x = 0;
    int temp_y = 0;
    int best_row;
    int best_col;
    int dir_x;
    int dir_y;
    int search_dirs[8][2] = {{ 1,  0}, {-1,  0}, { 0,  1}, { 0, -1},{ 1,  1}, { 1, -1}, {-1,  1}, {-1, -1}
    };

    scan_for_highest(view, current_x, current_y, &best_row, &best_col);
    // MAPS THE LOCATION OF THE BEST VALUES X AND Y
    // SO IT CAN THEN ESTIMATE THE  DIRECTION OF THE GRADIENT BY SEING IF THE VALUES ARE ABOVE OR BELLOW 0
    // IF ONE VALUE IS 0 THEN THE PEAK IS NOT IN THAT DIRECTION AND THEN WILL GO FOR THE NEXT ONE
    // IF BOTH ARE 1 IT WILL GO AT A 45 DEGREE ANGLE

    int mapped_x = best_col - 5;
    int mapped_y = best_row - 5;

    //FINDS WHAT QUADRENT THE BEST VALUE IS IN
    if (mapped_x > 0){dir_x = 1;}
    else{dir_x = 0;};

    if (mapped_y > 0){dir_y = 1;}
    else{dir_x = 0;};

    current_x = dir_x * 50;
    current_y = dir_y * 50;



    while (1) {
        // CREATES A NEW VIEW AFTER DOING THE INITIAL JUMP OF 50, FINDING THE BEST VALUE IN THE VIEW
        //ITERATES IN WHILE LOOP UNTIL THE PEAK IS FOUND
        float best_value = scan_for_highest(view,current_x, current_y,&best_row, &best_col);

        // TRANSLATES THE BEST COORDINATE TO REAL COORDINATES ON THE MAP AS VARIABLES
        temp_x = current_x + (best_col - VIEW_RADIUS);
        temp_y = current_y + (best_row - VIEW_RADIUS);

        // CHECKS IF THE BEST ROW ISNT THE CENTRE, INCASE OF PLATAUE
        // MOVES IF TRUE UPON CONTINUE
        // IF FALSE MOVES TO PLATAUE HANDLING
        if (best_row != VIEW_RADIUS || best_col != VIEW_RADIUS) {
            current_x = temp_x;
            current_y = temp_y;
            continue;
        }

        // CHECKS IF THE POSITION IS THE PEAK OR ON A PLATAUE
        // IF IT'S THE PEAK IT BREAKS AND DEACLARES PEAK
        // IF NOT IT GETS OUT OF THE PLATAUE IN THE BEST DIRECTION AND CONTINUES TO ITERATE THE LOOP
        
        if (!handle_plateau(view, &current_x, &current_y, best_value, search_dirs)) {
            break;   //PEAK FOUND BREAK LOOP
        }
    }

    declare_peak(temp_x, temp_y);
    
    path_point result = { temp_x, temp_y };
    return result;
}