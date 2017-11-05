#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include <cstdlib>


using namespace std;

/*********************************************************************
 *         Cost Info
 *********************************************************************/
struct input_cost{
    char item[5];
    int cost[5][5];
}input_cost;


struct temp_d{
    string s_array;
    int n_array;
}temp_d[1024];


/*********************************************************************
 *         print all element based on index for debugging
 *********************************************************************/
void print_all_structure( int num_item );
int minDistance(string left_string, string right_string, int count);

int min(int x, int y, int z)
{
    return min(x,min(y, z));
}

/*********************************************************************
 *         compare two strings
 *********************************************************************/
int minDistance(string left_string, string right_string, int count) {
    long s1 = left_string.length();
    long s2 = right_string.length();
    
    // Two string for temporarily save best solution
    string s1_align = "";
    string s2_align = "";
    //char item[5]= {' ','A','T','G','C'};
    //int cost[5][5]={{0,1,2,1,3},{1,0,1,5,1},{2,1,0,9,1},{1,5,9,0,1},{3,1,1,1,0}};
   
    //create editing table and reset it
    int d[s1+1][s2+1];
    memset( (void *)d, 0, sizeof(int)*(s1+1)*(s2+1) );
    //vector<vector<int> > d(s1 + 1, vector<int>(s2 + 1));
    
    
    // Base case for editing table[i][0]
    for(int i = 1; i < s1+1; i++){
        for(int m = 0; m < 5; m++){                   
            if(left_string[i-1] == input_cost.item[m]){
                d[i][0] = d[i-1][0] + input_cost.cost[m][0];
            }
        }
    }
    // Base case for editing table[i][0]
    for(int j = 1; j < s2+1; j++){
        for(int n = 0; n < 5; n++){                  
            if(right_string[j-1] == input_cost.item[n]){
                d[0][j] = d[0][j-1] + input_cost.cost[n][0];
            }
        }
    }
    
    //compare two last characters
    for(int i = 1; i < s1+1; i++){
        for(int j = 1; j < s2+1; j++){
            // allign and the character is the same
            for(int m = 0; m < 5; m++){          //item
                for(int n=0 ; n<5; n++){
                    if(left_string[i-1] == input_cost.item[m] && right_string[j-1] == input_cost.item [n]){
                        d[i][j] =min(d[i-1][j-1]+input_cost.cost[m][n], d[i-1][j]+input_cost.cost[m][0], d[i][j-1]+input_cost.cost[n][0]);
                    }
                }
            }
        }
    }
    
    
    //allignmen
    for(long i = s1; i >= 0; i--){
        for(long j = s2; j >= 0; j--){
            
            for(int m = 0; m < 5; m++){ 
                for(int n=0 ; n<5; n++){

                    // Search the cost of item
                    if(left_string[i-1] == input_cost.item[m] && right_string[j-1] == input_cost.item [n]){
                        
                        // Substitution condition
                        if(d[i][j] == (d[i-1][j-1] + input_cost.cost[m][n])){
                            s1_align = left_string[i-1] + s1_align;
                            s2_align = right_string[j-1] + s2_align;

                            i--;
                            j--;
                            m = 0;
                            n = 0;
                        }
                        // Insertion condition
                        else if(d[i][j] == (d[i][j-1] + input_cost.cost[n][0])){
                            s1_align = '-' + s1_align;
                            s2_align = right_string[j-1] + s2_align;
                            j--;
                            m = 0;
                            n = 0;
                        }
                        // Deletion condition
                        else if(d[i][j] == (d[i-1][j] + input_cost.cost[m][0])){
                            s1_align = left_string[i-1] + s1_align;
                            s2_align = '-' + s2_align;
                            i--;
                            m = 0;
                            n = 0;
                        }
                    }
                    
                    // For d[1][0] insertion
                    else if(right_string[j-1] == input_cost.item [n]){
                        if(d[i][j] == (d[i][j-1] + input_cost.cost[n][0])){
                            s1_align = '-' + s1_align;
                            s2_align = right_string[j-1] + s2_align;
                            j--;
                            m = 0;
                            n = 0;
                        }
                    }
                    //For d[0][1] insertion
                    else if(left_string[i-1] == input_cost.item[m]){
                        if(d[i][j] == (d[i-1][j] + input_cost.cost[m][0])){
                            s1_align = left_string[i-1] + s1_align;
                            s2_align = '-' + s2_align;
                            i--;
                            m = 0;
                            n = 0;
                        } 
                    }

                }
            }
        }
    }
    //cout<<s1_align<<",";
    //cout<<s2_align<<endl;
    //cout << "cost: " << endl ;
    
    // Save full temporary editing sequence
    temp_d[count].s_array = s1_align + "," + s2_align + ":";
    temp_d[count].n_array = d[s1][s2];
    
    return d[s1][s2];
}

/*********************************************************************
 *         Main Function
 *         Step 1: Get each line from cost file, then store cost to array.
 *                 If fail to open, then give fail message
 *         Step 2: Get each line from input file, then store string to array.
 *                 If fail to open, then give fail message
 *         Step 3: Compare two strings
 
 *********************************************************************/
int main(int argc, char const *argv[]){
    
    char sequence[1024];
    char alphabet[1024];
    fstream file;
    ofstream outfile;
    string left_string;
    string right_string;
    int count = 0;
    int m=0;
    int n=0;
    
     //Get each line from cost file, then store cost to array. If fail to open, then give fail message
     file.open("imp2cost.txt", ios::in);
     if(!file){
     cout << "open file failed." << endl;
     return -1;
     }
    
     //copy each alphabet to item[], First line save in char array, others save in int array
     file.getline(alphabet,sizeof(alphabet), '\n');
     int j = 0;
     for(int i = 2; i < 11 ; i+=2){
     strcpy(&input_cost.item[j], &alphabet[i]);
     //cout << input_cost.item[j] << endl;
     j++;
     }
     
     // Convert the costs from char to int
     for (int i = 0; i < 5; i++) {
     file.getline(alphabet,sizeof(alphabet), '\n');
         for(int i = 2; i < 11 ; i+=2){
            input_cost.cost[m][n]=atoi(&alphabet[i]);
            n++;
         }
     }
     file.close();

    //Get each line from input file, then store data to array. If fail to open, then give fail message
    //Compare two strings
    file.open("imp2input.txt", ios::in);
    if(!file){
        cout << "open file failed." << endl;
        return -1;
    }
    
    // Get two sequence from input file, and compare the min cost, then return
    while(!file.eof()){
        file.getline(sequence, sizeof(sequence), ',');
        left_string = string(sequence);
        
        file.getline(sequence, sizeof(sequence), '\n');
        right_string = string(sequence);
        
        minDistance(left_string, right_string, count);
        //cout << minDistance(left_string, right_string,count) << endl;
        count++;
    }
    file.close();

    // Clear the output file, avoiding overwriting
    outfile.open("imp2output_our.txt", ios::out);
    outfile.close();

    // Output the best editing solution to output file
    outfile.open("imp2output_our.txt", ios::out | ios::app);
    if(!outfile){
        cout << "open output file failed." << endl;
        return -1;
    }
    for(int i = 0; i < count-1 ; i++){
        outfile << temp_d[i].s_array << temp_d[i].n_array << endl;
    }
    outfile.close();

    return 0;
}