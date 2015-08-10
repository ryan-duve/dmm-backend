#include <stdio.h>
#include <string>
#include <iostream>

class DMMConverter{
  public:
    double convert(char *input){
      //printf("input=%s",input);
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
        val = "-1";
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
      else if (in[13] & 0x01)
      {
        unit    = "C";
        special = "TE";
      } 
      else 
      {
        std::cerr << "Unknown unit!" << std::endl;
      }

      //emit value( d_val, val, unit, special, true, re->id() );
      //std::cout << std::endl << "returning d_val = " << d_val << std::endl;

      //************************************************************************
      return d_val;
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
	std::cout << "val2="<<val2<<", pos="<<pos<<std::endl;
      if(pos+2 <= val2.length())//don't try inserting period beyond val
        val2.insert(2+pos,1,'.');
      //return val.left(2+pos) + "." + val.right(4-pos);
      return val2;
    }


};

extern "C" {
	DMMConverter* DMMConverter_new(){ return new DMMConverter();}
	double DMMConverter_convert(DMMConverter* dmm, char* input){return dmm->convert(input);}
}
