#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class BigDecimalInt {
private:
    string num ;
    bool sign ;
public :
    BigDecimalInt (string s)
    {
        bool valid=1;
        bool prefix = (s[0]=='-'||s[0]=='+') ;
        for (int i= prefix ; i<s.size(); i++ )
        {
            if ( (s[i]-'0') > 9 || (s[i]-'0') < 0 )
            {
               valid=0 ;
               break ;
            }
        }
        if (valid)
        {
            num=s.substr(prefix,s.size()-prefix);
            sign=(s[0] != '-');
        }
        else
        {
            cout<<"this is not a valid number\n";
        }
    }
    BigDecimalInt (int n )
    {
        num=to_string(abs(n));
        sign=(n >= 0);
    }
    friend bool operator > (BigDecimalInt num1 , BigDecimalInt num2)
    {
         if( ! num1.sign && num2.sign )
         {
             return ( false );
         }
         else if ( num1.sign && ! num2.sign )
         {
             return ( true ) ;
         }

         else if (! num1.sign && ! num2.sign )
         {
             return ( num1.num < num2.num ) ;
         }
         else
         {
             return  ( num1.num > num2.num );
         }
    }
    friend bool operator < (BigDecimalInt num1 , BigDecimalInt num2)
    {
        if( ! num1.sign && num2.sign )
         {
             return ( true );
         }
         else if ( num1.sign && ! num2.sign )
         {
             return ( false ) ;
         }

         else if (! num1.sign && ! num2.sign )
         {
             return  ( num1.num > num2.num );
         }
         else
         {
             return  ( num1.num < num2.num );
         }

    }
    friend bool operator == (BigDecimalInt num1 , BigDecimalInt num2)
    {
        return (    (   ( num1.sign == num2.sign )  &&  (  num1.num == num2.num )   ) ? ( true ) : ( false ) ) ;
    }
    friend ostream& operator << (ostream& out, BigDecimalInt n)
    {
        if (!n.sign)
        {
            cout<<'-';
        }
        cout<<n.num;
    }
    friend int Sign ( BigDecimalInt n )
    {
        if (n.sign)
        {
            return ( 1 ) ;
        }
        else
        {
            return ( -1 ) ;
        }
    }
    friend int Size ( BigDecimalInt n )
    {
        return ( n.num.size() ) ;
    }
     BigDecimalInt operator=   ( BigDecimalInt n2 )
    {
        num=n2.num ;
        sign=n2.sign ;
    }
    string add ( string first , string second )
    {
        reverse(first.begin() , first.end());
        reverse(second.begin(), second.end());
        first+="0";
        string ans = "" ;
        for ( int i=0 ; i<first.size(); i++)
        {
            int curr = first[i]-'0';
            if (i < second.size () )
            {
                curr += second[i]-'0' ;
            }
            if (curr >= 10 ) first [i+1] ++ ;
            curr%=10;
            ans+=  (char)('0'+curr) ;
        }
        reverse(ans.begin(), ans.end());
        int i=0 ;
        for ( i ; i<ans.size()-1; i++)
        {
            if (ans[i]!='0') return ( ans.substr(i,ans.size()-i) ) ;
        }
        return ( ans.substr(i,ans.size()-i) ) ;
    }
    string sub ( string first , string second )
    {
        reverse(first.begin() , first.end());
        reverse(second.begin(), second.end());
        string ans = "" ;
        for ( int i=0 ; i<first.size(); i++)
        {
            int curr = first[i]-'0';
            if (i < second.size () )
            {
                if (curr >= ( second[i] - '0') )
                {
                    curr-=( second[i] - '0');
                }
                else
                {
                    first [i+1]--;
                    curr+=10;
                    curr-=( second[i] - '0');
                }
            }
            ans+=(char)('0'+curr);
        }
        reverse(ans.begin(), ans.end());
        int i=0 ;
        for ( i ; i<ans.size()-1; i++)
        {
            if (ans[i]!='0') return ( ans.substr(i,ans.size()-i) ) ;
        }
        return ( ans.substr(i,ans.size()-i) ) ;
    }
    BigDecimalInt operator+= (BigDecimalInt n1 )
    {
        if ( ( !n1.sign &&  ! sign) || (  n1.sign &&  sign) )
        {
            sign= (  n1.sign &&   sign ) ;
            if (n1.num> num)
            {
            num= add( n1.num , num );
            }
            else
            {
            num= add( num , n1.num );
            }
        }
        else
        {
            if (n1.num > num)
            {
                sign = ( n1.sign );
                num = sub( n1.num , num );
            }
            else
            {
                sign = ( sign );
                num = sub( num, n1.num );
            }
        }
    }
    BigDecimalInt operator-= (BigDecimalInt n1 )
    {
        if ( ( n1.sign &&  ! sign) || ( ! n1.sign &&  sign) )
        {
            sign = (   ! n1.sign &&   sign ) ;
            if (n1.num> num)
            {
            num= add( n1.num , num );
            }
            else
            {
            num= add( num , n1.num );
            }
        }
        else
        {
            if (n1.num > num)
            {
                sign = ( ! n1.sign );
                num = sub( n1.num, num );
            }
            else
            {
                sign = ( sign );
                num = sub( num, n1.num );
            }
        }
    }

};
int main()
{
    //   testing ............
    BigDecimalInt n1 (1) ;
    BigDecimalInt n2 ("5") ;
    n2=n1;
    cout<<n2<<endl;
    n2+=n1;
    cout<<n2<<endl;
    cout<<Size(n1)<<endl;
    cout<<Sign(n2)<<endl;
    return 0;
}
