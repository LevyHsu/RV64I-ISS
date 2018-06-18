#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <cmath>

#include "memory.h"
#include "decode.h"
#include "processor.h"

using namespace std;

instructions::instructions(memory* main_memory,processor* cpu,bool verbose)
{
    debug=verbose;
    //debug=true;
    Main_Memory=main_memory;
    CPU=cpu;
    instruction_array = new int [64];
    for(int k=0;k<64;k++)
    {
       instruction_array[k]=0;
    }
}

void instructions::array_load(uint64_t memory_address)
{
    uint64_t data=Main_Memory->read_doubleword(memory_address);
    long long int i=0,r;
    for(int k=0;k<64;k++)
    {
       instruction_array[k]=0;
    }
    while(data != 0)
    {
      r = data % 2;
      instruction_array[i++] = r;
      data /= 2;
    }
     //cout<<endl<<"PC:"<<hex<<CPU->return_pc()<<endl;
     //cout<<"Memory read word: address:"<<hex<<memory_address<<" ir ="<<setfill('0')<<setw(8)<<hex<< (Main_Memory->read_doubleword(memory_address) & 0xffffffff) <<endl; 
}

long long int instructions::return_signed_bit_value(int begin,int end)
{
    long long int result=0,power=0;
    
    //positive
    if(instruction_array[end]==0)
    {
        for (int i=begin;i<end;i++)
        {
            if(instruction_array[i]==1)
                result +=  pow(2,power);
            power++;
        }
        return result;
    }
    //nagative
    else
    {
        for (int i=begin;i<end;i++)
        { 
            if(instruction_array[i]==0)
                result +=  pow(2,power);
            power++;
        }
        return ~result;
    }
    return 0;
}

long long int instructions::return_unsigned_bit_value(int begin,int end)
{
    long long int result=0,power=0;
    for (int i=begin;i<end+1;i++)
        {
            if(instruction_array[i]==1)
                result +=  pow(2,power);
            power++;
        }
    return result;
}

string instructions::instraction_type()
{
    string op;
    for (int i=0;i<7;i++)
    {
       op.push_back(instruction_array[i]+ '0');
       //cout<<"ins_array["<<i<<"] = "<<instruction_array[i]<<endl;
    }
    
    string funct3;
    for (int i=12;i<15;i++)
    {
       funct3.push_back(instruction_array[i]+ '0');
    }

    string funct7;
    for (int i=25;i<32;i++)
    {
       funct7.push_back(instruction_array[i]+ '0');
    }

    string csr;
    for (int i=20;i<32;i++)
    {
       csr.push_back(instruction_array[i]+ '0');
    }
    if(debug)
    {
        cout << "  OP  :" << op << endl;
        cout << "FUNCT3:" << funct3 << endl;
        cout << "FUNCT7:" << funct7 << endl;
    }
        
    //RV32I Base ins set
    if (op=="1110110") return "LUI";                    //Priority
    if (op=="1110100") return "AUIPC";
    if (op=="1111011") return "JAL";
    if (op=="1110011"&&funct3=="000") return "JALR";    //Priority
    if (op=="1100011"&&funct3=="000") return "BEQ";
    if (op=="1100011"&&funct3=="100") return "BNE";     //Priority
    if (op=="1100011"&&funct3=="001") return "BLT";
    if (op=="1100011"&&funct3=="101") return "BGE";
    if (op=="1100011"&&funct3=="011") return "BLTU";
    if (op=="1100011"&&funct3=="111") return "BGEU";
    if (op=="1100000"&&funct3=="000") return "LB";
    if (op=="1100000"&&funct3=="100") return "LH";
    if (op=="1100000"&&funct3=="010") return "LW";
    if (op=="1100000"&&funct3=="001") return "LBU";
    if (op=="1100000"&&funct3=="101") return "LHU";
    if (op=="1100010"&&funct3=="000") return "SB";
    if (op=="1100010"&&funct3=="100") return "SH";
    if (op=="1100010"&&funct3=="010") return "SW";
    if (op=="1100100"&&funct3=="000") return "ADDI";    //Priority
    if (op=="1100100"&&funct3=="010") return "SLTI";
    if (op=="1100100"&&funct3=="110") return "SLTIU";
    if (op=="1100100"&&funct3=="001") return "XORI";
    if (op=="1100100"&&funct3=="011") return "ORI";
    if (op=="1100100"&&funct3=="111") return "ANDI";
    if (op=="1100100"&&funct3=="100") return "SLLI"; //Priority
    if (op=="1100100"&&funct3=="101"&&instruction_array[30]==0) return "SRLI";
    if (op=="1100100"&&funct3=="101"&&instruction_array[30]==1) return "SRAI";
    if (op=="1100110"&&funct3=="000"&&funct7=="0000000") return "ADD";
    if (op=="1100110"&&funct3=="000"&&funct7=="0000010") return "SUB";
    if (op=="1100110"&&funct3=="100"&&funct7=="0000000") return "SLL";
    if (op=="1100110"&&funct3=="010"&&funct7=="0000000") return "SLT";
    if (op=="1100110"&&funct3=="110"&&funct7=="0000000") return "SLTU";
    if (op=="1100110"&&funct3=="001"&&funct7=="0000000") return "XOR";
    if (op=="1100110"&&funct3=="101"&&funct7=="0000000") return "SRL";
    if (op=="1100110"&&funct3=="101"&&funct7=="0000010") return "SRA";
    if (op=="1100110"&&funct3=="011"&&funct7=="0000000") return "OR";
    if (op=="1100110"&&funct3=="111"&&funct7=="0000000") return "AND";
    
    //No operation 
    if (op=="1111000"&&funct3=="000") return "FENCE";
    if (op=="1111000"&&funct3=="100") return "FENCE.I";
    //UMIMPLEMENTED
    if (op=="1100111"&&funct3=="000"&&csr=="000000000000") return "ECALL";
    if (op=="1100111"&&funct3=="000"&&csr=="100000000000") return "EBREAK";
    if (op=="1100111"&&funct3=="100") return "CSRRW";
    if (op=="1100111"&&funct3=="010") return "CSRRS";
    if (op=="1100111"&&funct3=="110") return "CSRRC";
    if (op=="1100111"&&funct3=="101") return "CSRRWI";
    if (op=="1100111"&&funct3=="011") return "CSRRSI";
    if (op=="1100111"&&funct3=="111") return "CSRRCI";

    //RV64I Base ins set
    if (op=="1100000"&&funct3=="011") return "LWU";
    if (op=="1100000"&&funct3=="110") return "LD";
    if (op=="1100010"&&funct3=="110") return "SD";
    //if (op=="1100100"&&funct3=="100") return "SLLI";
    //if (op=="1100100"&&funct3=="101") return "SRLI";
    //if (op=="1100100"&&funct3=="101") return "SRAI";
    if (op=="1101100"&&funct3=="000") return "ADDIW";              //Priority
    if (op=="1101100"&&funct3=="100"&&funct7=="0000000") return "SLLIW";
    if (op=="1101100"&&funct3=="101"&&instruction_array[30]==0) return "SRLIW";
    if (op=="1101100"&&funct3=="101"&&instruction_array[30]==1) return "SRAIW";
    if (op=="1101110"&&funct3=="000"&&funct7=="0000000") return "ADDW";
    if (op=="1101110"&&funct3=="000"&&funct7=="0000010") return "SUBW";
    if (op=="1101110"&&funct3=="100"&&funct7=="0000000") return "SLLW";
    if (op=="1101110"&&funct3=="101"&&funct7=="0000000") return "SRLW";
    if (op=="1101110"&&funct3=="101"&&funct7=="0000010") return "SRAW";

   
   return "ERROR";
}

void instructions::execute_command(uint64_t memory_address)
{
    array_load(memory_address);
    string type=instraction_type();
    if(debug)
    {
        cout<<"ins Type: "<<type<<endl;
    }
    if (type=="ERROR")
    {
        cout<<"Illegal instruction: "<< setw(8) << setfill('0') << right << hex <<Main_Memory->read_doubleword(memory_address)<<endl;
    }

    if (type=="LUI")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t imm = return_signed_bit_value(12,31) << 12;
        if (instruction_array[31]!=0)
        {
            imm |= 0xffffffff00000000;
        }
       CPU->set_reg(rd, imm);
       //cout<<"lui: rd = "<<dec<<rd<<", immed_U = "<<setfill('0')<<setw(16)<<hex<<imm<<endl; 
    }
    
    if (type=="AUIPC")
    {  
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t imm = return_signed_bit_value(12,31) << 12;
        if(instruction_array[31] != 0)
        {
            imm |= 0xffffffff00000000;
        }
        CPU->set_reg(rd, imm + CPU->return_pc());
        //cout<<"auipc: rd = "<<dec<<rd<<", immed_U = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;  
    }
    
    if (type=="JAL")
    {  
        uint64_t rd = return_unsigned_bit_value(7,11); 
        uint64_t imm10= return_unsigned_bit_value(21,30) << 1;
        uint64_t imm11= instruction_array[20] << 11;
        uint64_t imm19= return_unsigned_bit_value(12,19) << 12;
  
        uint64_t imm = imm19 | imm11 | imm10;
        if ( instruction_array[31] != 0 )
            imm |= 0xfffffffffff00000;
        
       CPU->set_reg(rd , CPU->return_pc() + 4 );
       CPU->set_pc(CPU->return_pc() + imm - 4);
    }
    if (type=="JALR")
    {
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t rd = return_unsigned_bit_value(7,11); 
        int64_t imm = return_signed_bit_value(20,31);
        if(instruction_array[31]!=0)
        {
            imm |= 0xfffffffffffff000;
        }
        //cout<<"jalr: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rd = "<<dec<<rd<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
        CPU->set_reg(rd ,CPU->return_pc() + 4 );
        CPU->set_pc( (( rs1 + imm ) & 0xfffffffffffffffe) - 4 );
    }
    if (type=="BEQ")
    { 
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
        uint64_t imm10_5 = return_unsigned_bit_value(25,30) << 5;
        uint64_t imm4_1 = return_unsigned_bit_value(8,11) << 1;
        uint64_t imm_11 = instruction_array[7] << 11 ;
        uint64_t immed_B = imm10_5 | imm4_1 | imm_11;
         if(instruction_array[31]!=0)
        {
            immed_B = (immed_B | 0xfffffffffffff000);
        }
        if(rs1 == rs2)
        {
            CPU->set_pc(CPU->return_pc() + immed_B -4 );
        }
    }
    if (type=="BNE")
    {    
        
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
        uint64_t imm10_5 = return_unsigned_bit_value(25,30) << 5;
        uint64_t imm4_1 = return_unsigned_bit_value(8,11) << 1;
        uint64_t imm_11 = instruction_array[7] << 11 ;
        uint64_t immed_B = imm10_5 | imm4_1 | imm_11;
         if(instruction_array[31]!=0)
        {
            immed_B = (immed_B | 0xfffffffffffff000);
        }
         //cout<<"bne: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_B = "<<setfill('0')<<setw(16)<<hex<<immed_B<<endl;
        if( rs1 != rs2)
        {  
            CPU->set_pc(CPU->return_pc() + immed_B - 4 );
        }
        //cout<<"-----RS1: "<<rs1<<"-----RS2: "<<rs2<<"-------"<<endl;
         //cout<<"NEW PC ="<<CPU->return_pc()<<endl;
         
    }
    if (type=="BLT")
    {
        int64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        int64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
        uint64_t imm10_5 = return_unsigned_bit_value(25,30) << 5;
        uint64_t imm4_1 = return_unsigned_bit_value(8,11) << 1;
        uint64_t imm_11 = instruction_array[7] << 11 ;
        uint64_t immed_B = imm10_5 | imm4_1 | imm_11;
         if(instruction_array[31]!=0)
        {
            immed_B = (immed_B | 0xfffffffffffff000);
        }
        if( rs1 < rs2)
        {
            CPU->set_pc(CPU->return_pc() + immed_B -4 );
        }
    }
    if (type=="BGE")
    {
        int64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        int64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
        uint64_t imm10_5 = return_unsigned_bit_value(25,30) << 5;
        uint64_t imm4_1 = return_unsigned_bit_value(8,11) << 1;
        uint64_t imm_11 = instruction_array[7] << 11 ;
        uint64_t immed_B = imm10_5 | imm4_1 | imm_11;
         if(instruction_array[31]!=0)
        {
            immed_B = (immed_B | 0xfffffffffffff000);
        }
        if( rs1 >= rs2)
        {
            CPU->set_pc(CPU->return_pc() + immed_B -4 );
        }
    }
    if (type=="BLTU")
    {
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
        uint64_t imm10_5 = return_unsigned_bit_value(25,30) << 5;
        uint64_t imm4_1 = return_unsigned_bit_value(8,11) << 1;
        uint64_t imm_11 = instruction_array[7] << 11 ;
        uint64_t immed_B = imm10_5 | imm4_1 | imm_11;
         if(instruction_array[31]!=0)
        {
            immed_B = (immed_B | 0xfffffffffffff000);
        }
        if( rs1 < rs2)
        {
            CPU->set_pc(CPU->return_pc() + immed_B -4 );
        }
    }
    if (type=="BGEU")
    {
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
        uint64_t imm10_5 = return_unsigned_bit_value(25,30) << 5;
        uint64_t imm4_1 = return_unsigned_bit_value(8,11) << 1;
        uint64_t imm_11 = instruction_array[7] << 11 ;
        uint64_t immed_B = imm10_5 | imm4_1 | imm_11;
         if(instruction_array[31]!=0)
        {
            immed_B = (immed_B | 0xfffffffffffff000);
        }
        if( rs1 >= rs2)
        {
            CPU->set_pc(CPU->return_pc() + immed_B -4 );
        }
    }
    if (type=="LB")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_signed_bit_value(20,31);
        if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        } 
        uint64_t address = imm + rs1;
        uint64_t data = Main_Memory->read_unaligned(address) & 0xff;
        if (data>>7!=0)
            data |= 0xFFFFFFFFFFFFFF00;
        CPU->set_reg(rd,data);
    }
    if (type=="LH")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_signed_bit_value(20,31);
        if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        } 
        uint64_t address = imm + rs1;
        uint64_t data = Main_Memory->read_unaligned(address) & 0xffff;
        if (data>>15!=0)
            data |= 0xFFFFFFFFFFFF0000;
        CPU->set_reg(rd,data);
    }
    if (type=="LW")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_signed_bit_value(20,31);
        if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        } 
        uint64_t address = imm + rs1;
        uint64_t data = Main_Memory->read_unaligned(address) & 0xffffffff;
        if (data>>31==1)
            data |= 0xffffffff00000000;
        CPU->set_reg(rd,data);
    }
    if (type=="LBU")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_signed_bit_value(20,31);
        if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        } 
        uint64_t address = imm + rs1;
        uint64_t data = Main_Memory->read_unaligned(address) & 0xff;
        data &= 0xFF;
        CPU->set_reg(rd,data);
    }
    if (type=="LHU")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_signed_bit_value(20,31);
        if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        } 
        uint64_t address = imm + rs1;
        uint64_t data = Main_Memory->read_unaligned(address) & 0xFFFF;
        data &= 0xFFFF;
        CPU->set_reg(rd,data);
    }
    if (type=="SB")
    {
        
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
        uint64_t imm4 = return_signed_bit_value(7,11);
        uint64_t imm11 = return_signed_bit_value(25,31) << 5 ;
        uint64_t imm = imm4 | imm11;
         if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        }
        uint64_t address = imm + rs1;
        int remainder = address % 8 ;
        address = address - address % 8 ;
        rs2 = rs2 << remainder*8;
        Main_Memory->write_doubleword(address,rs2, (0xff * pow(0x100,remainder)) );    
     //cout<<"sb: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_S = "<<setfill('0')<<setw(16)<<hex<<imm<<" rem : "<<dec<<remainder<<endl;
     //cout<<"Memory write word: address = "<<setw(16)<<hex<<address<<" data = "<<setfill('0')<<setw(16)<<hex<< rs2 <<" mask = "<<setw(16)<<hex<<((uint64_t)(0xff * pow(0x100,remainder)))<<endl; 
     
    }
    if (type=="SH")
    {
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24)) & 0xffff;
        uint64_t imm4 = return_signed_bit_value(7,11);
        uint64_t imm11 = return_signed_bit_value(25,31) << 5 ;
        uint64_t imm = imm4 | imm11;
         if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        }
        uint64_t address = imm + rs1;
        int remainder = address % 8 ;
        rs2 = rs2 << remainder*8;
        if ( remainder < 7 )
            Main_Memory->write_doubleword(address,rs2, (0xffff * pow(0x100,remainder)) );
        else
        {
            Main_Memory->write_doubleword(address, rs2 & ((8-remainder)*0xff), 0xffffffffffffffff - remainder * 0xff);
            Main_Memory->write_doubleword(address + 1 ,rs2 & ( 0xffff - (8-remainder) * 0xff) >> (8*(8-remainder) ) ,0x00000000000000ff);
        }
    }
    if (type=="SW")
    {
        //TOFIX
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24)) & 0xffffffff;
        uint64_t imm4 = return_signed_bit_value(7,11);
        uint64_t imm11 = return_signed_bit_value(25,31) << 5 ;
        uint64_t imm = imm4 | imm11;
         if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        }
        uint64_t address = imm + rs1;
        int remainder = address % 8 ;
        rs2 = rs2 << remainder*8;
        if ( remainder < 5 )
            Main_Memory->write_doubleword(address,rs2, (0xffffffff * pow(0x100,remainder)) );
        else
        {
            Main_Memory->write_doubleword(address, rs2 & ((8-remainder)*0xff), 0xffffffffffffffff - remainder * 0xff);
            Main_Memory->write_doubleword(address + 1 ,rs2 & ( 0xffffffff - (8-remainder) * 0xff) >> (8*(8-remainder) ) ,0x00000000000000ff);
        }
    }
    if (type=="ADDI")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_signed_bit_value(20,31);
        if(imm >>11 !=0)
            {
                imm |=  0xfffffffffffff000;
            }
        uint64_t result = rs1 + imm;
        CPU->set_reg(rd,result);  
        //cout<<"addi: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
    }
    if (type=="SLTI")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
        int64_t imm = return_signed_bit_value(20,31);

        if( (int64_t)rs1 < imm )
            CPU->set_reg(rd,1);
        else
            CPU->set_reg(rd,0);
    }
    if (type=="SLTIU")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_signed_bit_value(20,31);

        if( rs1 < imm )
            CPU->set_reg(rd,1);
        else
            CPU->set_reg(rd,0);
    }
    if (type=="XORI")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t imm = return_signed_bit_value(20,31);
       
       CPU->set_reg( rd , rs1 ^ imm);
    }
    if (type=="ORI")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t imm = return_signed_bit_value(20,31);
       
       CPU->set_reg( rd , rs1 | imm);
    }
    if (type=="ANDI")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t imm = return_signed_bit_value(20,31);
       
       CPU->set_reg( rd , rs1 & imm);
    }
    if (type=="SLLI")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t imm = return_signed_bit_value(20,31);
       if(imm >>11 !=0)
        {
            imm = (imm | 0xfffffffffffff000);
        }
        imm &=0x3f;
       CPU->set_reg( rd , rs1 << imm );
       //cout<<"slli: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", shamt = "<<dec<<imm<<endl;
    }
    if (type=="SRLI")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t imm = return_signed_bit_value(20,31);
       if(imm >>11 !=0)
        {
            imm = (imm | 0xfffffffffffff000);
        }
        imm &=0x3f;
       CPU->set_reg( rd , rs1 >> imm );
    }
    if (type=="SRAI")
    {
      uint64_t rd = return_unsigned_bit_value(7,11);
      uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
      uint64_t imm = (return_signed_bit_value(20,31) - 0x400);

        if( imm >>11 !=0 )
            {
                imm |=  0xfffffffffffff000;
            }
        imm &=0x3f;
       CPU->set_reg( rd , (int64_t)rs1 >> imm  );
    }
    if (type=="ADD")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       CPU->set_reg(rd ,rs1 + rs2);
    }
    if (type=="SUB")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       CPU->set_reg(rd ,rs1 - rs2);
    }
    if (type=="SLL")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t temp = rs2 & 0x3f;
        
       temp = rs1 << temp;
       CPU->set_reg(rd ,temp);
    }
    if (type=="SLT")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       int64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       int64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       
       if ( rs1 < rs2 )
       {
           CPU->set_reg(rd,1);
       }
        else
           CPU->set_reg(rd,0);
    }
    if (type=="SLTU")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       
       if ( rs1 < rs2 )
       {
           CPU->set_reg(rd,1);
       }
        else
           CPU->set_reg(rd,0);
    }
    if (type=="XOR")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       CPU->set_reg(rd , rs1 ^ rs2 );
    }
    if (type=="SRL")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t temp = rs2 & 0x3f;
        
       temp = rs1 >> temp;
       CPU->set_reg(rd ,temp);
    }
    if (type=="SRA")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       int64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t temp = rs2 & 0x3f;
        
       temp = rs1 >> temp;
       CPU->set_reg(rd ,temp);
    }
    if (type=="OR")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       CPU->set_reg(rd , rs1 | rs2 );
    }
    if (type=="AND")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       CPU->set_reg(rd , rs1 & rs2 );
    }
    if (type=="FENCE")
    {
       //DO NOTHING
    }
    if (type=="FENCE.I")
    {
       //DO NOTHING
    }
    if (type=="ECALL")
    {
       cout<<"ECALL: unimplemented instruction" <<endl;
    }
    if (type=="EBREAK")
    {
       cout<<"EBREAK: unimplemented instruction"<<endl;
    }
    if (type=="CSRRW")
    {
       cout<<"CSRRW: unimplemented instruction" <<endl;
    }
    if (type=="CSRRS")
    {
       cout<<"CSRRS: unimplemented instruction" <<endl;
    }
    if (type=="CSRRC")
    {
       cout<<"CSRRC: unimplemented instruction" <<endl;
    }
    if (type=="CSRRWI")
    {
       cout<<"CSRRWI: unimplemented instruction"<<endl;
    }
    if (type=="CSRRSI")
    {
       cout<<"CSRRSI: unimplemented instruction"<<endl;
    }
    if (type=="CSRRCI")
    {
       cout<<"CSRRCI: unimplemented instruction"<<endl;
    }
    if (type=="LWU")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_signed_bit_value(20,31);
        if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        } 
        uint64_t address = imm + rs1;
        uint64_t data = Main_Memory->read_unaligned(address) & 0xFFFFFFFF;
        data &= 0xFFFFFFFF;
        CPU->set_reg(rd,data);
    }
    if (type=="LD")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_signed_bit_value(20,31);
        if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        } 
        uint64_t address = imm + rs1;
        uint64_t data = Main_Memory->read_doubleword(address); 
        CPU->set_reg(rd,data);
        //cout<<"ld: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
    }
    if (type=="SD")
    {
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
        uint64_t imm4 = return_signed_bit_value(7,11);
        uint64_t imm11 = return_signed_bit_value(25,31) << 5 ;
        uint64_t imm = imm4 | imm11;
         if(instruction_array[31] != 0)
        {
            imm |= 0xfffffffffffff000;
        }
        uint64_t address = imm + rs1;
        int remainder = address % 8 ;
           
        if (remainder == 0)
            Main_Memory->set_address(address,rs2);
        else
        {
            Main_Memory->write_doubleword(address, rs2 & ((8-remainder)*0xff), 0xffffffffffffffff - remainder * 0xff);
            Main_Memory->write_doubleword(address + 1 ,rs2 & ( 0xffffffffffffffff - (8-remainder) * 0xff) >> (8*(8-remainder) ) , 0xffffffffffffffff-(8-remainder)*0xff00000000000000);
        }
    }
    /*Archived in RV32I
    if (type=="SLLI")
    {
       
    }
    if (type=="SRLI")
    {
       
    }
    if (type=="SRAI")
    {
       
    }
    */
    if (type=="ADDIW")
    { 
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_signed_bit_value(20,31);
        int32_t result = rs1 + imm;

        if (instruction_array[31]!=0)
            CPU->set_reg( rd , result | 0xFFFFFFFF00000000);
        CPU->set_reg( rd , result );
     
    //cout<<"addiw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
    }
    if (type=="SLLIW")
    {
       //TODO: if imm[5] != 0, generate exception message.
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t imm = return_unsigned_bit_value(20,24);
       uint64_t temp = (rs1 & 0xffffffff ) << imm;

       if((temp & 0xffffffff)>>31!=0)
            temp |= 0xffffffff00000000;
        else 
            temp &= 0xffffffff;
       CPU->set_reg(rd , temp);
    }
    if (type=="SRLIW")
    {   
        //TODO: if imm[5] != 0, generate exception message.
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t imm = return_unsigned_bit_value(20,24);
       uint64_t temp = (rs1 & 0xffffffff ) >> imm;

       if((temp & 0xffffffff)>>31!=0)
            temp |= 0xffffffff00000000;
        else 
            temp &= 0xffffffff;
       CPU->set_reg(rd , temp);
    }
    if (type=="SRAIW")
    {
        //TODO: if imm[5] != 0, generate exception message.
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t imm = return_unsigned_bit_value(20,24);
        uint64_t temp = ((int64_t)rs1 & 0xffffffff ) >> imm;

            if( ((int64_t)rs1 & 0xffffffff ) >> 31 != 0 )
            {
                uint64_t temp_mask = 0xffffffffffffffff << (32 - imm);
                temp |= temp_mask;
            }
            else
                temp = temp & 0xffffffff;

        CPU->set_reg(rd, temp);
    }
    if (type=="ADDW")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
       
       CPU->set_reg(rd ,(int32_t)rs1 + (int32_t)rs2 );
    }
    if (type=="SUBW")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
       
       CPU->set_reg(rd ,(int32_t)rs1 - (int32_t)rs2 );
    }
    if (type=="SLLW")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t temp = rs2 & 0x1f;
       temp = (rs1 & 0xffffffff) << temp;

       if((temp & 0xffffffff)>>31 != 0)
            temp |= 0xffffffff00000000;
        else 
            temp &= 0xffffffff;

       CPU->set_reg(rd, temp);
    }
    if (type=="SRLW")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t temp = rs2 & 0x1f;

       temp = (rs1 & 0xffffffff) >> temp;
        if((temp & 0xffffffff)>> 31 != 0)
          temp |=  0xffffffff00000000;
        else 
          temp &= 0xffffffff;

       CPU->set_reg(rd, temp);
    }
    if (type=="SRAW")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t temp = rs2 & 0x1f;

       uint64_t shamt = temp;
       uint64_t temp2 = (int64_t)rs1 & 0xffffffff;
       uint64_t sign = temp2 >>31;
       temp = temp2 >>shamt;

       if(sign!=0)
        {
          uint64_t value_mask = 0xffffffffffffffff << (32 - shamt);
          temp |= value_mask;
        }
        else
        {
          temp &= 0xffffffff;
        }

       CPU->set_reg(rd, temp);
    }
}