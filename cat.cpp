
#include <iostream>
#include <cstring>
 #include <fstream> 
using namespace std;
 int main (int argc, char** argv){ std::ifstream in; in.open(argv[1]); char c; while ((c=in.get())!=EOF) cout<<c; return 0;
}
