#ifndef _XMLNODE_
#define _XMLNODE_

class XMLTag;
class XMLVisitor;

typedef enum {
    NONE, NODE_XMLTAG, NODE_XMLPCDATA
} NODE_TYPE;

class XMLNode {
    public:
        XMLNode(NODE_TYPE type);
        void set_parent(XMLTag* parent);
        XMLTag* get_parent();
        NODE_TYPE get_type();
        int get_depth();
        void set_depth(int depth);
        bool get_visited();
        void set_visited(bool visited);
        virtual void accept(XMLVisitor* v) = 0;
    protected:
        NODE_TYPE type;
        int depth;
        XMLTag* parent;
    private:
        bool visited;
};

#endif
