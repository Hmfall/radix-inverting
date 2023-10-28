#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool proceed()
{
   char c;
   cout << endl
        << "1.Continue | 2.Exit ";
   do
   {
      c = _getch();
   } while ((c != '1') && (c != '2'));
   cout << endl;
   if (c == '1')
      return 1;
   return 0;
}

union real_num
{
   float pattern;
   char bin[sizeof(pattern)];
};

void binary_output_float(float value, bool sep)
{
   real_num none;
   none.pattern = value;
   int size = sizeof(value);

   for (int i = size - 1; i >= 0;)
   {
      for (int j = 0; j < 8;)
      {
         ((none.bin[i] & (128 >> j))) ? cout << "1" : cout << "0";
         __asm {
                inc j
         }
         ;
      }
      __asm {
            dec i;
      }
      ;
      if (sep)
         cout << " ";
   }
   cout << endl;
}

void conv(unsigned long value, bool m)
{
   float result;
   real_num none;
   int count = 0;
   unsigned long bitwise = 1;
   bitwise <<= 31;
   none.pattern = value;
   const int size = 32;

   char arr[size];
   char m_order[8];
   char m_mts[24];
   int order = 0;
   float mts = 0;

   while (true)
   {
      if (value & bitwise)
      {
         arr[count] = '1';
         count++;
      }
      else
      {
         arr[count] = '0';
         count++;
      }
      if (bitwise == 1)
         break;
      bitwise >>= 1;
   }

   char x;
   int i = 1;
   int j = 0;
   int pw = 1;
   do
   {
      for (i; i < 9;)
      {
         x = arr[i];
         i++;
         break;
      }
      for (j; j < 8;)
      {
         m_order[j] = x;
         j++;
         break;
      }
   } while (i != 9);

   for (int i = 7; i >= 0; i--)
   {
      if (m_order[i] == '1')
         order += pw;
      pw *= 2;
   }
   order -= 127;
   i = 9;
   j = 1;
   m_mts[0] = '1';
   do
   {
      for (i; i <= 32;)
      {
         x = arr[i];
         i++;
         break;
      }
      for (j; j < 24;)
      {
         m_mts[j] = x;
         j++;
         break;
      }
   } while (i != 32);

   for (int i = 0; i < 24; i++)
   {
      if (m_mts[i] == '1')
         mts += pow(2, (-i));
   }

   result = mts * (pow(2, order));
   if (m)
      result *= (-1);
   cout << result << endl;
}

unsigned long inv_float(float value)
{
   unsigned long res = 0;
   int count = 0;
   int pow = 1;

   real_num none;
   none.pattern = value;
   int size = sizeof(value);
   char *arr = new char[size * 8];

   for (int i = size - 1; i >= 0; i--)
   {
      for (int j = 0; j < 8; j++)
      {
         if (none.bin[i] & (128 >> j))
         {
            arr[count] = '1';
            __asm {

                    inc count

            }
            ;
         }
         else
         {
            arr[count] = '0';
            __asm {

                    inc count

            }
            ;
         }
      }
   }

   for (int i = size * 8 - 1; i >= 0; i--)
   {
      if (arr[i] == '1')
         res += pow;
      pow *= 2;
   }

   delete[] arr;
   return res;
}

long long ctrl_int(int count, bool minus, int radix, bool showDec)
{
   unsigned long long limit = 9223372036854775808, n = 0;
   long long result;
   bool flag = false;
   int num_of_digits = 0;
   char c;
   do
   {
      c = _getch();
      if (c >= '0' && c <= '9' && c - '0' < radix)
      {
         cout << c;
         n = n * radix + c - '0';
         __asm {

                inc num_of_digits

         }
      }
      else if (c >= 'A' && c <= 'Z' && c - 'A' + 10 < radix)
      {
         cout << c;
         n = n * radix + c - 'A' + 10;
         __asm {

                inc num_of_digits

         }
      }
      (c == '-' && minus) ? cout << c, flag = true : false;
   } while ((c != 13) && (count > num_of_digits));

   result = n;
   (flag) ? result *= (-1) : false;

   if (showDec)
      cout << endl
           << "inDec: " << result << endl;
   return result;
}

long long input_int(const char *promt, long long lower_limit,
                    long long upper_limit, int symbol, bool minus, int radix, bool showDec)
{
   long long value;
   do
   {
      cout << promt;
      value = ctrl_int(symbol, minus, radix, showDec);
      cout << endl;
      if (!((value >= lower_limit) && (value <= upper_limit)))
         cout << " Error! " << endl;
   } while (!((value >= lower_limit) && (value <= upper_limit)));
   return value;
}

void cnv_r(int radix)
{
   int num_of_digits, count;
   unsigned long long n;
   bool point, minus;
   double number;
   char c;
   do
   {
      num_of_digits = 0, count = 0;
      point = false, minus = false;
      n = 0;
      cout << "Double inRadix: ";
      do
      {
         c = _getch();
         if (c >= '0' && c <= '9' && c - '0' < radix)
         {
            cout << c;
            n = n * radix + c - '0';
            __asm {

                    inc num_of_digits

            }
         }
         else if (c >= 'A' && c <= 'Z' && c - 'A' + 10 < radix)
         {
            cout << c;
            n = n * radix + c - 'A' + 10;
            __asm {

                    inc num_of_digits

            }
         }
         (c == 45) ? cout << c, minus = true : false;
         (c == 46) ? cout << c, point = true : false;
         if (point && c != 13 && c != 46)
            count += 1;
      } while (c != 13 && 15 > num_of_digits);

      cout << fixed;
      cout.precision(count);

      number = n / pow(radix, count);
      (minus) ? number *= (-1) : false;
      cout << endl
           << "inDec " << number << endl;

      cout << "Binary code: " << endl;
      binary_output_float(number, 0);
   } while (proceed() && !point);
   cout << endl;
}

void cnv_i(int separator, int radix)
{
   unsigned long long bitwise = 1;
   long long value = 0;
   bool flag = false;
   int count = 0;
   char v_char;
   do
   {
      if (separator == 1)
      {
         bitwise <<= 7;
         value = input_int("Bool: ", 0, 1, 1, 0, radix, 0);
         cout << endl;
      }
      else if (separator == 2)
      {
         bitwise <<= 7;
         cout << "Char: ";
         v_char = _getche();
         cout << endl
              << "Binary: ";
         for (int i = 0; i < 8; i++)
         {
            (v_char & bitwise) ? cout << "1" : cout << "0";
            bitwise >>= 1;
         }
         flag = true;
      }
      else if (separator == 3)
      {
         bitwise <<= 31;
         value = input_int("Integer inRadix: ", -2147483648, 2147483647, 10, 1, radix, 1);
      }
      else if (separator == 4)
      {
         bitwise <<= 31;
         value = input_int("UInteger inRadix: ", 0, 4294967295, 10, 0, radix, 1);
      }
      else if (separator == 5)
      {
         bitwise <<= 63;
         value = input_int("Long long inRadix: ", -9223372036854775807,
                           9223372036854775807, 19, 1, radix, 1);
      }
      if (!flag)
      {
         cout << "Binary code: ";
         while (true)
         {
            (value & bitwise) ? cout << "1" : cout << "0";
            count++;
            if (count % 8 == 0)
               cout << " ";
            if (bitwise == 1)
               break;
            bitwise >>= 1;
         }
      }
   } while (proceed());
   cout << endl;
}

void print(int color, bool flag)
{
   switch (color)
   {
   case 1: // Red
      (flag) ? printf("\033[31m%s\033[0m", "1") : printf("\033[31m%s\033[0m", "0");
      break;
   case 2: // Yellow
      (flag) ? printf("\033[33m%s\033[0m", "1") : printf("\033[33m%s\033[0m", "0");
      break;
   case 3: // Green
      (flag) ? printf("\033[32m%s\033[0m", "1") : printf("\033[32m%s\033[0m", "0");
      break;
   case 4: // Blue
      (flag) ? printf("\033[34m%s\033[0m", "1") : printf("\033[34m%s\033[0m", "0");
      break;
   case 5: // Purple
      (flag) ? printf("\033[35m%s\033[0m", "1") : printf("\033[35m%s\033[0m", "0");
      break;
   }
}

void to_color(unsigned long data_v, unsigned long data, int color)
{
   unsigned int count = 0;
   unsigned long bitwise = 1;
   unsigned long bitwise_v = 1;
   int size = (sizeof(float) * 8);
   bool flag = true;
   bitwise <<= size - 2;
   bitwise_v <<= size - 2;

   while (true)
   {
      if (flag)
      {
         (data & bitwise) ? cout << "1" : cout << "0";
         flag = false;
      }
      if ((data_v & bitwise_v) ^ (data & bitwise))
      {
         if (data & bitwise)
         {
            print(color, 1);
            __asm {

                    inc count

            }
         }
         else
            print(color, 0);
      }
      else
      {
         (data_v & bitwise_v) ? cout << "1" : cout << "0";
      }

      if (bitwise_v == 1 && bitwise == 1)
         break;

      bitwise_v >>= 1;
      bitwise >>= 1;
   }
}

void output_i(unsigned long value, int size)
{
   for (int i = 0; i < size; i++)
   {
      // if (i != 0 && i % 8 == 0)
      //     cout << " ";
      cout << ((value >> (size - 1 - i)) & 1); // вывод бита
   }
   cout << endl;
}

void inv()
{
   typedef unsigned long type;
   int color, s, t_data;
   unsigned long value;
   unsigned long data = 0;
   unsigned long datv = 0;
   unsigned char new_data;
   unsigned short len;
   unsigned short cur_len;
   unsigned char bit;

   float x = 0;
   int a = 8;
   bool m = false;
   int b = sizeof(type);

   __asm {
        mov eax, a
        mov ebx, b

        mul ebx

        mov s, eax
   }
   ;

   cout << "______________________COLOR_______________________" << '\n'
        << "|                                                |" << '\n'
        << "| 1) Red                                         |" << '\n'
        << "| 2) Yellow                                      |" << '\n'
        << "| 3) Green                                       |" << '\n'
        << "| 4) Blue                                        |" << '\n'
        << "| 5) Purple                                      |" << endl;
   cout << "|________________________________________________|" << endl;

   color = input_int("Select the color: ", 1, 5, 1, 0, 10, 0);
   cout << endl;

   do
   {
      t_data = input_int("Select the type: 7 - 8 ('0' to exit): ", 0, 8, 1, 0, 10, 0);

      switch (t_data)
      {
      case 0:
         exit(0);

      case 7:
         data = input_int("UInteger: ", 0, 4294967295, 10, 0, 10, 0);
         cout << endl;
         output_i(data, s);

         datv = data;
         break;

      case 8:
         cout << "Float: ";
         cin >> x;
         binary_output_float(x, 0);
         data = inv_float(x);
         if (x < 0)
            m = true;
         datv = data;
         break;
      }

      len = s;
      cur_len = 1;
      bit = ((data >> (s - 1)) & 1); // первый бит

      for (int i = 1; i < s; i++)
      { // идем по битам
         unsigned char cur_bit = ((data >> (s - 1 - i)) & 1);
         if (cur_bit == bit)
         {
            cur_len++;
         }
         else
         {
            bit = cur_bit;
            if (cur_len < len)
               len = cur_len;
            cur_len = 1;
         }
      }

      if (cur_len < len)
         len = cur_len;

      type new_data = data;
      bit = ((data >> (s - 1)) & 1); // первый бит
      cur_len = 1;                   // текущая длина группы
      for (int i = 1; i < s; i++)    // идем по битам
      {
         unsigned char cur_bit = ((data >> (s - 1 - i)) & 1); // текущий бит
         if (cur_bit == bit)
         {
            __asm {

                    inc cur_len

            }
         }
         else
         { // новая группа
            if (cur_len == len)
            { // длина равна минимальной
               for (int j = i - 1; i - 1 - j < len; j--)
               {
                  new_data ^= ((type)1 << (s - 1 - j));
               }
            }
            bit = cur_bit;
            cur_len = 1;
         }
      }
      // проверяем последнюю группу
      if (cur_len == len)
      {
         for (int j = s - len; j < s; j++)
         {
            new_data ^= ((type)1 << (s - 1 - j));
         }
      }
      data = new_data;
      to_color(datv, data, color);
      cout << endl;
      conv(data, m);
      // cout << "Symbol: " << (char)data << endl;
   } while (t_data);
}

int main()
{
   long long data_type;
   int radix;
   int part;
   cout << "_______________________MENU_______________________" << '\n'
        << "|                     PART 1                     |" << '\n'
        << "| 1) Bool       (0 or 1) not radix               |" << '\n'
        << "| 2) Char       (symbol) not radix               |" << '\n'
        << "| 3) Integer    (-2 147 483 648...2 147 483 647) |" << '\n'
        << "| 4) UnInteger  (0...4 294 967 295)              |" << '\n'
        << "| 5) Long long  (-9 223 372 036 854 775 807...   |" << '\n'
        << "|            ...9 223 372 036 854 775 807)       |" << '\n'
        << "| 6) Float                                       |" << '\n'
        << "|                                                |" << '\n'
        << "|                     PART 2                     |" << '\n'
        << "| 7) Inverting integer                           |" << '\n'
        << "| 8) Inverting float                             |" << endl;
   cout << "|________________________________________________|" << endl;

   part = input_int("Select the part: (1 - 2): ", 1, 2, 1, 0, 10, 0);
   cout << endl;

   switch (part)
   {
   case 1:
      radix = input_int("Radix (2 - 32): ", 2, 32, 2, 0, 10, 0);
      cout << endl
           << endl;
      do
      {
         data_type = input_int("Select the type ('0' to exit): ", 0, 6, 1, 0, 10, 0);
         cout << endl;
         switch (data_type)
         {
         case 0:
            exit(0);
         case 1:
            cnv_i(1, radix);
            break;
         case 2:
            cnv_i(2, radix);
            break;
         case 3:
            cnv_i(3, radix);
            break;
         case 4:
            cnv_i(4, radix);
            break;
         case 5:
            cnv_i(5, radix);
            break;
         case 6:
            cnv_r(radix);
            break;
         }
      } while (data_type);
      break;
   case 2:
      inv();
      break;
   }
}
