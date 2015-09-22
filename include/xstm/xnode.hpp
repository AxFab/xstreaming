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
#ifndef _AX_DATA_XNODE_HPP
#define _AX_DATA_XNODE_HPP 1
#include <nkit/collections.hpp>
#include <nkit/encoding.hpp>
#include "xstm/xobject.hpp"


namespace xstm {

class XContainer;
class XEnumerator;


__abstract class XNode : public XObject
{
// XContainer are part of XNode. An container is the one handling the
// hierarchie.
friend class XContainer;

protected:
  XNode* nextNode_;
  XNode* previousNode_;

public:
  /// Constructor
  explicit XNode(XNodeType type);
  /// Destructor
  virtual ~XNode();
  /// Adds the specified content immediately after this node.
  void addAfterSelf(XNode* node);
  /// Adds a new XText content immediately after this node.
  void addAfterSelf(cstr string);
  /// Adds the specified content immediately before this node.
  void addBeforeSelf(XNode* node);
  /// Adds a new XText content immediately before this node.
  void addBeforeSelf(cstr string);
  /// Returns a collection of the ancestor elements of this node.
  /// If name is specified, the collection is filtered.
  XEnumerator ancestors(cstr name = NULL) const;
  /// Returns a filtered collection of the sibling elements after this node,
  /// in document order.
  XEnumerator elementsAfterSelf(cstr name = NULL) const;
  /// Returns a filtered collection of the sibling elements before this node,
  /// in document order.
  XEnumerator elementsBeforeSelf(cstr name = NULL) const;
  /// Determines if the current node appears after a specified node in terms
  /// of document order.
  bool isAfter(const XNode& node) const;
  /// Determines if the current node appears before a specified node in terms
  /// of document order.
  bool isBefore(const XNode& node) const;
  /// Returns a collection of the sibling nodes after this node, in document
  /// order.
  XEnumerator nodesAfterSelf() const;
  /// Returns a collection of the sibling nodes before this node, in document
  /// order.
  XEnumerator nodesBeforeSelf() const;
  /// Removes this node from its parent.
  void remove();
  /// Replaces this node with the specified content.
  void replaceWith(XNode* node);
  /// Replaces this node with a new XText content.
  void replaceWith(cstr string);

public:
  /// Gets the next sibling node of this node.
  XNode* nextNode() const { return nextNode_; }
  /// Gets the previous sibling node of this node.
  XNode* previousNode() const { return previousNode_; }

public:
  /// Compares the values of two nodes, including the values of all
  /// descendant nodes.
  static bool DeepEquals(const XNode& na, const XNode& nb);
  /// Create a XNode form a stream.
  // static XNode* ReadFrom(const XReader& stream);
};



}  // namespace xstm


#endif /* _AX_DATA_XNODE_HPP */
