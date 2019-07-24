# BufferLibrary
A C++ library to store buffer

## Purpose
Made to store and retrieve buffer of any object on the RAM and Store it in Files when required

Its usage is mainly targeted to simplify the transfer of Data as a buffer with the platform that supports c++ addons (For eg. NodeJS and Python) and make it easier to store and retrieve buffer from the objects/variables of environments that support c++ addons/extensions.

## Usage
### Using the Constructor
### > Buffer::Buffer()
Initializing crucial variables that control the buffers read and write mechanics
```c++
  Buffer abuf();
```
** Note: It is necessary to use Buffer.init_read() function before using Buffer.read() as an empty list can point to actual beginning of the list**

### > Buffer::Buffer( char* ,  size_t )
Constructor to initialize buffer and read-stream with 1st buffer data
Initializing crucial variables that control the buffers read and write mechanics
And adds the provided data in the buffer

```c++
  //Normal way to use it
  double decimal=2.2222222;
  Buffer buf((char*)(&decimal), sizeof(decimal));
```

```c++
  //More standerd way of using it with morden c++
  double decimal=2.2222222;
  
  //using std::reinterpret_cast
  Buffer buf(reinterpret_cast<char*>(&decimal), sizeof(double));
```

### Using the functions to enter and retrive data in the Buffer
### > inline void write( char* , size_t)
This function can be used to append data in the Buffer
It requires a char pointer and size of the data pointed by the char pointer in the arguments
The data is then copied as buffer and append in the object of the buffer class

```c++
  Buffer buf;//Creating an object of Buffer
  
  int intiger=5;
  buf.write((char*)(&intiger), sizeof(intiger));//buffer of intiger is appeded in the object `buf`
  
  double d=123.8989;
  buf.write((char*)(&d), sizeof(d));
  
  char str[]="HelloWorld";
  buf.write((char*)str, strlen(str)+1); 
  //strlen to find length of the string in str and +1 include the '\0' at the end of the string
```

```c++
  //More standerd way of using it with morden c++
  
  Buffer buf;//Creating an object of Buffer
  int intiger=5;
  buf.write(std::reinterpret_cast<char*>(&intiger), sizeof(intiger));//using std::reinterpret_cast
  
  double d=123.22166;
  buf.write(std::reinterpret_cast<char*>(&decimal), sizeof(double));
```





























