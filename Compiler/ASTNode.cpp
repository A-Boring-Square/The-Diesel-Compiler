#include "ASTNode.hpp"

ASTNode::ASTNode(const std::string& type, const std::string& value)
    : type(type), value(value) {}

void ASTNode::AddChild(ASTNode* child) {
    children.push_back(child);
}

const std::vector<ASTNode*>& ASTNode::GetChildren() const {
    return children;
}

const std::string& ASTNode::GetType() const {
    return type;
}

const std::string& ASTNode::GetValue() const {
    return value;
}
