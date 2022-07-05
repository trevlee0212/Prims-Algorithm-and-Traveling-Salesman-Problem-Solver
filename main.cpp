//  Created by Trevor Lee on 11/19/21.
//  Copyright © 2021 Trevor Lee. All rights reserved.
//
#include "location.h"
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include <limits.h>
#include <iomanip>

#include <algorithm>
using namespace std;
class A{
private:
    vector<prim_struct>chart;
    size_t size;
    double total_cost;
    

    
public:
    vector <location> input_coor;
    void set_up(){
        total_cost = 0;
        size = input_coor.size();
    }
    // input
    void create_input_coor(){
        cin >> size;
        input_coor.reserve(size);
        size_t count = size;
        while (count){
            int x_coor;
            int y_coor;
            cin >> x_coor >> y_coor;
            input_coor.emplace_back(x_coor, y_coor);
            --count;
        }
    }
   
    
    double partA_calculate_EuDistance(size_t g, size_t h){
        if ((input_coor[g].zone == 'n' && input_coor[h].zone == 'w') ||
            (input_coor[g].zone == 'w' && input_coor[h].zone == 'n')
            ){return numeric_limits<double>::infinity();}
        
         double hor = (double) (input_coor[g].x - input_coor[h].x)* (double)(input_coor[g].x - input_coor[h].x);
         double ver =  (double)(input_coor[g].y - input_coor[h].y)*  (double)(input_coor[g].y - input_coor[h].y);
        return sqrt (hor + ver);
    }
    
    double partC_calculate_EuDistance(size_t g, size_t h){
        if (g==h){return numeric_limits<double>::infinity();}
         double hor = (double) (input_coor[g].x - input_coor[h].x)* (double)(input_coor[g].x - input_coor[h].x);
         double ver =  (double)(input_coor[g].y - input_coor[h].y)*  (double)(input_coor[g].y - input_coor[h].y);
        return  (hor + ver);
    }
    
    // PART: A
    // algo
    void prim_algo(){
        prim_struct sample;
        
        chart.resize(size, sample) ;
        chart[0].d = 0;
        
        prim_struct smallest;
        for (size_t i=0; i< size;++i){
            smallest.d = numeric_limits<double>::infinity();
            
            int small = minElement();
            
            
            chart[(size_t)small].k = true;
            total_cost+=chart[(size_t)small].d;
            
            for (size_t j=0; j < size;++j){
                double tmp = partA_calculate_EuDistance((size_t)small, j);
                if (chart[j].k == false && tmp < chart[j].d){
                    chart[j].d = tmp;
                    chart[j].p = small;
                }
            }
        }
    }
    
    void part_c_prim_algo(){
        prim_struct sample;
        size= input_coor.size();
        chart.resize(size, sample) ;
        chart[0].d = 0;
        
        prim_struct smallest;
        for (size_t i=0; i< size;++i){
            smallest.d = numeric_limits<double>::infinity();
            
            int small = minElement();
            
            
            chart[(size_t)small].k = true;
            //square root
            total_cost+=sqrt(chart[(size_t)small].d);
            
            for (size_t j=0; j < size;++j){
                double tmp = partC_calculate_EuDistance((size_t)small, j);
                if (tmp < chart[j].d && chart[j].k == false){
                    chart[j].d = tmp;
                }
            }
        }
    }
    int minElement(){
        double sml = INT_MAX;
        int indx = -1;
        for (size_t k=0; k< size;++k){
            if (chart[k].d < sml && chart[k].k == false){
                sml = chart[k].d;
                indx = (int)k;
            }
        }
        return indx;
    }
    
    // output
    double total(){
        return total_cost;
    }
    void output(){
        cout << fixed << setprecision(2) << total_cost << "\n";
        for (size_t i=1; i< size; ++i){
            if ((int)i < chart[i].p){
                cout << i << " " << chart[i].p << "\n";
            }
            else {
               cout << chart[i].p << " " << i << "\n";
            }
        }
    }

};



class B{
    vector <location> input_coor;
    size_t size;
    double total_cost;
    vector <pair<bool,double>> travel_map;
    vector <size_t> best_path;
    vector<vector<double>> EuDistance;
    
    public:
    // input
    void create_input_coor(){
        cin >> size;
        input_coor.reserve(size);
        int x_coor;
        while (cin >> x_coor){
            int y_coor;
            cin >> y_coor;
            input_coor.emplace_back(x_coor, y_coor);
        }
        best_path.reserve(size+1);
        travel_map.resize(size, make_pair(false,-1));
        total_cost = 0;
    }
    
   
    // algo
    double partB_calculate_EuDistance(size_t g, size_t h){
        return sqrt (((double) (input_coor[g].x - input_coor[h].x)* (double)(input_coor[g].x - input_coor[h].x)) +  ((double)(input_coor[g].y - input_coor[h].y)*  (double)(input_coor[g].y - input_coor[h].y)));
    }
    
    void random_insertion_algo(){
        size_t farthest_city_idx = INT_MAX;
        double farthest_city_distance = -1;
        best_path.push_back(0);
        travel_map[0].first = true;
        
        // create the first line in graph
        for (size_t i=1; i<size;++i){
            double tmp = partB_calculate_EuDistance(0, i);
            if (tmp > farthest_city_distance){
                farthest_city_distance = tmp;
                farthest_city_idx = i;
            }
        }
        
        //finding the 2 points on graph
        best_path.push_back(farthest_city_idx);
        best_path.push_back(0);
        travel_map[farthest_city_idx].first = true;
        for (size_t i=1; i<input_coor.size();++i){
            if (travel_map[i].first == false){
                travel_map[i].second =partB_calculate_EuDistance(0, i);
            }
        }
        
        total_cost = 2 * farthest_city_distance;
        size_t count = size-2;
        // loop
        while (count){
            for (size_t i=1; i < travel_map.size(); ++i){
                if (travel_map[i].first == false){
                    farthest_city_idx = i;
                    break;
                    }
            }
            
            //calculate which edge can create the smallest increase
            double closest_diff = INT_MAX;
            size_t second = INT_MAX;
            double final_total_dist = -1;
            double original_total_dist = -1;
            for (size_t i=0; i < best_path.size()-1;++i){
                double original_distance = partB_calculate_EuDistance(best_path[i], best_path[i+1]);
                double total_distance = partB_calculate_EuDistance(best_path[i], farthest_city_idx) + partB_calculate_EuDistance(best_path[i+1], farthest_city_idx);
                double difference = total_distance - original_distance;
                if (difference < closest_diff) {
                    closest_diff = difference;
                    second = i+1;
                    original_total_dist = original_distance;
                    final_total_dist = total_distance;
                }
            }
            
            // insert the node to the smallest one
            best_path.insert(best_path.begin()+ (long)second, farthest_city_idx);
            total_cost -= original_total_dist;
            total_cost += final_total_dist;
            travel_map[farthest_city_idx].first = true;
            --count;
        }
    }
    
    void output(){
        cout << fixed << setprecision(2) << total_cost << "\n";
        for (size_t i =0 ; i<= best_path.size()-2; ++i){
            cout << best_path[i] << " ";
        }
        return;
    }
    
};

class C{
    vector <location> input_coor;
    size_t size;
    double total_cost;
    vector <pair<bool,double>> travel_map;
    vector <size_t> best_path;
    //vector<vector<double>> EuDistance;

    
    //part c only
    double current_cost;
    vector <size_t> current_path;
    
    public:
    // input
    void create_input_coor(){
        cin >> size;
        input_coor.reserve(size);
        int count = (int) size;
        while (count){
            int x_coor;
            int y_coor;
            cin >> x_coor >> y_coor;
            input_coor.emplace_back(x_coor, y_coor);
            --count;
        }
        best_path.reserve(size+1);
        travel_map.resize(size, make_pair(false,-1));
        current_path.reserve(size+1);
        total_cost = 0;
        current_cost = 0;
    }
    
    
   
    // PART B: FASTTSP
    // algo
    // take in 2 indeices
    double partB_calculate_EuDistance(size_t g, size_t h){
         double hor = (double) (input_coor[g].x - input_coor[h].x)* (double)(input_coor[g].x - input_coor[h].x);
         double ver =  (double)(input_coor[g].y - input_coor[h].y)*  (double)(input_coor[g].y - input_coor[h].y);
        return sqrt (hor + ver);
    }
    
    void random_insertion_algo(){
        size_t farthest_city_idx = INT_MAX;
        double farthest_city_distance = -1;
        best_path.push_back(0);
        travel_map[0].first = true;
        
        // create the first line in graph
        for (size_t i=1; i<size;++i){
            double tmp = partB_calculate_EuDistance(0, i);
            if (tmp > farthest_city_distance){
                farthest_city_distance = tmp;
                farthest_city_idx = i;
            }
        }
        
        best_path.push_back(farthest_city_idx);
        best_path.push_back(0);
        current_path.push_back(0);
        current_path.push_back(farthest_city_idx);
        current_path.push_back(0);
        travel_map[farthest_city_idx].first = true;
        for (size_t i=1; i<input_coor.size();++i){
            if (travel_map[i].first == false){
                travel_map[i].second =partB_calculate_EuDistance(0, i);
            }
        }
        
        total_cost = 2 * farthest_city_distance;
        size_t count = size-2;
        // loop
        while (count){
            for (size_t i=1; i < travel_map.size(); ++i){
                if (travel_map[i].first == false){
                    farthest_city_idx = i;
                    break;
                    }
            }
            double closest_diff = INT_MAX;
            size_t second = INT_MAX;
            double final_total_dist = -1;
            double original_total_dist = -1;
            for (size_t i=0; i < best_path.size()-1;++i){
                double original_distance = partB_calculate_EuDistance(best_path[i], best_path[i+1]);
                double total_distance = partB_calculate_EuDistance(best_path[i], farthest_city_idx) + partB_calculate_EuDistance(best_path[i+1], farthest_city_idx);
                double difference = total_distance - original_distance;
                if (difference < closest_diff) {
                    closest_diff = difference;
                    second = i+1;
                    original_total_dist = original_distance;
                    final_total_dist = total_distance;
                }
            }
            best_path.insert(best_path.begin()+ (long)second, farthest_city_idx);
           current_path.insert(current_path.begin()+ (long)second, farthest_city_idx);
            total_cost -= original_total_dist;
            total_cost += final_total_dist;
            travel_map[farthest_city_idx].first = true;
            --count;
        }
        
        
        best_path.pop_back();
        current_path.pop_back();
    }
    /*
    void two_opt(){
        for (size_t i=0; i<best_path.size()-3;++i){
            for (size_t j = i+2; j <best_path.size()-1; ++j){
                //original
        
                double base_line = partB_calculate_EuDistance(best_path[i], best_path[i+1]);
                double base_line2 = partB_calculate_EuDistance(best_path[j], best_path[j+1]);
                
                //modified
                
                double mod_line = partB_calculate_EuDistance(best_path[i], best_path[j]);
                double mod_line2 = partB_calculate_EuDistance(best_path[i+1], best_path[j+1]);
                
                if ((mod_line2 + mod_line) < base_line+base_line2){
                    reverse(best_path.begin()+(long)i+1, best_path.begin()+(long)j+1);
                    total_cost -= (base_line+base_line2 - (mod_line2 + mod_line));
                }

            }
        }
         current_path = best_path;
    }*/
    
    
    
    // PART C: OPTTSP
    void genPerms(size_t permLength) {
        if (permLength == input_coor.size()) {
            // add the distance back to 0
            double final_cost = current_cost + partB_calculate_EuDistance(current_path[permLength-1], current_path[0]);
            
            // check if min cost
            if (final_cost < total_cost){
                total_cost = final_cost;
                best_path = current_path;
            }
            return;
        } // if
        
        if (promising(permLength) == false){
            return;}
        
        for (size_t i = permLength; i < input_coor.size(); ++i) {
            swap(current_path[permLength], current_path[i]);
            double tmp_cost = partB_calculate_EuDistance(current_path[permLength],current_path[permLength-1]);
            // save the cost
            current_cost += tmp_cost;
            
            genPerms(permLength + 1);
            
            current_cost -= tmp_cost;
            swap(current_path[permLength], current_path[i]);
        } // for
    } // genPerms()
    
    bool promising(size_t perm_length){
        if (size-perm_length < 5){
            return true;
        }
        // connecting arms
        double beginning = numeric_limits<double>::infinity();
        double end = numeric_limits<double>::infinity();
        for (size_t i = perm_length; i < current_path.size();++i){
                beginning = min(partB_calculate_EuDistance
                                (current_path[0],current_path[i]), beginning);
                end = min(partB_calculate_EuDistance
                          (current_path[perm_length-1],current_path[i]), end);
        }
        
        // MST
         double mst_cost = prim_algo(perm_length);
        
        //TOTAL
        double planned_cost = mst_cost+current_cost + beginning + end;
        
        if (planned_cost < total_cost){return true;}
        else{return false;}
    }
    
    double prim_algo(size_t perm_length_input){
        A prim;
        
        for (size_t i= perm_length_input; i<size;++i){
            prim.input_coor.emplace_back(input_coor[current_path[i]].x,input_coor[current_path[i]].y);
        }
        
        prim.set_up();
        prim.part_c_prim_algo();
        return prim.total();
        
    }
    
    void output(){
        cout << fixed << setprecision(2) << total_cost << "\n";
        for (size_t i =0 ; i< best_path.size(); ++i){
            cout << best_path[i] << " ";
        }
    }
};

void getMode(int argc, char * argv[], char& g_mode) {
    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        {"mode",required_argument,nullptr, 'm'  },
        {"help",no_argument,nullptr, 'h'  },
        { nullptr,0,nullptr, '\0' }
    };

    
    while ((choice = getopt_long(argc, argv, "hm:", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'h':
            cerr << "Error: invalid option" << "\n";
            exit(0);
                
        case 'm':
                if ( *optarg == 'O'){
                    g_mode = 'O';
                }
                else if  ( *optarg == 'F'){
                    g_mode = 'F';
                }
                else if  ( *optarg == 'M'){
                    g_mode = 'M';
                }
                else {
                    cerr << "undefined game mode";
                    exit(1);
                }
                
            break;
        
        
        default:
            cerr << "Error: invalid option" << "\n";
            exit(1);
        } // switch
    } // while
}


int main(int argc, char * argv[]) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc,argv);
    char game_mode = '\0';
    getMode(argc, argv, game_mode);
    
    //Part A: MST
    if (game_mode == 'M'){
        A a_game;
        a_game.create_input_coor();
        a_game.prim_algo();
        a_game.output();
    }
    
    // PART B: FASTTSP
    else if (game_mode == 'F'){
        B b_game;
        b_game.create_input_coor();
        b_game.random_insertion_algo();
        b_game.output();
    }
    
    //PART C: OPTTSP
    else {
        C c_game;
        c_game.create_input_coor();
        c_game.random_insertion_algo();
        c_game.genPerms(1);
        c_game.output();
    }
    
    return 0;
}
