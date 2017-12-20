#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tie>

using ip = std::vector<std::string>;

void writeIp(ip::const_iterator beginIp ,ip::const_iterator endIp){
    for(auto ip_part = beginIp; ip_part!=endIp; ++ip_part){
        if (ip_part != beginIp)
        {
            std::cout << ".";
        }
        std::cout << *ip_part;
    }
    std::cout << std::endl;
}

ip split(const std::string &str, char d)
{
    auto r = ip();

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

auto ipTuple(ip x)->decltype(std::make_tuple(1,2,3,4)) {
    return std::make_tuple(std::stoi(x.at(0)), std::stoi(x.at(1)), std::stoi(x.at(2)), std::stoi(x.at(3)));
}

int main(int argc, char const *argv[])
{
    try
    {
        auto ip_pool= std::vector<ip>();

        for(std::string line; std::getline(std::cin, line);)
        {
            ip v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(),
                  [](ip x, ip y)->bool{return ipTuple(x)>ipTuple(y)};

        for(auto ip_ = ip_pool.cbegin(); ip_ != ip_pool.cend(); ++ip_)
        {
            writeIp(ip_->cbegin(), ip_->cend());
        }

        
        std::for_each(ip_pool.begin(), ip_pool.end(), [](std::vector<std::string> const&  x){
            if(std::stoi(x.at(0)) == 1) {
                writeIp(x->cbegin(), x->cend());
            }
        });


        std::for_each(ip_pool.begin(), ip_pool.end(), [](std::vector<std::string> const&  x){
            if(std::stoi(x.at(0)) == 46 && std::stoi(x.at(1)) == 70) {
                writeIp(x->cbegin(), x->cend());
            }
        });


        std::for_each(ip_pool.begin(), ip_pool.end(), [](std::vector<std::string> const&  x){
            if(std::stoi(x.at(0)) == 46 || std::stoi(x.at(1)) == 46 || std::stoi(x.at(2)) == 46 || std::stoi(x.at(3)) == 46) {
                writeIp(x->cbegin(), x->cend());
            }
        });

        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
