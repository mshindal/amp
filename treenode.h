#ifndef TREENODE_H
#define TREENODE_H
#include <QVariant>
#include <QList>
#define DEFAULT_METADATA_TEXT "Unknown"

class TreeNode
{
public:
    TreeNode();
    QString path = DEFAULT_METADATA_TEXT;
    QVariant title = DEFAULT_METADATA_TEXT;
    QVariant artist = DEFAULT_METADATA_TEXT;
    QVariant album = DEFAULT_METADATA_TEXT;
    QVariant track = DEFAULT_METADATA_TEXT;
    QVariant year = DEFAULT_METADATA_TEXT;
    TreeNode* parent = nullptr;
    QList<TreeNode*> children;
};

#endif // TREENODE_H
