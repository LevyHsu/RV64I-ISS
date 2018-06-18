#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <cmath>

#include "processor.h"
#include "memory.h"
#include "decode.h"


using namespace std;

processor::processor(memory* main_memory, bool verbose)
{
  Main_Memory=main_memory;
  debug=verbose;
  instruction_executed = 0;
  breakpoint=0xFFFFFFFFFFFFFFFFULL;

  pc_array = new int [64];
  for(int k=0;k<64;k++)
    {
       pc_array[k]=0;
    }
  if(debug)
    cout<<"PC Initilized"<<endl;

  //register[x0..31][0-31bit]
  
  register_array = new int *[64];
  for (int i = 0; i < 32; i++)
  {
    register_array[i] = new int [64];
    for (int j = 0; j < 64; j++)
    {
      register_array[i][j]=0;
    }
  }
  if(debug)
    cout<<"Register x0..x31 initialized"<<endl; 
}

void processor::show_pc()
{
  cout << setw(16) << setfill('0') << right << hex << return_pc() << endl;
}

uint64_t processor::return_pc()
{
  long long int result=0,poweroftwo=0;
  int temp;
  for (int i = 63; i > -1; i--)
  {
    if(pc_array[i]==1)
    {
      temp=63-i;
      poweroftwo = pow(2,temp);
      result = result + poweroftwo;
    }  
  }
  return result;
}

  // Set PC to new value
void processor::set_pc(uint64_t new_pc)
{
    
    if(debug)
          {
            cout<<"PC Original: "<<endl;
          }
      for (int j = 0; j < 64; j++)
        {
          if(debug)
            {
              cout<<pc_array[j];
            }
            pc_array[j]=0;
        }
        int i=63,r;   
        while(new_pc != 0)
        {
            r = new_pc % 2;
            pc_array[i--] = r;
            new_pc /= 2;
        }
         if(debug)
          {
            cout<<endl<<"PC After: "<<endl;
            for (int j = 0; j < 64; j++)
            {
                cout<<pc_array[j];
            }
            cout<<endl;
          }
          

}
uint64_t processor::return_reg(unsigned int reg_num)
{
  long long int result=0,poweroftwo=0;
  int temp;
  for (int i = 63; i > -1; i--)
  {
    if(register_array[reg_num][i]==1)
    {
      temp=63-i;
      poweroftwo = pow(2,temp);
      result = result + poweroftwo;
    }  
  }
  return result;
}

  // Display register value
void processor::show_reg(unsigned int reg_num)
{
  cout << setw(16) << setfill('0') << right << hex << return_reg(reg_num) << endl;
}

  // Set register to new value
void processor::set_reg(unsigned int reg_num, uint64_t new_value)
{
  if(reg_num!=0)
  {
      if(debug)
    {
      cout<<"Register["<<reg_num<<"] Original Value: ";
    }
    for (int j = 0; j < 64; j++)
    {  
      if (debug)
      {
        cout<<register_array[reg_num][j];
      }
      register_array[reg_num][j]=0;
    }
    
    int i=63,r;  
     while(new_value != 0)
    {
      r = new_value % 2;
      register_array[reg_num][i--] = r;
      new_value /= 2;
    }

    if(debug)
    {
      cout<<endl;
      cout<<"Register["<<reg_num<<"] Modified Value: ";
      for (int j = 0; j < 64; j++)
      {
        cout<<register_array[reg_num][j];
      }
      cout<<endl<<endl;
    }
  }
   else if(debug)
    {
      cout<<"Register[0] ALWAYS 0!";
    } 
}

  // Execute a number of instructions
void processor::execute(unsigned int num, bool breakpoint_check,processor* CPU)
{
 
  if(return_pc()%4 != 0)
    {
      cout<<"Unaligned pc: " << setw(16) << setfill('0') << hex << return_pc() << endl;
    }
    else 
        for(unsigned int i = 0; i < num; i++)
      {
        //if(i>500) //in case of overflow
          //break;
        if( breakpoint_check && (return_pc()==breakpoint) )
        {
              cout<<"Breakpoint reached at "<< setw(16) << setfill('0') << hex << return_pc() <<endl;
              break;
        }
        else
        {
            instructions* new_instruction;
            new_instruction = new instructions (Main_Memory,CPU,debug);
            new_instruction->execute_command(return_pc());
            set_pc(return_pc() + 4 );
            instruction_executed++;
        }  
      }
}

  // Clear breakpoint
void processor::clear_breakpoint()
{
    breakpoint=0xFFFFFFFFFFFFFFFF;
}

  // Set breakpoint at an address
void processor::set_breakpoint(uint64_t address)
{
    breakpoint=address;
}

uint64_t processor::get_instruction_count()
{
  return instruction_executed;
}

void processor::set_instruction_count(uint64_t set)
{
  instruction_executed += set;
}

  // Used for Postgraduate assignment. Undergraduate assignment can return 0.
uint64_t processor::get_cycle_count()
{
  //TODO
  return 0;
}

//for addiw, set certian bits to 0 or 1
void processor::set_reg_certian_bit(unsigned int reg_num, int start,int end,bool negative)
{
  for (int i=start;i<end+1;i++)
  {
    if (negative)
      register_array[reg_num][i]=1;
    else
      register_array[reg_num][i]=0;
  }
}