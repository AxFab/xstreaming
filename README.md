# XStreaming

XStreaming is a library use to parse and build xml files. Instead of using 
the common W3C standard this library provide a C++ implementation of the .NET
package `System.Xml.Linq`.

Also this library provide a way of loading Xml files as a stream. The 
`XReader` provide a read method capable to return xml objects as they come 
before the DOM is entirely build. This way parsed nodes can be freed to 
minimize memory consumption at no cost.

## Usage 

### Simple usage

```c++
XElement* root = XElement::Load("MyFile");
std::cout << "Load document XML : " << root.name() << std::endl;
// Note that ownership of XObject is always handle by the XDocument.
// You should not destroy this element directly;
delete root->document();
```

### Stream usage

```c++
class MyCatalogReader {
  XReader *reader_;
  MyCatalog *build_;
  explicit MyCatalogReader(XReader *reader)
  {
    reader_ = reader;
  }

  ~MyCatalogReader() 
  {
    reader_->dispose(); // Clean the underlying XDocument and close.
    delete reader_;
  }

  MyCatalog *readCatalog() 
  {
    XNode* current = reader_->read();
    if (current->nodeType() != XNODE_ELEMENT)
      return NULL;
    XElement* ndRoot = reinterpret_cast<XElement*>(current);
    if (ndSchema->name() != "catalog")
      return NULL;
    build_ = new MyCatalog(ndRoot->attributeString("name"));

    if (reader_->didClose())
      return build_; // The document contains only the '<catalog />' element

    for (;;) {
      XNode *node = reader_->read();
      // When we get the same element, it's means we close it!
      if (node == current) {
        reader_->dispose();
        return build_;
      }

      if (node->nodeType() != XNODE_ELEMENT)
        continue;

      XElement* ndChild = reinterpret_cast<XElement*>(node);
      if (ndChild->name() == "book") {
        build->add(new Book(ndChild->attributeString("name")))
        node->removeNodes(); // We limit memory consumtion this way!
      } else if (ndChild->name() == "album") {
        build->add(new Album(ndChild->attributeString("name")))
        node->removeNodes(); // We limit memory consumtion this way!
      } 
      // We ignore other tags, we could also add warning for unknown element!
    }
  }

  static MyCatalog *Read(cstr url)
  {
    XReader* read = new XReader(url);
    MyCatalogReader libReader(read);
    MyCatalog *catalog = libReader.readCatalog;
  }
}
```


## Internal design

### Resource objects (like `XReader`)

  Resource instance have a function named `close` hover they still respect 
  RAII (Resource Acquisition Is Initialization), as the destructor will 
  call the close automaticaly.

  However some factory class will provide a second method named `dipsose`.
  Such class usally have a resource that can be freed using close but also 
  create/instantiate some data. That are not release by a regular close and 
  as such won't be desallocate by the destructor.

  To desallocate all you need to use the dispose function.
  The principe here is that you get the choice of who gonna be te owner of 
  the new object. Often you want the factory to allocate your object and 
  then grab the ownership. But some other time the objects created are just 
  temporary, in this case the ownership should be keeped by the factory 
  class, But you will need to manually called the dispose methods.


