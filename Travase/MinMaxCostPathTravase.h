#pragma once

#include <array>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iterator>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <vector>

using namespace std;

namespace MinMaxCostPathTravase
{
class Node
{
  public:
    int   mRow;
    int   mCol;
    int   mData;
    Node* mLeft;
    Node* mRight;
    Node* mDown;
    Node* mUp;
    int   mID;
    Node(int row, int col, int data)
        : mRow(row)
        , mCol(col)
        , mData(data)
        , mLeft(nullptr)
        , mRight(nullptr)
        , mDown(nullptr)
        , mUp(nullptr)
        , mID(-1) {};
    Node(int row, int col, int data, Node* left, Node* right, Node* down, Node* up, int& id)
        : mRow(row)
        , mCol(col)
        , mData(data)
        , mLeft(left)
        , mRight(right)
        , mDown(down)
        , mUp(up)
        , mID(id){};

    static Node* minMaxPathTravasedNodes(vector<vector<int>> data, string str = "max");
    static bool  extractPath(Node* node, vector<array<int, 3>>& paths);
};

Node* Node::minMaxPathTravasedNodes(vector<vector<int>> data, string str)
{
    int row    = 0;
    int col    = 0;
    int maxRow = static_cast<int>(data.size());
    int maxCol = static_cast<int>(data[0].size());

    int   direction = 1;
    Node* node      = new Node(row, col, data[0][0], nullptr, nullptr, nullptr, nullptr, direction);
    if (data.size() > 0)
    {
        queue<Node*> q;
        q.push(node);
        bool status = true;

        while (row < maxRow - 1)
        {
            direction++;
            Node* temp = q.front();
            q.pop();

            if (temp->mLeft == nullptr && temp->mRight == nullptr && temp->mDown == nullptr && row == 0 && col == 0)
            {
                vector<int> vec    = {data[row][col + 1], data[row + 1][col]};
                auto        minmax = minmax_element(vec.begin(), vec.end());
                int         id = (str.compare("min") == 0) ? minmax.first - vec.begin() : minmax.second - vec.begin();
                int         value = (str.compare("min") == 0) ? *minmax.first : *minmax.second;

                switch (id)
                {
                    case (0):
                        temp->mRight = new Node(row,
                                                col + 1,
                                                value,
                                                new Node(temp->mRow, temp->mCol, temp->mData),
                                                nullptr,
                                                nullptr,
                                                nullptr,
                                                direction);
                        row          = temp->mRight->mRow;
                        col          = temp->mRight->mCol;
                        q.push(temp->mRight);
                        break;
                    case (1):
                        temp->mDown = new Node(row + 1,
                                               col,
                                               value,
                                               nullptr,
                                               nullptr,
                                               nullptr,
                                               new Node(temp->mRow, temp->mCol, temp->mData),
                                               direction);
                        row         = temp->mDown->mRow;
                        col         = temp->mDown->mCol;
                        q.push(temp->mDown);
                        break;
                }
                status = false;
            }

            if (col > 0 && col < maxCol - 1 && status)
            {
                vector<int>   vec   = {};
                map<int, int> table = {};

                if (temp->mLeft == nullptr)
                {
                    table.insert(make_pair(data[row][col - 1], 0));
                    vec.push_back(data[row][col - 1]);
                }

                if (temp->mRight == nullptr)
                {
                    table.insert(make_pair(data[row][col + 1], 1));
                    vec.push_back(data[row][col + 1]);
                }

                if (temp->mDown == nullptr)
                {
                    table.insert(make_pair(data[row + 1][col], 2));
                    vec.push_back(data[row + 1][col]);
                }

                sort(vec.begin(), vec.end());
                if (str.compare("max") == 0)
                {
                    reverse(vec.begin(), vec.end());
                }

                int value = vec[0];
                switch (table[value])
                {
                    case (0):
                        temp->mLeft = new Node(row,
                                               col - 1,
                                               value,
                                               nullptr,
                                               new Node(temp->mRow, temp->mCol, temp->mData),
                                               nullptr,
                                               nullptr,
                                               direction);
                        row         = temp->mLeft->mRow;
                        col         = temp->mLeft->mCol;
                        q.push(temp->mLeft);
                        break;
                    case (1):
                        temp->mRight = new Node(row,
                                                col + 1,
                                                value,
                                                new Node(temp->mRow, temp->mCol, temp->mData),
                                                nullptr,
                                                nullptr,
                                                nullptr,
                                                direction);
                        row          = temp->mRight->mRow;
                        col          = temp->mRight->mCol;
                        q.push(temp->mRight);
                        break;
                    case (2):
                        temp->mDown = new Node(row + 1,
                                               col,
                                               value,
                                               nullptr,
                                               nullptr,
                                               nullptr,
                                               new Node(temp->mRow, temp->mCol, temp->mData),
                                               direction);
                        row         = temp->mDown->mRow;
                        col         = temp->mDown->mCol;
                        q.push(temp->mDown);
                        break;
                    default:
                        break;
                }
                status = false;
            }

            if (col == 0 && status)
            {
                int id    = 0;
                int value = data[row + 1][col];
                if (temp->mRight == nullptr)
                {
                    vector<int> vec    = {data[row + 1][col], data[row][col + 1]};
                    auto        minmax = minmax_element(vec.begin(), vec.end());
                    id    = (str.compare("min") == 0) ? minmax.first - vec.begin() : minmax.second - vec.begin();
                    value = (str.compare("min") == 0) ? *minmax.first : *minmax.second;
                }

                switch (id)
                {
                    case (0):
                        temp->mDown = new Node(row + 1,
                                               col,
                                               value,
                                               nullptr,
                                               nullptr,
                                               nullptr,
                                               new Node(temp->mRow, temp->mCol, temp->mData),
                                               direction);
                        row         = temp->mDown->mRow;
                        col         = temp->mDown->mCol;
                        q.push(temp->mDown);
                        break;
                    case (1):
                        temp->mRight = new Node(row,
                                                col + 1,
                                                value,
                                                new Node(temp->mRow, temp->mCol, temp->mData),
                                                nullptr,
                                                nullptr,
                                                nullptr,
                                                direction);
                        row          = temp->mRight->mRow;
                        col          = temp->mRight->mCol;
                        q.push(temp->mRight);
                        break;
                }
            }

            if (col == maxCol - 1 && status)
            {
                int id    = 1;
                int value = data[row + 1][col];
                if (temp->mLeft == 0)
                {
                    vector<int> vec    = {data[row][col - 1], data[row + 1][col]};
                    auto        minmax = minmax_element(vec.begin(), vec.end());
                    id    = (str.compare("min") == 0) ? minmax.first - vec.begin() : minmax.second - vec.begin();
                    value = (str.compare("min") == 0) ? *minmax.first : *minmax.second;
                }

                switch (id)
                {
                    case (0):
                        temp->mLeft = new Node(row,
                                               col - 1,
                                               value,
                                               nullptr,
                                               new Node(temp->mRow, temp->mCol, temp->mData),
                                               nullptr,
                                               nullptr,
                                               direction);
                        row         = temp->mLeft->mRow;
                        col         = temp->mLeft->mCol;
                        q.push(temp->mLeft);
                        break;
                    case (1):
                        temp->mDown = new Node(row + 1,
                                               col,
                                               value,
                                               nullptr,
                                               nullptr,
                                               nullptr,
                                               new Node(temp->mRow, temp->mCol, temp->mData),
                                               direction);
                        row         = temp->mDown->mRow;
                        col         = temp->mDown->mCol;
                        q.push(temp->mDown);
                        break;
                }
            }
            status = true;
        }
    }
    return node;
}

bool Node::extractPath(Node* node, vector<array<int, 3>>& paths)
{
    if (node == nullptr)
    {
        paths = {};
        return false;
    }
    else
    {
        queue<Node*> q;
        q.push(node);
        paths.push_back({node->mRow, node->mCol, node->mData});
        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            if (temp->mLeft != nullptr && (temp->mLeft->mID > 0))
            {
                paths.push_back({temp->mLeft->mRow, temp->mLeft->mCol, temp->mLeft->mData});
                q.push(temp->mLeft);
            }
            if (temp->mRight != nullptr && (temp->mRight->mID > 0))
            {
                paths.push_back({temp->mRight->mRow, temp->mRight->mCol, temp->mRight->mData});
                q.push(temp->mRight);
            }
            if (temp->mDown != nullptr && (temp->mDown->mID > 0))
            {
                paths.push_back({temp->mDown->mRow, temp->mDown->mCol, temp->mDown->mData});
                q.push(temp->mDown);
            }
        }
    }
    return true;
}

} // namespace MinMaxCostPathTravase