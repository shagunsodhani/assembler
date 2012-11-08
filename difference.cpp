/* This file contains the code to subtract the two hexadecimal numbers
 * */
 
string difference(string string1,string string2)
{
    string c,d,a;
    c=string1;
    d=string2;
    if(chk(c,d))
        a= subtract(c,d);
    else
    {
        a= subtract(d,c);

        string b=a;
        int k;
        for(int i=0; i<a.length(); ++i)
        {
            if (a[i]=='A')
                k=10;
            else if(a[i]=='B')
                k=11;
            else if(a[i]=='C')
                k=12;
            else if(a[i]=='D')
                k=13;
            else if(a[i]=='E')
                k=14;
            else if(a[i]=='F')
                k=15;
            else
                k=a[i]-'0';

            b[i]=deci_equ[15-k];
        }
        a=add(b,"1");
    }
        return a;
}
#endif
