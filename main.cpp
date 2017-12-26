#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip = decltype(std::make_tuple<int,int,int,int>(1,2,3,4));

//функция для  записи ip
void writeIp(ip Ip){
    std::cout<<std::get<0>(Ip)<<"."<<std::get<1>(Ip)<<"."<<std::get<2>(Ip)<<"."<<std::get<3>(Ip)<<std::endl;
}

std::vector<std::string> split(const std::string &str, char d)
{
    auto r = std::vector<std::string>();

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
//form std::vector<std::string> to  tuple
auto ipTuple(std::vector<std::string> && x)->decltype(std::make_tuple(1,2,3,4)) {
    return std::make_tuple(std::stoi(x.at(0)), std::stoi(x.at(1)), std::stoi(x.at(2)), std::stoi(x.at(3)));
}

//filter by first or first and second bytes and output
template <typename... Args>
void filter(std::vector<ip>::const_iterator b, std::vector<ip>::const_iterator e, Args ...args) {
    auto byteTuple = std::make_tuple(std::forward<Args>(args)...))); 
}

//filter by any byte and output
void filterAnyByte(std::vector<ip>::const_iterator b, std::vector<ip>::const_iterator e, int anyByte){
    std::for_each(b, e, [anyByte](ip x){
        if(std::get<0>(x) == anyByte || std::get<1>(x) == anyByte || std::get<2>(x) == anyByte || std::get<3>(x) == anyByte) {
            writeIp(x);
        }
    });
}

int main(int argc, char const *argv[])
{
    try
    {
        auto ip_pool= std::vector<ip>();

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(ipTuple(split(v.at(0), '.')));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(),
                  [](ip x, ip y)->bool{return x>y;});
                  
        std::for_each(ip_pool.begin(), ip_pool.end(), [](ip x){writeIp(x);});
       
        filter(ip_pool.cbegin(), ip_pool.cend(), 1);
        filter(ip_pool.cbegin(), ip_pool.cend(), 46, 70);
        filterAnyByte(ip_pool.cbegin(), ip_pool.cend(), 46);
        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
