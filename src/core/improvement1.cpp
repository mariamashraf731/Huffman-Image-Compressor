#include <iostream>
#include "reading.h"
#include "huffman.h"
#include"freq_map.h"
#include "deserilize.h"
#include "Decoding.h"
#include <string>         // std::string
#include <cstddef>         // std::size_t


image pgm_read (const std::string);

int main(int argc, char* argv[])
{
std::string file_name (argv[1]);
std::size_t type = file_name.find_last_of(".");
std::string type_found = file_name.substr(type+1);

if (type_found == "pgm")
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
else if (type_found == "enc")
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

   return 0;
}
