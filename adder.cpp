/* This file contains the code to add 2 input strings
 * */
 
string add(string loc,string byte)
{
    string s = loc;
    string b = byte;
    string u,v;
    string y="NULL";
    string x,j;
    int n,m,k,p,q,c=0,r=0,e,f;
    n= s.length();
    m= b.length();
    f=n-m;
    v=s.substr(0,f);
    for(int i=m-1;i>=0;i--)
    {
        if(s[f+i]=='A')
        {
            p=10;
        }
        else if(s[f+i]=='B')
        {
            p=11;
        }
        else if(s[f+i]=='C')
        {
            p=12;
        }
        else if(s[f+i]=='D')
        {
            p=13;
        }
        else if(s[f+i]=='E')
        {
            p=14;
        }
        else if(s[f+i]=='F')
        {
            p=15;
        }
        else
			p=s[f+i]-'0';
        
        if(b[i]=='A')
        {
            q=10;
        }
        else if(b[i]=='B')
        {
            q=11;
        }
        else if(b[i]=='C')
        {
            q=12;
        }
        else if(b[i]=='D')
        {
            q=13;
        }
        else if(b[i]=='E')
        {
            q=14;
        }
        else if(b[i]=='F')
        {
            q=15;
        }
        else
			q=b[i]-'0';

		 k=p+q+c;
		 if(k>15)
		 r=k%16;
		 else r=k;
		 c=k/16;
		 if (r>9)
		 {
             switch(r)
             {
                     case 10:
						x='A';
						break;
                     case 11:
						x='B';
						break;
                     case 12:
						x='C';
						break;
                     case 13:
						x='D';
						break;
                     case 14:
						x='E';
						break;
                     case 15:
						x='F';
						break;
               }
		}
		 else
			x=r+'0';
		j=c+'0';
		y=x;
		if (f+i==3)
			u=y;
        else
            u=y+u;
     }
	 if(c==1)
		v=add(v,"1");
    return v+u;
}
