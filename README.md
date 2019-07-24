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
  //More standard way of using it with modern c++
  double decimal=2.2222222;
  
  //using std::reinterpret_cast
  Buffer buf(reinterpret_cast<char*>(&decimal), sizeof(double));
```

### Using the functions to enter and retrieve data in the Buffer
### > inline void write( char* , size_t)
This function can be used to append data in the Buffer
It requires a char pointer and size of the data pointed by the char pointer in the arguments
The data is then copied as a buffer and append in the object of the buffer class

```c++
  Buffer buf;//Creating an object of Buffer
  
  int integer=5;
  buf.write((char*)(&intiger), sizeof(integer));//buffer of intiger is appeded in the object `buf`
  
  double d=123.8989;
  buf.write((char*)(&d), sizeof(d));
  
  char str[]="HelloWorld";
  buf.write((char*)str, strlen(str)+1); 
  //strlen to find length of the string in str and +1 include the '\0' at the end of the string
```

```c++
  //More standard way of using it with modern c++
  
  Buffer buf;//Creating an object of Buffer
  int integer=5;
  buf.write(std::reinterpret_cast<char*>(&integer), sizeof(integer));//using std::reinterpret_cast
  
  double d=123.22166;
  buf.write(std::reinterpret_cast<char*>(&decimal), sizeof(double));
```

### > inline void read( char* , size_t )
This function can be used to copy data from the Buffer to the address provided as char* for provided length as size_t
It requires a char pointer and size of the data pointed by the char pointer in the arguments

```c++
//assuming that Buffer buf is filled with some buffer
  int integer;
  
  buf.write((char*)(&integer), sizeof(integer));
```
```c++
//assuming that Buffer buf is filled with some buffer
  int integer;
//More standard way of using it with modern c++
  buf.write(std::reinterpret_cast<char*>(&integer), sizeof(integer));
```

### > void init_read()
It is a very important function before using the function read(char*,size_t)
The job of this function is to initialize the read stream, means it points the read stream to begin to the buffer (just like seekg(0) in the filesystem)

This function must be called at least ones between the first piece of data getting stored in the buffer and read(char*,size_t) is called

```c++

/*In the situation below it is important to use init_read()
  As no Buffer.write does not calls init_read()
  And Constructor Buffer can not point read_stream to beginning of the buffer as,
  no begin of the buffer exists at that point
*/
  int intiger=5; double decimal=2.2222222; char cstring[] = "HelloBuffer";

  Buffer buf;//creating new buffer
  buf.write((char*)(&intiger), sizeof(intiger));
  buf.write(reinterpret_cast<char*>(&decimal), sizeof(double));
  buf.write(cstring, 12);

  int retinteger; double retdecimal; char retcstring[13];

  buf.init_read();//unsing init_read()

  buf.read((char*)(&retinteger), sizeof(integer));
  buf.read((char*)(&retdecimal), sizeof(double));
  buf.read(retcstring, 12);
  
  cout<<retinteger<<endl<<retdecimal<<endl<<retcstring<<endl;
```

### If using init_read() is an Issue, then use write_and_init_read(char*, size_t)
### > write_and_init_read( char* , size_t )
This function can be used to copy data from the Buffer to the address provided as char* for provided length as size_t
Use it just like read( char* , size_t )

And this function assures that the read stream is pointed to the beginning of the buffer

```c++

  int intiger=5; double decimal=2.2222222; char cstring[] = "HelloBuffer";

  Buffer buf;//creating new buffer
  buf.write_and_init_read((char*)(&integer), sizeof(integer));
  buf.write_and_init_read(reinterpret_cast<char*>(&decimal), sizeof(double));
  buf.write_and_init_read(cstring, 12);

  int retinteger; double retdecimal; char retcstring[13];
  
  //No need to call init_read()
  
  buf.read((char*)(&retinteger), sizeof(integer));
  buf.read((char*)(&retdecimal), sizeof(double));
  buf.read(retcstring, 12);
  
  cout<<retinteger<<endl<<retdecimal<<endl<<retcstring<<endl;
```

This can be very useful where it difficult or not possible to predict that when the buffer would be empty and the Buffer.write(), Buffer.read() or Buffer.clear() function gets called

### > clear()
The very purpose of this library is associated with Environments that support C++ addons/extensions hence it is important to assure that there is no memory leak

The job of this function is to free the memory allocated by the Buffer

```c++

  int intiger=5; double decimal=2.2222222; char cstring[] = "HelloBuffer";

  Buffer buf;//creating new buffer
  buf.write_and_init_read((char*)(&intiger), sizeof(intiger));
  buf.write_and_init_read(reinterpret_cast<char*>(&decimal), sizeof(double));
  buf.write_and_init_read(cstring, 12);
  
  cout<<"Size of buffer:" << buf._size();
  
  buf.clear();
  
  cout<<"Size of buffer:" << buf._size();
```

### Buffer I/O | Storing and Loading buffer from file

### > write_in_file( ofstream* )
This function can be used to store the data in the Buffer in the File pointer by (std::ofstream*) pointer
This function will open or close any file stream, it will just use the given file-stream in (std::ofstream*) pointer to write the file
```c++

//using write_in_file() to write the buffer in "fileforbuffer" file
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {

  int intiger=5; double decimal=2.2222222; char cstring[] = "HelloBuffer";

  Buffer buf;//creating new buffer
  //adding some data in the buffer
  buf.write((char*)(&integer), sizeof(integer));
  buf.write(reinterpret_cast<char*>(&decimal), sizeof(double));
  buf.write(cstring, 12);

  ofstream file("fileforbuffer", ios::binary);//opening output file-stream

  if( file.is_open() ){
    buf.write_in_file(&file);//writing the buffer in the output file-stream pointed by file
    file.close();//closing the file
  }

  buf.clear();

  return 0;
}

```
```c++
//using write_in_file() to append the buffer in "stackfileforbuffer" file
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {

  int integer=5; double decimal=2.2222222; char cstring[] = "HelloBuffer";

  Buffer buf;//creating new buffer
  //adding some data in the buffer
  buf.write((char*)(&integer), sizeof(integer));
  buf.write(reinterpret_cast<char*>(&decimal), sizeof(double));
  buf.write(cstring, 12);

  ofstream file("stackfileforbuffer", ios::binary | ios::app);//opening output file-stream

  if( file.is_open() ){
    buf.write_in_file(&file);//writing the buffer in the output file-stream pointed by file
    file.close();//closing the file
  }

  buf.clear();

  return 0;
}
```











