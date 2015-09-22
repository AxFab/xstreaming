/*
  This file is part of the XStreaming library
  Copyright (c) 2015 Fabien Bavent

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*/
#include "xstm/xelement.hpp"
#include "xstm/xexception.hpp"
#include "xstm/xtext.hpp"

namespace xstm {


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//      XNode
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/// Constructor
XNode::XNode(XNodeType type)
  : XObject(type)
{
  nextNode_ = NULL;
  previousNode_ = NULL;
}


/// Destructor
XNode::~XNode()
{
}


/// Adds the specified content immediately after this node.
void XNode::addAfterSelf(XNode* node)
{
  if (node == NULL)
    throw XNullParamException("node");

  node->parent_ = parent_;
  node->previousNode_ = this;
  node->nextNode_ = this->nextNode_;
  if (this->nextNode_ != NULL)
    this->nextNode_->previousNode_ = node;
  else
    this->parent_->lastNode_ = node;
  this->nextNode_ = node;
}


/// Adds a new XText content immediately after this node.
void XNode::addAfterSelf(cstr string)
{
  this->addAfterSelf(new XText(string));
}


/// Adds the specified content immediately before this node.
void XNode::addBeforeSelf(XNode* node)
{
  if (node == NULL)
    throw XNullParamException("node");

  node->parent_ = parent_;
  node->previousNode_ = this->previousNode_;
  node->nextNode_ = this;
  if (this->previousNode_ != NULL)
    this->previousNode_->nextNode_ = node;
  else
    this->parent_->firstNode_ = node;
  this->previousNode_ = node;
}


/// Adds a new XText content immediately before this node.
void XNode::addBeforeSelf(cstr string)
{
  this->addBeforeSelf(new XText(string));
}


/// Returns a collection of the ancestor elements of this node.
/// If name is specified, the collection is filtered.
XEnumerator XNode::ancestors(cstr name) const
{
  throw new XNotImplementedException();
}


/// Returns a filtered collection of the sibling elements after this node,
/// in document order.
XEnumerator XNode::elementsAfterSelf(cstr name) const
{
  throw new XNotImplementedException();
}


/// Returns a filtered collection of the sibling elements before this node,
/// in document order.
XEnumerator XNode::elementsBeforeSelf(cstr name) const
{
  throw new XNotImplementedException();
}


/// Determines if the current node appears after a specified node in terms
/// of document order.
bool XNode::isAfter(const XNode& node) const
{
  throw new XNotImplementedException();
}


/// Determines if the current node appears before a specified node in terms
/// of document order.
bool XNode::isBefore(const XNode& node) const
{
  throw new XNotImplementedException();
}


/// Returns a collection of the sibling nodes after this node, in document
/// order.
XEnumerator XNode::nodesAfterSelf() const
{
  throw new XNotImplementedException();
}


/// Returns a collection of the sibling nodes before this node, in document
/// order.
XEnumerator XNode::nodesBeforeSelf() const
{
  throw new XNotImplementedException();
}


/// Removes this node from its parent.
void XNode::remove()
{
  if (this->nextNode_ != NULL)
    this->nextNode_->previousNode_ = this->previousNode_;

  if (this->previousNode_ != NULL)
    this->previousNode_->nextNode_ = this->nextNode_;

  if (parent_ && parent_->firstNode_ == this)
    parent_->firstNode_ = this->nextNode_;

  if (parent_ && parent_->lastNode_ == this)
    parent_->lastNode_ = this->previousNode_;

  this->previousNode_ = NULL;
  this->nextNode_ = NULL;
  this->parent_ = NULL;
}


/// Replaces this node with the specified content.
void XNode::replaceWith(XNode* node)
{
  if (this->nextNode_ != NULL) {
    this->nextNode_->previousNode_ = node;
    node->nextNode_ = node;
  }

  if (this->nextNode_ != NULL) {
    this->previousNode_->nextNode_ = node;
    node->previousNode_ = node;
  }

  if (parent_ && parent_->firstNode_ == this)
    parent_->firstNode_ = node;

  if (parent_ && parent_->lastNode_ == this)
    parent_->lastNode_ = node;

  node->parent_ = parent_;
}


/// Replaces this node with a new XText content.
void XNode::replaceWith(cstr string)
{
  this->replaceWith(new XText(string));
}


/// Compares the values of two nodes, including the values of all descendant
/// nodes.
bool XNode::DeepEquals(const XNode& na, const XNode& nb)
{
  throw new XNotImplementedException();
}

}  // namespace xstm

