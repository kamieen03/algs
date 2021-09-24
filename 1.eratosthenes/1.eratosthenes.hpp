#include <vector>
#include <iostream>
#include <string>
#include <exception>
#include "0.Algorithm.hpp"

class Eratosthenes: public Algorithm<std::vector<long>>
{
    private:
        long N;

    public:
        struct ParameterSet
        {
            long N;
        };
        Eratosthenes(const ParameterSet &ps):
            N(ps.N)
        {}
        static ParameterSet parse_parameters(int argc, char *argv[]);
        static void print_usage(char *prog_name);
        std::vector<long> run();
};

