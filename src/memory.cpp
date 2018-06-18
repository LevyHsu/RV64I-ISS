/* ****************************************************************
   RISC-V Instruction Set Simulator
   Computer Architecture, Semester 1, 2018

   Class members for memory

**************************************************************** */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <inttypes.h> // unit64_t temporary for my IDE
#include <cmath>

#include "memory.h"
using namespace std;

// Constructor
memory::memory(bool verbose) 
{
  if(verbose)
    cout << "Memory Created" << endl; 
  debug = verbose;
}

void memory::creat_memory_block(uint64_t address)
{
  address=address-address%8;
  unsigned long long int block_num = (address-address%(BLOCKSIZE/8))/(BLOCKSIZE/8);
  unsigned long long int *block=new unsigned long long int [BLOCKSIZE];
  block_vector.push_back(block_num);
  block_pointer.push_back(block);

  if(debug)
  {
    cout << endl;
    cout << "--------DEBUG--------"<< endl;
    cout << "Memory Block Created"<< endl;
    cout << "Memory Address: "<<address<< endl;
    cout << "Block_Num: "<<block_num<< endl;
    cout << "Block_Address: "<<&block<< endl;
    cout << "--------DEBUG--------"<< endl;
    cout << endl;
  }
}


uint64_t memory::read_doubleword (uint64_t address) {
  // TODO: ...
  address = address - address%4; //incase not aligned
  unsigned long long int block_num = (address-address%(BLOCKSIZE/8))/(BLOCKSIZE/8);
  uint64_t result=0x0000000000000000ULL;
  unsigned long long int pos = find(block_vector.begin(), block_vector.end(), block_num) - block_vector.begin();
  if(pos < block_vector.size())
  {
    for(int j=0;j<64;j++)
      {
        if (*((block_pointer.at(pos) + 8*(address%(BLOCKSIZE/8)))+j)  ==  1)
        {
          long long int poweroftwo=pow(2,j);
          result = result + poweroftwo;
        }
        if(debug)
        {
          //cout<<"Value at ["<<j<<"]: "<<*((block_pointer.at(pos)+ 8*(address%(BLOCKSIZE/8)))+j)<<endl;
          //cout<<"Power of "<<j<<" = "<<pow(2,j)<<endl;
          //cout << "result = "<<result<<endl<<endl;
        }
      }
    //cout<<"Memory read word: address = "<<setw(16) << setfill('0') << hex << address << ", data = "<<setw(16) << setfill('0') << hex << result<<endl;
    return result;
  }
  creat_memory_block(address);
  return 0x0000000000000000ULL;
}
uint64_t memory::read_unaligned (uint64_t address){

  unsigned long long int block_num = (address-address%(BLOCKSIZE/8))/(BLOCKSIZE/8);
  uint64_t result=0x0000000000000000ULL;
  unsigned long long int pos = find(block_vector.begin(), block_vector.end(), block_num) - block_vector.begin();
  if(pos < block_vector.size())
  {
    for(int j=0;j<64;j++)
      {
        if (*((block_pointer.at(pos) + 8*(address%(BLOCKSIZE/8)))+j)  ==  1)
        {
          long long int poweroftwo=pow(2,j);
          result = result + poweroftwo;
        }
        if(debug)
        {
          //cout<<"Value at ["<<j<<"]: "<<*((block_pointer.at(pos)+ 8*(address%(BLOCKSIZE/8)))+j)<<endl;
          //cout<<"Power of "<<j<<" = "<<pow(2,j)<<endl;
          //cout << "result = "<<result<<endl<<endl;
        }
      }
    //cout<<"Memory read word: address = "<<setw(16) << setfill('0') << hex << address << ", data = "<<setw(16) << setfill('0') << hex << result<<endl;
    return result;
  }
  creat_memory_block(address);
  return 0x0000000000000000ULL;
}

//  if(binary_search (block_vector.begin(), block_vector.end(), block_num))
// Write a word of data to an address, mask contains 1s for bytes to be updated
void memory::write_doubleword (uint64_t address, uint64_t data, uint64_t mask) {
  address = address - address % 8 ;
  unsigned long long int block_num = (address-address%(BLOCKSIZE/8))/(BLOCKSIZE/8);
  unsigned long long int pos = find(block_vector.begin(), block_vector.end(), block_num) - block_vector.begin();

  if(pos < block_vector.size())
  {
    long long int i=0,r;
    int dataarray[64]={0};
    while(data != 0)
    {
      r = data % 2;
      dataarray[i++] = r;
      data /= 2;
    }

    int maskarray[64]={0};
    i=0;
    while(mask != 0)
    {
      r = mask % 2;
      maskarray[i++] = r;
      mask /= 2;
    }

   if(debug)
        {
          cout<<"Writing doubleword at address:" <<&*(block_pointer.at(pos)+ 8*(address%(BLOCKSIZE/8)))<<endl;
          cout<<"DataArray: ";
          for(int k=0;k<64;k++)
          {
           cout<<dataarray[k];
          }
          cout<<endl<<"MaskArray: ";
          for(int l=0;l<64;l++)
          {
           cout<<maskarray[l];
          }
          cout<<endl;
          cout<<"Original : ";    
        }

  for(int j=0;j<64;j++)
      {
        if(debug)
            cout<<*((block_pointer.at(pos)+ 8*(address%(BLOCKSIZE/8)))+j);
        if (maskarray[j]==1)
        {
          *((block_pointer.at(pos)+ 8*(address%(BLOCKSIZE/8)))+j)= dataarray[j];
        }    
      }
       if(debug)
      {
        cout<<endl;
        cout<<"  After  : "; 
        for(int i=0;i<64;i++)
          {
           cout<<*((block_pointer.at(pos)+ 8*(address%(BLOCKSIZE/8)))+i);
          }
        cout<<endl<<endl;
      }
        
  }
  else
  {
    creat_memory_block(address);
    write_doubleword(address,data,mask);
  }
}

// Display the word of data at an address
void memory::show_address (uint64_t address) {
  //cout << "0x" << setw(16) << setfill('0') << right << hex << read_doubleword(address) << endl;
  cout << setw(16) << setfill('0') << right << hex << read_doubleword(address) << endl;
}

// Set the word of data at an address
void memory::set_address (uint64_t address, uint64_t data) {
  write_doubleword(address,data,0xFFFFFFFFFFFFFFFFULL);
}

// Load a hex image file
bool memory::load_file(string file_name, uint64_t &start_address) {
  ifstream input_file(file_name);
  string input;
  unsigned int line_count = 0;
  unsigned int byte_count = 0;
  char record_start;
  char byte_string[3];
  char halfword_string[5];
  unsigned int record_length;
  unsigned int record_address;
  unsigned int record_type;
  unsigned int record_data;
  unsigned int record_checksum;
  bool end_of_file_record = false;
  uint64_t load_address;
  //uint64_t load_data;
  uint64_t load_mask;
  uint64_t load_base_address = 0x0000000000000000ULL;
  start_address = 0x0000000000000000ULL;
  if (input_file.is_open()) {
    while (true) {
      line_count++;
      input_file >> record_start;
      if (record_start != ':') {
	cout << "Input line " << dec << line_count << " does not start with colon character" << endl;
	return false;
      }
      input_file.get(byte_string, 3);
      sscanf(byte_string, "%x", &record_length);
      //cout<<"----------byte_string-----------:"<<byte_string<<endl;
      input_file.get(halfword_string, 5);
      sscanf(halfword_string, "%x", &record_address);
       //cout<<"----------halfword_string-----------:"<<halfword_string<<endl;
      input_file.get(byte_string, 3);
       //cout<<"----------byte_string2-----------:"<<byte_string<<endl;
      sscanf(byte_string, "%x", &record_type);
      switch (record_type) {
      case 0x00:  // Data record
	for (unsigned int i = 0; i < record_length; i++) {
	  input_file.get(byte_string, 3);
	  sscanf(byte_string, "%x", &record_data);
	  load_address = (load_base_address | (uint64_t)(record_address)) + i;
	  // TODO: code to store data byte in memory.
	  //   - load_address is the byte address at which to store
	  //   - record_data is the byte of data to store
    //                  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    //:10 0000 00 37 | 01 00 80 13 01 01 00 13 04 00 00 37 05 01 00 CF
    //:10 0010 00 03 | 25 05 00 B7 05 01 00 83 A5 45 00 37 06 01 00 4B
    //:10 0020 00 03 | 26 86 00 B7 06 01 00 83 A6 C6 00 EF 00 80 00 05
    //:10 0030 00 67 | 00 00 00 13 01 01 FD 23 26 81 02 13 04 01 03 60
    //:10 0040 00 23 | 2E A4 FC 23 2C B4 FC 23 2A C4 FC 23 28 D4 FC 98
    //:10 0050 00 03 | 27 C4 FD 83 27 84 FD 33 07 F7 00 83 26 44 FD 6F
    //:10 0060 00 83 | 27 04 FD B3 87 F6 00 B3 07 F7 40 23 26 F4 FE 89
    //:10 0070 00 83 | 27 C4 FE 13 85 07 00 03 24 C1 02 13 01 01 03 73
    //:04 0080 00 67 | 80 00 00 95
    //:02 0000 02 10 | 00 EC
    //:10 0000 00 17 | 00 00 00 F8 00 00 00 19 00 00 00 0F 00 00 00 B9
    //:00 0000 01 FF
	  // ...
    uint64_t offset = load_address % 8;
    load_mask = 0xFFULL << offset * 8;

    if(debug)
    {
    cout << "--------load_file--------"<< endl;
    cout << "address: "<< load_address << endl;
    cout << "data:    "<< (uint64_t)record_data<<offset*8 << endl;
    cout << "mask:    "<< load_mask<<endl;
    cout << "--------load_file--------"<< endl<<endl;
    }


    write_doubleword(load_address,(uint64_t)record_data<<offset*8,load_mask);
    
	  byte_count++;
	}
	break;
      case 0x01:  // End of file
	end_of_file_record = true;
	break;
      case 0x02:  // Extended segment address (set bits 19:4 of load base address)
	load_base_address = 0x0000000000000000ULL;
	for (unsigned int i = 0; i < record_length; i++) {
	  input_file.get(byte_string, 3);
	  sscanf(byte_string, "%x", &record_data);
	  load_base_address = (load_base_address << 8) | (record_data << 4);
	}
	break;
      case 0x03:  // Start segment address (ignored)
	for (unsigned int i = 0; i < record_length; i++) {
	  input_file.get(byte_string, 3);
	  sscanf(byte_string, "%x", &record_data);
	}
	break;
      case 0x04:  // Extended linear address (set upper halfword of load base address)
	load_base_address = 0x0000000000000000ULL;
	for (unsigned int i = 0; i < record_length; i++) {
	  input_file.get(byte_string, 3);
	  sscanf(byte_string, "%x", &record_data);
	  load_base_address = (load_base_address << 8) | (record_data << 16);
	}
	break;
      case 0x05:  // Start linear address (set execution start address)
	start_address = 0x0000000000000000ULL;
	for (unsigned int i = 0; i < record_length; i++) {
	  input_file.get(byte_string, 3);
	  sscanf(byte_string, "%x", &record_data);
	  start_address = (start_address << 8) | record_data;
	}
	break;
      }
      input_file.get(byte_string, 3);
      sscanf(byte_string, "%x", &record_checksum);
      input_file.ignore();
      if (end_of_file_record)
	break;
    }
    input_file.close();
    cout << dec << byte_count << " bytes loaded, start address = "
	 << setw(16) << setfill('0') << hex << start_address << endl;
    return true;
  }
  else {
    cout << "Failed to open file" << endl;
    return false;
  }
}

/*
Reference:
https://stackoverflow.com/questions/9245413/index-of-first-element-to-a-number-in-a-vector-with-stlalgorithm
https://stackoverflow.com/questions/31849915/how-to-initialize-a-uint64-t-array-to-0-in-c
https://stackoverflow.com/questions/20034297/decimal-to-hex-conversion-c-built-in-function
https://stackoverflow.com/questions/7401172/printing-hexadecimal-values-in-c
*/