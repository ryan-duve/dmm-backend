#include <stdio.h>
#include <string>
#include <iostream>

class DMMConverter{
  public:
    void convert(char *input){
      printf("input=%s",input);
      //************************************************************************
      const char *in = input;
      std::string val,special,unit;


      // check for overload else find sign and fill in digits 
      // 
      if (((in[3] & 0x07) == 0x07) && 
          ((in[4] & 0x0f) == 0x0d) && 
          ((in[5] & 0x07) == 0x06) &&
          ((in[6] & 0x0f) == 0x08))
      {
        val = "  0L";
      }
      else
      {
        if(in[1] & 0x08)
        {
          val = " -";   // negative;
        }
        else
        {
          val = "  ";
        }

        // create string;
        //
        for (int i=0; i<4; ++i)
        {
          val += DMMConverter::vc820Digit( ((in[1+2*i] << 4 ) & 0xf0) | (in[2+2*i] & 0x0f) );
        }
      }

      // find comma position
      //
      if (in[3] & 0x08)
      {
        val = insertComma( val, 1 );
      }
      else if (in[5] & 0x08)
      {
        val = insertComma( val, 2 );
      }
      else if(in[7] & 0x08)
      {
        val = insertComma( val, 3 );
      }

      double d_val = stod(val);
      std::cout << "d_val="<<d_val<<std::endl<<std::endl;

      // try to find some special modes
      //
      if (in[9] & 0x01) 
      {
        special = "DI";
      }
      if (in[0] & 0x08)
      {
        special = "AC";
      }
      else
      {
        special = "DC";
      }

      // try to find mode
      //
      if (in[11] & 0x08)
      {
        unit    = "F";
        special = "CA";
      }
      else if (in[11] & 0x04)
      {
        unit    = "Ohm";
        special = "OH";
      }
      else if (in[12] & 0x08)
      {
        unit = "A";
      }
      else if (in[12] & 0x02)
      {
        unit    = "Hz";
        special = "HZ";
      }
      else if (in[12] & 0x04)
      {
        unit = "V";
      }
      else if (in[10] & 0x04)
      {
        unit    = "%";
        special = "PC";
      }
      /* Can't find the reason for this any more
         else if (in[13] & 0x04)
         {
         unit    = "C";
         special = "TE";
         } 
         else if (in[13] & 0x02)
         {
         unit    = "F";
         special = "TE";
         }
         */
      else if (in[13] & 0x01)
      {
        unit    = "C";
        special = "TE";
      } 
      else 
      {
        std::cerr << "Unknown unit!" << std::endl;
      }

      // try to find prefix
      //
     // if (in[9] & 0x04)
     // {
     //   d_val /= 1e9;
     //   unit.insert(0,1,'n');
     // }
     // else if (in[9] & 0x08)
     // {
     //   d_val /= 1e6;
     //   unit.insert(0,1,'u');
     // }
     // else if (in[10] & 0x08)
     // {
     //   d_val /= 1e3;
     //   unit.insert(0,1,'m');
     // }
     // else if (in[9] & 0x02)
     // {
     //   d_val *= 1e3;
     //   unit.insert(0,1,'k');
     // }
     // else if (in[10] & 0x02)
     // {
     //   d_val *= 1e6;
     //   unit.insert(0,1,'M');
     // }

      //emit value( d_val, val, unit, special, true, re->id() );
      std::cout << d_val << val << unit << special <<std::endl;
      std::cout << "d_val" << d_val << std::endl;
      std::cout << "val" << val << std::endl;
      std::cout << "unit" << unit<< std::endl;
      std::cout << "special" << special << std::endl;

      //************************************************************************
    }

    const char *vc820Digit( int byte )
    {
      int           digit[10] = { 0x7d, 0x05, 0x5b, 0x1f, 0x27, 0x3e, 0x7e, 0x15, 0x7f, 0x3f };
      const char *c_digit[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

      byte &= 0x7f;

      for (int n=0; n<10; n++)
      {
        if (byte == digit[n]) return c_digit[n];
      }

      return 0;
    }

    std::string insertComma( const std::string & val, int pos )
    {
      std::string val2 = val;
      val2.insert(2+pos,1,'.');
      //return val.left(2+pos) + "." + val.right(4-pos);
      return val2;
    }


};

extern "C" {
  DMMConverter* DMMConverter_new(){ return new DMMConverter();}
  void DMMConverter_convert(DMMConverter* dmm, char* input){dmm->convert(input);}
}
