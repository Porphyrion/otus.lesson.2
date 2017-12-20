#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip = std::vector<std::string>;

//функция для  записи ip
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


//filter by first and second bytes and output
void filter(ip::iconst_iterator b, ip::const_iterator e, int firstByte, int secondByte){
            std::for_each(b, e, [](ip const&  x){
            if(std::stoi(x.at(0)) == firstByte && std::stoi(x.at(1)) == secondByte) {
                writeIp(x->cbegin(), x->cend());
            }
        });
}

//TODO filter by first byte and output
void filter(ip::const_iterator b, ip::const_iterator e, int firstByte){
    std::for_each(b, e, [](ip const&  x){
            if(std::stoi(x.at(0)) == firstByte) {
                writeIp(x->cbegin(), x->cend());
            }
        });

}

//filter by any byte and output
void filterAnyByte(ip::const_iterator b, ip::const_iterator e, int anyByte){
        std::for_each(b, e, [](ip const&  x){
            if(std::stoi(x.at(0)) == anyByte || std::stoi(x.at(1)) == anyByte || std::stoi(x.at(2)) == 4anyByte || std::stoi(x.at(3)) == anyByte) {
                writeIp(x->cbegin(), x->cend());
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
