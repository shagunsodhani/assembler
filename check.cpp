/* This file contains the code to check which string is larger
 * */
 
#include <iostream>
#include <string>

using namespace std;

bool chk(string a,string b)
{
    int p,q,diff,d;
    p = a.length();
    q = b.length();
    if(p>q)
    diff =  p-q;
    else
    diff = q-p;
    if((a[0]!='0')&&(p>q))
		return 1;
    else if ((a[0]=='0')&&(p>q))
    {
        for(int i=0;i<q;i++)
        {
			if(a[diff+i]>b[i])
			return 1;
			else if (a[diff+i]<b[i])
			return 0;
       }
    }
    else if(p==q)
    {
		for(int i=0;i<q;i++)
        {
			if(a[i]>b[i])
				return 1;
			else if (a[i]<b[i])
				return 0;
       }
   }
   else if(p<q)
   {
        for(int i = 0;i<diff;i++)
        {
            if(b[i]=='0')
            d = 1;
            else
            d = 0;break;
        }
        if(d==0)
			return 0;
        else
        {
            for(int i =0;i<p;i++)
            {
                if(a[i]>b[diff+i])
					return 1;
				else if (a[i]<b[diff+i])
					return 0;
            }
        }
    }
}
