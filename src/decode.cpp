#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <cmath>

 
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
    uint32_t data=Main_Memory->read_doubleword(memory_address) & 0xffffffff;
    long long int i=0,r;
    for(int k=0;k<32;k++)
    {
       instruction_array[k]=0;
    }
    while(data != 0)
    {
      r = data % 2;
      instruction_array[i++] = r;
      data /= 2;
    }
    if (debug)
    {
        cout<<endl<<"PC:"<<hex<<CPU->return_pc()<<endl;
        cout<<"Memory read word: address:"<<hex<<memory_address<<" ir ="<<setfill('0')<<setw(8)<<hex<< (Main_Memory->read_doubleword(memory_address) & 0xffffffff) <<endl; 
    }   
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
    if (op=="1100111"&&csr=="010000001100") return "MRET";

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

    //User software interrupt (cause 0)
    // mip.usip = 1
    if( (CPU->return_csr(0x344)&1) == 1)
    {
        //machine mode, not vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 0)
        {
             //if mie = 1
            if (((CPU->return_csr(0x300)&0x8)>>3) == 1)
            {  
                //mcause
                CPU->set_csr(0x342,0x8000000000000000);
                machine_mode_interrupt();
            }    
        }
        //machine mode, vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 1)
        {
            machine_mode_interrupt_vectored(0);
        }
        //User Mode
        if (CPU->return_prv() == 0)
        {   
            if(((CPU->return_csr(0x300)&0x8)>>3) == 1 || (CPU->return_csr(0x304)&1) == 1)
                //mepc
                CPU->set_csr(0x341,CPU->return_pc());

            if(((CPU->return_csr(0x300)&0x8)>>3) == 1)
                user_mode_interrupt(0);

            //usie   
            if((CPU->return_csr(0x304)&1) == 1)
            {
                CPU->set_csr(0x342,0x8000000000000000);
                user_mode_interrupt(1);
            }     
        }       
    }

    //Machine software interrupt (cause 3) in machine mode
    //mip.msip = 1
    if( ((CPU->return_csr(0x344)&0x8)>>3) == 1)
    {
        //machine mode, not vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 0)
        {
             //if mie = 1
            if (((CPU->return_csr(0x300)&0x8)>>3) == 1)
            {  
                //mcause
                CPU->set_csr(0x342,0x8000000000000003);
                machine_mode_interrupt_vectored(3);
            }    
        }
        //machine mode, vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 1)
        {
            machine_mode_interrupt_vectored(3);
        }
        //User Mode
        if (CPU->return_prv() == 0)
        {
            if(((CPU->return_csr(0x304)&0x8)>>3) == 1)
                CPU->set_csr(0x341,CPU->return_pc());

            if(((CPU->return_csr(0x300)&0x8)>>3) == 1)
                user_mode_interrupt(0);

            //msie
            if(((CPU->return_csr(0x304)&0x8)>>3) == 1)
            {
                CPU->set_csr(0x342,0x8000000000000003);
                user_mode_interrupt(1);
            }     
        }       
    }

    //User timer interrupt (cause 4) in machine mode
    //mip.utip = 1
    if( ((CPU->return_csr(0x344)&0x10)>>4) == 1)
    {
        //machine mode, not vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 0)
        {
             //if mie = 1
            if (((CPU->return_csr(0x300)&0x8)>>3) == 1)
            {  
                //mcause
                CPU->set_csr(0x342,0x8000000000000004);
                machine_mode_interrupt();
            }    
        }
        //machine mode, vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 1)
        {
            machine_mode_interrupt_vectored(4);
        }
        //User Mode
        if (CPU->return_prv() == 0)
        {    
            if(((CPU->return_csr(0x304)&0x10)>>4) == 1)
            //mepc
            CPU->set_csr(0x341,CPU->return_pc());

            if(((CPU->return_csr(0x300)&0x8)>>3) == 1)
                user_mode_interrupt(0);   
            if(((CPU->return_csr(0x304)&0x10)>>4) == 1)
            {
                CPU->set_csr(0x342,0x8000000000000004);
                user_mode_interrupt(1);
            }     
        }       
    }

    //Machine timer interrupt (cause 7) in machine mode
    if( ((CPU->return_csr(0x344)&0x80)>>7) == 1)
    {
        //machine mode, not vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 0)
        {
             //if mie = 1
            if (((CPU->return_csr(0x300)&0x8)>>3) == 1)
            {  
                //mcause
                CPU->set_csr(0x342,0x8000000000000007);
                machine_mode_interrupt();
            }    
        }
        //machine mode, vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 1)
        {
            machine_mode_interrupt_vectored(7);
        }
        //User Mode
        if (CPU->return_prv() == 0)
        {    
            if(((CPU->return_csr(0x304)&0x80)>>7) == 1)
            //mepc
            CPU->set_csr(0x341,CPU->return_pc());

            if(((CPU->return_csr(0x300)&0x8)>>3) == 1)
                user_mode_interrupt(0);   
            if(((CPU->return_csr(0x304)&0x80)>>7) == 1)
            {
                CPU->set_csr(0x342,0x8000000000000007);
                user_mode_interrupt(1);
            }     
        }       
    }

    //User external interrupt (cause 8) in machine mode
    if( ((CPU->return_csr(0x344)&0x100)>>8) == 1)
    {
        //machine mode, not vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 0)
        {
             //if mie = 1
            if (((CPU->return_csr(0x300)&0x8)>>3) == 1)
            {  
                //mcause
                CPU->set_csr(0x342,0x8000000000000008);
                machine_mode_interrupt();
            }    
        }
        //machine mode, vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 1)
        {
            machine_mode_interrupt_vectored(8);
        }
        //User Mode
        if (CPU->return_prv() == 0)
        {    
            if(((CPU->return_csr(0x304)&0x100)>>8) == 1)
            //mepc
            CPU->set_csr(0x341,CPU->return_pc());

            if(((CPU->return_csr(0x300)&0x8)>>3) == 1)
                user_mode_interrupt(0);   
            if(((CPU->return_csr(0x304)&0x100)>>8) == 1)
            {
                CPU->set_csr(0x342,0x8000000000000008);
                user_mode_interrupt(1);
            }     
        }       
    }

    //Machine external interrupt (cause 11) in machine mode
    if( ((CPU->return_csr(0x344)&0x800)>>11) == 1)
    {
        //machine mode, not vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 0)
        {
             //if mie = 1
            if (((CPU->return_csr(0x300)&0x8)>>3) == 1)
            {  
                //mcause
                CPU->set_csr(0x342,0x800000000000000B);
                machine_mode_interrupt();
            }    
        }
        //machine mode, vectored
        if (CPU->return_prv() == 3 && (CPU->return_csr(0x305)&1) == 1)
        {
            machine_mode_interrupt_vectored(11);
        }
        //User Mode
        if (CPU->return_prv() == 0)
        {    
            if(((CPU->return_csr(0x304)&0x800)>>11) == 1)
            //mepc
            CPU->set_csr(0x341,CPU->return_pc());

            if(((CPU->return_csr(0x300)&0x8)>>3) == 1)
                user_mode_interrupt(0);   
            if(((CPU->return_csr(0x304)&0x800)>>11) == 1)
            {
                CPU->set_csr(0x342,0x800000000000000B);
                user_mode_interrupt(1);
            }     
        }       
    }



    if (type=="ERROR")
    {
        //cout<<"Illegal instruction: "<< setw(8) << setfill('0') << right << hex <<Main_Memory->read_doubleword(memory_address)<<endl;
        //exit(1);
        CPU->set_csr(0x342,2);
        //mret(memory_address,0);
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
       if(debug)
            cout<<"lui: rd = "<<dec<<rd<<", immed_U = "<<setfill('0')<<setw(16)<<hex<<imm<<endl; 
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
        if (debug)
            cout<<"auipc: rd = "<<dec<<rd<<", immed_U = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;  
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
       if(debug)
         cout<<"jal: rd ="<<dec<<rd<<", immed_U = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;   
    }
    if (type=="JALR")
    {
        
        uint64_t rd = return_unsigned_bit_value(7,11);
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        int64_t imm = return_signed_bit_value(20,31);
        if(instruction_array[31]!=0)
        {
            imm |= 0xfffffffffffff000;
        }
        CPU->set_reg(rd ,CPU->return_pc() + 4 );
        CPU->set_pc( (( rs1 + imm ) & 0xfffffffffffffffe) - 4 );
        if(debug)
            cout<<"jalr: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rd = "<<dec<<rd<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
        
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
        if(debug)
            cout<<"beq: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<CPU->return_reg(return_unsigned_bit_value(20,24))<<", immed_B = "<<setfill('0')<<setw(16)<<hex<<immed_B<<endl;
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
        if( rs1 != rs2)
        {  
            CPU->set_pc(CPU->return_pc() + immed_B - 4 );
        }
        if (debug)
        {
            cout<<"bne: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_B = "<<setfill('0')<<setw(16)<<hex<<immed_B<<endl;
            cout<<"-----RS1: "<<rs1<<"-----RS2: "<<rs2<<"-------"<<endl;
            cout<<"NEW PC ="<<CPU->return_pc()<<endl;
        }     
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
        if(debug)
            cout<<"blt: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_B = "<<setfill('0')<<setw(16)<<hex<<immed_B<<endl;
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
         if(debug)
            cout<<"bge: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_B = "<<setfill('0')<<setw(16)<<hex<<immed_B<<endl;
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
        if(debug)
            cout<<"bltu: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_B = "<<setfill('0')<<setw(16)<<hex<<immed_B<<endl;
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
        if(debug)
            cout<<"bgeu: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_B = "<<setfill('0')<<setw(16)<<hex<<immed_B<<endl;
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
        if(debug)
            cout<<"lb: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
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
            data |= 0xffffffffffff0000;
        
        if (address%2 != 0)
            misaligned_load(address);
        else
            CPU->set_reg(rd,data);

        if(debug)
            cout<<"lh: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
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

        if (address%4 != 0)
            misaligned_load(address);
        else
            CPU->set_reg(rd,data);

        if(debug)
        {
            cout<<"lw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
            cout<<"Memory read word: address = "<<setw(16)<<hex<<address<<" data = "<<setfill('0')<<setw(16)<<hex<< data <<endl; 
        }   
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
        CPU->set_reg(rd,data);
        if(debug)
        {
            cout<<"lbu: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
            cout<<"Memory read word: address = "<<setw(16)<<hex<<address<<" data = "<<setfill('0')<<setw(16)<<hex<< data <<endl; 
        }
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
        uint64_t data = Main_Memory->read_unaligned(address) & 0xffff;
        data &= 0xFFFF;

        if (address%2 != 0)
            misaligned_load(address);
        else
            CPU->set_reg(rd,data);

        if(debug)
        {
            cout<<"lhu: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
            cout<<"Memory read word: address = "<<setw(16)<<hex<<address<<" data = "<<setfill('0')<<setw(16)<<hex<< data <<endl; 
        }
    }
    if (type=="SB")
    {
        
        uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
        uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24))& 0xff;
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
        if (debug)
        {
            cout<<"sb: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_S = "<<setfill('0')<<setw(16)<<hex<<imm<<" rem : "<<dec<<remainder<<endl;
            cout<<"Memory write word: address = "<<setw(16)<<hex<<address<<" data = "<<setfill('0')<<setw(16)<<hex<< rs2 <<" mask = "<<setw(16)<<hex<<((uint64_t)(0xff * pow(0x100,remainder)))<<endl; 
        }   

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

        if (address%2 != 0)
             misaligned_store(address);
        else
        {
            if ( remainder < 7 )
                Main_Memory->write_doubleword(address,rs2, (0xffff * pow(0x100,remainder)) );
            else
            {
                Main_Memory->write_doubleword(address, rs2 & ((8-remainder)*0xff), 0xffffffffffffffff - remainder * 0xff);
                Main_Memory->write_doubleword(address + 1 ,rs2 & ( 0xffff - (8-remainder) * 0xff) >> (8*(8-remainder) ) ,0x00000000000000ff);
            }
        }
        
         if (debug)
        {
            cout<<"sh: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_S = "<<setfill('0')<<setw(16)<<hex<<imm<<" rem : "<<dec<<remainder<<endl;
            cout<<"Memory write word: address = "<<setw(16)<<hex<<address<<" data = "<<setfill('0')<<setw(16)<<hex<< rs2 <<" mask = "<<setw(16)<<hex<<((uint64_t)(0xff * pow(0x100,remainder)))<<endl; 
        }
    }
    if (type=="SW")
    {
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

        if (address%4 != 0)
             misaligned_store(address);
        else
        {
             if ( remainder < 5 )
                Main_Memory->write_doubleword(address,rs2, (0xffffffff * pow(0x100,remainder)) );
             else
            {
                Main_Memory->write_doubleword(address, rs2 & ((8-remainder)*0xff), 0xffffffffffffffff - remainder * 0xff);
                Main_Memory->write_doubleword(address + 1 ,rs2 & ( 0xffffffff - (8-remainder) * 0xff) >> (8*(8-remainder) ) ,0x00000000000000ff);
            }
        }
       
         if (debug)
        {
            cout<<"sw: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_S = "<<setfill('0')<<setw(16)<<hex<<imm<<" rem : "<<dec<<remainder<<endl;
            cout<<"Memory write word: address = "<<setw(16)<<hex<<address<<" data = "<<setfill('0')<<setw(16)<<hex<< rs2 <<" mask = "<<setw(16)<<hex<<((uint64_t)(0xff * pow(0x100,remainder)))<<endl; 
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
        if (debug)  
            cout<<"addi: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
    }
    if (type=="SLTI")
    {
        uint64_t rd = return_unsigned_bit_value(7,11);
        int64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
        int64_t imm = return_signed_bit_value(20,31);

        if( (int64_t)rs1 < imm )
            CPU->set_reg(rd,1);
        else
            CPU->set_reg(rd,0);
        if(debug)
            cout<<"slti: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
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
         if(debug)
            cout<<"sltiu: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
    }
    if (type=="XORI")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t imm = return_signed_bit_value(20,31);
       
       CPU->set_reg( rd , rs1 ^ imm);
       if(debug)
            cout<<"xori: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
    }
    if (type=="ORI")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t imm = return_signed_bit_value(20,31);
       
       CPU->set_reg( rd , rs1 | imm);
       if(debug)
            cout<<"ori: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
    }
    if (type=="ANDI")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t imm = return_signed_bit_value(20,31);
       
       CPU->set_reg( rd , rs1 & imm);
       if(debug)
            cout<<"andi: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
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
       if (debug)
            cout<<"slli: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", shamt = "<<dec<<imm<<endl;
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
       if (debug)
            cout<<"srli: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", shamt = "<<dec<<imm<<endl;
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
       if (debug)
            cout<<"srai: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", shamt = "<<dec<<imm<<endl;
    }
    if (type=="ADD")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       CPU->set_reg(rd ,rs1 + rs2);
       if (debug)
            cout<<"add: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
    }
    if (type=="SUB")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       CPU->set_reg(rd ,rs1 - rs2);
        if (debug)
            cout<<"sub: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
    }
    if (type=="SLL")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t temp = rs2 & 0x3f;
        
       temp = rs1 << temp;
       CPU->set_reg(rd ,temp);
       if (debug)
            cout<<"sll: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
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
       if (debug)
            cout<<"slt: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
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
       if (debug)
            cout<<"sltu: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
    }
    if (type=="XOR")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       CPU->set_reg(rd , rs1 ^ rs2 );
       if (debug)
            cout<<"xor: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
    }
    if (type=="SRL")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t temp = rs2 & 0x3f;
        
       temp = rs1 >> temp;
       CPU->set_reg(rd ,temp);
       if (debug)
            cout<<"srl: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
    }
    if (type=="SRA")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       int64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t temp = rs2 & 0x3f;
        
       temp = rs1 >> temp;
       CPU->set_reg(rd ,temp);
       if (debug)
            cout<<"sra: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
    }
    if (type=="OR")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       CPU->set_reg(rd , rs1 | rs2 );
       if (debug)
            cout<<"or: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
    }
    if (type=="AND")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1= CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2= CPU->return_reg(return_unsigned_bit_value(20,24));
       CPU->set_reg(rd , rs1 & rs2 );
       if (debug)
            cout<<"and: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
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
        if (CPU->return_prv() == 0)
        {
            //ecall from user mode
            CPU->set_csr(0x342,8);

            //mepc set to current pc
            CPU->set_csr(0x341,CPU->return_pc());

            //pc set to mtvec
            CPU->set_pc(CPU->return_csr(0x305) - 4);

            CPU->set_instruction_count(CPU->get_instruction_count()-1); 
        }
        if(CPU->return_prv() == 3)
        {

            //ecall from machine mode
            CPU->set_csr(0x342,0xb);

            //mepc set to current pc
            CPU->set_csr(0x341,CPU->return_pc());

            //mstatus machine mode
            CPU->set_csr(0x300, CPU->return_csr(0x300) | 0x1800);

            //pc set to mtvec
            CPU->set_pc(CPU->return_csr(0x305) - 4);

            CPU->set_instruction_count(CPU->get_instruction_count()-1); 
        }
        
    }
    if (type=="EBREAK")
    {   
        //mpie = last mie
        if( (CPU->return_csr(0x300)&0x8)>>3 == 1)
        {
            CPU->set_csr(0x300,CPU->return_csr(0x300)|0x80);
        }
        else
        {
            CPU->set_csr(0x300,CPU->return_csr(0x300)&0xFFFFFFFFFFFFFF7F);
        }
        //
        if(CPU->return_prv()==3)
        {
            //mie
            //CPU->set_csr(0x300,CPU->return_csr(0x300) | 0x8);
            //mpp 
            CPU->set_csr(0x300, CPU->return_csr(0x300) | 0x1800);
            CPU->set_csr(0x341, CPU->return_pc());
        }
        if (CPU->return_prv()==0)
        {
            //mie
            //CPU->set_csr(0x300,CPU->return_csr(0x300) & 0xFFFFFFFFFFFFFFF7);
            //mpp
            CPU->set_csr(0x300, CPU->return_csr(0x300) & 0xFFFFFFFFFFFFE7FF);
        }
            
       //Direct Mode
       //When MODE=Direct, all traps into machine mode cause the pc to be set to the address in the BASE field
        if( (CPU->return_csr(0x305) & 0x1) == 0)
        {
            CPU->set_pc((CPU->return_csr(0x305) & 0xFFFFFFFFFFFFFFFC) - 4);
            CPU->set_prv(3);
        }
                  
       //Vectored Mode
       //When MODE=Vectored, all synchronous exceptions into machine mode cause the pc to be set to the address in the BASE
       //field, whereas interrupts cause the pc to be set to the address in the BASE field plus four times the interrupt cause number.
        else
        {
            CPU->set_pc((CPU->return_csr(0x305) & 0xFFFFFFFFFFFFFFFC) + 4* (CPU->return_csr(0x342)&8000000000000000) - 4);
            CPU->set_prv(3);
        }
        
        //Machine Mode
       
        //mcause
        CPU->set_csr(0x342,3);
        CPU->set_instruction_count(CPU->get_instruction_count()-1);
        CPU->set_csr(0x300,CPU->return_csr(0x300)&0xFFFFFFFFFFFFFFF7);
    }
     if (type=="MRET")
    {
        mret(memory_address,0);     
    }
    if (type=="CSRRW")
    {
        uint64_t csr = return_unsigned_bit_value(20,31);
        if (CPU->return_prv() == 0 || !CPU->csr_is_defined(csr) || (CPU->illegal_csr_write(csr)&&return_unsigned_bit_value(15,19) != 0) )
        {
            mret(memory_address,2);
        }
        else
        {
            //If rd=x0, then the instruction shall not read the CSR
            if(return_unsigned_bit_value(7,11) != 0)
            {
                CPU->set_reg(return_unsigned_bit_value(7,11),CPU->return_csr(csr));  
            }
            if(csr!=0x344)
                CPU->set_csr(csr,CPU->return_reg(return_unsigned_bit_value(15,19)));
            else
                CPU->set_csr(csr,CPU->return_reg(return_unsigned_bit_value(15,19)&0x111));
        }   
    }
    if (type=="CSRRS")
    {
        uint64_t csr = return_unsigned_bit_value(20,31);
        if (CPU->return_prv() == 0 || !CPU->csr_is_defined(csr) || (CPU->illegal_csr_write(csr)&&return_unsigned_bit_value(15,19) != 0) )
        {
            mret(memory_address,2);
        }
        else
        {
            CPU->set_reg(return_unsigned_bit_value(7,11),CPU->return_csr(csr));
            if(return_unsigned_bit_value(15,19) != 0 && csr!=0x344)
            {
                uint64_t mask = CPU->return_reg(return_unsigned_bit_value(15,19));
                CPU->set_csr(csr,CPU->return_csr(csr)|mask);
            }
            else if(return_unsigned_bit_value(15,19) != 0 && csr==0x344)
            {
                uint64_t mask = CPU->return_reg(return_unsigned_bit_value(15,19));
                CPU->set_csr(csr,(CPU->return_csr(csr)|mask)&0x111);
            }
        }   
    }
    if (type=="CSRRC")
    {
        uint64_t csr = return_unsigned_bit_value(20,31);
        if (CPU->return_prv() == 0 || !CPU->csr_is_defined(csr) || (CPU->illegal_csr_write(csr)&&return_unsigned_bit_value(15,19) != 0) )
        {
            mret(memory_address,2);
        }
        else
        {
            CPU->set_reg(return_unsigned_bit_value(7,11),CPU->return_csr(csr));
            if(return_unsigned_bit_value(15,19) != 0 && csr!=0x344)
            {
                uint64_t mask = CPU->return_reg(return_unsigned_bit_value(15,19));
                CPU->set_csr(csr,CPU->return_csr(csr)&(0xffffffffffffffff-mask));
            }
            else if(return_unsigned_bit_value(15,19) != 0 && csr==0x344)
            {
                uint64_t mask = CPU->return_reg(return_unsigned_bit_value(15,19));
                CPU->set_csr(csr,(CPU->return_csr(csr)&(0xffffffffffffffff-mask))&0x111);
            }    
        }
          
    }
    if (type=="CSRRWI")
    {
        uint64_t csr = return_unsigned_bit_value(20,31);
        if (CPU->return_prv() == 0 || !CPU->csr_is_defined(csr) || (CPU->illegal_csr_write(csr)&&return_unsigned_bit_value(15,19) != 0) )
        {
            mret(memory_address,2);
        }
        else
        {
            if(return_unsigned_bit_value(7,11) != 0)
            {
                CPU->set_reg(return_unsigned_bit_value(7,11),CPU->return_csr(csr));  
            }
            if(csr!=0x344)
                CPU->set_csr(csr,return_unsigned_bit_value(15,19));
            else
                CPU->set_csr(csr,return_unsigned_bit_value(15,19)&0x111);
        }
       
    }
    if (type=="CSRRSI")
    {
        uint64_t csr = return_unsigned_bit_value(20,31);
        if (CPU->return_prv() == 0 || !CPU->csr_is_defined(csr) || (CPU->illegal_csr_write(csr)&&return_unsigned_bit_value(15,19) != 0) )
        {
            mret(memory_address,2);
        }
        else
        {
            if(return_unsigned_bit_value(7,11) != 0)
            {
                CPU->set_reg(return_unsigned_bit_value(7,11),CPU->return_csr(csr));  
            }
            uint64_t mask = return_unsigned_bit_value(15,19);
            if(mask != 0 && csr!=0x344)
            {
                CPU->set_csr(csr,CPU->return_csr(csr)|mask);
            }
            else if(mask != 0 && csr==0x344)
            {
                CPU->set_csr(csr,(CPU->return_csr(csr)|mask)&0x111);
            }
        }     
    }
    if (type=="CSRRCI")
    {
        uint64_t csr = return_unsigned_bit_value(20,31);
        if (CPU->return_prv() == 0 || !CPU->csr_is_defined(csr) || (CPU->illegal_csr_write(csr)&&return_unsigned_bit_value(15,19) != 0) )
        {
            mret(memory_address,2);
        }
        else
        {
            if(return_unsigned_bit_value(7,11) != 0)
            {
                CPU->set_reg(return_unsigned_bit_value(7,11),CPU->return_csr(csr));  
            }
            uint64_t mask = return_unsigned_bit_value(15,19);
            if(mask != 0 && csr!=0x344)
            {
                CPU->set_csr(csr,CPU->return_csr(csr)&(0xffffffffffffffff-mask));
            }
            else if(mask != 0 && csr==0x344)
            {
                CPU->set_csr(csr,(CPU->return_csr(csr)&(0xffffffffffffffff-mask))&0x111);
            }
        } 
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
        if (address%4 != 0)
           misaligned_load(address);
        else
            CPU->set_reg(rd,data);
        if(debug)
            cout<<"lwu: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
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
            if (address%8!=0)
                misaligned_load(address);
            else
            { 
                CPU->set_reg(rd,data);
            }
            
            if (debug)
            cout<<"ld: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
        
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
        if (remainder != 0)
             misaligned_store(address);
        else
        {
            if (remainder == 0)
                Main_Memory->set_address(address,rs2);
            else
            {
                Main_Memory->write_doubleword(address, rs2 & ((8-remainder)*0xff), 0xffffffffffffffff - remainder * 0xff);
                Main_Memory->write_doubleword(address + 1 ,(rs2 & ( 0xffffffffffffffff - (8-remainder) * 0xff)) >> (8*(8-remainder) ) , 0xffffffffffffffff-(8-remainder)*0xff00000000000000);
            }
        }   
        
        if(debug)
        {
            cout<<"sd: rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<", immed_S = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
            cout<<"Memory write word: address:"<<hex<<address<<" data ="<<setfill('0')<<setw(16)<<hex<<rs2<<endl; 
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
        
        int32_t result = (rs1 + imm) & 0xffffffff;

        if (instruction_array[31]!=0)
            CPU->set_reg( rd , result | 0xffffffff00000000);
        CPU->set_reg( rd , result );
     if (debug)
        cout<<"addiw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", immed_I = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
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
       if(debug)
            cout<<"slliw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", shamt = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
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
       if(debug)
            cout<<"srliw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", shamt = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
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
        if(debug)
            cout<<"sraiw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", shamt = "<<setfill('0')<<setw(16)<<hex<<imm<<endl;
    }
    if (type=="ADDW")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t result = rs1 + rs2;
       if((result & 0xffffffff)>>31!=0)
        result |= 0xffffffff00000000;
      else
        result &= 0xffffffff;
       CPU->set_reg(rd ,result);
       if(debug)
          cout<<"addw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
    }
    if (type=="SUBW")
    {
       uint64_t rd = return_unsigned_bit_value(7,11);
       uint64_t rs1 = CPU->return_reg(return_unsigned_bit_value(15,19));
       uint64_t rs2 = CPU->return_reg(return_unsigned_bit_value(20,24));
       uint64_t result = rs1 - rs2;
       if((result & 0xffffffff)>>31!=0)
        result |= 0xffffffff00000000;
      else
        result &= 0xffffffff;
       CPU->set_reg(rd ,result );
       if(debug)
          cout<<"subw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
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
       if(debug)
          cout<<"sllw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
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
       if(debug)
          cout<<"srlw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
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
       if(debug)
          cout<<"sraw: rd = "<<dec<<rd<<", rs1 = "<<dec<<return_unsigned_bit_value(15,19)<<", rs2 = "<<dec<<return_unsigned_bit_value(20,24)<<endl;
    }
}

void instructions::mret(uint64_t memory_address, unsigned int Cause_code)
{
         if (Cause_code == 0 && CPU->return_prv() == 3)
        {
            if (debug)
                cout<<"Mode 0 3"<<endl;
            //MIEis set to MPIE;
            if(((CPU->return_csr(0x300)&0x80)>>7) == 1)
            {
                CPU->set_csr(0x300,CPU->return_csr(0x300)|0x8);
            }
            else
            {
                CPU->set_csr(0x300,CPU->return_csr(0x300)&0xFFFFFFFFFFFFFFF7);
            }

            //the privilege mode is changed to y in MPP
            if(((CPU->return_csr(0x300)&0x1800)>>11) == 3)
            {
                CPU->set_prv(3);
            }  
            else
            {
                CPU->set_prv(0);
            }
            //MPIE is set to 1   
            CPU->set_csr(0x300,CPU->return_csr(0x300)|0x80);

            //MPP is set to U-Mode
            CPU->set_csr(0x300,CPU->return_csr(0x300)&0xFFFFFFFFFFFFE7FF);

            //mepc register is written with the virtual address of the instruction that took the trap
            
            CPU->set_pc(CPU->return_csr(0x341) - 4);
        }
        //Illegal instruction trap on mret in user mode
        else if(CPU->return_prv() == 0)
        {
            if (debug)
                cout<<"Mode x 0"<<endl;
            //An mret instruction executed in user mode. mcause 2
            CPU->set_csr(0x342,2);

            //mepc set to current pc
            CPU->set_csr(0x341,CPU->return_pc());

            //mtval holds current instruction
            CPU->set_csr(0x343,Main_Memory->read_doubleword(memory_address) & 0xffffffff);

            //pc set to mtvec
            CPU->set_pc(CPU->return_csr(0x305) - 4);

            CPU->set_instruction_count(CPU->get_instruction_count()-1);
        }
        else if (Cause_code == 2 && CPU->return_prv() == 3)
        {
            if (debug)
                cout<<"Mode 2 3"<<endl;
            //MPP
            CPU->set_csr(0x300,CPU->return_csr(0x300)|0x1800);

            //MPIE
            CPU->set_csr(0x300,CPU->return_csr(0x300)&0xFFFFFFFFFFFFFF7F);

            //An mret instruction executed in user mode. mcause 2
            CPU->set_csr(0x342,2);

            //mepc set to current pc
            CPU->set_csr(0x341,CPU->return_pc());

            //mtval holds current instruction
            CPU->set_csr(0x343,Main_Memory->read_doubleword(memory_address) & 0xffffffff);

            //pc set to mtvec
            CPU->set_pc(CPU->return_csr(0x305) - 4);

            CPU->set_instruction_count(CPU->get_instruction_count()-1); 
        }
        if (debug)
            cout<<Cause_code<<" "<<CPU->return_prv()<<endl;
}

void instructions::misaligned_instr()
{
    //mcause
    CPU->set_csr(0x342,0);

    //mepc
    CPU->set_csr(0x341,CPU->return_pc());

    //mstatus MPP
    CPU->set_csr(0x300,CPU->return_csr(0x300)|0x1800);

    //mtval
    CPU->set_csr(0x343,CPU->return_pc());
    
    //pc
    CPU->set_pc(CPU->return_csr(0x305) - 4);

    CPU->set_instruction_count(CPU->get_instruction_count()-1);
}

void instructions::misaligned_load(uint64_t error_address)
{
    //mcause
    CPU->set_csr(0x342,4);

    //mepc
    CPU->set_csr(0x341,CPU->return_pc());

    //mstatus MPP
    CPU->set_csr(0x300,CPU->return_csr(0x300)|0x1800);

    //mtval
    CPU->set_csr(0x343,error_address);

    //pc
    CPU->set_pc(CPU->return_csr(0x305) - 4);

    CPU->set_instruction_count(CPU->get_instruction_count()-1);
}

void instructions::misaligned_store(uint64_t error_address)
{
    //mcause
    CPU->set_csr(0x342,6);

    //mepc
    CPU->set_csr(0x341,CPU->return_pc());

    //mstatus MPP
    CPU->set_csr(0x300,CPU->return_csr(0x300)|0x1800);

    //mtval
    CPU->set_csr(0x343,error_address);

    //pc
    CPU->set_pc(CPU->return_csr(0x305) - 4);

    CPU->set_instruction_count(CPU->get_instruction_count()-1);
}

//interrupt in machine mode
void instructions::machine_mode_interrupt()
{
    //mie
    CPU->set_csr(0x300,CPU->return_csr(0x300)&0xFFFFFFFFFFFFFFF7);

    //mpie
    CPU->set_csr(0x300,CPU->return_csr(0x300)|0x80);

    //mpp
    CPU->set_csr(0x300,CPU->return_csr(0x300)|0x1800);

    //mepc
    CPU->set_csr(0x341,CPU->return_pc());

    //pc
    CPU->set_pc(CPU->return_csr(0x305));
}

void instructions::machine_mode_interrupt_vectored(int causecode)
{
    //mepc
     CPU->set_csr(0x341,CPU->return_pc());

    //mie
        CPU->set_csr(0x300,CPU->return_csr(0x300)&0xFFFFFFFFFFFFFFF7);

    //pc
    CPU->set_pc((CPU->return_csr(0x305)&0xFFFFFFFFFFFFFFFE)+ 4*causecode);

    //mpie
    CPU->set_csr(0x300,CPU->return_csr(0x300)|0x80);

    //mpp
    CPU->set_csr(0x300,CPU->return_csr(0x300)|0x1800);

    CPU->set_csr(0x342,0x8000000000000000 + causecode);
}

void instructions::user_mode_interrupt(int mode)
{
    if ( mode == 0)
    {
        //mie
        CPU->set_csr(0x300,CPU->return_csr(0x300)&0xFFFFFFFFFFFFFFF7);

        //mpie
        CPU->set_csr(0x300,CPU->return_csr(0x300)|0x80);

        //pc
        CPU->set_pc(CPU->return_csr(0x305));

        //CPU->set_prv(0);
    }
    if (mode == 1)
    {
        CPU->set_prv(3);
        CPU->set_pc(CPU->return_csr(0x305));
    }
    
}

