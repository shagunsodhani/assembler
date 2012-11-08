/* This file contains the code to 
 * */
   
string convert1(string loc,string byte)
{
    string s = loc;
    string b = byte;
    string u,v;
    string y="NULL";
    string x,j;
    int n,m,k,p,q,c=0,r=0,e,f;
    n= s.length();
    m= b.length();
    f=n-m;//int f is difference in the length of the two strings
    v=s.substr(0,f);//string v is the extra string of larger string
    for(int i=m-1;i>=0;i--)
    {
        //p is the equivalent 
        c=0;
        //cout<<"f+i="<<s[f+i]<<endl;
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
         p=s[f+i]-'0';//to convert the character to int
         //cout<<"p="<<p<<endl;

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
        //cout<<"q="<<q<<endl;
        if(p<q)
        { 
			c=1;
            k=p+16-q;
        //cout<<s[f+i-1];
			s[f+i-1]=((s[f+i-1]-'0')-1)+'0';
        //cout<<s[f+i-1];
        }
        else
			k=p-q;
    //cout<<"k="<<k<<endl;
    //if(k>15)
     //r=k%16;
		r=k;
     //c=k/16;
     //cout<<"r="<<r<<endl;
     //cout<<"c="<<c<<endl;
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
     //cout<<"x="<<x<<endl;
                     //j=c+'0';
                     //cout<<"j="<<j<<endl;
             y=x;
             //cout<<"y"<<y<<endl;
             if (f+i==3)
				u=y;
             else
				u=y+u;
             //cout<<"u="<<u<<endl;
     }
           if(c==1)
				v=convert1(v,"1");
    return v+u;
}
