#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>
#include <memory>
#include "0.Algorithm.hpp"

typedef std::pair<float,float> Point;
typedef std::vector<std::shared_ptr<Point> > Dataset;

class ConvexHull: public Algorithm<Dataset> {
    private:
        // Input data
        Dataset datapoints;

        // Holds convex hull Points
        Dataset solution;

        // Reads in @file and turns it into Dataset
        static Dataset read_datafile(std::ifstream &file);

        // Computes determinant of a 2x2 matrix formed using @p, @p1 and @p2
        float det(const std::shared_ptr<Point> &p,
                  const std::shared_ptr<Point> &p1,
                  const std::shared_ptr<Point> &p2);

        // Returns the part of @datapoints on the left side of the line from @p1
        // to @p2
        Dataset split(const std::shared_ptr<Point> &p1,
                      const std::shared_ptr<Point> &p2,
                      const Dataset &datapoints);

        // Computes the furthest point in @datapoints from the line from @p1 to
        // @p2 and uses it as split point for further computation
        void extend(const std::shared_ptr<Point> &p1,
                    const std::shared_ptr<Point> &p2,
                    const Dataset &datapoints);
    public:
        struct ParameterSet: public Algorithm::ParameterSet
        {
            Dataset datapoints;
        };
        ConvexHull(const ParameterSet &ps):
            datapoints(ps.datapoints),
            Algorithm::Algorithm<Dataset>(ps)
        {}
        static ParameterSet parse_parameters(int argc, char *argv[]);
        static void print_usage(char *prog_name);
        Dataset run();
};
