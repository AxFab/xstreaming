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
#ifndef _XSTM_XCONTAINER_HPP
#define _XSTM_XCONTAINER_HPP 1
#include "xstm/xobject.hpp"

#include "xnode.hpp"

namespace xstm {


/// Represents a node that can contain other nodes.
__abstract class XContainer : public XNode
{
// Container is part of the inode, just all the node can't be container so
// they are split
friend class XNode;
protected:
  XNode* firstNode_;
  XNode* lastNode_;
public:
  /// Constructor
  explicit XContainer(XNodeType type);
  /// Destructor
  virtual ~XContainer();
  /// Adds the specified content as children of this XContainer.
  void add(XNode* node);
  /// Adds a new XText content as children of this XContainer.
  void add(cstr content);
  /// Adds the specified content as the first children of this XContainer.
  void addFirst(XNode* node);
  /// Adds a new XText content as the first children of this XContainer.
  void addFirst(cstr content);
  // TODO(axfab) CreateWriter
  /// Returns a collection of the descendant nodes for this document or
  /// element, in document order.
  XEnumerator descendantNodes();
  /// Returns a collection of the descendant elements for this document or
  /// element, in document order.
  XEnumerator descendants(cstr name);
  /// Gets the first child element with the specified name.
  XElement* element(cstr name);
  /// Returns a filtered collection of the child elements of this element or
  /// document.
  XEnumerator elements(cstr name);
  /// Returns a collection of the child nodes of this element or document, in
  /// document order.
  XEnumerator nodes();
  /// Removes the child nodes from this document or element.
  void removeNodes();
  /// Replaces the children nodes of this document or element with the
  /// specified content.
  void replaceNodes(XNode* node);
  /// Replaces the children nodes of this document or element with the
  /// specified content.
  void replaceNodes(cstr content);

  /// Get the first child node of this node.
  XNode* firstNode() const { return firstNode_; }
  /// Get the last child node of this node.
  XNode* lastNode() const { return lastNode_; }

protected:
  virtual void setDocument(XDocument* doc);
};

}  // namespace xstm

#endif /* _XSTM_XCONTAINER_HPP */

