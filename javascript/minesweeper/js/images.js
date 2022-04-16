function imagesClass()
{
  this.data =
  [
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAI0lEQVQoz2NsaGhgIAWwMDAwODg4EK+BiYFEMKphVMOAaQAA8qgCYuGct0oAAAAASUVORK5CYII=',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAUElEQVQoz2NsaGhgIAWwMDAwODg4EK+BiYFEgFODg4O9g4M9sRqwKsWpAY9qLBrwq8ai4cCBgwcOHKRLKFFNAwt+T0O4yL6i2Ab8QUQXTwMAvzQQozmm/soAAAAASUVORK5CYII=',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAWUlEQVQoz6VRyQ3AMAijlQfzaIzGaPlVUYDIqPwQvoDH3W1SMDOSOuG1YWFvGLVVMAqHDn2McNfLKihx6g5djF0Ld2h2hg49CV0GaYd8nE/ix6fFs44dxoQFb64ddIR/xVkAAAAASUVORK5CYII=',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAU0lEQVQoz2NsaGhgIAWwMDAwODg4EK+BiYFEwAJn2eO25+CBA6TZgGwWC1Zj8FhLgR/wmEqyHwjYgGwexDZ7Bwe4IG3igeRQQnYkgXigQloiWQMAMqAXbrRR3JAAAAAASUVORK5CYII=',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAASklEQVQoz2NsaGhgIAWwMDAwODg4EK+BiYFEwILGd3A4AGEcOOCAzCbfBiZcxlPND0yYxkPYaFxqhBKmu2kQSnSJaWSANTZo7yQALJIW6Nsy7xkAAAAASUVORK5CYII=',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAATUlEQVQoz2NsaGhgIAWwMDAwODg4EK+BiYFEwAJnHcBrj8OBAxTbgGkYtf2AxzPIdhJlA7IRLPidjmkbzeKBNBuQXctCZPCT7weSNQAALn8TLuGpSPAAAAAASUVORK5CYII=',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAU0lEQVQoz2NsaGhgIAWwMDAwODg4EK+BiYFEwILMcThwAKuiA0hOYCKoGp8NmOZR2w+43IbdD3gAshEE/IBpG238gN0GPKGJLMVCfAyQ6QeSNQAAhXsVrhPr2eoAAAAASUVORK5CYII=',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAS0lEQVQoz2NsaGhgIAWwMDAwODg4EK+BiYFEwAJn4bfnwIEDFNsANwMZYFpLsg34NMCNR7acejZgNZ56NuAynrJ4wBqvVEhLJGsAADCEE6hnSRL0AAAAAElFTkSuQmCC',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAX0lEQVQoz2NsaGhgIAWwMDAwODg4EK+BiYFEwILMOXDgAFZFyE5gIqgaTYoFv3mYplDgBwcHB4h5mKZi9wPJNsANxvTDgQMH4IKUxQPB8EWxAU8CQZZiwSVBtbREsgYAkkkfrrxX2l4AAAAASUVORK5CYII=',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAOUlEQVQoz2P8//8/A9Hg4MGDTCSpPnDgAAucQ1DDgQMHGBgYSLABAkY1jBQNLPBURawNJKlmYGAAABNOF3BNCy13AAAAAElFTkSuQmCC',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAZUlEQVQoz5WSUQ7AIAxC0XgvOTo9mftosizTqPhVLS8UtYwxcL0iolpqSe3dHAFJANYOnezkstVm6d6nWuo/EJIHJLPH1qFDKhbgOZAkmcXhWmdFnuiTyh6pzY9/BvJX3Ya21AAebFIrt52peTUAAAAASUVORK5CYII=',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAYElEQVQoz62SUQrAIAxDk+G9583fvjaEVmfZ/BChTdoXdO9dldMknRXNMSu4Ktia4PuOj1xAtokl1hMAYMZTZmjRw/YsNB4Byyg1YHyLlTf7JCWybkfo0Ykg5revscNzAQ6hFyc1Mq88AAAAAElFTkSuQmCC',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAZ0lEQVQoz6WR0Q0AIQhDgThYR2O0bsb9mUsAI5EvI2ltn+ruMpklIgDuBdYtOheT4Vh2BZAPtYBkTgKA5OmFiIiIrs+4w8oeqtpBI7l2+vOH7BpvWP80uns7ECxZq7uX0Uvxc4ebPh/uuDAiURO0egAAAABJRU5ErkJggg==',
    'iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAIAAACQkWg2AAAAlElEQVQoz5VR2xEEIQgLN/a1lGZp2cq4D5RVdJ07vhhIeCRSa8U/UQCo6u+Ez1vjbUojXKrXcU8AGuEmveqzdU687pjnpJGTZkc3/yAAAAPMDD2P+v7p1hPZopusSRPxJTPaASQbgeTZEG5/WO+2s3EkR3RwYnwmuIKyaDBqXVa92b/09O42T8Yld1KMnpaxtJUlAb5VRUgnD//x0AAAAABJRU5ErkJggg==',
    'iVBORw0KGgoAAAANSUhEUgAAAA8AAAAPCAIAAAC0tAIdAAAAAXNSR0IArs4c6QAAAEJJREFUKM9jbGhoYCAOODg4MBGv1N7enol4pQwMDCzIQrhUQ5QyMDAQ65JR1dRRzYIWW4TNJlIpAwMDw4EDB/4TDQASjjXndY/JIwAAAABJRU5ErkJggg=='
  ];
  this.image = new Array();
  for(var i = 0; i < this.data.length; i++)
  {
    this.image[i] = new Image()
    this.image[i].src = 'data:image/png;base64,'+this.data[i];
  }
  this.frameIndex = this.data.length-1;
  this.frameGrids = 5;

  this.isLoaded = function()
  {
    for(var i = 0; i < this.data.length; i++)
      if
      (
        this.image[i].complete == false ||
        (this.image[i].naturalWidth != undefined && this.image[i].naturalWidth == 0)
      )
        return false;
    return true;
  };

  this.getFieldSize = function()
  {
    return this.image[0].naturalWidth;
  };

  this.getFrameSize = function()
  {
    return this.image[this.frameIndex].naturalWidth/this.frameGrids;
  };

  this.getFrameGrids = function()
  {
    return this.frameGrids;
  };

  this.getImage = function(i)
  {
    return this.image[i];
  };

  this.getFrame = function()
  {
    return this.image[this.frameIndex];
  };

  this.whenLoad = function(finish)
  {
    if(this.isLoaded() == true)
      finish();
    else
      setTimeout
      (
        (
          function(self)
          {
            return function()
            {
              self.whenLoad(finish);
            }
          }
        )(this),
        100
      );
  };
}
