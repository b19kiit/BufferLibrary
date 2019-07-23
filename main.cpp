/*
Author:Rishav Bhowmik
Description:To show some functionalities of OpenSource C++ library buffer.h
*/


#include <iostream>
#include <vector>
#include <fstream>
#include "buffer.h"

using namespace std;

int main(int argc, char const *argv[]) {

  int intiger=5; double decimal=2.2222222;
  char cstring[] = "HelloBuffer";

  //creating new buffer
  Buffer buf;
  buf.write((char*)(&intiger), sizeof(intiger));
  buf.write((char*)(&decimal), sizeof(double));
  buf.write((char*)cstring, 12);

  cout<<"Size of the buffer:"<<buf._size()<<endl;

  int retintiger=5; double retdecimal=2.2;
  char retcstring[13];
  buf.init_read();
  buf.read((char*)(&retintiger), sizeof(intiger));
  buf.read((char*)(&retdecimal), sizeof(double));
  buf.read(retcstring, 12);
  
  cout<<retintiger<<endl<<retdecimal<<endl<<retcstring<<endl;
  return 0;
}
