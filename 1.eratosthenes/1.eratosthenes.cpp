#include "1.eratosthenes.hpp"

void Eratosthenes::print_usage(char *prog_name)
{
    std::cerr << "Usage: " << prog_name << " N\n";
    std::cerr << "N - natural number, biggest number checked for primality\n";
}

Eratosthenes::ParameterSet Eratosthenes::parse_parameters(int argc, char *argv[])
{
    if (argc != 2)
    {
        Eratosthenes::print_usage(argv[0]);
        throw std::runtime_error("Wrong number of arguments");
    }

    try
    {
        const long N = std::stol(argv[1]);
        ParameterSet ps;
        ps.N = N;
        return ps;
    }
    catch(std::exception& e)
    {
        Eratosthenes::print_usage(argv[0]);
        throw std::runtime_error("Wrong argument provided");
    }
}

std::vector<long> Eratosthenes::run()
{
    std::vector<bool> is_prime(N, true);
    std::vector<long> primes {2};
    is_prime[0] = false;
    is_prime[1] = false;
    long i = 3;
    while (i <= N/2+1)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            for(long j = i*i; j <= N; j += i)
            {
                is_prime[j] = false;
            }
        }
        i += 2;
    }
   return primes;
}

int main(int argc, char *argv[])
{
    try{
        auto ps = Eratosthenes::parse_parameters(argc, argv);
        Eratosthenes er(ps);
        const std::vector<long> primes = er.run();
        for (const long &p : primes)
        {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

