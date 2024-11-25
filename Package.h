#ifndef PACKAGE_H
#define PACKAGE_H

#include <iostream>
#include <string>
#include <sstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/access.hpp>

class Package
{
    public:
        Package() = default;
        Package(uint8_t type, std::string data);
        ~Package() = default;

        std::string serialize();
        static Package deserialize(const std::string& data);

        uint8_t GetType() const;
        const std::string& GetData() const;
    private:
        uint8_t type_;
        std::string data_;

        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & type_;
            ar & data_;
        }
};

#endif // PACKAGE_H