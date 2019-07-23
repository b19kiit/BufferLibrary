/*
Author:Rishav Bhowmik
Description:OpenSource C++ library to store buffer on RAM arbitrarily
*/

#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<list>

using namespace std;

struct BufferPiece{
    size_t data_length=0;
    char *data;
    BufferPiece() {
        data_length=0;
    }
    BufferPiece(char *buffer, size_t length) {//No current Use
        if(!length){
            return;
        }
        data = (char*)malloc(data_length = length);//allocating space and setting `data_length`
        while((length--)>0){
            data[length] = buffer[length];
        }
    }
    size_t put_data(char *buffer, size_t length) {
        if(data_length){
            free(data);data_length=0;
        }
        if(!length){
            return data_length;
        }
        data = (char*)malloc(data_length = length);//allocating space and setting `data_length`
        while((length--)>0){
            (data[length] = buffer[length]);
        }
        return data_length;
    }
    void erase(){
        if(data_length){
            free(data);data_length=0;
        }
    }

    void write(ofstream *f) {
        f->write(data,data_length);
    }

    void read(ifstream *f, size_t length) {
        erase();//erase all allocation
        data = (char*)malloc(data_length = length);//allocating space and setting `data_length`
        f->read(data, data_length);//reading from the file stream
    }
};

class Buffer{
    unsigned long long int size=0;
    list<BufferPiece> pieces;
protected:
    char platform_init_used = 1;

    //readstream variables
    list<BufferPiece>::iterator read_piece;
    unsigned long long int read_pointer=0, read_piece_pointer=0;
public:
    //Constructor to initialize buffer and read-stream with no initial data
    Buffer(){
        //Initializing crucial variables that control the buffers read and write mechanics
        size = 0;
        read_pointer = 0;
        read_piece = pieces.begin();
        read_piece_pointer=0;
        platform_init_used=0;
    }

    //platform_init() : to be used when no Constructor is called and memory is allocated arbitrarily to the Buffer object.
    //It has platform_init_used flag variable to make sure it dysfunctional when called illegally, although this OOP safety mechanism can fail under some circumstances.
    void platform_init(){//!!!don't use it if not needed!!!
        if(!platform_init_used)return;

        //Initializing crucial variables that control the buffers read and write mechanics
        size = 0;
        read_pointer = 0;
        read_piece = pieces.begin();
        read_piece_pointer=0;
        platform_init_used=0;
    }

    //Constructor to initialize buffer and read-stream with 1st buffer data
    Buffer(char* buffer, size_t length){
        //Initializing crucial variables that control the buffers read and write mechanics
        size = 0;
        read_pointer = 0;
        read_piece = pieces.begin();
        read_piece_pointer=0;

        pieces.push_back(BufferPiece());//Adding a new element to the pieces list

        list<BufferPiece>::reverse_iterator last=pieces.rbegin();//iterator to excess new last element of `pieces` list

        last->data_length=0;//assigning data_length to 0 to prevent corruption where default constructor is not called with list::push_back() function
        size += last->put_data(buffer, length);//copying buffer in the new last element of `pieces` list

        platform_init_used=0;
        //init read() operations:-
        read_piece = pieces.begin();
        read_piece_pointer = 0;read_pointer = 0;
    }

    //init_read() : Set the read-stream to starting byte of the buffer
    inline void init_read(){
        read_piece = pieces.begin();
        read_piece_pointer = 0;read_pointer = 0;
    }

    /*
    write(char*, size_t) : Append buffer with `(char*) pointer` and `size of data`
    You can copare its usage with std::ofstream.write(char*, size_t);
    */
    inline void write(char* buffer, size_t length){

        if(!length) return;//stop here in the function when length is 0

        list<BufferPiece>::reverse_iterator last = pieces.rbegin();//iterator to excess last element of `pieces` list

        if(last != pieces.rend()){
            if(!last->data_length){//Reuse the last element of `pieces` list of it contains no Data. Though, it is a very unlikely condition
                size+=last->put_data(buffer, length);return;//copying buffer in the last element of `pieces` list, updating `size` terminating the function
            }
        }
        
        pieces.push_back(BufferPiece());//Adding a new element at the end of the pieces list
        last = pieces.rbegin();//pointing interator `last` to new last element
        last->data_length=0;//assigning data_length to 0 to prevent corruption where default constructor is not called with list::push_back() function
        size += last->put_data(buffer, length);//copying buffer in the new last element of `pieces` list and updating `size`
        //init_read();
    }

    /*
    write_and_init_read(char*, size_t) : Append buffer with `(char*)` pointer and `size of data`
    And also set the read-stream to starting byte of the buffer
    */
    void write_and_init_read(char* buffer, size_t length){
        write(buffer, length);//calling the normal write funtion to append the buffer;
        init_read();//seting read-stream to starting byte of the buffer
    }

    /*
    read(char*, size_t) : Read buffer and assign its values as be the assigned 'length' as size_t variable from locaton pointed by `(char*)` pointer
    */
    void read(char* buffer, size_t length){
        if((read_pointer+length)>size){return;}
        for(size_t i=0;i<length;i){
            if((read_piece == pieces.end())||(read_pointer>=size)){
                return;
            }
            else if(read_piece->data_length <= read_piece_pointer){
                read_piece++;read_piece_pointer=0;continue;
            }else{
                buffer[i++]=read_piece->data[read_piece_pointer++];
                read_pointer++;
            }
        }
    }

    void clear(){//moves the read stream to begining and clears data in Buffer object
        init_read();
        for(list<BufferPiece>::iterator i=pieces.begin(); i!=pieces.end(); i++){
            i->erase();
        }
        size = 0;
    }


    //Methods to perform I/O of the Buffer..............................
    void write_in_file(ofstream *f){//simply writes the buffer into provided file stream
        f->write(reinterpret_cast<char*>(&size), sizeof(size));//write the size of the buffer
        for(list<BufferPiece>::iterator i=pieces.begin(); i!=pieces.end(); i++){
            i->write(f);//write the buffers from the pieces list
        }
    }


    void read_from_file(ifstream *f){//reads the buffer from a file that was made using write_in_file() or any file made in a similar manner
        clear();//clearing all data previously stored in the Buffer
        f->read(reinterpret_cast<char*>(&size), sizeof(size));
        pieces.push_back(BufferPiece());
        list<BufferPiece>::iterator i=pieces.begin();
        i->read(f, size);
        init_read();
    }

    void append_from_file(ifstream *f){
        unsigned long long int append_size;
        f->read(reinterpret_cast<char*>(&append_size), sizeof(append_size));
        cout<<append_size;
        if(!append_size){return;}
        
        list<BufferPiece>::reverse_iterator last = pieces.rbegin();//iterator to excess last element of `pieces` list
        
        if(last != pieces.rend()){
            if(!last->data_length){//Reuse the last element of `pieces` list of it contains no Data.
                last->read(f, append_size); size+=append_size;return;//reading buffer to a single link of `pieces` list
            }
        }
                  
        pieces.push_back(BufferPiece());//Adding a new element at the end of the pieces list
        last = pieces.rbegin();//pointing interator `last` to new last element
        last->data_length=0;//assigning data_length to 0 to prevent corruption where default constructor is not called with list::push_back() function
        last->read(f, append_size);size += append_size;
        
    }

    //Methods to return private member values............................
    size_t _size(){
        return size;
    }
    size_t _read_pointer(){
        return read_pointer;
    }
};
