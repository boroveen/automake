#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;
int name,name1,lib[20],lib1;
bool lib2=true,Install=true,Uninstall=true;
void help(){
	cout << "automake -i -u -n main.cpp main -l -lib" << endl;
	cout << "-i - enable install in Makefile" << endl;
	cout << "-u - enable uninstall in Makefile" << endl;
	cout << "-n - name. file.cpp and file binary" << endl;
	cout << "-l - include library" << endl;
}
int main(int argc,char* argv[]){
	if(argc==1){
		help();
	}
	else{
		for(int i=0;i<argc;i++){
			if(string(argv[i])=="-h"){
				help();
				i=argc;
			}
			else if(string(argv[i])=="-n"){
				name=i+1,name1=i+2;
			}
			else if(string(argv[i])=="-l"){
				lib2=false;
				lib1=argc-i;
				for(int g=0;g<argc-i;g++) lib[g]=i+g;
			}
			else if(string(argv[i])=="-i") Install=false;
			else if(string(argv[i])=="-u") Uninstall=false;
		}
	}
	system("touch Makefile");
	fstream makefile;
	makefile.open("Makefile");
	makefile << "# created with boroveen/automake" << endl << endl;
	makefile << "all: " << argv[name1] << endl << endl;
	makefile << argv[name1] << ":" << endl;
	makefile << "	" << "g++ " << argv[name] << " -o " << argv[name1];
	if(!lib2) for(int i=1;i<lib1;i++) makefile << " " << argv[lib[i]];
	makefile << endl << endl;
	if(!Install){
		makefile << "install:" << endl;
		makefile << "	" << "sudo cp " << argv[name1] << " /bin" << endl << endl;
	}
	if(!Uninstall){
		makefile << "uninstall:" << endl;
		makefile << "	" << "sudo rm /bin/" << argv[name1] << endl << endl;
	}
	return 0;
}
