javascript:

  function removePlugins(node)
  {
    if
    (
      node.nodeType == 1 &&
      (
        node.tagName.toLowerCase() == 'applet' ||
        node.tagName.toLowerCase() == 'embed' ||
        node.tagName.toLowerCase() == 'iframe' ||
        node.tagName.toLowerCase() == 'object'
      )
    )
    {
      var parent = node.parentNode;
      var box = document.createElement('div');
      box.style.overflow = 'hidden';
      box.style.width = document.defaultView.getComputedStyle(node, '').getPropertyValue('width');
      box.style.height = document.defaultView.getComputedStyle(node, '').getPropertyValue('height');
      box.style.border = '1px solid black';
      parent.insertBefore(box, node);
      parent.removeChild(node);
    }
    else if(node.childNodes != null)
      for(var i = 0; i < node.childNodes.length; i++)
        removePlugins(node.childNodes[i]);
  }

  removePlugins(document.body);
