#include <iostream>
#include <utils.h>
#include "s_rlbwt.h"

using namespace srlbwt;
using namespace std;

void help(){
	cout << "s-rlbwt-space: breakdown of index space usage" << endl;
	cout << "Usage: s-rlbwt-space <index_basename>" << endl;
	cout << "   <index_basename>    basename of all index files" << endl;
	exit(0);
}


int main(int argc, char** argv){

	if(argc != 2)
		help();

	s_rlbwt<> idx;
	idx.load_from_file(argv[1]);

	auto space = idx.print_space();

	cout << "\nTOT s-rlbwt space: " << space << " Bytes" <<endl;


}
