#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip = std::vector<int>;
using string_ip = std::vector<std::string>;

//функция для  записи ip
void writeIp(ip anyIp){
    for(auto i = anyIp.begin();i!=anyIp.end();i++ ){
        if(i!=anyIp.begin()){
            std::cout<<"."<<*i;
        } else{
            std::cout<<*i;
        }
    }
    std::cout<<std::endl;
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

//from std::vector<std::string>  to std::vector<int>
ip ipIntVector(string_ip && x) {
    auto rez = ip{};
    for(auto i : x){
        rez.push_back(std::stoi(i));
    }
    return rez;
}

//filter by first or first and second bytes and output
template <class ... Args>
void filter(std::vector<ip>::const_iterator b, std::vector<ip>::const_iterator e, Args ... args) {

    auto x = std::vector<int>{(args)...};
    std::for_each(b, e , [x](ip someIp){
        for (int i = 0; i < x.size(); ++i){
            if(x.at(i) != someIp.at(i))  return;
        }
        writeIp(someIp);
    });
}

//filter by any byte and output
void filterAnyByte(std::vector<ip>::const_iterator b, std::vector<ip>::const_iterator e, int anyByte){

    std::for_each(b, e, [anyByte](ip x){
        if(std::any_of(x.begin(),x.end(), [anyByte](int byte){ return byte == anyByte; }) ){
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
            string_ip v = split(line, '\t');
            ip_pool.push_back(ipIntVector(split(v.at(0), '.')));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(),std::greater<ip>());
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
