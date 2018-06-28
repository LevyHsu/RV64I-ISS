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
  //debug=true;

  //User Mode
  Privilege_level = 3 ;
  instruction_executed = 0;
  breakpoint=0xffffffffffffffff;
  f11_f14_read_only=false;

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

  //Csr intialized
  csr_array = new int *[64];
  for (int i = 0; i < 4096; i++)
  {
    csr_defined[i] = false;
    csr_array[i] = new int [64];
    for (int j = 0; j < 64; j++)
    {
      csr_array[i][j]=0;
    }
  }

  set_csr(0xF11,0x0000000000000000);   //mevendorid
  set_csr(0xF12,0x0000000000000000);   //marchid
  set_csr(0xF13,0x2018020000000000);   //mimpid
  set_csr(0xF14,0x0000000000000000);   //mhartid
  set_csr(0x300,0x0000000200000000);   //mstatus
  set_csr(0x301,0x8000000000100100);   //misa 
  set_csr(0x304,0x0000000000000000);   //mie
  set_csr(0x305,0x0000000000000000);   //mtvec
  set_csr(0x340,0x0000000000000000);   //mscratch  
  set_csr(0x341,0x0000000000000000);   //mepc
  set_csr(0x342,0x0000000000000000);   //mcause
  set_csr(0x343,0x0000000000000000);   //mtval
  set_csr(0x344,0x0000000000000000);   //mip
  csr_defined[0xF11]=true;
  csr_defined[0xF12]=true;
  csr_defined[0xF13]=true;
  csr_defined[0xF14]=true;
  csr_defined[0x300]=true;
  csr_defined[0x301]=true;
  csr_defined[0x304]=true;
  csr_defined[0x305]=true;
  csr_defined[0x340]=true;
  csr_defined[0x341]=true;
  csr_defined[0x342]=true;
  csr_defined[0x343]=true;
  csr_defined[0x344]=true;
  f11_f14_read_only =true;
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
      cout<<"Register[0] ALWAYS 0!"<<endl;
    } 
}

  // Execute a number of instructions
void processor::execute(unsigned int num, bool breakpoint_check,processor* CPU)
{
      for(unsigned int i = 0; i < num; i++)
      {
        //in case of abnormal exit 
        if( breakpoint_check && (return_pc()==breakpoint))
        {
              cout<<"Breakpoint reached at "<< setw(16) << setfill('0') << hex << return_pc() <<endl;
              break;
        }
        else
        {
            instructions* new_instruction;
            new_instruction = new instructions (Main_Memory,CPU,debug);
            if(return_pc()%4!=0)
                new_instruction->misaligned_instr();
            else
                new_instruction->execute_command(return_pc());
            set_pc(return_pc() + 4 );
            instruction_executed++;
            if(instruction_executed>100000)
            {
              cout<<"ERROR!"<<endl;
              exit(1);
            }     
        }  
      }
}

  // Clear breakpoint
void processor::clear_breakpoint()
{
    breakpoint=0xffffffffffffffff;
}

  // Set breakpoint at an address
void processor::set_breakpoint(uint64_t address)
{
    if(debug)
      cout<<"NEW Brake Point:"<< setw(16) << setfill('0') <<hex<<address<<endl;
    breakpoint=address;
}

void processor::set_instruction_count(uint64_t count)
{
    instruction_executed = count;
}

uint64_t processor::get_instruction_count()
{
  return instruction_executed;
}

  // Used for Postgraduate assignment. Undergraduate assignment can return 0.
uint64_t processor::get_cycle_count()
{
  //TODO
  return 0;
}

void processor::show_prv()
{
    if (Privilege_level==0)
      cout<<"0 (user)"<<endl;
    else
      cout<<"3 (machine)"<<endl;
}

void processor::set_prv(unsigned int prv_num)
{
  if ( prv_num==3 || prv_num==0 )
  {
      Privilege_level = prv_num;
          
  }   
  else if (debug)
  {
    cout<<"Supports User/Machine Mode Only"<<endl;
  }
}

unsigned int processor::return_prv()
{
  return Privilege_level;
}

void processor::show_csr(unsigned int csr_num)
{
  if(!csr_defined[csr_num])
  {
      cout<<"Illegal CSR number"<<endl;
  }
  else
  {
      uint64_t result=0,poweroftwo=0,temp;
      for (int i = 63; i > -1; i--)
      {
          if(csr_array[csr_num][i]==1)
          {
            temp=63-i;
            poweroftwo = pow(2,temp);
            result = result + poweroftwo;
          }  
      }
      cout << setw(16) << setfill('0') << right << hex << result << endl;
  }
  
}

uint64_t processor::return_csr(unsigned int csr_num)
{
  if(!csr_defined[csr_num])
  {
      cout<<"Illegal CSR number"<<endl;
  }
  else
  {
      uint64_t result=0,poweroftwo=0,temp;
      for (int i = 63; i > -1; i--)
      {
          if(csr_array[csr_num][i]==1)
          {
            temp=63-i;
            poweroftwo = pow(2,temp);
            result = result + poweroftwo;
          }  
      }
      return result;
  }
  return 0;
}

void processor::set_csr(unsigned int csr_num, uint64_t new_value)
{
    //mstatus
    if(csr_num==0x300)
    {
        new_value &= 0x1888;
        new_value |= 0x200000000;
    }

    //misa
    if(csr_num==0x301)
        new_value = 0x8000000000100100;

    //mie
    if(csr_num==0x304)
        new_value &= 0x999;

    if(csr_num==0x305)
    {
        //Direct Mode
        if( (new_value&0x1) == 0)
        {
            new_value &= 0xfffffffffffffffc;
        }
        //Vectored Mode
        else
        {
            new_value &= 0xffffffffffffff01;
        }
    }

    //mscratch
    if(csr_num==0x340)
        new_value &= 0xffffffffffffffff;

    //mepc
    if(csr_num==0x341)
        new_value &= 0xfffffffffffffffc;

    //mcause
    if(csr_num==0x342)
        new_value &= 0x800000000000000f;

    //mtval
    if(csr_num==0x343)
        new_value &= 0xffffffffffffffff;
    
    if(csr_num==0x344)
        new_value &= 0x999;

    if(csr_num==0xf11)
    {
      if(f11_f14_read_only)
          cout<<"Illegal write to read-only CSR"<<endl;
      new_value = 0x0000000000000000;
    }

    if(csr_num==0xf12)
    {
       if(f11_f14_read_only)
          cout<<"Illegal write to read-only CSR"<<endl;
      new_value = 0x0000000000000000;
    }

    if(csr_num==0xf13)
    {
       if(f11_f14_read_only)
          cout<<"Illegal write to read-only CSR"<<endl;
      new_value = 0x2018020000000000;
    }

    if(csr_num==0xf14)
    {
       if(f11_f14_read_only)
          cout<<"Illegal write to read-only CSR"<<endl;
      new_value = 0x0000000000000000;
    }

    if(debug)
    {
      cout<<"new_value:"<<setw(16)<< setfill('0')<<hex<<new_value<<endl;
      cout<<"Csr["<<hex<<csr_num<<"] Original Value: ";
    }
    
    for (int j = 0; j < 64; j++)
    {  
      if (debug)
      {
        cout<<csr_array[csr_num][j];
      }
      csr_array[csr_num][j]=0;
    }
    
    int i=63,r;  
     while(new_value != 0)
    {
      r = new_value % 2;
      csr_array[csr_num][i--] = r;
      new_value /= 2;
    }

    if(debug)
    {
      cout<<endl;
      cout<<"Csr["<<hex<<csr_num<<"] Modified Value: ";
      for (int j = 0; j < 64; j++)
      {
        cout<<csr_array[csr_num][j];
      }
      cout<<endl<<endl;
    }
}

bool processor::csr_is_defined(unsigned int csr_num)
{
  return csr_defined[csr_num];
}

bool processor::illegal_csr_write(unsigned int csr_num)
{
  if((csr_num==0xf11)||(csr_num==0xf12)||(csr_num==0xf13)||(csr_num==0xf14))
     return true;
  return false;
}