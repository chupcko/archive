var queryID = undefined;
var submitID = undefined;
var statusID = undefined;
var searchID = undefined;
var viewID = undefined;
var httpRequest = undefined;
var inSend = undefined;

function getHttpRequest()
{
  var httpRequest;
  if(window.XMLHttpRequest !== undefined)
    httpRequest = new XMLHttpRequest();
  else
    httpRequest = new ActiveXObject('Microsoft.XMLHTTP');
  if(httpRequest.overrideMimeType !== undefined)
    httpRequest.overrideMimeType('text/xml');
  return httpRequest;
}

function statusSet(text)
{
  statusID.innerHTML = text;
}

function statusClear()
{
  statusID.innerHTML = '&nbsp;';
}

function onLoad()
{
  queryID = document.getElementById('query');
  submitID = document.getElementById('submit');
  statusID = document.getElementById('status');
  searchID = document.getElementById('search');
  viewID = document.getElementById('view');
  queryID.value = '';
  queryID.focus();
  statusClear();
  searchHide();
  viewHide();
  httpRequest = getHttpRequest();
  inSend = false;
}

function doneSearch()
{
  try
  {
    if(httpRequest.readyState == 4)
    {
      if(this.httpRequest.status == 200)
      {
        statusSet('Done');
        searchFill(httpRequest.responseXML);
      }
      else
        statusSet('Bad URL');
      httpRequest.abort();
      inSend = false;
    }
  }
  catch(error)
  {
    statusSet('Error in communication "'+error+'"');
    httpRequest.abort();
    inSend = false;
  }
}

function submitSearch()
{
  if(inSend !== true)
  {
    viewHide();
    statusSet('Search ...');
    inSend = true;
    httpRequest.onreadystatechange = function(){doneSearch()};
    httpRequest.open('GET', 'rr/?rr_request=ep/search&query='+queryID.value, true);
    httpRequest.setRequestHeader('If-Modified-Since', new Date(0));
    httpRequest.send(null);
  }
  else
    statusSet('Wait ...');
  return false;
}

function searchHide()
{
  searchID.style.display = 'none';
}

function searchShow()
{
  searchID.style.display = 'block';
}

function searchFill(xml)
{
  var xmlResult = xml.getElementsByTagName('result')[0];
  if(xmlResult.getAttribute('code') != 0)
  {
    statusSet(xmlResult.getAttribute('text'));
    searchHide();
    return;
  }
  var result = '';
  var xmlEmoticons = xml.getElementsByTagName('emoticons')[0];
  if(parseInt(xmlEmoticons.getAttribute('count')) == 0)
  {
    statusSet('No data');
    searchHide();
    return;
  }
  var result = '<div class="center">';
  var xmlEmoticon = xmlEmoticons.getElementsByTagName('emoticon');
  var tdNumber = 0;
  for(var i = 0; i < xmlEmoticon.length; i++)
  {
    if(tdNumber != 0 && tdNumber%5 == 0)
      result += '<br/>';
    result += '<div class="searchItem"><div class="searchEmoticon">'+escapeHTML(xmlEmoticon[i].firstChild.nodeValue)+'</div><a href="" onclick="return submitView('+xmlEmoticon[i].getAttribute('id')+');" class="searchView">View</a></div>';
    tdNumber++;
  }
  result += '</div>';
  searchID.innerHTML = result;
  searchShow();
}

function viewHide()
{
  viewID.style.display = 'none';
}

function viewShow()
{
  viewID.style.display = 'block';
}

function doneView()
{
  try
  {
    if(httpRequest.readyState == 4)
    {
      if(this.httpRequest.status == 200)
      {
        statusSet('Done');
        viewFill(httpRequest.responseXML);
      }
      else
        statusSet('Bad URL');
      httpRequest.abort();
      inSend = false;
    }
  }
  catch(error)
  {
    statusSet('Error in communication "'+error+'"');
    httpRequest.abort();
    inSend = false;
  }
}

function submitView(id)
{
  if(inSend !== true)
  {
    viewHide();
    statusSet('Get ...');
    inSend = true;
    httpRequest.onreadystatechange = function(){doneView()};
    httpRequest.open('GET', 'rr/?rr_request=ep/emoticon/view&id='+id, true);
    httpRequest.setRequestHeader('If-Modified-Since', new Date(0));
    httpRequest.send(null);
  }
  else
    statusSet('Wait ...');
  return false;
}

function keyPressSearch(event)
{
  var keyCode;
  if(event.which !== undefined)
    keyCode = event.which;
  else
    keyCode = event.keyCode;
  switch(keyCode)
  {
    case 8:
      queryID.value = queryID.value.substring(0, queryID.value.length-1)
      break;
    case 0:
    case 9:
      submit.focus();
      return false;
    default:
      queryID.value += String.fromCharCode(keyCode);
  }
  if(queryID.value != '')
    submitSearch();
  else
  {
    searchHide();
    statusClear();
  }
  return false;
}

function viewFill(xml)
{
  var xmlResult = xml.getElementsByTagName('result')[0];
  if(xmlResult.getAttribute('code') != 0)
  {
    statusSet(xmlResult.getAttribute('text'));
    return;
  }
  var result = '';
  var xmlEmoticon = xml.getElementsByTagName('emoticon')[0];
  var emoticon = xmlEmoticon.getAttribute('emoticon');
  var xmlDescriptions = xmlEmoticon.getElementsByTagName('descriptions')[0];
  if(parseInt(xmlDescriptions.getAttribute('count')) == 0)
  {
    statusSet('No data');
    return;
  }
  var result = '<div class="searchItem"><div class="searchEmoticon">'+escapeHTML(emoticon)+'</div><a href="" onclick="return viewBack();" class="searchView">Back</a></div><ul>';
  var xmlDescription = xmlEmoticon.getElementsByTagName('description');
  for(var i = 0; i < xmlDescription.length; i++)
    result += '<li>'+escapeHTML(xmlDescription[i].firstChild.nodeValue)+'</li>';
  result += '</ul>';
  viewID.innerHTML = result;
  searchHide();
  viewShow();
}

function viewBack()
{
  viewHide();
  searchShow();
  return false;
}

function escapeHTML(text)
{
  return text.replace(/&/g, '&amp;').replace(/"/g, '&quot').replace(/</g, '&lt;').replace(/>/g, '&gt;');
}