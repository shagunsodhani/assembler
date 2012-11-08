/* This contains the code for the two passes of the assembler
 * */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

#include "OPTAB.H"
#include "adder.cpp"
#include "variables.cpp"
#include "subtract.cpp"
#include "check.cpp"
#include "difference.cpp"

string n[20][7];
// First Column Adddress Second Column Label
// Third Column Operation
// Fourth Column Operation Field
// Fifth Format Specification
// Six Final Opcode

// TO return address corresponding to LABEL
string SYMField(string a)
{
    int c=0;
    while(SYMTAB[c][0]!=a)
    {
        c++;
    }
    return SYMTAB[c][1];
}

// To return OPCODE
string OPCode(string a)
{
    for(int i=0;i<45;i++)
    {
        if(OPTAB[i][0]==a)
        return OPTAB[i][1];
    }
}

//String Conversion to Hexadecimal
string hexcnvt2(int p)
{
    long int j;
    char q1;
    string hex;
    while(p!=0)
    {
        j = p%16;
        switch (j)
        {
            case 10:q1 = 'A';break;
            case 11:q1 = 'B';break;
            case 12:q1 = 'C';break;
            case 13:q1 = 'D';break;
            case 14:q1 = 'E';break;
            case 15:q1 = 'F';break;
            default :q1 = j+'0';break;
        }
        hex += q1;
        p = p/16;
    }
    int m = hex.length();
    char z;
    for(int i =0;i<m/2;i++)
    {
        z = hex[m-i-1];
        hex[m-i-1] = hex[i];
        hex[i] =  z;
    }
    return hex;
}

// To Check whether whether it is immediate addressing OR indirect addressing
/*#0
 *@1
 *default 2
 * */
int CheckDir_Indir(string a)
{
    if(a[0]=='#')
		 return 0;
    else if(a[0]=='@')
         return 1;
    else
         return 2;
}

// To Check Whether it is a Operation or RESB , RESW , WORD ,BYTE
bool CheckOPTAB(string a)
{
    for(int i=0;i<45;i++)
       if(OPTAB[i][0]==a)
       return 1;
    return 0;
}
// To check for a comma
bool CheckCOMMA(string a)
{
    for(int i=0;i<a.length();i++)
    {
        if(a[i]==',')
        return 1;
    }
    return 0;
}
// To take up the label before comma
string takelabel(string a)
{
    int c=0;
    for(int i =0;i<a.length();i++)
    {

        if(a[i]==',')
        break;
        c++;
    }
    string b = a.substr(0,c);
    return b;

}

// To check format 3 OR 4
string CheckFormat(string a)
{
    if(a[0]=='+')
    {
    //    a=a.substr(1,a.length());
        return "4";
    }
    else if(CheckOPTAB(a))// Checks whether it is operation or not and then return wether it is Format 3 OR Format 2
         {
             for(int i=0;i<45;i++)
             if(OPTAB[i][0]==a)
             return OPTAB[i][2];
         }
    else if(a=="WORD")
         return "5";
    else if(a=="RESW")
         return "6";
    else if(a=="BYTE")
         return "7";
    else if(a=="RESB")
         return "8";
    else return "0";
}

// To Check whether label is present in SYMTAB OR NOT
bool CheckSYMTAB(string a)
{
    int c=0;
    while(SYMTAB[c][0]!="END")
    {
        if(SYMTAB[c][0]==a)
        return 1;
        c++;
    }
    return 0;
}

// Inserting label in SYMTAB
void Insert_SYMTAB(string a)
{
    int c=0;
    while(SYMTAB[c][0]!="END")
    {
        c++;
    }
    SYMTAB[c][0]=a;
    SYMTAB[c+1][0]="END";
    return;
}

// Inserting address for label in SYMTAB
void Insert_SYMTAB_Addr(string a,string addr)
{
    int c=0;
    while(SYMTAB[c][0]!="END")
    {
        if(SYMTAB[c][0]==a)
        {
            SYMTAB[c][1]=addr;
            return;
        }
        c++;
    }
    SYMTAB[c][0]=a;
    SYMTAB[c][1]=addr;
    SYMTAB[c+1][0]="END";
}

vector<string> explode( const string &delimiter, const string &explodeme);

int main()
{
    SYMTAB[0][0]="START";
    SYMTAB[1][0]="END";
    ifstream in;
    string str;
    in.open("work.txt");
    getline(in,str);
    int f=0,h=1,count=0;//count is number of rows, f is used to traverse the array and h is the column number
    while(str!="END")
    {
          vector<string> v = explode(" ", str);
          while(v[f]=="")// used to eliminate the whitespaces at the begining of each line
          {
              f=f+1;
              h=2;
          }
          for(int j=f;j<(v.size());j++)
          {
              n[count][h]=v[j];
              if(h==2)
                  n[count][4]=CheckFormat(n[count][h]);
              h=h+1;
          }
        v.clear();
        getline(in, str);
        count++;h=1;f=0;
    }
    in.close();
    n[count][1]="END";
    string ProgAddr=n[0][3];
    n[0][0]=ProgAddr;
    string loc=ProgAddr;// Location Pointer
    for(int i=1;i<count;i++)
    {
        n[i][0]=loc;
        int label=atoi(n[i][4].c_str());
        switch(label)
        {
            case 2://Format 2 : allowed operations  ADDR SUBR TIXR
            {
                string temp=n[i][3];
                if(temp=="T")
					n[i][6]=OPCode(n[i][2])+"50";
                else if(temp=="S")
					n[i][6]=OPCode(n[i][2])+"40";
                else
                {
                    for(int j=0;j<6;j++)
                        if(n[i][3][0]==REGISTER[j][1][0])
                        {
                            n[i][6]+=OPCode(n[i][2])+REGISTER[j][0];
                            break;
                        }
                    for(int j=0;j<6;j++)
                    if(n[i][3][2]==REGISTER[j][1][0])
                    {
                        n[i][6]+=REGISTER[j][0];
                        break;
                    }
                }
                loc=add(loc,"2");
                break;
            }
            case 3://Format 3 : allowed
            {
                if(CheckDir_Indir(n[i][3])==2&&!CheckCOMMA(n[i][3]))  //
                   {
                       if(!CheckSYMTAB(n[i][3]))
                       {
                           Insert_SYMTAB(n[i][3]);
                       }
                       n[i][5]="0";
                       if(n[i][1]!="")
                        {
                           Insert_SYMTAB(n[i][1]);
                           Insert_SYMTAB_Addr(n[i][1],loc);
                         }
                   }
                   else if(CheckDir_Indir(n[i][3])==2&& CheckCOMMA(n[i][3]))
                   {
                       string p1 = takelabel(n[i][3]);
                       if(!CheckSYMTAB(p1))
                       {
                          Insert_SYMTAB(p1);
                       }
                       if(n[i][1]!="")
                       {
                           Insert_SYMTAB(n[i][1]);
                           Insert_SYMTAB_Addr(n[i][1],loc);
                       }
                       n[i][5]="8";
                   }
                   else if(CheckDir_Indir(n[i][3])==0)
                        {
                            n[i][5]="1"; //Immediate addressing
                            n[i][6]=n[i][3].substr(1,n[i][3].length());// This is to modify 12 to 012
                            string temp;
                            for(int j=0;j<(3-n[i][6].length());j++)
                            temp+="0";
                            n[i][6]=temp+n[i][6];
                        }
                        else if(CheckDir_Indir(n[i][3])==1)
                             {
                                 n[i][5]="2"; //Indirect addressing
                                n[i][3]=n[i][3].substr(1,n[i][3].length());// This is to modify 12 to 012
                            string temp;
                            for(int j=0;j<(3-temp.length());j++)
                            temp+="0";
                            n[i][6]=temp+n[i][3];
                            }
                loc=add(loc,"3");
                break;
            }
            case 4://Format 4
            {
                loc=add(loc,"4");
                break;
            }
            case 5://WORD
            {
                n[i][5]="4";
                Insert_SYMTAB_Addr(n[i][1],loc);
                loc=add(loc,"3");
                break;
            }
            case 6://RESW
            {
                n[i][5]="4";
                Insert_SYMTAB_Addr(n[i][1],loc);
                int var=atoi(n[i][3].c_str());
                int k = 3*var;
                string temp = hexcnvt2(k);
                loc=add(loc,temp);
                break;
            }
            case 7://BYTE
            {
                n[i][5]="4";
                Insert_SYMTAB_Addr(n[i][1],loc);
                loc=add(loc,"1");
                break;
            }
            case 8://RESB
            {
                n[i][5]="4";
                Insert_SYMTAB_Addr(n[i][1],loc);
                int var=atoi(n[i][3].c_str());
                string temp = hexcnvt2(var);
                loc=add(loc,temp);
                break;
            }

        }
     }
     n[count][0]=loc;// These statements are for the last line
     n[count][2]=ProgAddr;
     string ProgLength=difference(n[count][0],ProgAddr); // Program Length is Stored

     for(int y=0;y<count+1;y++)
		{
                for(int l=0;l<5;l++)
                {
                        cout<<setfill(' ')<<setw(8)<<n[y][l]<<" ";
                }
                cout<<endl;
        }
    int c=0;
    cout<<endl;
    cout<<"SYMTAB is"<<endl;
     while(SYMTAB[c][0]!="END")
    {
        cout<<setfill(' ')<<setw(8)<<SYMTAB[c][0]<<"  "<<setw(8)<<SYMTAB[c][1]<<endl;
        c++;
    }
    SYMTAB[c][0]="END";
    SYMTAB[c][1]=loc;
            cout<<setfill(' ')<<setw(8)<<SYMTAB[c][0]<<"  "<<setw(8)<<SYMTAB[c][1]<<endl;

    // Code for PASS 2 begins here

    cout<<"Code for PASS 2 begins here"<<endl;
    for(int i=1;i<count;i++)
    {
         if(n[i][5]=="1") //Immediate Addressing
         {
             //string temp1;
             //temp1=difference(SYMField(n[i][6]),n[i+1][0]);
             //temp1=temp1.substr(1,temp1.length());
             n[i][6]=(add(OPCode(n[i][2]),"1")+"0"+n[i][6]);
         }
         else if(n[i][5]=="2")  // Indirect Addressing
         {
             //string temp1;
             //temp1=difference(SYMField(n[i][6]),n[i+1][0]);
             //temp1=temp1.substr(1,temp1.length());
             n[i][6]=(add(OPCode(n[i][2]),"2")+"0"+n[i][6]);
         }
         else if(n[i][4]=="4") //format 4
         {
            n[i][6]=add(OPCode(n[i][2].substr(1,n[i][3].length())),"3")+"10"+SYMField(n[i][3]);
         }
          else if(n[i][5]=="8")// this is for buffer,x
         {
            string p1=takelabel(n[i][3]);
             string temp1;
             string temp=add(OPCode(n[i][2]),"3");
             temp=temp+"A";
             temp1=difference(SYMField(p1),n[i+1][0]);
             temp1=temp1.substr(1,temp1.length());
             temp=temp+temp1;
             n[i][6]=temp;
         }

         else if(n[i][4]=="3")//format 3
         {
                          //temp1=difference(SYMField(n[i][6]),n[i+1][0]);
             //temp1=temp1.substr(1,temp1.length());
             string temp1;
             string temp=add(OPCode(n[i][2]),"3");
             temp=temp+"2";//program counter realtive
             temp1=difference(SYMField(n[i][3]),n[i+1][0]);
             temp1=temp1.substr(1,temp1.length());
             temp=temp+temp1;
             n[i][6]=temp;
         }
         else if(n[i][4]!="2")//format 2
         {
             n[i][6]="";
         }
    }
    for(int y=0;y<count;y++)
        {
                for(int l=0;l<7;l++)
                {
                        if(l==5||l==4)
                        continue;
                        cout<<setfill(' ')<<setw(10)<<n[y][l]<<" ";
                }
                cout<<endl;
        }
    // Generating an Object Program
    ofstream out;
    out.open("OUTPUT.txt");
    out<<"H|"<<setfill(' ')<<setw(6)<<n[0][1]<<"|"<<setfill('0')<<setw(6)<<ProgAddr<<"|"<<setw(6)<<ProgLength<<endl;
    out<<"T|";
    out<<setfill('0')<<setw(6)<<ProgAddr<<"|1E|";
    for(int i=1;i<count;i++)
    {
        if(n[i][4]=="3"||n[i][4]=="4")
        out<<n[i][6]<<"|";
    }
    out<<endl;
    for(int i=1;i<count;i++)
    {
        if(n[i][4]=="4")
        out<<"M|"<<setfill('0')<<setw(6)<<n[i][0]<<"|05"<<endl;
    }
    out<<"E|"<<setfill('0')<<setw(6)<<ProgAddr<<endl;

    cout<<"Program Length is "<<ProgLength<<endl;

}

vector<string> explode( const string &delimiter, const string &str)//This is the function to break the string ( similar to explode function of php)
{
    vector<string> arr;
    int strleng = str.length();
    int delleng = delimiter.length();
    if (delleng==0)
        return arr;//no change

    int i=0;
    int k=0;
    while( i<strleng )
    {
        int j=0;
        while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
        if (j==delleng)//found delimiter
        {
            arr.push_back(str.substr(k, i-k));
            i+=delleng;
            k=i;
        }
        else
        i++;
    }
    arr.push_back(  str.substr(k, i-k) );
    return arr;
}
