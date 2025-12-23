#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<unordered_map>
#include<QFileDialog>
#include<QMessageBox>
#include "reading.h"
#include<map>
#include<QLabel>
#include "huffman.h"
#include<deserilize.h>
#include<Decoding.h>
#include<iostream>
#include <fstream>
#include <vector>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this,tr("choose"),"",tr("images(*.pgm)"));
     image pgm_read (const std::string);


        QString name = filename;
        std::string text = name.toUtf8().constData();
        image im = pgm_read (text );

        std::map<uint8_t,int> Frequency = freq_map (im.pixels_values);

        std::map<uint8_t,std::string> huffmanCode = buildhuffmanTree( Frequency);

        std::string compressed_string = bits_string(im.pixels_values,huffmanCode);

        std::vector <uint8_t> compressed_bytes = bytes_array(compressed_string);


        //serilizing compressed image

        std::ofstream out;
        out.open("encoded.enc", std::ios::out | std::ios::binary);
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

    QString message="your image has been compressed into .enc file.....check your Build GUI directory";
    QMessageBox::information(this,"compression completed",message);

}

void MainWindow::on_pushButton_2_clicked()
{
    QString message="choose encoded.enc file";
    QMessageBox::information(this,"instructions to decompress",message);

    QString filename= QFileDialog::getOpenFileName(this,tr("choose"),"",tr("images(*.enc)"));
    QString name = filename;
    std::string text = name.toUtf8().constData();
    image pgm_read (const std::string);
    image im = pgm_read (text );
    deserillized compressed_data= deserilize(text);
    std::vector <uint8_t> decoded = decode( compressed_data.freq_map, &compressed_data.bits_string);
    std::ofstream image_out;
    image_out.open("image.pgm", std::ios::out | std::ios::binary);
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

   if(QString::compare("image.pgm",QString())!=0){
        QImage image;
        bool valid=image.load("image.pgm");
        if(valid){
           ui->label->setPixmap(QPixmap::fromImage(image));
       }else{
           // error handling
        }
    }
image_out.close();


    ui->label_6->setText("Width: "+QString::number(im.cols));
    ui->label_7->setText("Height "+QString::number(im.rows));

    //int compression_ratio = ((im.pixels_values.size() / (compressed_data.bytes_array_size))) ;
    //ui->label_8->setText("Compression ratio: "+QString::number(compression_ratio * 100) +"%" );




}
