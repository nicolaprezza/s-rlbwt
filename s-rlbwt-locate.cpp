#include <iostream>
#include <utils.h>
#include "s_rlbwt.h"

using namespace srlbwt;
using namespace std;

void help(){
	cout << "s-rlbwt-locate: locate all occurrences of the input patterns. Note that this program" << endl;
	cout << "discards the output (i.e. text positions), and should be used only for benchmark purposes." << endl << endl;
	cout << "Usage: s-rlbwt-locate <index_basename> <patterns_file>" << endl;
	cout << "   <index_basename>    basename of all index files" << endl;
	cout << "   <patterns_file>     file in pizza&chili format containing the patterns." << endl;
	exit(0);
}

void search(string idx_basename, string patterns, bool optimize = true){

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;

    auto t1 = high_resolution_clock::now();

    s_rlbwt<> idx;

	idx.load_from_file(idx_basename);

	auto t2 = high_resolution_clock::now();

	cout << "searching patterns ... " << endl;
	ifstream ifs(patterns);

	//read header of the pizza&chilli input file
	//header example:
	//# number=7 length=10 file=genome.fasta forbidden=\n\t
	string header;
	std::getline(ifs, header);

	ulint n = get_number_of_patterns(header);
	ulint m = get_patterns_length(header);

	uint last_perc = 0;

	ulint occ_tot=0;

	//extract patterns from file and search them in the index
	for(ulint i=0;i<n;++i){

		uint perc = (100*i)/n;
		if(perc>last_perc){
			cout << perc << "% done ..." << endl;
			last_perc=perc;
		}

		string p = string();

		for(ulint j=0;j<m;++j){
			char c;
			ifs.get(c);
			p+=c;
		}

		//cout << "locating " << idx.count(p) << " occurrences of "<< p << " ... " << flush;

		auto occ = idx.locate(p);	//occurrences
		occ_tot+=occ.size();

		//cout << "done." << endl;

		//for(auto o:occ) cout << o << " ";
		//cout << endl;

	}

	double occ_avg = (double)occ_tot / n;

	cout << endl << occ_avg << " average occurrences per pattern" << endl;

	ifs.close();

	auto t3 = high_resolution_clock::now();

	//printRSSstat();

	uint64_t load = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	cout << "Load time : " << load << " milliseconds" << endl;

	uint64_t search = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
	cout << "number of patterns n = " << n << endl;
	cout << "pattern length m = " << m << endl;
	cout << "total number of occurrences  occ_t = " << occ_tot << endl;
	cout << "m * occ_t  = " << occ_tot*m << endl;
	cout << "n*m + occ_t  = " << n*m+occ_tot << endl << endl;

	cout << "Total time : " << search << " milliseconds" << endl;
	cout << "Search time : " << (double)search/n << " milliseconds/pattern (total: " << n << " patterns)" << endl;
	cout << "Search time : " << (double)search/occ_tot << " milliseconds/occurrence (total: " << occ_tot << " occurrences)" << endl;

}

int main(int argc, char** argv){

	if(argc != 3)
		help();

	cout << "Loading s-rlbwt index" << endl;
	search(argv[1],argv[2]);

}
