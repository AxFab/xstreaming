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
#ifndef _XSTM_XOBJECT_HPP
#define _XSTM_XOBJECT_HPP 1
#include <nkit/string.hpp>

#ifndef __abstract
/// Add a macro (often empty) to signal an abstract class
# define __abstract
#endif

namespace xstm {

class XDocument;
class XElement;


/// Indicate the type of an XObject or XNode type.
enum XNodeType
{
  XNODE_UNDEF = 0,
  XNODE_ELEMENT = 1,
  XNODE_ATTRIBUTE = 2,
  XNODE_TEXT = 3,
  XNODE_CDATA_SECTION = 4,
  XNODE_ENTITY_REFERENCE = 5,
  XNODE_ENTITY = 6,
  XNODE_PROCESSING_INSTRUCTION = 7,
  XNODE_COMMENT = 8,
  XNODE_DOCUMENT = 9,
  XNODE_DOCUMENT_TYPE = 10,
  XNODE_DOCUMENT_FRAGMENT = 11,
  XNODE_NOTATION = 12
};


/// This abstract object define the base of all items related
/// to XML node tree.
__abstract class XObject
{
public:  // Constructors & Public Methods
  /// Initializes a new instance of XObject class.
  explicit XObject(XNodeType type);
  /// Destructor declared as virtual
  virtual ~XObject() {}
  /// Returns the indented XML for this object.
  virtual cstr toString() const = 0;

public:  // Public Accessors
  /// Gets the node type for this node/object.
  XNodeType nodeType() const { return nodeType_; }
  /// Gets the next sibling node of this object.
  XDocument* document() const { return document_; }
  /// Gets the parent element of this object.
  XElement* parent() const { return parent_; }
  /// Converts this object to a string representation.

public:  // Public Static Methods
  static cstr FormatAttName(cstr value);
  static cstr FormatAttText(cstr value);
  static cstr FormatName(cstr value);
  static cstr FormatText(cstr value);

protected:  // Protected Accessors
  /// Sets the parent element of this object.
  void setParent(XElement* parent);
  /// Sets the document of this object.
  virtual void setDocument(XDocument* doc);

protected:  // Protected Data-Members
  XNodeType nodeType_;
  XDocument* document_;
  XElement* parent_;
};


class XEnumerator
{
};


}  // namespace xstm

#endif /* _XSTM_XOBJECT_HPP */
