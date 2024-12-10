#include <iostream>
#include <unordered_map>
#include <vector>

int main()
{
    std::unordered_map<int, int> map;
    int list_size, target;
    std::vector<std::pair<int, int>> result;

    std::cout << "Enter the size of the list: ";
    std::cin >> list_size;

    int list[list_size];
    std::cout << "Enter the elements of the list: ";

    for (int i = 0; i < list_size; i++)
    {
        std::cin >> list[i];
    }

    std::cout << "Enter the target sum: ";
    std::cin >> target;

    for (int i = 0; i < list_size; i++)
    {
        int diff = target - list[i];
        if (map.find(diff) != map.end() && map.find(list[i]) == map.end())
        {
            result.push_back(std::make_pair(map[diff], diff));
        }
        map[list[i]] = diff;
    }

    if (result.size() == 0)
    {
        std::cout << "No pairs found\n";
    }
    else
    {
        std::cout << std::endl;
        std::cout << "The pairs are: ";
        for (auto i : result)
        {
            std::cout << "(" << i.first << ", " << i.second << ") ";
        }
        std::cout << "\n";
    }

    return 0;
}