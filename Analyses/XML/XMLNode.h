#ifndef _XMLNODE_
#define _XMLNODE_

#include <string>

class XMLTag;
class XMLVisitor;

typedef enum {
    NONE, NODE_XMLTAG, NODE_XMLPCDATA
} NODE_TYPE;

class XMLNode {
    public:
        XMLNode(NODE_TYPE type);
        void setParent(XMLTag* parent);
        XMLTag* getParent();
        NODE_TYPE getType();
        int getDepth();
        void setDepth(int depth);
        bool getVisited();
        void setVisited(bool visited);
        std::string getName();
        virtual bool accept(XMLVisitor* v) = 0;
    protected:
        NODE_TYPE type;
        int depth;
        XMLTag* parent;
    private:
        bool visited;
};

#endif
