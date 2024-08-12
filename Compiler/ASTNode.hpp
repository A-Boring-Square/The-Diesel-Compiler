#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <string>
#include <vector>

class ASTNode {
public:
    ASTNode(const std::string& type, const std::string& value);

    void AddChild(ASTNode* child);
    const std::vector<ASTNode*>& GetChildren() const;
    const std::string& GetType() const;
    const std::string& GetValue() const;

private:
    std::string type;
    std::string value;
    std::vector<ASTNode*> children;
};

#endif // ASTNODE_HPP
