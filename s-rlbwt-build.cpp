#include <iostream>
#include <utils.h>
#include "s_rlbwt.h"

using namespace srlbwt;
using namespace std;

string out_basename=string();
string input_file=string();
int sa_rate = 512;

void help(){
	cout << "s-rlbwt-build" << endl << endl;
	cout << "Usage: s-rlbwt-build [options] <input_file_name>" << endl;
	cout << "   -o <basename>         use 'basename' as prefix for all index files. Default: basename is the specified input_file_name"<<endl<<endl;
	cout << "   -sr                   suffix array sampling rate. Default = 512." << endl;
	cout << "   <input_file_name>     input text file." << endl;
	exit(0);
}

void parse_args(char** argv, int argc, int &ptr){

	assert(ptr<argc);

	string s(argv[ptr]);
	ptr++;

	if(s.compare("-o")==0){

		if(ptr>=argc-1){
			cout << "Error: missing parameter after -o option." << endl;
			help();
		}

		out_basename = string(argv[ptr]);
		ptr++;

	}if(s.compare("-sr")==0){

		if(ptr>=argc-1){
			cout << "Error: missing parameter after -sr option." << endl;
			help();
		}

		sa_rate = atoi(argv[ptr]);

		if(sa_rate < 0){
			cout << "Error: sampling rate must be non-negative" << endl;
			help();
		}

		ptr++;

	}else{
		cout << "Error: unrecognized '" << s << "' option." << endl;
		help();
	}

}

int main(int argc, char** argv){

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;

    auto t1 = high_resolution_clock::now();

	//parse options

    out_basename=string();
    input_file=string();
	int ptr = 1;

	if(argc<2) help();

	while(ptr<argc-1)
		parse_args(argv, argc, ptr);

	input_file = string(argv[ptr]);

	if(out_basename.compare("")==0)
		out_basename = string(input_file);

	cout << "Building s-rlbwt of input file '" << input_file << "'" << endl;
	cout << "Prefix '" << out_basename << "' will be used for all index files." << endl;

	string input;

	{

		std::ifstream fs(input_file);
		std::stringstream buffer;
		buffer << fs.rdbuf();

		input = buffer.str();

	}

	s_rlbwt<> idx = s_rlbwt<>(input,sa_rate);
	idx.save_to_file(out_basename);

	//printRSSstat();

	auto t2 = high_resolution_clock::now();
	ulint total = duration_cast<duration<double, std::ratio<1>>>(t2 - t1).count();
	cout << "Build time : " << get_time(total) << endl;

}
