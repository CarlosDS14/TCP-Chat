#include "Package.h"

Package::Package(uint8_t type, std::string data) : type_(type), data_(data) {}

uint8_t Package::GetType() const {return type_;}
const std::string& Package::GetData() const {return data_;}

std::string Package::serialize()
{
    std::ostringstream oss;
    boost::archive::binary_oarchive oa(oss);
    oa << *this;
    return oss.str();
}

Package Package::deserialize(const std::string& data)
{
    std::istringstream iss(data);
    boost::archive::binary_iarchive ia(iss);
    Package package;
    ia >> package;
    return package;
}