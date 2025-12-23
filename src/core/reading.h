#ifndef READING_H
#define READING_H

#include<iostream>
#include <string>
#include<vector>
#include <fstream>
#include<cstdint>


struct image {

    unsigned int rows;
    unsigned int cols;
    unsigned int maxVal;
    std::string format;
    std::vector <uint8_t> pixels_values;
    unsigned int num_pixels;
};

image pgm_read( const std::string filepath)
{
    image im;

    //opening image
    std::ifstream s;
    s.open(filepath,std::ios::binary);
    /* if(!s)
    {
        std::cout << "not opened"<<std::endl;
        return im;
    }*/
    //else std::cout<<"opened"<<std::endl;

    s>>im.format;//getting image format

    s>>im.cols;//getting number of columns

    s>>im.rows;//getting number of rows

    im.num_pixels=im.cols*im.rows; //getting number of pixels

    // std::cout<< "num of pixels "<<im.num_pixels<<std::endl;

    s>>im.maxVal;//getting maximum pixel value

    // std::cout<< "MAXVAL"<< im.maxVal<<std::endl;

    im.pixels_values.resize(im.num_pixels);//resizing the pixels vector
    s.ignore();

    // read the elements in the pixelsvalues into the vector
    for(unsigned int i = 0;i<im.num_pixels;i++)
    {
        s>>std::noskipws>>im.pixels_values[i];
    }
    /*
    if(im.num_pixels!=im.pixels_values.size()){
        std::cout<<"couldn't read all pixels"<<std::endl;
    }
    else std::cout <<"all has been read"<<std::endl;
    */
    s.close();

    return im;


}


#endif // READING_H
