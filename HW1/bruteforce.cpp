#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <sstream>
#include <string>
#include <string.h>

using namespace std;

struct dot{
  float x;
  float y;
}point[100000];

struct mp{
  int from;
  int to;
}minpair[50000];

double dist(struct dot a, struct dot b){
  return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

void swapidx(int *a, int *b){
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void swapidx2(struct mp *a, struct mp *b){
  struct mp tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int main(int argc, char const *argv[]) {
  fstream file;
  fstream out;
  char buf[1024];
  int idx = 0;
  int resultidx = 0;
  double mindist = numeric_limits<double>::max();
  string token;
  //stringstream ss;
  //stringstream trans;

  file.open(argv[1], ios::in);
  if(!file){
    cerr << "open file failed." << endl;
    return -1;
  }
  /*while(!file.eof()){
    file.getline(buf, sizeof(buf));
    //cout << buf << endl;
    point[idx].x = (int)buf[0] - 48;
    point[idx].y = (int)buf[2] - 48;
    //cout << point[idx].x << " " << point[idx].y << endl;
    idx++;
  }*/

  while(!file.eof()){
    file.getline(buf, sizeof(buf));
    stringstream ss(buf);
    ss >> token;
    point[idx].x = stof(token);
    ss >> token;
    point[idx].y = stof(token);
    idx++;
  }

  file.close();
  idx--;
  //cout << idx << endl;
  /*for(int i=0 ; i<idx ; i++){
    cout << point[i].x << " , " << point[i].y << endl;
  }*/
  for(int i=0 ; i<idx ; i++){
    for(int j=i+1 ; j<idx ; j++){
      //if(i == j) continue;
      if(dist(point[i], point[j]) < mindist){
        //memset(minpair, 0, sizeof(minpair));
        resultidx = 0;
        mindist = dist(point[i], point[j]);
        minpair[resultidx].from = i;
        minpair[resultidx].to = j;
        resultidx++;
      }
      else if(dist(point[i], point[j]) == mindist){
        minpair[resultidx].from = i;
        minpair[resultidx].to = j;
        resultidx++;
      }
      /*cout << point[minpair[i].from].x << " " << point[minpair[i].from].y << " " << point[minpair[i].to].x << " " << point[minpair[i].to].y << endl;
      if(resultidx == 10) break;*/
      //cout << resultidx << endl;
    }
  }
  cout << "ready to write into file." << endl;

  for(int i=0 ; i<resultidx ; i++){
    if(point[minpair[i].from].x > point[minpair[i].to].x || point[minpair[i].from].y > point[minpair[i].to].y){
      swapidx(&minpair[i].from, &minpair[i].to);
    }
  }
  for(int k=0 ; k<resultidx ; k++){
    for(int i=0 ; i<resultidx-1 ; i++){
      for(int j=i+1 ; j<resultidx ; j++){
        if(point[minpair[i].from].x > point[minpair[j].from].x){
          swapidx2(&minpair[i], &minpair[j]);
        }
        else if(point[minpair[i].from].y > point[minpair[j].from].y){
          swapidx2(&minpair[i], &minpair[j]);
        }
      }
    }
  }

  out.open("output_bruteforce.txt", ios::out);
  out << mindist << "\n";
  for(int i=0 ; i<resultidx ; i++){
    out << point[minpair[i].from].x << " " << point[minpair[i].from].y << " " << point[minpair[i].to].x << " " << point[minpair[i].to].y << endl;
  }
  out.close();

  return 0;
}
