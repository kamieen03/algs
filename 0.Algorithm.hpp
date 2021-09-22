template <typename T>
class Algorithm
{
    public:
        struct ParameterSet{};
        Algorithm(const ParameterSet&){};
        static void print_usage(char *prog_name);
        static ParameterSet parse_parameters(int argc, char* argv[]);
        virtual T run() = 0;
};

