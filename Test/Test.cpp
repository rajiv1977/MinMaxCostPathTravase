
#include "MinMaxCostPathTravase.h"

int main(void)
{
    // Generate random matrix
    // Given matrix
    int row        = 4;
    int col        = 4;
    int martixSize = row * col;

    // generate a random gaussian random matrix
    const int nrolls = 10000; // number of experiments
    const int nstars = 100;   // maximum number of stars to distribute

    std::default_random_engine            generator;
    std::chi_squared_distribution<double> distribution(4.5);

    map<int, int> mapi = {};
    for (int i = 0; i < nrolls; ++i)
    {
        int number = distribution(generator);
        if (number < martixSize)
            mapi[number]++;
    }

    vector<int> vmap = {};
    for (const auto& m : mapi)
    {
        vmap.push_back(m.second);
    }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(vmap.begin(), vmap.end(), std::default_random_engine(seed));

    vector<vector<int>> A = {};
    vector<int>         a = {};
    for (const auto& v : vmap)
    {
        a.push_back(v);
        if (a.size() == row)
        {
            A.push_back(a);
            a = {};
        }
    }

    // print intput:
    for (auto& a : A)
    {
        copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
        cout << "\n" << endl;
    }
    cout << "\n" << endl;

    auto                  selectedNodes = MinMaxCostPathTravase::Node::minMaxPathTravasedNodes(A);
    vector<array<int, 3>> paths         = {};
    vector<int>           collect       = {};
    if (MinMaxCostPathTravase::Node::extractPath(selectedNodes, paths))
    {
        for (const auto& p : paths)
        {
            cout << p[0] << " " << p[1] << " " << p[2] << endl;
            collect.push_back(p[2]);
        }
    }
    cout << " " << endl;
    cout << accumulate(collect.begin(), collect.end(), 0) << endl;

    return EXIT_SUCCESS;
}
