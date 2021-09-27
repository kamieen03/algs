#include "2.convex_hull.hpp"


void ConvexHull::print_usage(char *prog_name)
{
    std::cerr << "Usage: " << prog_name << " file_path\n";
    std::cerr << "file_path - path to file contatining data points of the format\n";
    std::cerr << "x0 y0\nx1 y1\nx2 y2\n..." << std::endl;
}

Dataset ConvexHull::read_datafile(std::ifstream &file)
{
    Dataset datapoints;
    float x, y;
    while(true)
    {
        file >> x;
        if(file.eof()) break;
        file >> y;
        Point *p = new Point(x,y);
        datapoints.push_back(std::shared_ptr<Point>(p));
    }
    return datapoints;
}

ConvexHull::ParameterSet ConvexHull::parse_parameters(int argc, char *argv[])
{
    if (argc != 2)
    {
        ConvexHull::print_usage(argv[0]);
        throw std::runtime_error("Wrong number of arguments");
    }

    try
    {
        std::ifstream infile;
        infile.open(argv[1], std::ifstream::in);
        Dataset datapoints = read_datafile(infile);
        infile.close();
        ConvexHull::ParameterSet ps;
        ps.datapoints = datapoints;
        return ps;
    }
    catch(std::exception& e)
    {
        ConvexHull::print_usage(argv[0]);
        throw std::runtime_error("Couldn't read the file");
    }
}

float ConvexHull::det(const std::shared_ptr<Point> &p,
          const std::shared_ptr<Point> &p1,
          const std::shared_ptr<Point> &p2)
{
    float x1 = p->first - p1->first;
    float x2 = p2->first - p1->first;
    float y1 = p->second - p1->second;
    float y2 = p2->second - p1->second;
    return x1*y2 - x2*y1;
}

Dataset ConvexHull::split(const std::shared_ptr<Point> &p1,
                          const std::shared_ptr<Point> &p2,
                          const Dataset &datapoints)
{
    Dataset new_datapoints;
    for (const auto &p : datapoints)
    {
        if (det(p, p1, p2) < 0)
        {
            new_datapoints.push_back(p);
        }
    }
    return new_datapoints;
}

void ConvexHull::extend(const std::shared_ptr<Point> &p1,
               const std::shared_ptr<Point> &p2,
               const Dataset &datapoints)
{
    if (datapoints.size() == 0)
    {
        return;
    }
    auto furthest_point = *std::min_element(datapoints.begin(), datapoints.end(),
            [&p1, &p2, this](const auto &q1, const auto &q2) {return det(q1,p1,p2) < det(q2,p1,p2);});
    solution.push_back(furthest_point);

    Dataset left_part = split(p1, furthest_point, datapoints);
    extend(p1, furthest_point, left_part);
    Dataset right_part = split(furthest_point, p2, datapoints);
    extend(furthest_point, p2, right_part);
}

Dataset ConvexHull::run()
{
    auto left_point = *std::min_element(datapoints.begin(), datapoints.end(),
            [](const auto &p1, const auto &p2) {return p1->first < p2->first;});
    auto right_point = *std::max_element(datapoints.begin(), datapoints.end(),
            [](const auto &p1, const auto &p2) {return p1->first < p2->first;});
    Dataset left_part = split(left_point, right_point, datapoints);
    Dataset right_part = split(right_point, left_point, datapoints);
    solution.push_back(left_point);
    solution.push_back(right_point);

    extend(left_point, right_point, left_part);
    extend(right_point, left_point, right_part);

    return solution;
}

int main(int argc, char *argv[])
{
    try
    {
        ConvexHull::ParameterSet ps = ConvexHull::parse_parameters(argc, argv);
        ConvexHull ch(ps);
        Dataset convex_hull = ch.run();
        for (const auto &p : convex_hull)
        {
            std::cout << p->first << " " << p->second << "\n";
        }
        std::cout << std::flush;
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

