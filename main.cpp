#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

// class player {
// public:
    
// };

// class game {
// public:
//     game(int num) : numCandies(num){}

// private:
//     int numCandies;
//     std::vector<player> 
// };

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::pair<int,int> & p) {
	os << "(" << p.first << "," << p.second << ")";
	return os;
    }
}

class solution {
public:
    solution(int mn, int mx) : min(mn), max(mx){}
    
    std::vector<std::vector<std::pair<int,int>>> takeCandies(int num) {
	auto paths = getPaths(num, std::vector<std::pair<int,int>>());
	return paths;
    }

private:
    int min, max;
    
    std::vector<std::vector<std::pair<int,int>>> getPaths(int num, const std::vector<std::pair<int,int>> & curr) {
	std::vector<std::vector<std::pair<int,int>>> result;
	if (sum(curr) == num) {
	    result.push_back(curr);
	}
	else {
	    auto next = getNext(num-sum(curr));
	    for (auto nx : next) {
		auto cpy = curr;
		cpy.push_back(nx);
		auto temp = getPaths(num, cpy);
		std::copy(temp.begin(),temp.end(),std::inserter(result,result.end()));
	    }
	}
	return result;
    }

    std::vector<std::pair<int,int>> getNext(int n) {
	std::vector<std::pair<int,int>> next;
	if (n%(min+max) == 1) {
	    if (n > 1){
	    for (int i = min; i <= max; i++)
		next.push_back(std::make_pair(i, max+min-i));
	    }
	    else {
		next.push_back(std::make_pair(1,0));
	    }	    
	}
	else {
	    int i = min;
	    while (i < max && (n-i)%(min+max) != 1)
		i++;
	    for (int j = min; j <= std::min(max, n-i); j++) {
		next.push_back(std::make_pair(i, j));
	    }
	}
	return next;
    }

    int sum(const std::vector<std::pair<int,int>> & vec) {
	return std::accumulate(vec.begin(),vec.end(),0,
			       [](int i, const std::pair<int,int> & p){
				   return i+p.first+p.second;
			       });
    }
};

int main() {
    int numCandies = 51;
    int mintake = 1, maxtake = 4;

    solution soln(mintake, maxtake);
    auto paths = soln.takeCandies(numCandies);
    std::for_each(paths.begin(), paths.end(),
		  [](const std::vector<std::pair<int,int>> & vec){
		      std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::pair<int,int>>(std::cout, ""));
		      std::cout << std::endl;
		  });
}
