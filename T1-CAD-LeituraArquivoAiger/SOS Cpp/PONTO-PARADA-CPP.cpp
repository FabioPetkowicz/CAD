// string::substr
#include <iostream>
#include <string>

using namespace std;

int main ()
{
  std::string str= "aag 11 5 0 2 6";
  
size_t pos2 = str.find(" ");
string str2 = str.substr(pos2+1);
cout << str2 << '\n';

size_t pos3 = str2.find(" ");
string str3 = str2.substr(pos3+1);
cout << str3 << '\n';   


                           
//  std::string str2 = str.substr (3,str.size()-1);     // "11 5 0 2 6"

  return 0;
}

/*
std::string str= "aag 11 5 0 2 6";
  
    std::size_t pos2 = str.find(" ");
    std::string str2 = str.substr(pos2+1);
    std::cout << str2 << '\n';

    std::size_t pos3 = str2.find(" ");
    std::string str3 = str2.substr(pos3+1);
    std::cout << str3 << '\n';
*/
