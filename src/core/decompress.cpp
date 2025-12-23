#include <iostream>
#include "deserilize.h"
#include "Decoding.h"



int main (int argc ,char* argv[]) 
{

    deserillized compressed_data= deserilize("./compressed/"+std::string(argv[1]));
    std::vector <uint8_t> decoded = decode( compressed_data.freq_map, &compressed_data.bits_string);

    std::ofstream image_out;

    image_out.open("./decompressed/image.pgm", std::ios::out | std::ios::binary);

    image_out<<compressed_data.format<<std::endl;
    image_out<<compressed_data.cols<<" "<<compressed_data.rows<<std::endl;
    image_out<<compressed_data.maxval<<std::endl;

    unsigned int i = 0;

    for (auto d : decoded)
    {
        image_out<<d;
        if (++i == compressed_data.cols)
            image_out<< std::endl;
    }

    image_out.close();




}
