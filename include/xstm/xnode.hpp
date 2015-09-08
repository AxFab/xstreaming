
#ifndef _AX_DATA_XNODE_HPP 
#define _AX_DATA_XNODE_HPP 1
#include "axkit.hpp"

namespace axkit {


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

class XAttribute;
class XAttributeMap;
class XCData;
class XComment;
class XDeclaration;
class XDocument;
class XElement;
class XEnumerator;
class XNode;
class XObject;
class XReader;
class XWriter;
class XText;




__abstract class XObject 
{
protected:
  XNodeType nodeType_;
  XDocument* document_;
  XElement* parent_;

public:
  /// Initializes a new instance of XObject class.
  XObject(XNodeType type);
  /// Destructor
  virtual ~XObject() {}
  /// Returns the indented XML for this object.
  virtual cstr toString() const = 0;
  /// Writes this node to a stream.
  virtual void writeTo(const XWriter& stream) const = 0;

public:
  /// Gets the node type for this node.
  XNodeType nodeType() const { return nodeType_; }
  /// Gets the next sibling node of this node.
  XDocument* document() const { return document_; }
  /// Gets the parent element of this object.
  XElement* parent() const { return parent_; }
  /// Converts this object to a string representation.
  
protected:
  /// Sets the parent element of this object.
  void setParent(XElement* parent);
  virtual void setDocument(XDocument* doc);

public:
  static cstr FormatAttName(cstr value);
  static cstr FormatAttText(cstr value);
  static cstr FormatName(cstr value);
  static cstr FormatText(cstr value);
};

class XAttribute : public XObject
{
// Attribute are part of element. An element handle the hierarchie of its attributes.
friend class XElement;

protected:
  NString name_;
  NString value_;
  XAttribute* next_;
  XAttribute* previous_;

public:
  /// Initializes a new instance of the XAttribute class by copy.
  XAttribute(const XAttribute& attribut);
  /// Initializes a new instance of the XAttribute class from the 
  /// specified name and value.
  XAttribute(cstr name, cstr value = NULL);
  /// Removes this attribute from its parent element.
  XAttribute* remove();
  /// Returns the indented XML for this object.
  virtual cstr toString() const;
  /// Writes this node to a stream.
  virtual void writeTo(const XWriter& stream) const;

public:
  /// Gets the next attribute of the parent element.
  XAttribute* next() const { return next_; }
  /// Gets the previous attribute of the parent element.
  XAttribute* previous() const { return previous_; }
  /// Gets the value of this attribute.
  cstr name() const { return name_.c_str(); }
  /// Gets the value of this attribute.
  cstr value() const { return value_.c_str(); }
  /// Sets the value of this attribute.
  void setValue(cstr value) { value_ = XObject::FormatAttText(value); }
};

__abstract class XNode : public XObject
{
// XContainer are part of XNode. An container is the one handling the hierarchie.
friend class XContainer;

protected:
  XNode* nextNode_;
  XNode* previousNode_;

public:
  /// Constructor
  XNode(XNodeType type);
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
  /// Returns a filtered collection of the sibling elements after this node, in document order.
  XEnumerator elementsAfterSelf(cstr name = NULL) const;
  /// Returns a filtered collection of the sibling elements before this node, in document order.
  XEnumerator elementsBeforeSelf(cstr name = NULL) const;
  /// Determines if the current node appears after a specified node in terms of document order.
  bool isAfter(const XNode& node) const;
  /// Determines if the current node appears before a specified node in terms of document order.
  bool isBefore(const XNode& node) const;
  /// Returns a collection of the sibling nodes after this node, in document order.
  XEnumerator nodesAfterSelf() const;
  /// Returns a collection of the sibling nodes before this node, in document order.
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
  /// Compares the values of two nodes, including the values of all descendant nodes.
  static bool DeepEquals(const XNode& na, const XNode& nb);
  /// Create a XNode form a stream.
  static XNode* ReadFrom(const XReader& stream);
};

class XText : public XNode 
{
protected:
  NString value_;

public:
  /// Initializes a new instance of XText class.
  XText(cstr string);
  /// Returns the indented XML for this object.
  virtual cstr toString() const;
  /// Writes this node to a stream.
  virtual void writeTo(const XWriter& stream) const;

public:
  /// Gets the value of this node.
  cstr value() const { return value_.c_str(); }
  /// Sets the value of this node.
  void setValue(cstr value) { value_ = XObject::FormatText(value); }
};

class XCData : public XNode
{
private:
  NString value_;

public:
  /// Initializes a new instance of XText class.
  XCData(cstr string);
  /// Returns the indented XML for this object.
  virtual cstr toString() const;
  /// Writes this node to a stream.
  virtual void writeTo(const XWriter& stream) const;

public:
  /// Gets the value of this node.
  cstr value() const { return value_.c_str(); }
  /// Sets the value of this node.
  void setValue(cstr value) { value_ = value; }
};

class XComment : public XNode
{
private:
  NString value_;

public:
  /// Initializes a new instance of XComment class.
  XComment(cstr string);
  /// Returns the indented XML for this object.
  virtual cstr toString() const;
  /// Writes this node to a stream.
  virtual void writeTo(const XWriter& stream) const;

public:
  /// Gets the value of this node.
  cstr value() const { return value_.c_str(); }
  /// Sets the value of this node.
  void setValue(cstr value) { value_ = value; }
};

/// Represents a node that can contain other nodes.
__abstract class XContainer : public XNode
{
// Container is part of the inode, just all the node can't be container so they are split
friend class XNode; 
protected:
  XNode* firstNode_;
  XNode* lastNode_;
public:
  /// Constructor
  XContainer(XNodeType type);
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
  // TODO CreateWriter
  /// Returns a collection of the descendant nodes for this document or element, in document order.
  XEnumerator descendantNodes();
  /// Returns a collection of the descendant elements for this document or element, in document order.
  XEnumerator descendants(cstr name);
  /// Gets the first child element with the specified name.
  XElement* element(cstr name);
  /// Returns a filtered collection of the child elements of this element or document.
  XEnumerator elements(cstr name);
  /// Returns a collection of the child nodes of this element or document, in document order.
  XEnumerator nodes();
  /// Removes the child nodes from this document or element.
  void removeNodes();
  /// Replaces the children nodes of this document or element with the specified content.
  void replaceNodes(XNode* node);
  /// Replaces the children nodes of this document or element with the specified content.
  void replaceNodes(cstr content);
  
  /// Get the first child node of this node.
  XNode* firstNode() const { return firstNode_; }
  /// Get the last child node of this node.
  XNode* lastNode() const { return lastNode_; }

protected:
  virtual void setDocument(XDocument* doc);
};

class XAttributeMap : public NMap<XAttribute>
{
public:
  virtual ~XAttributeMap();
  static XAttributeMap* Parse(cstr string);
  cstr string(cstr name) const;
};

class XElement : public XContainer
{
private:
  NString name_;
  XAttributeMap *attributes_;

public:
  XElement(cstr name, XAttributeMap *map);
  virtual ~XElement();
  
  /// Returns the indented XML for this object.
  virtual cstr toString() const;
  /// Writes this node to a stream.
  virtual void writeTo(const XWriter& stream) const;

  NString attributeString(cstr name) const
  {
    return attributes_->string(name);
  }

  bool attributeBool(cstr name, bool& value) const
  {
    NString str = attributes_->string(name);
    return false;
  }
  
  NString name() { return name_; }
};

class XName
{
private:
  NString name_;
  NString prefix_;
  NString namespace_;
public:
  operator NString() 
  { 
    NString str = NString::Empty;
    str += NString(namespace_) + NString(name_);
    return str;
  }
};

class XDeclaration : public XObject
{
private:
  NString encoding_;
  NString standalone_;
  NString version_;
public:
  XDeclaration(cstr version = NULL, cstr encoding = NULL, cstr standalone = NULL);
  /// Returns the indented XML for this object.
  virtual cstr toString() const;
  /// Writes this node to a stream.
  virtual void writeTo(const XWriter& stream) const;
  
  cstr encoding() const { return encoding_.c_str(); }
  cstr standalone() const { return standalone_.c_str(); }
  cstr version() const { return version_.c_str(); }

  void setEncoding(cstr encoding);
  void setStandalone(cstr standalone);
  void setVersion(cstr version);
};

class XEnumerator 
{
};

class XDocument : public XContainer
{
private:
public:
  XDocument();
  /// Returns the indented XML for this object.
  virtual cstr toString() const;
  /// Writes this node to a stream.
  virtual void writeTo(const XWriter& stream) const;
};

class XNullParamException 
{
public:
  XNullParamException(cstr param) {}
  static void Throw(cstr param) { throw new XNullParamException(param); }
};


class XNotImplementedException
{
public:
  static void Throw() { throw new XNotImplementedException(); }
};

} // namespace axkit

/// Sets the parent element of this object.
inline void axkit::XObject::setParent(XElement* parent)
{ 
  parent_ = parent; 
  setDocument(parent->document_);
}

/// Sets the parent element of this object.
inline void axkit::XObject::setDocument(XDocument* doc)
{
  document_ = doc;
}

#endif /* _AX_DATA_XNODE_HPP */
