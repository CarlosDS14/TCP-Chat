#include "Package.h"
#include <iostream>
#include <thread>
#include <vector>
#include <boost/asio.hpp>

int command(std::string command);
void HelpCommand();
void SearchFunc(std::string user);
void TESTCommand();
void ExceptionMessage(const std::string e, const bool boost_error);

const std::string serverip = "127.0.0.1";
const int serverport = 45455;

int main(int argc, char* argv[])
{
    if (argv[1] == "")
    {
        return 3;
    }
    switch (command(std::string(argv[1])))
    {
        case 0:
            SearchFunc(std::string(argv[2]));
            break;
        case 5:
            if (argc > 2)
            {
                std::cout<<"Error using broom, incorrect number of arguments for parameter -h"<<std::endl;
                break;
            }
            HelpCommand();
            break;
        case 255:
            TESTCommand();
            break;
        default:
            std::cout<<"No parameter \""<<argv[1]<<"\" exist!"<<std::endl;
            std::cout<<"Type \"broom -h\" for help"<<std::endl;
            break;
    }

    return 0;
}

int command(std::string command)
{
    if (command == "-h") return 5;
    else if (command == "-s") return 0;
    else if (command == "-TEST") return 255;
    else return -1;
}

void HelpCommand()
{
    std::cout<<"All prefixes:"<<std::endl;
    std::cout<<"  -h   Help page"<<std::endl;
    std::cout<<"  -s [User] Search a user"<<std::endl;
}

void SearchFunc(std::string user)
{
    char buffer[1024];
    boost::system::error_code error_code;
    try
    {
        std::memset(buffer, 0, sizeof(buffer));
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(serverip, std::to_string(serverport));
        boost::asio::connect(socket, endpoints, error_code);
        Package Searchuser(5, user);
    }
    catch (const boost::system::error_code& e)
    {
        ExceptionMessage(e.what(), true);
    }
    catch (const std::exception& e)
    {
        ExceptionMessage(e.what(), false);
    }
}

void TESTCommand()
{
    char buffer[1024];
    try
    {
        std::memset(buffer, 0, sizeof(buffer));
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(serverip, std::to_string(serverport));
        boost::asio::connect(socket, endpoints);
        Package TestData(3, "This is a test");
        std::string SerializedData = TestData.serialize();
        boost::asio::write(socket, boost::asio::buffer(SerializedData));
        TestData.~Package();

        size_t length_data = socket.read_some(boost::asio::buffer(buffer));
        Package serverData = Package::deserialize(std::string(buffer, length_data));
        std::cout<<"\nMessage recived from server:"<<std::endl;
        std::cout<<"Type: "<<serverData.GetType()<<std::endl;
        std::cout<<"Data: "<<serverData.GetData()<<'\n'<<std::endl;
        std::cout<<"Destroying package..."<<std::endl;
        serverData.~Package();
        std::cout<<"Data destroyed!"<<std::endl;
    }
    catch (const std::exception& e)
    {
        ExceptionMessage(e.what(), false);
    }
}

void ExceptionMessage(const std::string e, const bool boost_error)
{
    if (boost_error)
    {
        switch (boost_error)
        {
            default:
                std::cout<<"Un error desconocido ha ocurrido con la conexion!\n<--------------------------------->\n"<<e<<"\n<--------------------------------->"<<std::endl;
        }
    }
    else
    {
        std::cout<<"Una excepcion desconocida ha ocurrido!\n<--------------------------------->\n"<<e<<"\n<--------------------------------->"<<std::endl;
    }
}