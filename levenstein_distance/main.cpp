
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdint>

#include "../lib/measure.h"

int32_t get_levenshtein_distance(const std::string &str1, const std::string &str2) {
    size_t n = str1.size() + 1;
    size_t m = str2.size() + 1;
    std::vector<int32_t> D(n * m);
    for(size_t i = 0; i < n; i++) {
        D[i * m + 0] = i;
    }
    for(size_t j = 0; j < m; j++) {
        D[0 * m + j] = j;
    }

    for(size_t i = 1; i < n; i++) {
        for(size_t j = 1; j < m; j++) {
            int32_t c = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            D[i * m + j] = std::min(std::min(D[(i - 1) * m + j    ] + 1,
                                             D[ i      * m + j - 1] + 1),
                                             D[(i - 1) * m + j - 1] + c);
        }
    }
    assert(((n - 1) * m + m - 1) == D.size() - 1);
    return D[(n-1) * m + m - 1];
}

int main(void) {
    std::ios::sync_with_stdio(false);

    // 1. Read two strings
    std::string str1;
    std::string str2;
    std::cin >> str1 >> str2;
    int32_t dist;
    measure_and_print([&str1, &str2,&dist] ()
        {
            // 2. Calculate Levenshtein distance between strings
            dist = get_levenshtein_distance(str1, str2);

        });

    
    // 3. Write result
    std::cout << dist << std::endl;
}
