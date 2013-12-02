
#include <iostream>
#include <queue>

int main()
{
    std::queue<int> x;

    x.push(1);
    x.push(2);
    x.push(3);

    std::cout << x.front() << std::endl;
    std::cout << x.size() << std::endl;
    x.pop();
    std::cout << x.front() << std::endl;
    std::cout << x.size() << std::endl;
    x.pop();
    std::cout << x.front() << std::endl;
    std::cout << x.size() << std::endl;
    x.pop();
    
    std::cout << x.front() << std::endl;

    return 0;
}
