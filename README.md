# BufferLibrary
A C++ library to store buffer

## Purpose
Made to store and retrieve buffer of any object on the RAM and Store it in Files when required

Its usage is mainly targeted to simplify the transfer of Data as a buffer with the platform that supports c++ addons (For eg. NodeJS and Python) and make it easier to store and retrieve buffer from the objects of C++ addons supporting environments.

## Usage
### Using the Constructor
### > Buffer::Buffer()
Initializing crucial variables that control the buffers read and write mechanics
```c++
  Buffer abuf();
```
** Note: It is necessary to use Buffer.init_read() before using Buffer.read() as an empty list can point to actual beginning of the list**

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
  Buffer buf(reinterpret_cast<char*>(&decimal), sizeof(double));
```
