#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>

using namespace std;

struct {
  int x, y;
}p[10];

void generate(int i, int range){
  p[i].x = rand() % range;
  p[i].y = rand() % range;
  for(int j=0 ; j<i ; j++){
    if(p[i].x == p[j].x && p[i].y == p[j].y)
      generate(i, range);
  }
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  cout << "please input 1~5 as exponent base on 10 to generate ten points." << endl;
  int ex, range;
  cin >> ex;
  range = pow(10, ex);
  for(int i=0 ; i<10 ; i++){
    generate(i, range);
  }

  fstream file;
  file.open("point.input", ios::out);
  for(int i=0 ; i<10 ; i++){
    file << p[i].x << " " << p[i].y << endl;
  }
  file.close();
  cout << "> point.input" << endl;
  return 0;
}
