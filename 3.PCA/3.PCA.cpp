#include "3.PCA.hpp"

void PCA::print_usage(char *prog_name)
{
    std::cerr << "Usage: " << prog_name << "file_path\n";
    std::cerr << "file_path - path to data file storing matrix row by row";
    std::cerr << " with numbers separated by spaces" << std::endl;
}

Eigen::MatrixXf PCA::read_datafile(std::ifstream &file)
{
    int rows, cols;
    file >> rows;
    file >> cols;
    Eigen::MatrixXf X(rows, cols);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            file >> X(i,j);
    return X;
}



PCA::ParameterSet PCA::parse_parameters(int argc, char *argv[])
{
    if (argc != 2)
    {
        PCA::print_usage(argv[0]);
        throw "Wrong number of arguments";
    }

    try
    {
        std::ifstream file;
        file.open(argv[1]);
        auto X = read_datafile(file);
        file.close();
        ParameterSet ps;
        ps.X = X;
        return ps;
    }
    catch(std::exception& e)
    {
        PCA::print_usage(argv[0]);
        throw "Wrong argument provided";
    }
}



Eigen::MatrixXf PCA::run()
{
    // zero-mean and compute covariance matrix
    X.rowwise() -= X.colwise().mean();
    Eigen::MatrixXf C = X.transpose()*X / X.rows();
    Eigen::EigenSolver<Eigen::MatrixXf> es(C);

    // get eigenvalues and sort them in descending order
    Eigen::VectorXf evs = Eigen::real(es.eigenvalues().array());
    std::vector<int> idx(evs.size());
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(),       // argsort
            [&evs](int left, int right) {
                return evs(left)>evs(right);
            });
    Eigen::VectorXf sorted_evs(evs.size());
    for (size_t i = 0; i < idx.size(); i++)
        sorted_evs(i) = evs(idx[i]);

    // sort eigenvectors according to the same order
    Eigen::MatrixXf evecs = Eigen::real(es.eigenvectors().array());
    Eigen::MatrixXf sorted_evecs(evecs.rows(), evecs.cols());
    for (size_t i = 0; i < idx.size(); i++)
        sorted_evecs.col(i) = evecs.col(idx[i]);

    // transform data and save eigens
    X = X*sorted_evecs;
    eigenvalues = sorted_evs;
    eigenvectors = sorted_evecs;

    return X;
}

int main(int argc, char *argv[])
{
    auto ps = PCA::parse_parameters(argc, argv);
    PCA er(ps);
    std::cout << er.run() << "\n\n";
    std::cout << er.get_eigenvalues() << "\n\n";
    std::cout << er.get_eigenvectors() << std::endl;
    return 0;
}

