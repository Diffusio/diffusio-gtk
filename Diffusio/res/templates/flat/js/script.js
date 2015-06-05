/*
 * Diffusio - Build presentation websites easily
 * https://github.com/diffusio
 * http://diffusio.co
 * 
 * Copyright (C) 2015 
 * 
 * Pierre JACQUIER  
 * http://pierre-jacquier.com
 * 
 * Grégoire DUVAUCHELLE
 * https://github.com/kalterkrieg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


Array.prototype.shuffle = function() {
  var i = this.length, j, temp;
  if ( i == 0 ) return this;
  while ( --i ) {
     j = Math.floor( Math.random() * ( i + 1 ) );
     temp = this[i];
     this[i] = this[j];
     this[j] = temp;
  }
}
var map;
var address = document.getElementById("map_legend_address").innerHTML;
var geocoder;
var mapOptions = {
  zoom: 15,
  mapTypeId: google.maps.MapTypeId.ROADMAP
}

initialize();
update();
document.body.scrollTop = 5;
document.body.scrollTop = 0;
var marker;
var last_scroll_pos = 0; 
var dS;
var b_wth, b_hgt;
var news = document.getElementsByClassName('news');
var news_l = news.length;
var y=document.getElementById('cover').style.top;
var colors = ["#F44336","#E91E63","#9C27B0","#673AB7","#3F51B5","#2196F3","#009688","#4CAF50","#FF5722","#795548","#607D8B"];
colors.shuffle();
var j=0;
for(var i=0;i<news_l;i++)
{
    news[i].style.background = colors[j];
    if(i>9)
        news[i].style.display = 'none';
    if(j>9)
        j = 0;
    else 
        j++;
}

document.getElementById('news_to_display').max = news_l;
update();
function setDisplayedNews()
{
    var max_news = document.getElementById('news_to_display').value;
    for(var i=max_news;i<news_l;i++)
    {
        news[i].style.display = 'none';
    }
    for(var i=0;i<max_news;i++)
    {
        news[i].style.display = 'inline-block';
    }
}

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

      }
    });
}


function getViewport() {
 // the more standards compliant browsers (mozilla/netscape/opera/IE7) use window.innerWidth and window.innerHeight
 if (typeof window.innerWidth != 'undefined') {
   b_wth = window.innerWidth,
   b_hgt = window.innerHeight
 }

// IE6 in standards compliant mode (i.e. with a valid doctype as the first line in the document)
 else if (typeof document.documentElement != 'undefined'
 && typeof document.documentElement.clientWidth !=
 'undefined' && document.documentElement.clientWidth != 0) {
    b_wth = document.documentElement.clientWidth,
    b_hgt = document.documentElement.clientHeight
 }

 // older versions of IE
 else {
   b_wth = document.getElementsByTagName('body')[0].clientWidth,
   b_hgt = document.getElementsByTagName('body')[0].clientHeight
 }
 return [b_wth, b_hgt];
}


function openCircleNews(id)
{
    smoothScrollTo(document.getElementById('content_2').offsetTop);
    var i;
    for(i=0;i<news_l;i++)
        if(news[i].id != ('news_' + id))
            news[i].style.transform = 'translateX(-' + document.getElementById('wrapper').offsetWidth + 'px)';
        else
        {
          news[i].style.transform = 'translateY(-' + (news[i].offsetTop ) + 'px)';
            news[i].style.width = '80%';
            news[i].getElementsByClassName('news_content')[0].style.display = 'block';
            news[i].getElementsByClassName('read_more')[0].innerHTML = "CLOSE";
            news[i].getElementsByClassName('read_more')[0].style.color = 'white';
            news[i].getElementsByClassName('read_more')[0].onmousedown = function() {closeCircleNews(id)};
        }
}

function closeCircleNews(id)
{
    var news = document.getElementsByClassName('news');
    var news_l = news.length;
    var i;
    for(i=0;i<news_l;i++)
        if(news[i].id != ('news_' + id))
            news[i].style.transform = 'translateX(0px)';
        else
        {
          news[i].style.transform = 'translateY(0px)';
            news[i].style.width = '300';
            news[i].getElementsByClassName('news_content')[0].style.display = 'none';
            news[i].getElementsByClassName('read_more')[0].innerHTML = "READ MORE";
            news[i].getElementsByClassName('read_more')[0].onmousedown = function() {openCircleNews(id)};
        }
    smoothScrollTo(document.getElementById('content_2').offsetTop);
}

function update()  
{
        var icons = document.getElementsByClassName('tab_img');
        var tabs = document.getElementsByClassName('sub_tab');
        document.getElementById('map_canvas').style.height = 0.6*b_hgt;
        document.getElementById('cover').style.height = 0.6*b_hgt;
        document.getElementById('header').style.height = 0.4*b_hgt;
        document.getElementById('header').style.top = 0.6*b_hgt;
        if(b_wth < 700)
        {
            document.getElementById('cover').style.height = 0.7*b_hgt;
            document.getElementById('header').style.height = 0.3*b_hgt;
            document.getElementById('header').style.top = 0.7*b_hgt;
        }
        document.getElementById('content_1').style.top = 0.6*b_hgt;
        document.getElementById('content_2').style.top = 0.6*b_hgt;
        document.getElementById('content_3').style.top = 0.6*b_hgt;
        getViewport();
        dS = (document.body.scrollTop - last_scroll_pos) * 0.2;
        y=document.getElementById('cover').style.top;
        y = parseInt(y);
        y -= dS;
        document.getElementById('cover').style.top = y;
        document.getElementById('cover').style.top -= parseInt(dS);
    if(document.body.scrollTop >= document.getElementById("content_1").offsetTop - 110 && document.body.scrollTop <= ( document.getElementById("content_2").offsetTop - document.getElementById('header_1').offsetHeight ))
    {
        document.getElementById('header_1').style.display = "block";
    }
    else
    {
        document.getElementById('header_1').style.display = "none";
    }
     if(document.body.scrollTop >= document.getElementById("content_1").offsetTop - 110)
        document.getElementById('h1_tabs').style.display = "block";
    else
        document.getElementById('h1_tabs').style.display = "none";
    if(document.body.scrollTop >= document.getElementById('content_2').offsetTop && document.body.scrollTop >= document.getElementById('content_2').offsetTop)
        document.getElementById('header_2').style.position = 'fixed';
    else
        document.getElementById('header_2').style.position = 'absolute';
    if(document.body.scrollTop > document.getElementById('content_2').offsetTop + document.getElementById('content_2').offsetHeight)
        document.getElementById('header_3').style.position = 'fixed';
    else
        document.getElementById('header_3').style.position = 'absolute';
    last_scroll_pos = document.body.scrollTop;
}

function scrollToTop()
{
    document.body.scrollTop = 0;
    last_scroll_pos = 0;
    document.getElementById('cover').style.top=0;   
}

function animation(effectFrame, duration, from, to, easing, framespacing) {
    var start = Date.now(),
        change = to - from;
    duration = duration || 1000;
    if(typeof from === 'function') {
        easing = from;
        from = 0;
    }
    easing = easing || function(x, t, b, c, d) { return c*t/d+b; };
    from = from || 0;
    to = to || 1;
    framespacing = framespacing || 1;
    
    (function interval() {
        var time = (Date.now() - start);
         if(time < duration) {
            effectFrame(easing(0, time, from, change, duration));
             scrolling = true;
            window.setTimeout(interval, framespacing );
        } else {
            effectFrame(to);
            scrolling = false;
        }
    }());
}
           

window.smoothScrollTo = function (target, duration) {
    var start = window.pageYOffset;        
    duration = duration || 500;
    
    animation(function(position) { window.scroll(0,position); }, duration, start, target);
    
};

function openMapDropdown()
{
    document.getElementById("dropdown_map").style.transition = "max-height 5s, max-width 5s, opacity 0.3s"
    document.getElementById("drop_item_1").style.transition = "font-size 0.3s";
    document.getElementById("drop_item_2").style.transition = "font-size 0.3s";
    document.getElementById("drop_item_3").style.transition = "font-size 0.3s";
    document.getElementById("dropdown_map").style.opacity = 1;
    document.getElementById("drop_item_1").style.fontSize = "15px";
    document.getElementById("drop_item_2").style.fontSize = "15px";
    document.getElementById("drop_item_3").style.fontSize = "15px";
    document.getElementById("dropdown_map").style.maxWidth = "9999px";
    document.getElementById("dropdown_map").style.maxHeight = "9999px";
}

function closeMapDropdown()
{
    document.getElementById("dropdown_map").style.transition = "max-height 0.3s, max-width 0.3s, opacity 0.3s"
    document.getElementById("drop_item_1").style.transition = "font-size 0.3s";
    document.getElementById("drop_item_2").style.transition = "font-size 0.3s";
    document.getElementById("drop_item_3").style.transition = "font-size 0.3s";
    document.getElementById("dropdown_map").style.opacity = 0;
    document.getElementById("drop_item_1").style.fontSize = "0em";
    document.getElementById("drop_item_2").style.fontSize = "0em";
    document.getElementById("drop_item_3").style.fontSize = "0em";
    document.getElementById("dropdown_map").style.maxWidth = "0px";
    document.getElementById("dropdown_map").style.maxHeight = "0px";
}
