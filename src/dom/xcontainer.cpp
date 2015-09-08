#include "xstm/xnode.hpp"
using namespace axkit;

/// Constructor
XContainer::XContainer(XNodeType type)
  : XNode(type)
{
  firstNode_ = NULL;
  lastNode_ = NULL;
}

XContainer::~XContainer() 
{
  XNode *node = firstNode_;
  while (node) {
    firstNode_ = node->nextNode_;
    delete node;
    node = firstNode_;
  }
}

/// Adds the specified content as children of this XContainer.
void XContainer::add(XNode* node)
{
  node->previousNode_ = this->lastNode_;
  node->nextNode_ = NULL;

  if (this->lastNode_)
    this->lastNode_->nextNode_ = node;
  else
    this->firstNode_ = node;
  
  this->lastNode_ = node;
  if (this->nodeType_ == XNODE_ELEMENT)
    node->parent_ = static_cast<XElement*>(this);
  else {
    node->parent_ = NULL;
    node->setDocument(static_cast<XDocument*>(this));
  }

}

/// Adds a new XText content as children of this XContainer.
void XContainer::add(cstr content)
{
  add(new XText(content));
}

/// Adds the specified content as the first children of this XContainer.
void XContainer::addFirst(XNode* node)
{
  node->previousNode_ = NULL;
  node->nextNode_ = this->lastNode_;

  if (this->firstNode_)
    this->firstNode_->previousNode_ = node;
  else
    this->lastNode_ = node;
  
  this->lastNode_ = node;
}

/// Adds a new XText content as the first children of this XContainer.
void XContainer::addFirst(cstr content)
{
  add(new XText(content));
}

/// Returns a collection of the descendant nodes for this document or element, in document order.
XEnumerator XContainer::descendantNodes()
{
  throw new XNotImplementedException();
}

/// Returns a collection of the descendant elements for this document or element, in document order.
XEnumerator XContainer::descendants(cstr name)
{
  throw new XNotImplementedException();
}

/// Gets the first child element with the specified name.
XElement* XContainer::element(cstr name)
{
  throw new XNotImplementedException();
}

/// Returns a filtered collection of the child elements of this element or document.
XEnumerator XContainer::elements(cstr name)
{
  throw new XNotImplementedException();
}

/// Returns a collection of the child nodes of this element or document, in document order.
XEnumerator XContainer::nodes()
{
  throw new XNotImplementedException();
}

/// Removes the child nodes from this document or element.
void XContainer::removeNodes()
{
  XNode* iter;
  XNode* node = this->firstNode_;
  while (node) {
    iter = node ->nextNode_;
    delete node;
    node = iter;
  }

  this->firstNode_ = NULL;
  this->lastNode_ = NULL;
}

/// Replaces the children nodes of this document or element with the specified content.
void XContainer::replaceNodes(XNode* node)
{
  throw new XNotImplementedException();
}

/// Replaces the children nodes of this document or element with the specified content.
void XContainer::replaceNodes(cstr content)
{
  throw new XNotImplementedException();
}

void XContainer::setDocument(XDocument* doc)
{
  XObject::setDocument(doc);
  for (XNode* node = this->firstNode_; node; node = node->nextNode_)
    node->setDocument(doc);
}

