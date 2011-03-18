#ifndef _XMLNODE_
#define _XMLNODE_

class XMLTag;
//#include "XMLVisitor.h"

typedef enum {
	NODE_XMLTAG, NODE_XMLPCDATA
} NODE_TYPE;

class XMLNode {
	private:
		bool visited;
	protected:
		NODE_TYPE type;
		int depth;
		XMLTag* parent;
	public:
		void set_parent(XMLTag* parent);
		NODE_TYPE get_type();
		int get_depth();
		void set_depth(int depth);
		//virtual void accept(XMLVisitor* v);
		bool get_visited();
		void set_visited(bool visited);
};

#endif
