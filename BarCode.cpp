#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <cmath>
#include <string>
#include <cstring>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <Image.h>
#include <string.h>

using namespace std;
char filename[255];

class image
{

protected:
    string fname;
    int printbar(string barcode)
    {
        HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);

        for (int j = 0; j < 15; j++)
        {
            for (int i = 0; i < barcode.size(); i++)
            {
                if (barcode[i] == '1')
                {
                    SetConsoleTextAttribute(hc, 07);
                    cout << " ";
                }
                else
                {
                    SetConsoleTextAttribute(hc, 0xfc);
                    cout << " ";
                }
            }
            cout << "\n";
        }
        genimage(barcode);
        return 0;
    }

    void genimage(string barcode)
    {
        HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
        cout << "\nDo you wish to save the file(Y/N)?";
        string confirm = "";
        cin >> confirm;
        if (confirm == "Y" || confirm == "YES")
        {
            cout << "Enter Name of File[filename.bmp]: ";
            cin >> confirm;
            strcpy(filename, confirm.c_str());
        }
        int width = 512;
        const int height =  400;
        int bar = 0;
        int pixelsize = width/barcode.size();
        int quietzone = (width - barcode.size() * pixelsize) / 2;
        if (quietzone < 0)
            quietzone = 0;
        Image bitmap(width, height);

        for (int x = 0; x < width; x++) {

            for (int y = 0; y < height; y++)
            {
                    bitmap.SetColor(Color(1, 1, 1), x, y);
            }
        }

        int count = 0;
        for (int x = quietzone; x < (quietzone + barcode.size() * pixelsize); x++) {

            for (int y = 0 ; y < height ; y++)
            {

                     if (barcode[bar] == '1')
                    {

                             bitmap.SetColor(Color(0, 0, 0), x, y);
                    }
                    else
                    {
                             bitmap.SetColor(Color(1, 1, 1), x, y);
                    }

            }
            count++;

            if (count == pixelsize)
            {
                bar++;
                count = 1;
            }

            }


          bitmap.Export(filename);
    }
};

class GenerateCode
{
protected:
    GenerateCode()
    {
    }
    ~GenerateCode()
    {
    }
    string Gencode39(const string& input)
    {
        const unordered_map<char, string> code39Map = {
       {'0', "101001101101"}, {'1', "110100101011"}, {'2', "101100101011"},
       {'3', "110110010101"}, {'4', "101001101011"}, {'5', "110100110101"},
       {'6', "101100110101"}, {'7', "101001011011"}, {'8', "110100101101"},
       {'9', "101100101101"}, {'A', "110101001011"}, {'B', "101101001011"},
       {'C', "110110100101"}, {'D', "101011001011"}, {'E', "110101100101"},
       {'F', "101101100101"}, {'G', "101010011011"}, {'H', "110101001101"},
       {'I', "101101001101"}, {'J', "101011001101"}, {'K', "110101010011"},
       {'L', "101101010011"}, {'M', "110110101001"}, {'N', "101011010011"},
       {'O', "110101101001"}, {'P', "101101101001"}, {'Q', "101010110011"},
       {'R', "110101011001"}, {'S', "101101011001"}, {'T', "101011011001"},
       {'U', "110010101011"}, {'V', "100110101011"}, {'W', "110011010101"},
       {'X', "100101101011"}, {'Y', "110010110101"}, {'Z', "100110110101"},
       {'-', "100101011011"}, {'.', "110010101101"}, {' ', "100110101101"},
       {'*', "101011110111"}, {'$', "100101001001"}, {'/', "100100101001"},
       {'+', "100101001101"}, {'%', "101001001001"}
        };

        string encodedString;
        for (char c : input) {
            auto it = code39Map.find(c);
            if (it != code39Map.end()) {
                encodedString += it->second;
                encodedString += "0"; // add separator between characters
            }
            else {
                cout << "Error: character " << c << " cannot be encoded in Code 39 barcode" << endl;
                return "";
            }
        }

        // Add start/stop character (*) at the beginning and end of the barcode
        encodedString = "1001011011010" + encodedString + "0100101101101";
        return encodedString;
    }

    string Gencode93(string& data)
    {
        //intput = "*" +input ;
        // Code 93 character table
        unordered_map<char, string> code93_table{
        {'0', "100010100"}, {'1', "101001000"}, {'2', "101000100"}, {'3', "101000010"},
        {'4', "100101000"}, {'5', "100100100"}, {'6', "100100010"}, {'7', "101010000"},
        {'8', "100010010"}, {'9', "100001010"}, {'A', "110101000"}, {'B', "110100100"},
        {'C', "110100010"}, {'D', "110010100"}, {'E', "110010010"}, {'F', "110001010"},
        {'G', "101101000"}, {'H', "101100100"}, {'I', "101100010"}, {'J', "100110100"},
        {'K', "100011010"}, {'L', "101011000"}, {'M', "101001100"}, {'N', "101000110"},
        {'O', "100101100"}, {'P', "100010110"}, {'Q', "110110100"}, {'R', "110110010"},
        {'S', "110101100"}, {'T', "110100110"}, {'U', "110010110"}, {'V', "110011010"},
        {'W', "101101100"}, {'X', "101100110"}, {'Y', "100110110"}, {'Z', "100111010"},
        {'-', "100101110"}, {'.', "111010100"}, {' ', "111010010"}, {'$', "111001010"},
        {'/', "101101110"}, {'+', "101110110"}, {'%', "110101110"}, {'*', "100100110"},
        {'(', "111011010"}, {')', "111010110"}, {'[', "100110010"}, {']', "111011110"},
        {'{', "111001100"}, {'}', "111001001"}, {'<', "101111000"}, {'>', "101000111"},
        {'@', "101011110"}, {'\'', "101111110"}, {':', "111101010"}, {'\\', "111101000"},
        {'^', "111010111"}, {'_', "111010011"}, {'`', "111001101"}, {'|', "101010111"}
        };
        vector<char> codeIndex =
        {
           '0','1','2','3','4','5','6','7','8',
           '9','A','B','C','D','E','F','G','H',
           'I','J','K','L','M','N','O','P','Q',
           'R','S','T','U','V','W','X','Y','Z',
           '-','.',' ','$','/','+','%','*','(',
           ')','[',']','{','}','<','>','@','\'',
           ':','\\','^','_','`','|'
        };
        int weight = 1;
        int cSum = 0;
        int kSum = 0;

        for (auto it = data.rbegin(); it != data.rend(); ++it) {
            cSum += weight * distance(codeIndex.begin(), find(codeIndex.begin(), codeIndex.end(), *it));
            weight++;
            if (weight > 20)
                weight = 1;
        }

        char cCheck = codeIndex[cSum % 47];

        weight = 1;

        for (auto it = data.rbegin(); it != data.rend(); ++it) {
            kSum += weight * distance(codeIndex.begin(), find(codeIndex.begin(), codeIndex.end(), *it));
            weight++;
            if (weight > 15)
                weight = 1;
        }

        kSum += distance(codeIndex.begin(), find(codeIndex.begin(), codeIndex.end(), cCheck)) * weight;

        char kCheck = codeIndex[kSum % 47];

        string result;

        for (char c : data) {
            result += code93_table[c];
        }

        result += code93_table[cCheck];
        result += code93_table[kCheck];
        result = "101011110" + result + "1010111101";
        return result;
    }

    string Gencode128(string data)
    {
        // The Code 128 character set table
        vector<string> code128_table =
        {
            "11011001100", "11001101100", "11001100110", "10010011000",
            "10010001100", "10001001100", "10011001000", "10011000100",
            "10001100100", "11001001000", "11001000100", "11000100100",
            "10110011100", "10011011100", "10011001110", "10111001100",
            "10011101100", "10011100110", "11001110010", "11001011100",
            "11001001110", "11011100100", "11001110100", "11101101110",
            "11101001100", "11100101100", "11100100110", "11101100100",
            "11100110100", "11100110010", "11011011000", "11011000110",
            "11000110110", "10100011000", "10001011000", "10001000110",
            "10110001000", "10001101000", "10001100010", "11010001000",
            "11000101000", "11000100010", "10110111000", "10110001110",
            "10001101110", "10111011000", "10111000110", "10001110110",
            "11101110110", "11010001110", "11000101110", "11011101000",
            "11011100010", "11011101110", "11101011000", "11101000110",
            "11100010110", "11101101000", "11101100010", "11100011010",
            "11101111010", "11001000010", "11110001010", "10100110000",
            "10100001100", "10010110000", "10010000110", "10000101100",
            "10000100110", "10110010000", "10110000100", "10011010000",
            "10011000010", "10000110100", "10000110010", "11000010010",
            "11001010000", "11110111010", "11000010100", "10001111010",
            "10100111100", "10010111100", "10010011110", "10111100100",
            "10011110100", "10011110010", "11110100100", "11110010100",
            "11110010010", "11011011110", "11011110110", "11110110110",
            "10101111000", "10100011110", "10001011110", "10111101000",
            "10111100010", "11110101000", "11110100010", "10111011110",
            "10111101110", "11101011110", "11110101110", "11010000100",
            "11010010000", "11010011100", "11000111010"
        };
        string encodedData;
        int a = 0;
        for (char ch : data)
        {
            if (ch >= 0 && ch <= 95)
            {
                a = 1;
            }
            else if (ch >= 32 && ch <= 127)
            {
                a = 2;
            }
            else if (ch >= '0' && ch <= '9')
            {
                a = 3;
            }
            else
            {
                cout << ch << " does not belong to any code set in Code 128." << endl;
            }
        }
        for (char c : data)
        {
            if (c >= 0 && c <= 95)
            {
                // Start character (Code A)
                encodedData = code128_table[103];
            }
            else if (c >= 32 && c <= 127)
            {
                //start character (Code B)
                encodedData = code128_table[104];
            }
            else if (c >= '0' && c <= '9')
            {
                //Start character (Code C)
                encodedData = code128_table[105];
            }
        }

        // Calculate check character
        switch (a)
        {
        case 1:
        {
            int checkSum = 103;
            for (int i = 0; i < data.length(); i++)
            {
                int codeValue = int(data[i]) - 32;
                checkSum += codeValue * (i + 1);
                encodedData += code128_table[codeValue];
            }
            checkSum %= 102;
            encodedData += code128_table[checkSum];
            encodedData += "11010000100";
            break;
        }
        case 2:
        {
            int checkSum = 104;
            for (int i = 0; i < data.length(); i++)
            {
                int codeValue = int(data[i]) - 32;
                checkSum += codeValue * (i + 1);
                encodedData += code128_table[codeValue];
            }
            checkSum %= 103;
            encodedData += code128_table[checkSum];
            encodedData += "1100011101011";
            break;
        }
        case 3:
        {
            int checkSum = 105;
            for (int i = 0; i < data.length(); i++)
            {
                int codeValue = int(data[i]) - 32;
                checkSum += codeValue * (i + 1);
                encodedData += code128_table[codeValue];
            }
            checkSum %= 104;
            encodedData += code128_table[checkSum];
            encodedData += "110100111";
            break;
        }
        default:cout << "";
        }


        return encodedData;
    }

    string GencodeITF(string digits)
    {
        vector<string> codes = { "00110", "10001", "01001", "11000", "00101",
                                    "10100", "01100", "00011", "10010", "01010" };
        string result = "";
        for (int i = 0; i < digits.size(); i += 2) {
            string first = codes[digits[i] - '0'];
            string second = codes[digits[i + 1] - '0'];
            for (int j = 0; j < first.size(); ++j) {
                result += first[j];
                result += second[j];
            }
        }
        return result;
    }

    string  GencodeEAN13(string digits)
    {
        string result = "";
        string leftOdd[] =
        {
            "0001101", "0011001", "0010011", "0111101", "0100011",
            "0110001", "0101111", "0111011", "0110111", "0001011"
        };
        string leftEven[] =
        {
            "0100111", "0110011", "0011011", "0100001", "0011100",
            "0111000", "0000100", "0010000", "0001000","0010110"
        };
        string right[] =
        {
            "1110010","1100110","1101100","1000010","1011100",
            "1001110","1010000","1000100","1001000","1110100"
        };

        result += '101';
        for (int i = 0; i < 6; i++) {
            if ((digits[0] - '0') & (1 << (5 - i))) {
                result += leftEven[digits[i + 1] - '0'];
            }
            else {
                result += leftOdd[digits[i + 1] - '0'];
            }
        }
        result += "01010";
        for (int i = 7; i < 13; i++) {
            result += right[digits[i] - '0'];
        }
        result += '101';

        return result;
    }


    string GencodeUPCA(string input)
    {
        // Calculate the check digit
        int sumOdd = 0;
        int sumEven = 0;
        for (int i = 0; i < 11; i++) {
            int digit = input[i] - '0';
            if (i % 2 == 0) {
                sumOdd += digit;
            }
            else {
                sumEven += digit;
            }
        }
        int checkDigit = (10 - ((3 * sumOdd + sumEven) % 10)) % 10;
        // Add the check digit to the data
        input += to_string(checkDigit);
        // Generate the barcode pattern
        string encodedData = "101";  //starting
        for (int i = 0; i < 6; i++) {
            char digit = input[i];
            switch (digit) {
            case '0': encodedData += "0001101"; break;
            case '1': encodedData += "0011001"; break;
            case '2': encodedData += "0010011"; break;
            case '3': encodedData += "0111101"; break;
            case '4': encodedData += "0100011"; break;
            case '5': encodedData += "0110001"; break;
            case '6': encodedData += "0101111"; break;
            case '7': encodedData += "0111011"; break;
            case '8': encodedData += "0110111"; break;
            case '9': encodedData += "0001011"; break;
            default: break;
            }
        }
        encodedData += "01010"; //central part
        for (int i = 6; i < 12; i++) {
            char digit = input[i];
            switch (digit)
            {
            case '0': encodedData += "1110010"; break;
            case '1': encodedData += "1100110"; break;
            case '2': encodedData += "1101100"; break;
            case '3': encodedData += "1000010"; break;
            case '4': encodedData += "1011100"; break;
            case '5': encodedData += "1001110"; break;
            case '6': encodedData += "1010000"; break;
            case '7': encodedData += "1000100"; break;
            case '8': encodedData += "1001000"; break;
            case '9': encodedData += "1110100"; break;
            default: break;
            }
        }
        encodedData += "101"; //ending
        return encodedData;
    }
};


class readdata
{
protected:
    string b;

    readdata()
    {
        b = "";
    }
    ~readdata()
    {

    }
    string readcode39data()
    {
        cout << "Enter data(maximum 43 character; A-Z & 0-9): ";
        getline(cin >> ws, b);
        return b;
    }
    string readcode93data()
    {
        cout << "Enter data(maximum 48 character; A-Z & 0-9): ";
        getline(cin >> ws, b);
        return b;
    }
    string filename()
    {
        cout << "Enter Name of File[filename.bmp]: ";
        getline(cin >> ws, b);
        return b;
    }
    string readcode128data()
    {
        cout << "Enter data(maximum 60 character): ";
        getline(cin >> ws, b);
        return b;
    }
    string readITFdata()
    {
        cout << "Enter data(maximum 14 character;0-9): ";
        cin >> b;
        return b;
    }
    string readEAN13data()
    {
        cout << "Enter data(must be 13 digit; 0-9): ";
        cin >> b;
        return b;
    }
    string readUPCAdata()
    {
        cout << "Enter data(maximum 12 digits;number of digits must be even; 0-9): ";
        cin >> b;
        return b;
    }
};

class dataexam :public GenerateCode, public image
{
private:
    int len;
protected:
    dataexam()
    {
        len = 0;
    }
    void examdata(string str, int x)
    {
        string k;
        len = str.length();
        switch (x)
        {
        case 1:
        {
            if (len <= 43)
            {
                k = Gencode39(str);
            }
            else
                invalid();
            break;
        }
        case 2:
        {
            if (len <= 48)
            {
                k = Gencode93(str);
            }
            else
                invalid();
            break;
        }
        case 3:
        {
            if (len <= 60)
            {
                k = Gencode128(str);
            }
            else
                invalid();
            break;
        }
        case 4:
        {
            if (len <= 14 && len % 2 == 0)
            {
                k = GencodeITF(str);
            }
            else
                invalid();
            break;
        }
        case 5:
        {
            if (len == 13)
            {
                k = GencodeEAN13(str);
            }
            else
                invalid();
            break;
        }
        case 6:
        {
            if (len <= 12)
            {
                for (int i = len; i <= 12; i++)
                {
                    str = str + "0";
                }
                k = GencodeUPCA(str);
            }
            else
                invalid();
            break;
        }
        default:cout << "Program breakdown" << endl;
        }
        cout << "Encoded String(Binary equivalent):\t" << k << endl;
        dataexam::printbar(k);
    }
    void invalid()
    {
        cout << "Error";
    }

};

class readtype : protected readdata, public dataexam
{
private:
    int t;
public:
    readtype()
    {
        t = 0;
    }
    ~readtype()
    {
        t = 0;
    }
    int CodeTypeRead()
    {
        cout << "Enter the type of the barcode" << endl;
        cout << "\n\t1. Code 39 \n\t2. Code 93 \n\t3. Code 128 \n\t4. ITF\n\t5. EAN-13 \n\t6. UPC\n\nEnter:\t";
        cin >> t;

        return (t);
    }

    int analysetype()
    {
        string str;
        int i = CodeTypeRead();

        switch (t)
        {
        case 1:
        {
            str = readcode39data();
            examdata(str, 1);
            break;
        }
        case 2:
        {
            str = readcode93data();
            examdata(str, 2);
            break;
        }
        case 3:
        {
            str = readcode128data();
            examdata(str, 3);
            break;
        }
        case 4:
        {
            str = readITFdata();
            examdata(str, 4);
            break;
        }
        case 5:
        {
            str = readEAN13data();
            examdata(str, 5);
            break;
        }
        case 6:
        {
            str = readUPCAdata();
            examdata(str, 6);
            break;
        }
        default:invalid();

        };
        return 0;
    }

    int invalid()
    {
        cout << "ERROR:  INVALID INPUT!!!!!" << endl;
        return 0;

    }
};

int main()
{
restart:
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_MAXIMIZE);
    system("cls");
    system("color E1");
    readtype a1;
    int i = a1.analysetype();
    int ch = cin.get();
    system("cls");

    //for saving

    main();
    return 0;
}

