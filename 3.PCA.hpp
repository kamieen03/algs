#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <vector>
#include <algorithm>
#include <numeric>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "0.Algorithm.hpp"

class PCA: public Algorithm<Eigen::MatrixXf>
{
    private:
        Eigen::MatrixXf X;
        Eigen::MatrixXf eigenvectors;
        Eigen::VectorXf eigenvalues;

        static Eigen::MatrixXf read_datafile(std::ifstream &file);

    public:
        struct ParameterSet
        {
            Eigen::MatrixXf X;
        };
        PCA(const ParameterSet &ps):
            X(ps.X)
        {}
        static ParameterSet parse_parameters(int argc, char *argv[]);
        static void print_usage(char *prog_name);
        Eigen::MatrixXf run();
        Eigen::VectorXf get_eigenvalues() {return Eigen::MatrixXf(eigenvalues);};
        Eigen::MatrixXf get_eigenvectors() {return Eigen::MatrixXf(eigenvectors);};

};

