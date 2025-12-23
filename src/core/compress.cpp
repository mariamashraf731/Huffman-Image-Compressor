#include<iostream>
#include "reading.h"
#include<map>
#include "huffman.h"





int main(int argc, char* argv[])
{
    image im;

    im = pgm_read ("./data/"+std::string(argv[1]));

    std::map<uint8_t,int> Frequency = freq_map (im.pixels_values);

    std::map<uint8_t,std::string> huffmanCode = buildhuffmanTree( Frequency);

    std::string compressed_string = bits_string(im.pixels_values,huffmanCode);

    std::vector <uint8_t> compressed_bytes = bytes_array(compressed_string);


    //serilizing compressed image

    std::ofstream out;
    out.open("./compressed/image.enc", std::ios::out | std::ios::binary);
    //data
    out<<im.format<<std::endl;
    out<<im.cols<<" "<<im.rows<<std::endl;
    out<<im.maxVal<<std::endl;
    out<<compressed_bytes.size()<<" "<< compressed_string.size()<<" " << Frequency.size() <<std::endl;

    //frequency map
    for (auto m : Frequency)
    {
        out << (int)m.first<< " " << m.second << std::endl;
    }

    //compressed array
    unsigned int i = 0;

    for (auto byte : compressed_bytes )
    {
        out << byte;
        if (++i == im.cols)
            out<< std::endl;
    }





    out.close();

}
