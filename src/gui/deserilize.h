#ifndef DESERILIZE_H
#define DESERILIZE_H
#include<fstream>
#include<iostream>
#include <string>
#include<vector>
#include<cstdint>
#include<map>
#include<bitset>

struct deserillized {
    std::string bits_string ;
    std::map<uint8_t,int> freq_map;
    unsigned int bytes_array_size;
    unsigned int bits_string_size;
    unsigned int freq_map_size;
    unsigned int cols;
    unsigned int rows;
    unsigned int maxval;
    std::string format;
};
deserillized deserilize(std::string filepath)
{
    deserillized dd;
    std::ifstream ifs;
    ifs.open(filepath, std::ios::in |std::ios::binary);
    /* if(!ifs)
    {
        std::cout << "not opened"<<std::endl;
        return dd;
    }
    else std::cout<<"opened"<<std::endl;*/

    ifs>>dd.format;//getting image format

    ifs>>dd.cols;//getting number of columns

    ifs>>dd.rows;//getting number of rows

    ifs>>dd.maxval;//getting maximum pixel value
    ifs>>dd.bytes_array_size;
    ifs>>dd.bits_string_size;
    ifs>>dd.freq_map_size;
    ifs.ignore();

    dd.bits_string="";
    dd.freq_map={};


    //reading frequency map
    for(unsigned int i=0; i< dd.freq_map_size;i++)
    {
        int key =0;
        int val=0;
        ifs>>key;
        ifs>>val;
        dd.freq_map.insert({uint8_t(key),val});

    }
   /* if(dd.freq_map.size()!=dd.freq_map_size)
    {
        std::cout<<"freq_map not complete   "<< dd.freq_map.size()<< " "<<dd.freq_map_size <<std::endl;

        return dd;
    }
    else std::cout <<"freq map done"<<std::endl;*/

    ifs.ignore();
    //reading bits_string
    for(unsigned int i=0;i<dd.bytes_array_size;i++)
    {
        uint8_t temp;
        ifs>>std::noskipws>>temp;
        std::bitset<8> bits = std::bitset<8>(temp);
        dd.bits_string += bits.to_string();
    }

    if(dd.bits_string.size()< dd.bits_string_size){
        std::cout << "not all bits are read"<<std::endl;
        std::cout<<dd.bits_string.size();
        return dd;
    }

    std::cout<<"deserilized successfully"<<std::endl;
    return dd;
    ifs.close();

}

#endif // DESERILIZE_H
