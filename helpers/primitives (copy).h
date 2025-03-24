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
class MiniTx{
public:
    uint256 hash;
    uint64_t size;
    uint64_t vsize;
    vector<TxIn*> txins;
    MiniTx(string h, uint64_t s, uint64_t vs){
        hash = uint256S(h);
        size = s;
        vsize = vs;
    };
    string toString(){
        string str = "{\n";
        str += "\t\t\t\'hash\': "; str += "\'"; str += hash.ToString(); str += "\',\n";
        str += "\t\t\t\'size\': ";  str += to_string(size); str += ",\n";
        str += "\t\t\t\'vsize\': ";  str += to_string(vsize); str += ",\n";
        str += "\t\t\t\'TxIns\': "; str += "["; str += to_string(txins.size()); str += "]\n";
        str += "\n\t\t}";
        return str;
    }
};
class Block {
public:
    uint256 hash;
    uint256 coinbasetxhash;
    vector<MiniTx*> txs;
    uint64_t size;
    uint64_t time;
    uint64_t mediantime;
    Block(string h, uint64_t s, uint64_t t, uint64_t mt){
        hash = uint256S(h); size = s; time = t; mediantime = mt;
    };
    string toString(){
        string str = "{\n";
        str += "\t\'hash\': "; str += "\'"; str += hash.ToString(); str += "\',\n";
        str += "\t\'time\': ";  str += to_string(time); str += ",\n";
        str += "\t\'size\': ";  str += to_string(size); str += ",\n";
        str += "\t\'mediantime\': ";  str += to_string(mediantime); str += ",\n";
        str += "\t\'txs\': ["; 
        for (auto t : txs)
            str += "\n\t\t" + t->toString();
        str += "]\n";
        str += "}\n";
        return str;
    }
};


class Exit_Tx{
    string type;
    string reason;
    uint256 hash;
	uint64_t ancestor_count;
	uint64_t descendant_count;
	uint64_t ancestor_fee;
	uint64_t descendant_fee;
	uint64_t ancestor_size;
	uint64_t descendant_size;
    uint64_t size;
	uint64_t amount;
    uint64_t fee;
    string time;
    vector<TxIn *> vtxin;

public:
    Exit_Tx(){}

    Exit_Tx(string type, string reason, string hash_str, uint64_t ancestor_count, uint64_t descendant_count,
       uint64_t ancestor_fee, uint64_t descendant_fee, uint64_t ancestor_size, uint64_t descendant_size, uint64_t size,
       uint64_t amount, uint64_t fee, string time) :                              type(type),
                                                                                    reason(reason),
                                                                                    ancestor_count(ancestor_count),
                                                                                    descendant_count(descendant_count),
                                                                                    ancestor_fee(ancestor_fee),
                                                                                    descendant_fee(descendant_fee),
                                                                                    ancestor_size(ancestor_size),
                                                                                    descendant_size(descendant_size),
                                                                                    size(size), amount(amount),
                                                                                    fee(fee), time(time){
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

    uint64_t getAncestor_count() const {
        return ancestor_count;
    }

    uint64_t getDescendant_count() const {
        return descendant_count;
    }

    uint64_t getAncestor_fee() const {
        return ancestor_fee;
    }

    uint64_t getDescendant_fee() const {
        return descendant_fee;
    }

    uint64_t getAncestor_size() const {
        return ancestor_size;
    }

    uint64_t getDescendant_size() const {
        return descendant_size;
    }

    uint64_t getSize() const {
        return size;
    }

    uint64_t getAmount() const {
        return amount;
    }

    uint64_t getFee() const {
        return fee;
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
                          +string("\t\"reason\": ") + "\""+this->getReason()+"\"" + ",\n"
                          + string("\t\"hash\": ") + "\"" + this->getHash().ToString() + "\"" + ",\n"
                          + string("\t\"ancestor_count\": ") + to_string(this->getAncestor_count()) + string(",\n")
                          + string("\t\"descendant_count\": ") + to_string(this->getDescendant_count()) + string(",\n")
                          + string("\t\"ancestor_fee\": ") + to_string(this->getAncestor_fee()) + string(",\n")
                          + string("\t\"descendant_fee\": ") + to_string(this->getDescendant_fee()) + string(",\n")
                          + string("\t\"ancestor_size\": ") + to_string(this->getAncestor_size()) + string(",\n")
                          + string("\t\"descendant_size\": ") + to_string(this->getDescendant_size()) + string(",\n")
                          + string("\t\"time\": ") + this->getTime() + ",\n"
                          + string("\t\"size\": ") + to_string(this->getSize()) + ",\n"
                          + string("\t\"amount\": ") + to_string(this->getAmount()) + ",\n"
                          + string("\t\"fee\":") + to_string(this->getFee()) + ",\n"
                          + string("\t\"TxIn\": ") + " [ " + to_string(this->getvTxIn().size()) + " ]\n"
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
	uint64_t ancestor_count;
	uint64_t descendant_count;
	uint64_t ancestor_fee;
	uint64_t descendant_fee;
	uint64_t ancestor_size;
	uint64_t descendant_size;
    uint64_t size;
	uint64_t amount;
    uint64_t fee;
    string time;
    vector<TxIn *> vtxin;

public:
    Tx(){}

    Tx(string type, string hash_str, uint64_t ancestor_count, uint64_t descendant_count,
       uint64_t ancestor_fee, uint64_t descendant_fee, uint64_t ancestor_size, uint64_t descendant_size, uint64_t size,
       uint64_t amount, uint64_t fee, string time) : type(type),
                                                                                    ancestor_count(ancestor_count),
                                                                                    descendant_count(descendant_count),
                                                                                    ancestor_fee(ancestor_fee),
                                                                                    descendant_fee(descendant_fee),
                                                                                    ancestor_size(ancestor_size),
                                                                                    descendant_size(descendant_size),
                                                                                    size(size), amount(amount),
                                                                                    fee(fee), time(time){
                                                                                        hash = uint256S(hash_str);
                                                                                    }

    const string &getType() const {
        return type;
    }

    const uint256 &getHash() const {
        return hash;
    }

    uint64_t getAncestor_count() const {
        return ancestor_count;
    }

    uint64_t getDescendant_count() const {
        return descendant_count;
    }

    uint64_t getAncestor_fee() const {
        return ancestor_fee;
    }

    uint64_t getDescendant_fee() const {
        return descendant_fee;
    }

    uint64_t getAncestor_size() const {
        return ancestor_size;
    }

    uint64_t getDescendant_size() const {
        return descendant_size;
    }

    uint64_t getSize() const {
        return size;
    }

    uint64_t getAmount() const {
        return amount;
    }

    uint64_t getFee() const {
        return fee;
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
                          + string("\t\"ancestor_count\": ") + to_string(this->getAncestor_count()) + string(",\n")
                          + string("\t\"descendant_count\": ") + to_string(this->getDescendant_count()) + string(",\n")
                          + string("\t\"ancestor_fee\": ") + to_string(this->getAncestor_fee()) + string(",\n")
                          + string("\t\"descendant_fee\": ") + to_string(this->getDescendant_fee()) + string(",\n")
                          + string("\t\"ancestor_size\": ") + to_string(this->getAncestor_size()) + string(",\n")
                          + string("\t\"descendant_size\": ") + to_string(this->getDescendant_size()) + string(",\n")
                          + string("\t\"time\": ") + this->getTime() + ",\n"
                          + string("\t\"size\": ") + to_string(this->getSize()) + ",\n"
                          + string("\t\"amount\": ") + to_string(this->getAmount()) + ",\n"
                          + string("\t\"fee\":") + to_string(this->getFee()) + ",\n"
                          + string("\t\"TxIn\": ") + " [ " + to_string(this->getvTxIn().size()) + " ]\n"
                          + "}\n\n";
        return log;
    }

    bool operator < (const Tx& othertx) const
    {
        
        return this->getHash().GetCheapHash() < othertx.getHash().GetCheapHash();

    }

};
