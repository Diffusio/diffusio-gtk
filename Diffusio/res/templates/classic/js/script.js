//Variables
var map;
var address = document.getElementById("map_legend_address").innerHTML;
var geocoder;
var marker;
            
//Initialisation
document.getElementById("open_link").href = "https://www.google.fr/maps/search/" + address.replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+");
document.getElementById("open_link_1").href = "https://www.google.fr/maps/search/" + address.replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+");
document.getElementById("open_link_2").href = "https://www.here.com/search/" + address.replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+");

if((""+window.location+"").indexOf("#") == -1 && (""+window.location+"").indexOf("#more") == -1 && (""+window.location+"").indexOf("#news") == -1 && (""+window.location+"").indexOf("#presentation") == -1)
    window.location += "#presentation";
var index = (""+window.location+"").indexOf("#");
var root;
if(index != -1)
    root = (""+window.location+"").substring(0,index);
else
    root = (""+window.location+"")
if((""+window.location+"") == root + "#presentation")
    setVisibleNotVisibleNotVisible(1,2,3);
if((""+window.location+"") == root + "#news")
    setVisibleNotVisibleNotVisible(2,3,1)
if((""+window.location+"") == root + "#more")
    setVisibleNotVisibleNotVisible(3,2,1)
var mapOptions = {
  zoom: 15,
  mapTypeId: google.maps.MapTypeId.ROADMAP
}
initialize();
            
//Functions
function initialize() {
    geocoder = new google.maps.Geocoder();
    map = new google.maps.Map(document.getElementById('map_canvas'), mapOptions);
    codeAddress();
}

function codeAddress() {
    geocoder.geocode( { 'address': address}, function(results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        map.setCenter(results[0].geometry.location);
        if(marker)
          marker.setMap(null);
        marker = new google.maps.Marker({
            map: map,
            position: results[0].geometry.location,
            draggable: true
        });

      } else {
        alert('Geocode was not successful for the following reason: ' + status);
      }
    });
}

function openCircleNews(id)
{
    document.getElementById('news_' + id).getElementsByClassName('news_summary')[0].style.display = "none";
    document.getElementById('news_content_' + id).style.display = "block";
    document.getElementById('news_' + id).getElementsByClassName('read_more')[0].innerHTML = "CLOSE";
    document.getElementById('news_' + id).getElementsByClassName('read_more')[0].onmousedown = function () { closeCircleNews(id); };
    document.body.scrollTop = document.getElementById('news_' + id).offsetTop - 10;
}

function closeCircleNews(id)
{
    document.getElementById('news_' + id).getElementsByClassName('news_summary')[0].style.display = "block";
    document.getElementById('news_content_' + id).style.display = "none";
    document.getElementById('news_' + id).getElementsByClassName('read_more')[0].innerHTML = "READ MORE";
    document.getElementById('news_' + id).getElementsByClassName('read_more')[0].onmousedown = function () { openCircleNews(id); };
}

function setVisibleNotVisibleNotVisible(visible, not_visible1, not_visible2)
{

    document.getElementById('tab_' + visible).className = "selectedTab";
    document.getElementById('tab_' + not_visible1).className = " unselectedTab";
    document.getElementById('tab_' + not_visible2).className = "unselectedTab ";
    document.getElementById('content_' + visible).className = "content visible";
    document.getElementById('content_' + not_visible1).className = "content notVisible";
    document.getElementById('content_' + not_visible2).className = "content notVisible ";
    switch(visible)
    {
        case 1:
                window.location = root + "#presentation";
                break;
        case 2:    
                window.location = root + "#news"
                break;
        case 3:     
                window.location = root + "#more"
                break;
    }
}