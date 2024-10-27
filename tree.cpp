#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <memory>
#include <iostream> 

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

struct KDNode {
    Point point;
    std::unique_ptr<KDNode> left, right;
    KDNode(const Point& p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
private:
    std::unique_ptr<KDNode> root;
    
    // Helper function to build tree recursively
    std::unique_ptr<KDNode> buildTree(std::vector<Point>& points, int depth, int start, int end) {
        if (start >= end) return nullptr;
        if (start + 1 == end) {
            return std::make_unique<KDNode>(points[start]);
        }
        
        int axis = depth % 2;  // 0 for x, 1 for y
        int mid = start + (end - start) / 2;  // Changed to avoid potential overflow
        
        // Sort based on current axis
        if (axis == 0) {
            std::nth_element(points.begin() + start, points.begin() + mid,
                           points.begin() + end,
                           [](const Point& a, const Point& b) { return a.x < b.x; });
        } else {
            std::nth_element(points.begin() + start, points.begin() + mid,
                           points.begin() + end,
                           [](const Point& a, const Point& b) { return a.y < b.y; });
        }
        
        auto node = std::make_unique<KDNode>(points[mid]);
        node->left = buildTree(points, depth + 1, start, mid);
        node->right = buildTree(points, depth + 1, mid + 1, end);
        return node;
    }
    
    // Helper function for nearest neighbor search
    void findNearestHelper(const KDNode* node, const Point& target, Point& nearest, 
                          double& minDist, int depth) const {
        if (!node) return;
        
        double dist = distance(node->point, target);
        if (dist < minDist) {
            minDist = dist;
            nearest = node->point;
        }
        
        int axis = depth % 2;
        double axisDist = (axis == 0) ? target.x - node->point.x : target.y - node->point.y;
        
        // Determine which subtree to search first
        std::unique_ptr<KDNode>* firstSide = axisDist <= 0 ? &const_cast<KDNode*>(node)->left : &const_cast<KDNode*>(node)->right;
        std::unique_ptr<KDNode>* secondSide = axisDist <= 0 ? &const_cast<KDNode*>(node)->right : &const_cast<KDNode*>(node)->left;
        
        findNearestHelper(firstSide->get(), target, nearest, minDist, depth + 1);
        
        // Only check the other side if it could contain a closer point
        if (axisDist * axisDist < minDist) {
            findNearestHelper(secondSide->get(), target, nearest, minDist, depth + 1);
        }
    }
    
    double distance(const Point& a, const Point& b) const {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return dx * dx + dy * dy;  // Using squared distance to avoid sqrt
    }
    
public:
    KDTree(std::vector<Point>& points) {
        if (points.empty()) {
            root = nullptr;
            return;
        }
        root = buildTree(points, 0, 0, points.size());
    }
    
    Point findNearest(const Point& target) const {
        if (!root) {
            return Point(0, 0); // Or throw an exception
        }
        Point nearest;
        double minDist = std::numeric_limits<double>::max();
        findNearestHelper(root.get(), target, nearest, minDist, 0);
        return nearest;
    }
};

int main() {
    std::vector<Point> points = {
        {2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}
    };
    
    KDTree tree(points);
    Point target(6, 5);
    Point nearest = tree.findNearest(target);
    
    std::cout << "Nearest point to (" << target.x << ", " << target.y 
            << ") is (" << nearest.x << ", " << nearest.y << ")\n";
    
    return 0;
}