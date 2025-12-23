#ifndef FREQ_MAP_H
#define FREQ_MAP_H

#include <map>
#include<vector>
#include <iostream>
#include<cstdint>


std::map<uint8_t,int> freq_map (std::vector<uint8_t> image){
    std::map< uint8_t, int > pixelsfreq;
    for( unsigned int i = 0 ; i < image.size() ; ++i )
        pixelsfreq[ image[i] ]++;
    return pixelsfreq;
}

void print_freq_map (std::map <uint8_t,int> const &m)
{
    for (auto it = m.cbegin(); it != m.cend(); ++it) {
        std::cout << "{" << (*it).first << ": " << (*it).second << std::endl;
    }
}

unsigned int freq_count(std::map<uint8_t,int> const m)
{
    unsigned int allfreq=0;
    for (auto it = m.cbegin(); it != m.cend(); ++it) {
        allfreq  = allfreq + (*it).second ;
    }
    return allfreq;
}



#endif // FREQ_MAP_H
