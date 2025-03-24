#pragma once
#include <cstdint>
#include <string>
#include <functional> //for std::hash
#include <vector>
#include <iostream>
#include "uint256.h"
using namespace std;

class TxIn{
	uint256 hash;
	uint64_t index;
public:
    TxIn(const string hash_str, uint64_t index) :  index(index) {
        hash = uint256S(hash_str);
    }

    const uint256 &getHash() const {
        return hash;
    }

    uint64_t getIndex() const {
        return index;
    }
    string toString(){
      return this->getHash().ToString() + to_string(this->getIndex());
    }
};

class Exit_Tx{
    string type;
    string reason;
    uint256 hash;
    string time;

public:
    Exit_Tx(){}

    Exit_Tx(string type, string reason, string hash_str, string time) :                              type(type),
                                                                                    reason(reason),
                                                                                    time(time){
                                                                                    hash = uint256S(hash_str);
                                                                                    }

    const string &getType() const {
        return type;
    }
  
    const string &getReason() const {
       return reason;
    }

    const uint256 &getHash() const {
        return hash;
    }


    string getTime() const {
        return time;
    }



    string toString(){
        std::string log = "{\n"
                          + string("\t\"type\": ") + "\""+this->getType()+"\"" + ",\n"
                          +string("\t\"reason\": ") + "\""+this->getReason()+"\"" + ",\n"
                          + string("\t\"hash\": ") + "\"" + this->getHash().ToString() + "\"" + ",\n"
                     
                          + string("\t\"time\": ") + this->getTime() + ",\n"
                      
                
                          + "}\n\n";
        return log;
    }

    bool operator < (const Exit_Tx& othertx) const
    {
        
        return this->getHash().GetCheapHash() < othertx.getHash().GetCheapHash();

    }

};

class Tx{
    string type;
    uint256 hash;
    string time;
    vector<TxIn *> vtxin;

public:
    Tx(){}

    Tx(string type, string hash_str, string time) : type(type), time(time) { hash = uint256S(hash_str);
                                                                                    }

    const string &getType() const {
        return type;
    }

    const uint256 &getHash() const {
        return hash;
    }


    string getTime() const {
        return time;
    }


    vector<TxIn *> &getvTxIn()  {
        return vtxin;
    }
    string toString(){
        std::string log = "{\n"
                          + string("\t\"type\": ") + "\""+this->getType()+"\"" + ",\n"
                          + string("\t\"hash\": ") + "\"" + this->getHash().ToString() + "\"" + ",\n"
              
                          + string("\t\"time\": ") + this->getTime() + ",\n"
                       
                          + string("\t\"TxIn\": ") + " [ " + to_string(this->getvTxIn().size()) + " ]\n"
                          + "}\n\n";
        return log;
    }

    bool operator < (const Tx& othertx) const
    {
        
        return this->getHash().GetCheapHash() < othertx.getHash().GetCheapHash();

    }

};
