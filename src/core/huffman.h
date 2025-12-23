#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <queue>
#include <map>
#include "freq_map.h"
#include <bitset>
#include <string>
#include <vector>


// a tree node
struct Node
{
    uint8_t pixel;
    int freq;
    Node *left, *right;
};

// function to allocate a new node
Node* getnode (uint8_t pixel, int freq, Node* left, Node* right)
{
    Node* node = new Node();
    node->pixel = pixel;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}
//comparison object to be used to order the heap
struct comp
{
    bool operator()(Node* l, Node* r)
    {
        //highest priority item has lowest frequency
        return l->freq > r->freq;

    }
};
//traverse the huffman tree and store huffman codes in a map
void encode(Node* root, std::string str, std::map<uint8_t , std::string> &huffmanCode)
{
    if (root== nullptr)
        return;
    // found a leaf node
    if (!root->left && !root->right)
    {
        huffmanCode[root->pixel] = str;
    }
    encode(root->left , str +"0" , huffmanCode);
    encode(root->right , str + "1", huffmanCode);

}

// Builds Huffman tree and decode the input
std::map<uint8_t, std::string> buildhuffmanTree( std::map<uint8_t,int> freq_map)
{
    //creating a priority queue to store leaf nodes of huffmantree
    std::priority_queue<Node* , std::vector<Node*> , comp >Pq;

    //create a leaf node for each character and add it to the priority_queue
    for(auto pair: freq_map) {
        Pq.push(getnode(pair.first , pair.second , nullptr , nullptr));
    }

    //do it till there's more than 1 node in the queue
    while( Pq.size() != 1 )
    {
        //Removing the two nodes of the highest priority from the queue
        Node* left= Pq.top();
        Pq.pop();
        Node* right= Pq.top();
        Pq.pop();

        //create new internal node as parent of those two nodes
        // its frequency is the sum of their frequency
        //add this node to the priority_queue
        int sum = left->freq + right->freq;
        Pq.push(getnode( '\0' , sum , left , right));
    }

    // root stores pointer to root of huffmantree
    Node* root = Pq.top();

    //transverse the huffmantree and store the code in the map
    std::map<uint8_t , std::string > huffmanCode;
    encode (root , "" , huffmanCode);

    //print huffman Code
    /* cout << " Huffman codes are :\n" << '\n';
    for (auto pair: huffmanCode){
        cout << pair.first << " " << pair.second << '\n';
    }*/
    return huffmanCode;
}

//get the compressed code of the image
std::string bits_string (std::vector <uint8_t> image,  std::map <uint8_t , std::string > hCode){
    std::string bits_string="";
    //cout << " bits string  :  ";
    for(auto pixel : image){
        //  std::cout << hCode.at(ch);
        bits_string += hCode.at(pixel);
    }
    return bits_string;
}

//converting bits string to bytes array
std::vector <uint8_t> bytes_array (std::string bits_string){
    unsigned int remaining_bits = (8-(bits_string.size()%8));
    std::string temp="";
    std::vector <uint8_t> bytes_array ;
    for(auto b :bits_string){
        temp.push_back(b);
        if(temp.size()==8){
            std::bitset<8> byte(temp);
            bytes_array.push_back(uint8_t(byte.to_ulong()));
            temp.clear();
        }
    }
    if(remaining_bits==8){
        // std::cout<<"no remaining"<<std::endl;
        // std::cout<< "compressed size :   "<<bytes_array.size()<<std::endl;
        return bytes_array;

    }

    else{
        for(int i =0 ;i<remaining_bits;i++)
        {
            temp.push_back('0');
        }
        std::bitset<8> remaining_byte (temp);
        bytes_array.push_back(uint8_t(remaining_byte.to_ulong()));
    }



    // std::cout<< "compressed size :   "<<bytes_array.size()<<std::endl;

    //printing bytes_array
    /*
      for(auto i: bytes_array)
      {
          std::cout<<i <<" ";
      }
      */
    return bytes_array;

}
#endif // HUFFMAN_H
