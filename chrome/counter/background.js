chrome.app.runtime.onLaunched.addListener
(
  function()
  {
    chrome.app.window.create
    (
      'main.html',
      {
        'outerBounds':
        {
          'width': 240,
          'height': 120
        }
      }
    );
  }
);
