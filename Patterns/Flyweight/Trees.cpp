// ===========================================================================
// Trees.cpp // Flyweight Pattern
// ===========================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <memory>

namespace TreesFlyweight {

    class Tree
    {
    private:
        std::string m_style;
        int m_height;

    public:
        // c'tor(s)
        Tree(std::string style) : m_style{ style }, m_height{ 6 } {}

        // getter
        std::string getStyle() { return m_style; }
        int getHeight() { return m_height; }
    };

    class TreePosition
    {
    private:
        int m_x;
        int m_y;

    public:
        TreePosition(int x, int y) : m_x{ x }, m_y{ y } {}

        // getter
        int getX() { return m_x; }
        int getY() { return m_y; }

        // setter
        void setX(int x) { m_x = x; }
        void setY(int y) { m_y = y; }
    };

    class TreeFactory
    {
    private:
        std::unordered_map<std::string, std::weak_ptr<Tree>> m_treeMap;

    public:
        TreeFactory() {};

        std::shared_ptr<Tree> getTree(std::string style)
        {
            // palm, cypress, garden
            if (!(style.compare("palm") == 0 || style.compare("cypress") == 0 || style.compare("garden") == 0))
            {
                return nullptr;
            }

            if (m_treeMap.find(style) != m_treeMap.end())
            {
                std::cout << "     --> Tree with style " << style << " already in Factory Cache!" << std::endl;

                std::shared_ptr<Tree> tp = m_treeMap[style].lock();

                return tp;
            }

            std::cout << "     ==> Creating new tree with style " << style << std::endl;

            std::shared_ptr<Tree> tree{ std::make_shared<Tree>(style) };

            m_treeMap[style] = tree;
            
            return tree;
        }
    };

    class Game
    {
    private:
        TreeFactory m_treeFactory;

    public:
        Game() {};

        void addTree(int x, int y, std::string style)
        {
            std::shared_ptr<Tree> tree{ m_treeFactory.getTree(style) };

            if (tree == nullptr) {
                return;
            }

            std::shared_ptr<TreePosition> position { 
                std::make_shared<TreePosition>(x, y) 
            };

            renderTree(tree, position);
        }

    private:
        void renderTree(std::shared_ptr<Tree>& tree, std::shared_ptr<TreePosition>& position)
        {
            int x{ position->getX() };
            int y{ position->getY() };

            std::string style{ tree->getStyle() };

            std::cout
                << "Tree with " << style << " style"
                << " rendered at " << x << ", " << y << std::endl;
        }
    };
}

void test_trees_game()
{
    using namespace TreesFlyweight;

    // using palm, cypress and garden styles
    Game game{};
    game.addTree(1, 3, "palm");
    game.addTree(2, 5, "cypress");
    game.addTree(4, 8, "palm");
    game.addTree(4, 9, "cypress");
    game.addTree(5, 3, "garden");
}


// ===========================================================================
// End-of-File
// ===========================================================================
